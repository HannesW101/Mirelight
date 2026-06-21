// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/player/player_controller.hpp"
#include "world/world_config.hpp"

#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"
#include "module-game/components/include/animator.hpp"
#include "module-game/components/include/sprite_renderer.hpp"
#include "module-core/events/include/sfml_event_manager.hpp"
#include "module-core/events/include/event_type.hpp"

#include "entities/entity_config.hpp"
#include "module-utils/include/math.hpp"

#include <array>
#include <cmath>
#include <cstdint>

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
// Animation table
// ----------------------------------------------------------------------------

namespace {

struct Directional_clip {

    char const* tex_key;
    char const* sheet_key;

    // Indexed by Facing (FRONT, BACK, LEFT, RIGHT).
    std::array<char const*, 4> clips;
};

// Indexed by Anim_state (IDLE, WALK, ...).
constexpr std::array<Directional_clip, 2> ANIM_TABLE = {{

    // IDLE
    { "player_idle", "player_idle_sheet",
        { "idle_front", "idle_back", "idle_left", "idle_right" }
    },

    // WALK
    { "player_walk", "player_walk_sheet",
        { "walk_front", "walk_back", "walk_left", "walk_right" }
    },
}};

} // namespace

// ============================================================================
// Class Player_controller
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Player_controller::Player_controller(
    Walkable_provider const& walkable,
    float speed
    )
    : _walkable(walkable)
    , _speed(speed)
{}

// ----------------------------------------------------------------------------
void Player_controller::on_start() {

    auto& em  = SFML_event_manager::instance();
    auto  lid = listener_id();

    em.register_callback(SFML_event_type::KEYHELD_W,    [this](auto&) { _key_w = true;  }, lid);
    em.register_callback(SFML_event_type::KEYHELD_A,    [this](auto&) { _key_a = true;  }, lid);
    em.register_callback(SFML_event_type::KEYHELD_S,    [this](auto&) { _key_s = true;  }, lid);
    em.register_callback(SFML_event_type::KEYHELD_D,    [this](auto&) { _key_d = true;  }, lid);
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
void Player_controller::set_animator(
    titan::game::Animator*        anim,
    titan::game::Sprite_renderer* sprite
    ) {

    _animator = anim;
    _sprite   = sprite;
}

// ----------------------------------------------------------------------------
void Player_controller::_apply_animation() {

    if (!_animator) { return; }

    auto const& clip = ANIM_TABLE[static_cast<std::uint8_t>(_anim_state)];
    if (_sprite) { _sprite->set_texture(clip.tex_key); }
    _animator->set_spritesheet(clip.sheet_key);
    _animator->play(clip.clips[static_cast<std::uint8_t>(_facing)]);
}

// ----------------------------------------------------------------------------
bool Player_controller::_can_stand_at(
    sf::Vector2f center
    ) const {

    // Check all four corners of the player's collision box (feet region).
    constexpr float HW = entity_cfg::COLLISION_HW;
    constexpr float HH = entity_cfg::COLLISION_HH;

    auto ok = [&](
        float x,
        float y
        ) {

        int const tx = static_cast<int>(std::floor(x / world_cfg::TILE_SIZE));
        int const ty = static_cast<int>(std::floor(y / world_cfg::TILE_SIZE));
        return _walkable.is_walkable(tx, ty);
        };

    return ok(center.x - HW, center.y - HH)
        && ok(center.x + HW, center.y - HH)
        && ok(center.x - HW, center.y + HH)
        && ok(center.x + HW, center.y + HH);
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

    bool const now_moving = length_sq(dir) > 0.0f;

    Anim_state const new_state  = now_moving ? Anim_state::WALK : Anim_state::IDLE;
    Facing           new_facing = _facing;
    if (now_moving) {
        if (std::abs(dir.x) >= std::abs(dir.y)) {

            new_facing = (dir.x < 0.0f) ? Facing::LEFT : Facing::RIGHT;
        } else {

            new_facing = (dir.y < 0.0f) ? Facing::BACK : Facing::FRONT;
        }
    }

    if (new_state != _anim_state || new_facing != _facing) {

        _anim_state = new_state;
        _facing     = new_facing;
        _apply_animation();
    }

    if (!now_moving) { return; }

    sf::Vector2f const step = normalize(dir) * (_speed * dt);
    auto&              t    = owner().transform();
    sf::Vector2f const cur  = t.position();
    sf::Vector2f       next = cur;

    sf::Vector2f try_x{cur.x + step.x, cur.y};
    if (_can_stand_at(try_x)) { next.x = try_x.x; }

    sf::Vector2f try_y{next.x, cur.y + step.y};
    if (_can_stand_at(try_y)) { next.y = try_y.y; }

    t.set_position(next);
}

} // namespace mirelight
