#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "SFML/System/Vector2.hpp"

// ============================================================================
// Forward declarations (1/2)
// ----------------------------------------------------------------------------

namespace titan::game   { class World; class Game_object; }
namespace titan::render { class Camera; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations (2/2)
// ----------------------------------------------------------------------------

class Chunk_streamer;

// ============================================================================
// Class Player_factory
// ----------------------------------------------------------------------------

class Player_factory {

public:
    Player_factory(
        titan::game::World& world,
        Chunk_streamer const& streamer,
        titan::render::Camera& world_camera
        );

    titan::game::Game_object* create(sf::Vector2f position);

private:
    titan::game::World&    _world;
    Chunk_streamer const&  _streamer;
    titan::render::Camera& _camera;
};

} // namespace mirelight
