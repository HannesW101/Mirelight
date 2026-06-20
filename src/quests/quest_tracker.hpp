#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "quests/quest.hpp"

#include <string>
#include <unordered_map>
#include <vector>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Quest_tracker
// ----------------------------------------------------------------------------

class Quest_tracker {

public:
    void load(std::string const& path);

    Quest_state  state(int quest_id) const;
    Quest const* quest(int quest_id) const;

    Quest const* available_for(std::string const& npc) const;
    Quest const* ready_for    (std::string const& npc) const;

    void accept  (int quest_id);
    void complete(int quest_id);
    void hand_in (int quest_id);

private:
    std::vector<Quest>                    _quests;
    std::unordered_map<int, Quest_state>  _states;
    std::unordered_map<int, std::size_t>  _index;
    bool                                  _loaded = false;

    Quest const* _find(int id) const;
    void _refresh_availability();
};

} // namespace mirelight
