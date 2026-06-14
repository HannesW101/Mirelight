#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-game/include/game_component.hpp"

#include "SFML/System/Vector2.hpp"

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

class Chunk_streamer;

// ============================================================================
// Class Player_controller
// ----------------------------------------------------------------------------

class Player_controller final : public titan::game::Game_component {

public:
    Player_controller(Chunk_streamer const& streamer, float speed);

    void update(float dt) override;

    sf::Vector2f world_position() const;

private:
    Chunk_streamer const& _streamer;
    float                 _speed;

    bool _can_stand_at(sf::Vector2f world_pos) const;
};

} // namespace mirelight
