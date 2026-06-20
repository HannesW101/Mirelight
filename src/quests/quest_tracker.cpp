// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "quests/quest_tracker.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Quest_tracker
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Quest const* Quest_tracker::_find(
    int id
    ) const {

    auto it = _index.find(id);
    return (it != _index.end()) ? &_quests[it->second] : nullptr;
}

// ----------------------------------------------------------------------------
void Quest_tracker::_refresh_availability() {

    for (auto const& q : _quests) {

        auto& s = _states[q.id];
        if (s != Quest_state::LOCKED) { continue; }

        bool prereq_met = (q.prerequisite == -1) ||
                          (_states.count(q.prerequisite) &&
                          _states.at(q.prerequisite) == Quest_state::COMPLETED);

        if (prereq_met) { s = Quest_state::AVAILABLE; }
    }
}

// ----------------------------------------------------------------------------
void Quest_tracker::load(
    std::string const& path
    ) {

    if (_loaded) { return; }
    _loaded = true;

    std::ifstream f(path);
    if (!f.is_open()) { return; }

    nlohmann::json root;
    try { f >> root; } catch (...) { return; }

    for (auto const& jq : root["quests"]) {

        Quest q;
        q.id           = jq["id"].get<int>();
        q.prerequisite = jq.value("prerequisite", -1);
        q.type         = (jq["type"].get<std::string>() == "main") ? Quest_type::MAIN : Quest_type::SIDE;
        q.npc          = jq["npc"].get<std::string>();
        q.title        = jq["title"].get<std::string>();
        q.description  = jq["description"].get<std::string>();
        q.hand_in_text = jq.value("hand_in_text", "Thank you!");

        for (auto const& jr : jq.value("rewards", nlohmann::json::array())) {

            Quest_reward r;
            r.type  = jr["type"].get<std::string>();
            r.name  = jr.value("name", "");
            r.count = jr.value("count", 1);
            q.rewards.push_back(std::move(r));
        }

        _states[q.id] = Quest_state::LOCKED;
        _index[q.id]  = _quests.size();
        _quests.push_back(std::move(q));
    }

    _refresh_availability();
}

// ----------------------------------------------------------------------------
Quest_state Quest_tracker::state(
    int quest_id
    ) const {

    auto it = _states.find(quest_id);
    return (it != _states.end()) ? it->second : Quest_state::LOCKED;
}

// ----------------------------------------------------------------------------
Quest const* Quest_tracker::quest(
    int quest_id
    ) const {

    return _find(quest_id);
}

// ----------------------------------------------------------------------------
Quest const* Quest_tracker::available_for(
    std::string const& npc
    ) const {

    for (auto const& q : _quests) {

        if (q.npc == npc && state(q.id) == Quest_state::AVAILABLE) { return &q; }
    }

    return nullptr;
}

// ----------------------------------------------------------------------------
Quest const* Quest_tracker::ready_for(
    std::string const& npc
    ) const {

    for (auto const& q : _quests) {

        if (q.npc == npc && state(q.id) == Quest_state::READY_TO_HAND_IN) { return &q; }
    }

    return nullptr;
}

// ----------------------------------------------------------------------------
void Quest_tracker::accept(
    int quest_id
    ) {

    auto it = _states.find(quest_id);
    if (it == _states.end() || it->second != Quest_state::AVAILABLE) { return; }

    // Temporary for testing
    it->second = Quest_state::READY_TO_HAND_IN;
}

// ----------------------------------------------------------------------------
void Quest_tracker::complete(
    int quest_id
    ) {

    auto it = _states.find(quest_id);
    if (it != _states.end() && it->second == Quest_state::ACTIVE) {

        it->second = Quest_state::READY_TO_HAND_IN;
    }
}

// ----------------------------------------------------------------------------
void Quest_tracker::hand_in(
    int quest_id
    ) {

    auto it = _states.find(quest_id);
    if (it == _states.end() || it->second != Quest_state::READY_TO_HAND_IN) { return; }

    it->second = Quest_state::COMPLETED;
    _refresh_availability();
}

} // namespace mirelight
