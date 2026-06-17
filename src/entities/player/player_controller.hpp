#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-game/include/game_component.hpp"
#include "module-core/events/include/event_listener.hpp"
#include "world/walkable_provider.hpp"

#include "SFML/System/Vector2.hpp"

#include <cstdint>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::game { class Animator; class Sprite_renderer; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Enums
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
enum class Facing : std::uint8_t {

    FRONT,
    BACK,
    LEFT,
    RIGHT
};

// ----------------------------------------------------------------------------
enum class Anim_state : std::uint8_t {

    IDLE,
    WALK
};

// ============================================================================
// Class Player_controller
// ----------------------------------------------------------------------------

class Player_controller final
    : public titan::game::Game_component
    , public titan::events::Event_listener
    {

public:
    Player_controller(Walkable_provider const& walkable, float speed);

    void on_start()  override;
    void on_detach() override;
    void update(float dt) override;

    sf::Vector2f world_position() const;
    void set_animator(titan::game::Animator* anim, titan::game::Sprite_renderer* sprite);

private:
    Walkable_provider const& _walkable;
    float                    _speed;

    bool _key_w = false;
    bool _key_a = false;
    bool _key_s = false;
    bool _key_d = false;

    titan::game::Animator*        _animator   = nullptr;
    titan::game::Sprite_renderer* _sprite     = nullptr;
    Facing                        _facing     = Facing::FRONT;
    Anim_state                    _anim_state = Anim_state::IDLE;

    bool _can_stand_at(sf::Vector2f world_pos) const;
    void _apply_animation();
};

} // namespace mirelight
