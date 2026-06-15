// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/player/player_controller.hpp"
#include "world/chunks/chunk_streamer.hpp"
#include "world/world_config.hpp"

#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"
#include "module-core/events/include/sfml_event_manager.hpp"
#include "module-core/events/include/event_type.hpp"

#include "module-utils/include/math.hpp"

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
using namespace titan::events;

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
void Player_controller::on_start() {

    auto& em  = SFML_event_manager::instance();
    auto lid = listener_id();

    em.register_callback(SFML_event_type::KEYHELD_W, [this](auto&) { _key_w = true;  }, lid);
    em.register_callback(SFML_event_type::KEYHELD_A, [this](auto&) { _key_a = true;  }, lid);
    em.register_callback(SFML_event_type::KEYHELD_S, [this](auto&) { _key_s = true;  }, lid);
    em.register_callback(SFML_event_type::KEYHELD_D, [this](auto&) { _key_d = true;  }, lid);

    em.register_callback(SFML_event_type::KEYRELEASE_W, [this](auto&) { _key_w = false; }, lid);
    em.register_callback(SFML_event_type::KEYRELEASE_A, [this](auto&) { _key_a = false; }, lid);
    em.register_callback(SFML_event_type::KEYRELEASE_S, [this](auto&) { _key_s = false; }, lid);
    em.register_callback(SFML_event_type::KEYRELEASE_D, [this](auto&) { _key_d = false; }, lid);
}

// ----------------------------------------------------------------------------
void Player_controller::on_detach() {

    SFML_event_manager::instance().deregister_listener(listener_id());
}

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

    sf::Vector2f dir{0.0f, 0.0f};
    if (_key_a) { dir.x -= 1.0f; }
    if (_key_d) { dir.x += 1.0f; }
    if (_key_w) { dir.y -= 1.0f; }
    if (_key_s) { dir.y += 1.0f; }

    if (length_sq(dir) <= 0.0f) { return; }

    sf::Vector2f const step = normalize(dir) * (_speed * dt);
    auto& t  = owner().transform();
    sf::Vector2f const cur = t.position();
    sf::Vector2f next = cur;

    sf::Vector2f try_x{cur.x + step.x, cur.y};
    if (_can_stand_at(try_x)) { next.x = try_x.x; }

    sf::Vector2f try_y{next.x, cur.y + step.y};
    if (_can_stand_at(try_y)) { next.y = try_y.y; }

    t.set_position(next);
}

} // namespace mirelight
