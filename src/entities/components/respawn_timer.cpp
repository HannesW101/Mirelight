// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/components/respawn_timer.hpp"
#include "world/areas/area_state.hpp"
#include "world/areas/game_session.hpp"

#include "module-game/include/game_object.hpp"

#include <utility>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Respawn_timer
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Respawn_timer::Respawn_timer(
    Area_id area,
    std::string spawn_id,
    double respawn_seconds,
    Area_state_store& store,
    Game_session const& session
    )
    : _area(std::move(area))
    , _spawn_id(std::move(spawn_id))
    , _respawn_seconds(respawn_seconds)
    , _store(store)
    , _session(session)
{}

// ----------------------------------------------------------------------------
void Respawn_timer::destroy_now() {

    _store.mark_destroyed(_area, _spawn_id, _session.world_time());
    owner().destroy();
}

} // namespace mirelight
