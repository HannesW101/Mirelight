#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/area_id.hpp"

#include <string>
#include <vector>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Structs
// ----------------------------------------------------------------------------

struct Spawn_entry {

    std::string spawn_id; // stable, author assigned identity
    std::string type; // looked up in Object_factory ("tree", "rock", ...)
    float       local_x = 0.0f; // tile units, relative to area origin, not grid snapped
    float       local_y = 0.0f;
    float       footprint_w = 1.0f; // tile units the rendered object spans
    float       footprint_h = 1.0f;
    std::string variant; // which texture/look within the type
    double      respawn_seconds = 0.0; // 0 = never respawns once destroyed
};

// ----------------------------------------------------------------------------
struct Spawn_table {

    Area_id area;
    std::vector<Spawn_entry> objects;
};

// ============================================================================
// Class Spawn_table_loader
// ----------------------------------------------------------------------------

class Spawn_table_loader {

public:
    explicit Spawn_table_loader(std::string data_dir);

    Spawn_table load(Area_id const& area) const;

private:
    std::string _data_dir;

    std::string _path_for(Area_id const& area) const;
};

} // namespace mirelight
