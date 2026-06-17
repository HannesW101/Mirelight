#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/area_id.hpp"
#include "world/areas/spawn_table.hpp"

#include "SFML/System/Vector2.hpp"

#include <functional>
#include <string>
#include <unordered_map>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::game {

class World;
class Game_object;
}

namespace mirelight {

class Area_state_store;
class Game_session;
}

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Object_factory
// ----------------------------------------------------------------------------

class Object_factory {

public:
    using Builder = std::function<titan::game::Game_object*(
        titan::game::World& world,
        sf::Vector2f world_pos,
        Spawn_entry const& entry,
        Area_id const& area,
        Area_state_store& store,
        Game_session const& session
        )>;

    void register_type(std::string type, Builder builder);

    titan::game::Game_object* build(
        sf::Vector2f world_pos,
        Spawn_entry const& entry,
        Area_id const& area,
        titan::game::World& world,
        Area_state_store& store,
        Game_session const& session
        ) const;

private:
    std::unordered_map<std::string, Builder> _builders;
};

// ============================================================================
// Functions
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void register_default_object_types(Object_factory& factory);

} // namespace mirelight
