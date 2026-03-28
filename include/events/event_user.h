#ifndef EVENTS_EVENT_USER
#define EVENTS_EVENT_USER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include <typeindex>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::events {

// ===========================================================================
// Class Event_user
// ---------------------------------------------------------------------------

class Event_user {

public:
    virtual ~Event_user() = default;

protected:
    Event_user() = default;

    std::type_index _get_caller_id() const { return std::type_index(typeid(*this)); }
};

} // namespace mirelight::events

#endif
