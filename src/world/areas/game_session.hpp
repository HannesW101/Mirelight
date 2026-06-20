#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/area_state.hpp"
#include "quests/quest_tracker.hpp"

#include <string>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Game_session
// ----------------------------------------------------------------------------

class Game_session {

public:
    explicit Game_session(std::string save_dir = "data/saves/default");

    void update(float dt);

    double world_time() const;

    Area_state_store& state_store();
    Area_state_store const& state_store() const;

    Quest_tracker&       quests();
    Quest_tracker const& quests() const;

    std::string const& save_dir() const;

private:
    Area_state_store _store;
    Quest_tracker    _quests;
    std::string      _save_dir;
    double           _world_time_seconds = 0.0;
};

} // namespace mirelight
