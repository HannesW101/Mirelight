#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/area_id.hpp"
#include "world/areas/spawn_table.hpp"
#include "world/areas/object_factory.hpp"

#include "SFML/System/Vector2.hpp"

#include <cstdint>
#include <unordered_map>
#include <vector>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::game { class World; }

namespace mirelight { class Area_state_store; class Game_session; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Object_spawner
// ----------------------------------------------------------------------------

class Object_spawner {

public:
    Object_spawner(
        Spawn_table_loader loader,
        Object_factory const& factory,
        Area_state_store& store,
        Game_session const& session
        );

    void spawn_area(Area_id const& area, sf::Vector2f area_origin_world, titan::game::World& world);

    void unload_area(Area_id const& area, titan::game::World& world);

private:
    Spawn_table_loader      _loader;
    Object_factory const&   _factory;
    Area_state_store&       _store;
    Game_session const&     _session;

    std::unordered_map<Area_id, Spawn_table, Area_id_hash> _table_cache;
    std::unordered_map<Area_id, std::vector<std::uint64_t>, Area_id_hash> _spawned_ids;
};

} // namespace mirelight
