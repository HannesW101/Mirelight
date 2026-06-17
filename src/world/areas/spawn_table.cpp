// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/spawn_table.hpp"

#include "module-utils/include/logger.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <utility>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::utils;

// ============================================================================
// Class Spawn_table_loader
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Spawn_table_loader::Spawn_table_loader(
    std::string data_dir
    )
    : _data_dir(std::move(data_dir))
{}

// ----------------------------------------------------------------------------
std::string Spawn_table_loader::_path_for(
    Area_id const& area
    ) const {

    if (area.kind == Area_id::Kind::CHUNK) {

        return _data_dir + "/world/" + std::to_string(area.chunk_x) + "_" + std::to_string(area.chunk_y) + ".spawns.json";
    }

    return _data_dir + "/areas/" + area.interior_name + "/spawns.json";
}

// ----------------------------------------------------------------------------
Spawn_table Spawn_table_loader::load(
    Area_id const& area
    ) const {

    Spawn_table table;
    table.area = area;

    std::ifstream file(_path_for(area));
    if (!file.is_open()) { return table; } // no authored objects for this area

    nlohmann::json root;
    try {

        file >> root;
    } catch (std::exception const& e) {

        LOG(Log_lvl::ERR) << std::string("Spawn_table_loader: parse error: ") + e.what();
        return table;
    }

    if (!root.contains("objects") || !root["objects"].is_array()) { return table; }

    for (auto const& entry : root["objects"]) {

        Spawn_entry e;
        e.spawn_id        = entry.value("spawn_id", std::string{});
        e.type            = entry.value("type", std::string{});
        e.local_x         = entry.value("local_x", 0.0f);
        e.local_y         = entry.value("local_y", 0.0f);
        e.footprint_w     = entry.value("footprint_w", 1.0f);
        e.footprint_h     = entry.value("footprint_h", 1.0f);
        e.variant         = entry.value("variant", std::string{});
        e.respawn_seconds = entry.value("respawn_seconds", 0.0);

        if (e.spawn_id.empty() || e.type.empty()) { continue; }

        table.objects.push_back(std::move(e));
    }

    return table;
}

} // namespace mirelight
