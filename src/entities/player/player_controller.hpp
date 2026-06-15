#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-game/include/game_component.hpp"
#include "module-core/events/include/event_listener.hpp"

#include "SFML/System/Vector2.hpp"

#include <cstdint>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace mirelight { class Chunk_streamer; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Player_controller
// ----------------------------------------------------------------------------

class Player_controller final
    : public titan::game::Game_component
    , public titan::events::Event_listener
    {

public:
    Player_controller(Chunk_streamer const& streamer, float speed);

    void on_start()  override;
    void on_detach() override;
    void update(float dt) override;

    sf::Vector2f world_position() const;

private:
    Chunk_streamer const& _streamer;
    float                 _speed;

    bool _key_w = false;
    bool _key_a = false;
    bool _key_s = false;
    bool _key_d = false;

    bool _can_stand_at(sf::Vector2f world_pos) const;
};

} // namespace mirelight
