// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/area_state.hpp"

#include "module-utils/include/logger.hpp"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::utils;

// ============================================================================
// Class Area_state_store
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Area_runtime_state& Area_state_store::get_or_create(
    Area_id const& area
    ) {

    auto it = _areas.find(area);
    if (it != _areas.end()) { return it->second; }

    Area_runtime_state fresh;
    fresh.area = area;
    return _areas.emplace(area, std::move(fresh)).first->second;
}

// ----------------------------------------------------------------------------
void Area_state_store::mark_destroyed(
    Area_id const& area,
    std::string const& spawn_id,
    double world_time
    ) {

    Area_runtime_state& state = get_or_create(area);
    Object_state& obj = state.deviations[spawn_id];
    obj.spawn_id = spawn_id;
    obj.destroyed = true;
    obj.destroyed_at_world_time = world_time;
}

// ----------------------------------------------------------------------------
bool Area_state_store::is_destroyed_and_unexpired(
    Area_id const& area,
    std::string const& spawn_id,
    double world_time,
    double respawn_seconds
    ) const {

    auto area_it = _areas.find(area);
    if (area_it == _areas.end()) { return false; }

    auto obj_it = area_it->second.deviations.find(spawn_id);
    if (obj_it == area_it->second.deviations.end() || !obj_it->second.destroyed) { return false; }

    if (respawn_seconds <= 0.0) { return true; } // never respawns

    double const elapsed = world_time - obj_it->second.destroyed_at_world_time;
    return elapsed < respawn_seconds;
}

// ----------------------------------------------------------------------------
std::string Area_state_store::_path_for(
    Area_id const& area,
    std::string const& save_dir
    ) const {

    return save_dir + "/" + area.to_key() + ".state.json";
}

// ----------------------------------------------------------------------------
void Area_state_store::save_area(
    Area_id const& area,
    std::string const& save_dir
    ) const {

    auto it = _areas.find(area);
    if (it == _areas.end() || it->second.deviations.empty()) { return; } // pristine: no file

    nlohmann::json root;
    root["area"]["kind"] = (area.kind == Area_id::Kind::CHUNK) ? "chunk" : "interior";
    if (area.kind == Area_id::Kind::CHUNK) {

        root["area"]["x"] = area.chunk_x;
        root["area"]["y"] = area.chunk_y;
    } else {

        root["area"]["name"] = area.interior_name;
    }

    auto& devs = root["deviations"] = nlohmann::json::array();
    for (auto const& [id, obj] : it->second.deviations) {

        nlohmann::json e;
        e["spawn_id"]    = obj.spawn_id;
        e["destroyed"]   = obj.destroyed;
        e["destroyed_at"] = obj.destroyed_at_world_time;
        devs.push_back(std::move(e));
    }

    std::filesystem::path const path(_path_for(area, save_dir));
    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);

    std::ofstream file(path);
    if (!file.is_open()) {

        LOG(Log_lvl::ERR) << "Area_state_store: cannot write " + path.string();
        return;
    }

    file << root.dump(2);
}

// ----------------------------------------------------------------------------
void Area_state_store::load_area(
    Area_id const& area,
    std::string const& save_dir
    ) {

    std::ifstream file(_path_for(area, save_dir));
    if (!file.is_open()) { return; } // pristine area, no save file yet

    nlohmann::json root;
    try {

        file >> root;
    } catch (std::exception const& e) {

        LOG(Log_lvl::ERR) << std::string("Area_state_store: parse error: ") + e.what();
        return;
    }

    if (!root.contains("deviations") || !root["deviations"].is_array()) { return; }

    Area_runtime_state& state = get_or_create(area);
    for (auto const& entry : root["deviations"]) {

        Object_state obj;
        obj.spawn_id = entry.value("spawn_id", std::string{});
        obj.destroyed = entry.value("destroyed", false);
        obj.destroyed_at_world_time = entry.value("destroyed_at", 0.0);

        if (obj.spawn_id.empty()) { continue; }
        state.deviations[obj.spawn_id] = std::move(obj);
    }
}

// ----------------------------------------------------------------------------
void Area_state_store::save_all(
    std::string const& save_dir
    ) const {

    for (auto const& [id, state] : _areas) { save_area(id, save_dir); }
}

// ----------------------------------------------------------------------------
void Area_state_store::forget_area(
    Area_id const& area
    ) {

    _areas.erase(area);
}

} // namespace mirelight
