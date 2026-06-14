// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/player/player_controller.hpp"
#include "world/chunks/chunk_streamer.hpp"
#include "world/world_config.hpp"

#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"

#include "module-utils/include/math.hpp"

#include "SFML/Window/Keyboard.hpp"

#include <cmath>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::game;
using namespace titan::utils;

// ============================================================================
// Class Player_controller
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Player_controller::Player_controller(
    Chunk_streamer const& streamer,
    float speed
    )
    : _streamer(streamer)
    , _speed(speed)
{}

// ----------------------------------------------------------------------------
sf::Vector2f Player_controller::world_position() const {

    return owner().transform().position();
}

// ----------------------------------------------------------------------------
bool Player_controller::_can_stand_at(
    sf::Vector2f world_pos
    ) const {

    int const tx = static_cast<int>(std::floor(world_pos.x / world_cfg::TILE_SIZE));
    int const ty = static_cast<int>(std::floor(world_pos.y / world_cfg::TILE_SIZE));

    return _streamer.is_walkable(tx, ty);
}

// ----------------------------------------------------------------------------
void Player_controller::update(
    float dt
    ) {

    using Key = sf::Keyboard::Key;

    sf::Vector2f dir { 0.0f, 0.0f };
//TODO why not register?
    if (sf::Keyboard::isKeyPressed(Key::A) || sf::Keyboard::isKeyPressed(Key::Left))  { dir.x -= 1.0f; }
    if (sf::Keyboard::isKeyPressed(Key::D) || sf::Keyboard::isKeyPressed(Key::Right)) { dir.x += 1.0f; }
    if (sf::Keyboard::isKeyPressed(Key::W) || sf::Keyboard::isKeyPressed(Key::Up))    { dir.y -= 1.0f; }
    if (sf::Keyboard::isKeyPressed(Key::S) || sf::Keyboard::isKeyPressed(Key::Down))  { dir.y += 1.0f; }

    if (length_sq(dir) <= 0.0f) { return; }

    sf::Vector2f const step = normalize(dir) * (_speed * dt);
    auto& t = owner().transform();
    sf::Vector2f const cur = t.position();

    sf::Vector2f next = cur;

    sf::Vector2f try_x { cur.x + step.x, cur.y };
    if (_can_stand_at(try_x)) { next.x = try_x.x; }

    sf::Vector2f try_y { next.x, cur.y + step.y };
    if (_can_stand_at(try_y)) { next.y = try_y.y; }

    t.set_position(next);
}

} // namespace mirelight
