#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/area_id.hpp"

#include <string>
#include <unordered_map>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Structs
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
struct Object_state {

    std::string spawn_id;
    bool        destroyed = false;
    double      destroyed_at_world_time = 0.0; // seconds, Game_session::world_time()
};

// ----------------------------------------------------------------------------
struct Area_runtime_state {

    Area_id area;
    std::unordered_map<std::string, Object_state> deviations;
};

// ============================================================================
// Class Area_state_store
// ----------------------------------------------------------------------------

class Area_state_store {

public:
    Area_runtime_state& get_or_create(Area_id const& area);

    void mark_destroyed(Area_id const& area, std::string const& spawn_id, double world_time);

    bool is_destroyed_and_unexpired(
        Area_id const& area,
        std::string const& spawn_id,
        double world_time,
        double respawn_seconds
        ) const;

    void save_area(Area_id const& area, std::string const& save_dir) const;
    void load_area(Area_id const& area, std::string const& save_dir);

    void save_all(std::string const& save_dir) const;

    void forget_area(Area_id const& area);

private:
    std::unordered_map<Area_id, Area_runtime_state, Area_id_hash> _areas;

    std::string _path_for(Area_id const& area, std::string const& save_dir) const;
};

} // namespace mirelight
