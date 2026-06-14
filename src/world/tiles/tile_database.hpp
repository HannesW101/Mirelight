#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/tiles/tile.hpp"

#include <string>
#include <unordered_map>
#include <vector>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Tile_database
// ----------------------------------------------------------------------------

class Tile_database {

public:
    bool load(std::string const& path);

    Tile_def const& by_id(Tile_id id) const;

    Tile_id id_of(std::string const& name) const;

    std::size_t count() const;

private:
    std::vector<Tile_def>                    _defs;
    std::unordered_map<std::string, Tile_id> _by_name;
    Tile_def                                 _empty;
};

} // namespace mirelight
