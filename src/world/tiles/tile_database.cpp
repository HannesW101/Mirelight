// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/tiles/tile_database.hpp"

#include "module-utils/include/logger.hpp"

#include <nlohmann/json.hpp>

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
// Class Tile_database
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
bool Tile_database::load(
    std::string const& path
    ) {

    std::ifstream file(path);
    if (!file.is_open()) {

        LOG(Log_lvl::ERR) << "Tile_database: cannot open " + path;
        return false;
    }

    nlohmann::json root;
    try {

        file >> root;
    } catch (std::exception const& e) {

        LOG(Log_lvl::ERR) << std::string("Tile_database: parse error: ") + e.what();
        return false;
    }

    _defs.clear();
    _by_name.clear();

    // Ensure id 0 is the reserved "empty" tile
    _empty = Tile_def{ 0, "empty", "", false, 0, 0 };
    _defs.push_back(_empty);

    if (!root.contains("tiles") || !root["tiles"].is_array()) {

        LOG(Log_lvl::ERR) << "Tile_database: missing 'tiles' array";
        return false;
    }

    for (auto const& entry : root["tiles"]) {

        Tile_def def;
        def.id       = static_cast<Tile_id>(entry.value("id", 0));
        def.name     = entry.value("name", std::string{});
        def.texture  = entry.value("texture", std::string{});
        def.walkable = entry.value("walkable", true);
        def.atlas_x  = entry.value("atlas_x", 0);
        def.atlas_y  = entry.value("atlas_y", 0);

        if (def.id == 0) { continue; } // 0 reserved

        if (_defs.size() <= def.id) { _defs.resize(static_cast<std::size_t>(def.id) + 1u, _empty); }
        _defs[def.id] = def;
        _by_name[def.name] = def.id;
    }

    LOG(Log_lvl::INFO) << "Tile_database: loaded " + std::to_string(_by_name.size()) + " tiles";
    return true;
}

// ----------------------------------------------------------------------------
Tile_def const& Tile_database::by_id(
    Tile_id id
    ) const {

    if (id < _defs.size()) { return _defs[id]; }
    return _empty;
}

// ----------------------------------------------------------------------------
Tile_id Tile_database::id_of(
    std::string const& name
    ) const {

    auto it = _by_name.find(name);
    return it != _by_name.end() ? it->second : Tile_id{ 0 };
}

// ----------------------------------------------------------------------------
std::size_t Tile_database::count() const {

    return _by_name.size();
}

} // namespace mirelight
