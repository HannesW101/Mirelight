#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/walkable_provider.hpp"

#include "SFML/System/Vector2.hpp"

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::game   { class World; class Game_object; }
namespace titan::render { class Camera; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Player_factory
// ----------------------------------------------------------------------------

class Player_factory {

public:
    Player_factory(
        titan::game::World& world,
        Walkable_provider const& walkable,
        titan::render::Camera& world_camera
        );

    titan::game::Game_object* create(sf::Vector2f position);

private:
    titan::game::World&       _world;
    Walkable_provider const&  _walkable;
    titan::render::Camera&    _camera;
};

} // namespace mirelight
