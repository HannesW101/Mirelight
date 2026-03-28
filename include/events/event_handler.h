#ifndef EVENTS_EVENT_HANDLER
#define EVENTS_EVENT_HANDLER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "events/event_defs.h"

#include <SFML/Graphics.hpp>

#include <map>
#include <functional>
#include <vector>
#include <optional>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::events {

// ===========================================================================
// Class Event_handler
// ---------------------------------------------------------------------------

class Event_handler final {

public:
    static Event_handler& get_instance();

    ~Event_handler          (                    ) = default;
    Event_handler           (Event_handler const&) = delete;
    Event_handler& operator=(Event_handler const&) = delete;
    Event_handler           (Event_handler&&     ) = delete;
    Event_handler& operator=(Event_handler&&     ) = delete;

    void handle_events(std::optional<sf::Event> const& event);

    void register_event(Event_id const& event_id, std::function<void()> const& func);

    void deregister_event(Event_id const& event_id);
    void deregister_event(std::type_index const& caller_id);
    void deregister_event(Event_type const event_type);

private:
    Event_handler();

    void _execute_event(Event_type const event_type);

    void _handle_window_closed_events           (std::optional<sf::Event> const& event);
    void _handle_window_resized_events          (std::optional<sf::Event> const& event);
    void _handle_window_lost_focus_events       (std::optional<sf::Event> const& event);
    void _handle_window_gained_focus_events     (std::optional<sf::Event> const& event);
    void _handle_text_entered_events            (std::optional<sf::Event> const& event);
    void _handle_mouse_moved_events             (std::optional<sf::Event> const& event);
    void _handle_mouse_button_pressed_events    (std::optional<sf::Event> const& event);
    void _handle_mouse_button_release_events    (std::optional<sf::Event> const& event);
    void _handle_mouse_wheel_events             (std::optional<sf::Event> const& event);
    void _handle_mouse_enter_window_events      (std::optional<sf::Event> const& event);
    void _handle_mouse_left_window_events       (std::optional<sf::Event> const& event);
    void _handle_joystick_button_pressed_events (std::optional<sf::Event> const& event);
    void _handle_joystick_button_released_events(std::optional<sf::Event> const& event);
    void _handle_joystick_moved_events          (std::optional<sf::Event> const& event);
    void _handle_joystick_connected_events      (std::optional<sf::Event> const& event);
    void _handle_joystick_disconnected_events   (std::optional<sf::Event> const& event);
    void _handle_touch_began_events             (std::optional<sf::Event> const& event);
    void _handle_touch_moved_events             (std::optional<sf::Event> const& event);
    void _handle_touch_ended_events             (std::optional<sf::Event> const& event);
    void _handle_sensor_changed_events          (std::optional<sf::Event> const& event);
    void _handle_key_pressed_events             (std::optional<sf::Event> const& event);
    void _handle_key_released_events            (std::optional<sf::Event> const& event);

    std::map<Event_id, Event_vec> _callbacks;
};

} // namespace mirelight::events

#endif
