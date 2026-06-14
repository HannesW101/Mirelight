// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/player/player_factory.hpp"
#include "entities/player/player_controller.hpp"
#include "entities/components/camera_follow.hpp"

#include "module-game/include/world.hpp"
#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"
#include "module-game/components/include/sprite_renderer.hpp"

#include "module-render/include/render_layer.hpp"

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::game;
using namespace titan::render;

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

namespace {

constexpr float PLAYER_SPEED = 200.0f; // pixels/sec
}

// ============================================================================
// Class Player_factory
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Player_factory::Player_factory(
    World& world,
    Chunk_streamer const& streamer,
    Camera& world_camera
    )
    : _world(world)
    , _streamer(streamer)
    , _camera(world_camera)
{}

// ----------------------------------------------------------------------------
Game_object* Player_factory::create(
    sf::Vector2f position
    ) {

    Game_object* player = _world.spawn("player");
    player->transform().set_position(position);

    auto* sprite = player->add_component<Sprite_renderer>();
    sprite->set_texture("player");
    sprite->set_origin_centered(true);
    sprite->set_layer(Render_layer::ENTITIES);

    player->add_component<Player_controller>(_streamer, PLAYER_SPEED);
    player->add_component<Camera_follow>(_camera);

    return player;
}

} // namespace mirelight
