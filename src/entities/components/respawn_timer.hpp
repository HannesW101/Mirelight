#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-game/include/game_component.hpp"
#include "world/areas/area_id.hpp"

#include <string>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace mirelight {

class Area_state_store;
class Game_session;
}

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Respawn_timer
// ----------------------------------------------------------------------------

class Respawn_timer final : public titan::game::Game_component {

public:
    Respawn_timer(
        Area_id area,
        std::string spawn_id,
        double respawn_seconds,
        Area_state_store& store,
        Game_session const& session
        );

    void destroy_now();

private:
    Area_id              _area;
    std::string          _spawn_id;
    double                _respawn_seconds;
    Area_state_store&    _store;
    Game_session const&  _session;
};

} // namespace mirelight
