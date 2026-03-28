// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "events/event_handler.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::events {

// ===========================================================================
// Class Event_handler
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Event_handler& Event_handler::get_instance() {

    static Event_handler instance;
    return instance;
}

// ---------------------------------------------------------------------------
void Event_handler::handle_events(std::optional<sf::Event> const& event) {

    if (!event.has_value()) { return; }

         if (event->is<sf::Event::Closed>())                 { _handle_window_closed_events(event); }
    else if (event->is<sf::Event::Resized>())                { _handle_window_resized_events(event); }
    else if (event->is<sf::Event::FocusLost>())              { _handle_window_lost_focus_events(event); }
    else if (event->is<sf::Event::FocusGained>())            { _handle_window_gained_focus_events(event); }
    else if (event->is<sf::Event::TextEntered>())            { _handle_text_entered_events(event); }
    else if (event->is<sf::Event::MouseMoved>())             { _handle_mouse_moved_events(event);}
    else if (event->is<sf::Event::MouseButtonPressed>())     { _handle_mouse_button_pressed_events(event); }
    else if (event->is<sf::Event::MouseButtonReleased>())    { _handle_mouse_button_release_events(event); }
    else if (event->is<sf::Event::MouseWheelScrolled>())     { _handle_mouse_wheel_events(event); }
    else if (event->is<sf::Event::MouseEntered>())           { _handle_mouse_enter_window_events(event); }
    else if (event->is<sf::Event::MouseLeft>())              { _handle_mouse_left_window_events(event); }
    else if (event->is<sf::Event::JoystickButtonPressed>())  { _handle_joystick_button_pressed_events(event); }
    else if (event->is<sf::Event::JoystickButtonReleased>()) { _handle_joystick_button_released_events(event); }
    else if (event->is<sf::Event::JoystickMoved>())          { _handle_joystick_moved_events(event); }
    else if (event->is<sf::Event::JoystickConnected>())      {_handle_joystick_connected_events(event); }
    else if (event->is<sf::Event::JoystickDisconnected>())   { _handle_joystick_disconnected_events(event); }
    else if (event->is<sf::Event::TouchBegan>())             { _handle_touch_began_events(event); }
    else if (event->is<sf::Event::TouchMoved>())             { _handle_touch_moved_events(event); }
    else if (event->is<sf::Event::TouchEnded>())             { _handle_touch_ended_events(event); }
    else if (event->is<sf::Event::SensorChanged>())          { _handle_sensor_changed_events(event); }
    else if (event->is<sf::Event::KeyPressed>())             { _handle_key_pressed_events(event); }
    else if (event->is<sf::Event::KeyReleased>())            { _handle_key_released_events(event); }
}

// ---------------------------------------------------------------------------
void Event_handler::register_event(Event_id const& event_id, std::function<void()> const& func) {

    _callbacks[event_id].push_back(func);
}

// ---------------------------------------------------------------------------
void Event_handler::deregister_event(Event_id const& event_id) {

    std::erase_if(_callbacks, [&](auto const& pair) {

        return pair.first == event_id;
    });
}

// ---------------------------------------------------------------------------
void Event_handler::deregister_event(std::type_index const& caller_id) {

    std::erase_if(_callbacks, [&](auto const& pair) {

        return pair.first.caller_id == caller_id;
    });
}

// ---------------------------------------------------------------------------
void Event_handler::deregister_event(Event_type const event_type) {

    std::erase_if(_callbacks, [&](auto const& pair) {

        return pair.first.event_type == event_type;
    });
}

// ---------------------------------------------------------------------------
Event_handler::Event_handler()
    : _callbacks()
{}

// ---------------------------------------------------------------------------
void Event_handler::_execute_event(Event_type const event_type) {

    for (auto const& [event_id, event_vec] : _callbacks) {

        if (event_id.event_type == event_type) {

            for (auto const& func : event_vec) {

                func();
            }
        }
    }
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_window_closed_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::WINDOW_CLOSED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_window_resized_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::WINDOW_RESIZED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_window_lost_focus_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::WINDOW_LOST_FOCUS);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_window_gained_focus_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::WINDOW_GAINED_FOCUS);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_text_entered_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::WINDOW_TEXT_ENTERED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_mouse_moved_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::MOUSE_MOVED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_mouse_button_pressed_events(
    std::optional<sf::Event> const& event
    ) {

    if (auto btn_press = event->getIf<sf::Event::MouseButtonPressed>()) {

        switch (btn_press->button) {

        case sf::Mouse::Button::Left:   _execute_event(Event_type::MOUSE_BUTTON_LEFT_PRESS   ); break;
        case sf::Mouse::Button::Right:  _execute_event(Event_type::MOUSE_BUTTON_RIGHT_PRESS  ); break;
        case sf::Mouse::Button::Middle: _execute_event(Event_type::MOUSE_BUTTON_MIDDLE_PRESS ); break;
        case sf::Mouse::Button::Extra1: _execute_event(Event_type::MOUSE_BUTTON_EXTRA_1_PRESS); break;
        case sf::Mouse::Button::Extra2: _execute_event(Event_type::MOUSE_BUTTON_EXTRA_2_PRESS); break;
        }
    }
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_mouse_button_release_events(
    std::optional<sf::Event> const& event
    ) {

    if (auto mouse_released = event->getIf<sf::Event::MouseButtonReleased>()) {

        switch (mouse_released->button) {

        case sf::Mouse::Button::Left:   _execute_event(Event_type::MOUSE_BUTTON_LEFT_RELEASE   ); break;
        case sf::Mouse::Button::Right:  _execute_event(Event_type::MOUSE_BUTTON_RIGHT_RELEASE  ); break;
        case sf::Mouse::Button::Middle: _execute_event(Event_type::MOUSE_BUTTON_MIDDLE_RELEASE ); break;
        case sf::Mouse::Button::Extra1: _execute_event(Event_type::MOUSE_BUTTON_EXTRA_1_RELEASE); break;
        case sf::Mouse::Button::Extra2: _execute_event(Event_type::MOUSE_BUTTON_EXTRA_2_RELEASE); break;
        }
    }
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_mouse_wheel_events(
    std::optional<sf::Event> const& event
    ) {

    if (auto mouse_released = event->getIf<sf::Event::MouseWheelScrolled>()) {

        if (mouse_released->delta > 0) {

            _execute_event(Event_type::MOUSE_WHEEL_UP);
        } else {

            _execute_event(Event_type::MOUSE_WHEEL_DOWN);
        }
    }
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_mouse_enter_window_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::MOUSE_ENTER_WINDOW);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_mouse_left_window_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::MOUSE_LEAVE_WINDOW);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_joystick_button_pressed_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::JOYSTICK_BUTTON_PRESSED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_joystick_button_released_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::JOYSTICK_BUTTON_RELEASED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_joystick_moved_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::JOYSTICK_MOVED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_joystick_connected_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::JOYSTICK_CONNECTED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_joystick_disconnected_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::JOYSTICK_DISCONNECTED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_touch_began_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::TOUCH_BEGAN);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_touch_moved_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::TOUCH_MOVED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_touch_ended_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::TOUCH_ENDED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_sensor_changed_events(
    std::optional<sf::Event> const& event
    ) {

    static_cast<void>(event);
    _execute_event(Event_type::SENSOR_CHANGED);
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_key_pressed_events(
    std::optional<sf::Event> const& event
    ) {

    if (auto const key_pressed = event->getIf<sf::Event::KeyPressed>()) {

        switch (key_pressed->code) {

        case sf::Keyboard::Key::Unknown   :                                                 break;
        case sf::Keyboard::Key::A         : _execute_event(Event_type::KEYPRESS_A);         break;
        case sf::Keyboard::Key::B         : _execute_event(Event_type::KEYPRESS_B);         break;
        case sf::Keyboard::Key::C         : _execute_event(Event_type::KEYPRESS_C);         break;
        case sf::Keyboard::Key::D         : _execute_event(Event_type::KEYPRESS_D);         break;
        case sf::Keyboard::Key::E         : _execute_event(Event_type::KEYPRESS_E);         break;
        case sf::Keyboard::Key::F         : _execute_event(Event_type::KEYPRESS_F);         break;
        case sf::Keyboard::Key::G         : _execute_event(Event_type::KEYPRESS_G);         break;
        case sf::Keyboard::Key::H         : _execute_event(Event_type::KEYPRESS_H);         break;
        case sf::Keyboard::Key::I         : _execute_event(Event_type::KEYPRESS_I);         break;
        case sf::Keyboard::Key::J         : _execute_event(Event_type::KEYPRESS_J);         break;
        case sf::Keyboard::Key::K         : _execute_event(Event_type::KEYPRESS_K);         break;
        case sf::Keyboard::Key::L         : _execute_event(Event_type::KEYPRESS_L);         break;
        case sf::Keyboard::Key::M         : _execute_event(Event_type::KEYPRESS_M);         break;
        case sf::Keyboard::Key::N         : _execute_event(Event_type::KEYPRESS_N);         break;
        case sf::Keyboard::Key::O         : _execute_event(Event_type::KEYPRESS_O);         break;
        case sf::Keyboard::Key::P         : _execute_event(Event_type::KEYPRESS_P);         break;
        case sf::Keyboard::Key::Q         : _execute_event(Event_type::KEYPRESS_Q);         break;
        case sf::Keyboard::Key::R         : _execute_event(Event_type::KEYPRESS_R);         break;
        case sf::Keyboard::Key::S         : _execute_event(Event_type::KEYPRESS_S);         break;
        case sf::Keyboard::Key::T         : _execute_event(Event_type::KEYPRESS_T);         break;
        case sf::Keyboard::Key::U         : _execute_event(Event_type::KEYPRESS_U);         break;
        case sf::Keyboard::Key::V         : _execute_event(Event_type::KEYPRESS_V);         break;
        case sf::Keyboard::Key::W         : _execute_event(Event_type::KEYPRESS_W);         break;
        case sf::Keyboard::Key::X         : _execute_event(Event_type::KEYPRESS_X);         break;
        case sf::Keyboard::Key::Y         : _execute_event(Event_type::KEYPRESS_Y);         break;
        case sf::Keyboard::Key::Z         : _execute_event(Event_type::KEYPRESS_Z);         break;
        case sf::Keyboard::Key::Num0      : _execute_event(Event_type::KEYPRESS_NUM0);      break;
        case sf::Keyboard::Key::Num1      : _execute_event(Event_type::KEYPRESS_NUM1);      break;
        case sf::Keyboard::Key::Num2      : _execute_event(Event_type::KEYPRESS_NUM2);      break;
        case sf::Keyboard::Key::Num3      : _execute_event(Event_type::KEYPRESS_NUM3);      break;
        case sf::Keyboard::Key::Num4      : _execute_event(Event_type::KEYPRESS_NUM4);      break;
        case sf::Keyboard::Key::Num5      : _execute_event(Event_type::KEYPRESS_NUM5);      break;
        case sf::Keyboard::Key::Num6      : _execute_event(Event_type::KEYPRESS_NUM6);      break;
        case sf::Keyboard::Key::Num7      : _execute_event(Event_type::KEYPRESS_NUM7);      break;
        case sf::Keyboard::Key::Num8      : _execute_event(Event_type::KEYPRESS_NUM8);      break;
        case sf::Keyboard::Key::Num9      : _execute_event(Event_type::KEYPRESS_NUM9);      break;
        case sf::Keyboard::Key::Escape    : _execute_event(Event_type::KEYPRESS_ESCAPE);    break;
        case sf::Keyboard::Key::LControl  : _execute_event(Event_type::KEYPRESS_LCONTROL);  break;
        case sf::Keyboard::Key::LShift    : _execute_event(Event_type::KEYPRESS_LSHIFT);    break;
        case sf::Keyboard::Key::LAlt      : _execute_event(Event_type::KEYPRESS_LALT);      break;
        case sf::Keyboard::Key::LSystem   : _execute_event(Event_type::KEYPRESS_LSYSTEM);   break;
        case sf::Keyboard::Key::RControl  : _execute_event(Event_type::KEYPRESS_RCONTROL);  break;
        case sf::Keyboard::Key::RShift    : _execute_event(Event_type::KEYPRESS_RSHIFT);    break;
        case sf::Keyboard::Key::RAlt      : _execute_event(Event_type::KEYPRESS_RALT);      break;
        case sf::Keyboard::Key::RSystem   : _execute_event(Event_type::KEYPRESS_RSYSTEM);   break;
        case sf::Keyboard::Key::Menu      : _execute_event(Event_type::KEYPRESS_MENU);      break;
        case sf::Keyboard::Key::LBracket  : _execute_event(Event_type::KEYPRESS_LBRACKET);  break;
        case sf::Keyboard::Key::RBracket  : _execute_event(Event_type::KEYPRESS_RBRACKET);  break;
        case sf::Keyboard::Key::Semicolon : _execute_event(Event_type::KEYPRESS_SEMICOLON); break;
        case sf::Keyboard::Key::Comma     : _execute_event(Event_type::KEYPRESS_COMMA);     break;
        case sf::Keyboard::Key::Period    : _execute_event(Event_type::KEYPRESS_PERIOD);    break;
        case sf::Keyboard::Key::Apostrophe: _execute_event(Event_type::KEYPRESS_QUOTE);     break;
        case sf::Keyboard::Key::Slash     : _execute_event(Event_type::KEYPRESS_SLASH);     break;
        case sf::Keyboard::Key::Backslash : _execute_event(Event_type::KEYPRESS_BACKSLASH); break;
        case sf::Keyboard::Key::Grave     : _execute_event(Event_type::KEYPRESS_TILDE);     break;
        case sf::Keyboard::Key::Equal     : _execute_event(Event_type::KEYPRESS_EQUAL);     break;
        case sf::Keyboard::Key::Hyphen    : _execute_event(Event_type::KEYPRESS_DASH);      break;
        case sf::Keyboard::Key::Space     : _execute_event(Event_type::KEYPRESS_SPACE);     break;
        case sf::Keyboard::Key::Enter     : _execute_event(Event_type::KEYPRESS_RETURN);    break;
        case sf::Keyboard::Key::Backspace : _execute_event(Event_type::KEYPRESS_BACKSPACE); break;
        case sf::Keyboard::Key::Tab       : _execute_event(Event_type::KEYPRESS_TAB);       break;
        case sf::Keyboard::Key::PageUp    : _execute_event(Event_type::KEYPRESS_PAGEUP);    break;
        case sf::Keyboard::Key::PageDown  : _execute_event(Event_type::KEYPRESS_PAGEDOWN);  break;
        case sf::Keyboard::Key::End       : _execute_event(Event_type::KEYPRESS_END);       break;
        case sf::Keyboard::Key::Home      : _execute_event(Event_type::KEYPRESS_HOME);      break;
        case sf::Keyboard::Key::Insert    : _execute_event(Event_type::KEYPRESS_INSERT);    break;
        case sf::Keyboard::Key::Delete    : _execute_event(Event_type::KEYPRESS_DELETE);    break;
        case sf::Keyboard::Key::Add       : _execute_event(Event_type::KEYPRESS_ADD);       break;
        case sf::Keyboard::Key::Subtract  : _execute_event(Event_type::KEYPRESS_SUBTRACT);  break;
        case sf::Keyboard::Key::Multiply  : _execute_event(Event_type::KEYPRESS_MULTIPLY);  break;
        case sf::Keyboard::Key::Divide    : _execute_event(Event_type::KEYPRESS_DIVIDE);    break;
        case sf::Keyboard::Key::Left      : _execute_event(Event_type::KEYPRESS_LEFT);      break;
        case sf::Keyboard::Key::Right     : _execute_event(Event_type::KEYPRESS_RIGHT);     break;
        case sf::Keyboard::Key::Up        : _execute_event(Event_type::KEYPRESS_UP);        break;
        case sf::Keyboard::Key::Down      : _execute_event(Event_type::KEYPRESS_DOWN);      break;
        case sf::Keyboard::Key::Numpad0   : _execute_event(Event_type::KEYPRESS_NUMPAD0);   break;
        case sf::Keyboard::Key::Numpad1   : _execute_event(Event_type::KEYPRESS_NUMPAD1);   break;
        case sf::Keyboard::Key::Numpad2   : _execute_event(Event_type::KEYPRESS_NUMPAD2);   break;
        case sf::Keyboard::Key::Numpad3   : _execute_event(Event_type::KEYPRESS_NUMPAD3);   break;
        case sf::Keyboard::Key::Numpad4   : _execute_event(Event_type::KEYPRESS_NUMPAD4);   break;
        case sf::Keyboard::Key::Numpad5   : _execute_event(Event_type::KEYPRESS_NUMPAD5);   break;
        case sf::Keyboard::Key::Numpad6   : _execute_event(Event_type::KEYPRESS_NUMPAD6);   break;
        case sf::Keyboard::Key::Numpad7   : _execute_event(Event_type::KEYPRESS_NUMPAD7);   break;
        case sf::Keyboard::Key::Numpad8   : _execute_event(Event_type::KEYPRESS_NUMPAD8);   break;
        case sf::Keyboard::Key::Numpad9   : _execute_event(Event_type::KEYPRESS_NUMPAD9);   break;
        case sf::Keyboard::Key::F1        : _execute_event(Event_type::KEYPRESS_F1);        break;
        case sf::Keyboard::Key::F2        : _execute_event(Event_type::KEYPRESS_F2);        break;
        case sf::Keyboard::Key::F3        : _execute_event(Event_type::KEYPRESS_F3);        break;
        case sf::Keyboard::Key::F4        : _execute_event(Event_type::KEYPRESS_F4);        break;
        case sf::Keyboard::Key::F5        : _execute_event(Event_type::KEYPRESS_F5);        break;
        case sf::Keyboard::Key::F6        : _execute_event(Event_type::KEYPRESS_F6);        break;
        case sf::Keyboard::Key::F7        : _execute_event(Event_type::KEYPRESS_F7);        break;
        case sf::Keyboard::Key::F8        : _execute_event(Event_type::KEYPRESS_F8);        break;
        case sf::Keyboard::Key::F9        : _execute_event(Event_type::KEYPRESS_F9);        break;
        case sf::Keyboard::Key::F10       : _execute_event(Event_type::KEYPRESS_F10);       break;
        case sf::Keyboard::Key::F11       : _execute_event(Event_type::KEYPRESS_F11);       break;
        case sf::Keyboard::Key::F12       : _execute_event(Event_type::KEYPRESS_F12);       break;
        case sf::Keyboard::Key::F13       : _execute_event(Event_type::KEYPRESS_F13);       break;
        case sf::Keyboard::Key::F14       : _execute_event(Event_type::KEYPRESS_F14);       break;
        case sf::Keyboard::Key::F15       : _execute_event(Event_type::KEYPRESS_F15);       break;
        case sf::Keyboard::Key::Pause     : _execute_event(Event_type::KEYPRESS_PAUSE);     break;
        }
    }
}

// ---------------------------------------------------------------------------
void Event_handler::_handle_key_released_events(
    std::optional<sf::Event> const& event
    ) {

    if (auto const key_released = event->getIf<sf::Event::KeyReleased>()) {

        switch (key_released->code) {

        case sf::Keyboard::Key::Unknown   :                                                   break;
        case sf::Keyboard::Key::A         : _execute_event(Event_type::KEYRELEASE_A);         break;
        case sf::Keyboard::Key::B         : _execute_event(Event_type::KEYRELEASE_B);         break;
        case sf::Keyboard::Key::C         : _execute_event(Event_type::KEYRELEASE_C);         break;
        case sf::Keyboard::Key::D         : _execute_event(Event_type::KEYRELEASE_D);         break;
        case sf::Keyboard::Key::E         : _execute_event(Event_type::KEYRELEASE_E);         break;
        case sf::Keyboard::Key::F         : _execute_event(Event_type::KEYRELEASE_F);         break;
        case sf::Keyboard::Key::G         : _execute_event(Event_type::KEYRELEASE_G);         break;
        case sf::Keyboard::Key::H         : _execute_event(Event_type::KEYRELEASE_H);         break;
        case sf::Keyboard::Key::I         : _execute_event(Event_type::KEYRELEASE_I);         break;
        case sf::Keyboard::Key::J         : _execute_event(Event_type::KEYRELEASE_J);         break;
        case sf::Keyboard::Key::K         : _execute_event(Event_type::KEYRELEASE_K);         break;
        case sf::Keyboard::Key::L         : _execute_event(Event_type::KEYRELEASE_L);         break;
        case sf::Keyboard::Key::M         : _execute_event(Event_type::KEYRELEASE_M);         break;
        case sf::Keyboard::Key::N         : _execute_event(Event_type::KEYRELEASE_N);         break;
        case sf::Keyboard::Key::O         : _execute_event(Event_type::KEYRELEASE_O);         break;
        case sf::Keyboard::Key::P         : _execute_event(Event_type::KEYRELEASE_P);         break;
        case sf::Keyboard::Key::Q         : _execute_event(Event_type::KEYRELEASE_Q);         break;
        case sf::Keyboard::Key::R         : _execute_event(Event_type::KEYRELEASE_R);         break;
        case sf::Keyboard::Key::S         : _execute_event(Event_type::KEYRELEASE_S);         break;
        case sf::Keyboard::Key::T         : _execute_event(Event_type::KEYRELEASE_T);         break;
        case sf::Keyboard::Key::U         : _execute_event(Event_type::KEYRELEASE_U);         break;
        case sf::Keyboard::Key::V         : _execute_event(Event_type::KEYRELEASE_V);         break;
        case sf::Keyboard::Key::W         : _execute_event(Event_type::KEYRELEASE_W);         break;
        case sf::Keyboard::Key::X         : _execute_event(Event_type::KEYRELEASE_X);         break;
        case sf::Keyboard::Key::Y         : _execute_event(Event_type::KEYRELEASE_Y);         break;
        case sf::Keyboard::Key::Z         : _execute_event(Event_type::KEYRELEASE_Z);         break;
        case sf::Keyboard::Key::Num0      : _execute_event(Event_type::KEYRELEASE_NUM0);      break;
        case sf::Keyboard::Key::Num1      : _execute_event(Event_type::KEYRELEASE_NUM1);      break;
        case sf::Keyboard::Key::Num2      : _execute_event(Event_type::KEYRELEASE_NUM2);      break;
        case sf::Keyboard::Key::Num3      : _execute_event(Event_type::KEYRELEASE_NUM3);      break;
        case sf::Keyboard::Key::Num4      : _execute_event(Event_type::KEYRELEASE_NUM4);      break;
        case sf::Keyboard::Key::Num5      : _execute_event(Event_type::KEYRELEASE_NUM5);      break;
        case sf::Keyboard::Key::Num6      : _execute_event(Event_type::KEYRELEASE_NUM6);      break;
        case sf::Keyboard::Key::Num7      : _execute_event(Event_type::KEYRELEASE_NUM7);      break;
        case sf::Keyboard::Key::Num8      : _execute_event(Event_type::KEYRELEASE_NUM8);      break;
        case sf::Keyboard::Key::Num9      : _execute_event(Event_type::KEYRELEASE_NUM9);      break;
        case sf::Keyboard::Key::Escape    : _execute_event(Event_type::KEYRELEASE_ESCAPE);    break;
        case sf::Keyboard::Key::LControl  : _execute_event(Event_type::KEYRELEASE_LCONTROL);  break;
        case sf::Keyboard::Key::LShift    : _execute_event(Event_type::KEYRELEASE_LSHIFT);    break;
        case sf::Keyboard::Key::LAlt      : _execute_event(Event_type::KEYRELEASE_LALT);      break;
        case sf::Keyboard::Key::LSystem   : _execute_event(Event_type::KEYRELEASE_LSYSTEM);   break;
        case sf::Keyboard::Key::RControl  : _execute_event(Event_type::KEYRELEASE_RCONTROL);  break;
        case sf::Keyboard::Key::RShift    : _execute_event(Event_type::KEYRELEASE_RSHIFT);    break;
        case sf::Keyboard::Key::RAlt      : _execute_event(Event_type::KEYRELEASE_RALT);      break;
        case sf::Keyboard::Key::RSystem   : _execute_event(Event_type::KEYRELEASE_RSYSTEM);   break;
        case sf::Keyboard::Key::Menu      : _execute_event(Event_type::KEYRELEASE_MENU);      break;
        case sf::Keyboard::Key::LBracket  : _execute_event(Event_type::KEYRELEASE_LBRACKET);  break;
        case sf::Keyboard::Key::RBracket  : _execute_event(Event_type::KEYRELEASE_RBRACKET);  break;
        case sf::Keyboard::Key::Semicolon : _execute_event(Event_type::KEYRELEASE_SEMICOLON); break;
        case sf::Keyboard::Key::Comma     : _execute_event(Event_type::KEYRELEASE_COMMA);     break;
        case sf::Keyboard::Key::Period    : _execute_event(Event_type::KEYRELEASE_PERIOD);    break;
        case sf::Keyboard::Key::Apostrophe: _execute_event(Event_type::KEYRELEASE_QUOTE);     break;
        case sf::Keyboard::Key::Slash     : _execute_event(Event_type::KEYRELEASE_SLASH);     break;
        case sf::Keyboard::Key::Backslash : _execute_event(Event_type::KEYRELEASE_BACKSLASH); break;
        case sf::Keyboard::Key::Grave     : _execute_event(Event_type::KEYRELEASE_TILDE);     break;
        case sf::Keyboard::Key::Equal     : _execute_event(Event_type::KEYRELEASE_EQUAL);     break;
        case sf::Keyboard::Key::Hyphen    : _execute_event(Event_type::KEYRELEASE_DASH);      break;
        case sf::Keyboard::Key::Space     : _execute_event(Event_type::KEYRELEASE_SPACE);     break;
        case sf::Keyboard::Key::Enter     : _execute_event(Event_type::KEYRELEASE_RETURN);    break;
        case sf::Keyboard::Key::Backspace : _execute_event(Event_type::KEYRELEASE_BACKSPACE); break;
        case sf::Keyboard::Key::Tab       : _execute_event(Event_type::KEYRELEASE_TAB);       break;
        case sf::Keyboard::Key::PageUp    : _execute_event(Event_type::KEYRELEASE_PAGEUP);    break;
        case sf::Keyboard::Key::PageDown  : _execute_event(Event_type::KEYRELEASE_PAGEDOWN);  break;
        case sf::Keyboard::Key::End       : _execute_event(Event_type::KEYRELEASE_END);       break;
        case sf::Keyboard::Key::Home      : _execute_event(Event_type::KEYRELEASE_HOME);      break;
        case sf::Keyboard::Key::Insert    : _execute_event(Event_type::KEYRELEASE_INSERT);    break;
        case sf::Keyboard::Key::Delete    : _execute_event(Event_type::KEYRELEASE_DELETE);    break;
        case sf::Keyboard::Key::Add       : _execute_event(Event_type::KEYRELEASE_ADD);       break;
        case sf::Keyboard::Key::Subtract  : _execute_event(Event_type::KEYRELEASE_SUBTRACT);  break;
        case sf::Keyboard::Key::Multiply  : _execute_event(Event_type::KEYRELEASE_MULTIPLY);  break;
        case sf::Keyboard::Key::Divide    : _execute_event(Event_type::KEYRELEASE_DIVIDE);    break;
        case sf::Keyboard::Key::Left      : _execute_event(Event_type::KEYRELEASE_LEFT);      break;
        case sf::Keyboard::Key::Right     : _execute_event(Event_type::KEYRELEASE_RIGHT);     break;
        case sf::Keyboard::Key::Up        : _execute_event(Event_type::KEYRELEASE_UP);        break;
        case sf::Keyboard::Key::Down      : _execute_event(Event_type::KEYRELEASE_DOWN);      break;
        case sf::Keyboard::Key::Numpad0   : _execute_event(Event_type::KEYRELEASE_NUMPAD0);   break;
        case sf::Keyboard::Key::Numpad1   : _execute_event(Event_type::KEYRELEASE_NUMPAD1);   break;
        case sf::Keyboard::Key::Numpad2   : _execute_event(Event_type::KEYRELEASE_NUMPAD2);   break;
        case sf::Keyboard::Key::Numpad3   : _execute_event(Event_type::KEYRELEASE_NUMPAD3);   break;
        case sf::Keyboard::Key::Numpad4   : _execute_event(Event_type::KEYRELEASE_NUMPAD4);   break;
        case sf::Keyboard::Key::Numpad5   : _execute_event(Event_type::KEYRELEASE_NUMPAD5);   break;
        case sf::Keyboard::Key::Numpad6   : _execute_event(Event_type::KEYRELEASE_NUMPAD6);   break;
        case sf::Keyboard::Key::Numpad7   : _execute_event(Event_type::KEYRELEASE_NUMPAD7);   break;
        case sf::Keyboard::Key::Numpad8   : _execute_event(Event_type::KEYRELEASE_NUMPAD8);   break;
        case sf::Keyboard::Key::Numpad9   : _execute_event(Event_type::KEYRELEASE_NUMPAD9);   break;
        case sf::Keyboard::Key::F1        : _execute_event(Event_type::KEYRELEASE_F1);        break;
        case sf::Keyboard::Key::F2        : _execute_event(Event_type::KEYRELEASE_F2);        break;
        case sf::Keyboard::Key::F3        : _execute_event(Event_type::KEYRELEASE_F3);        break;
        case sf::Keyboard::Key::F4        : _execute_event(Event_type::KEYRELEASE_F4);        break;
        case sf::Keyboard::Key::F5        : _execute_event(Event_type::KEYRELEASE_F5);        break;
        case sf::Keyboard::Key::F6        : _execute_event(Event_type::KEYRELEASE_F6);        break;
        case sf::Keyboard::Key::F7        : _execute_event(Event_type::KEYRELEASE_F7);        break;
        case sf::Keyboard::Key::F8        : _execute_event(Event_type::KEYRELEASE_F8);        break;
        case sf::Keyboard::Key::F9        : _execute_event(Event_type::KEYRELEASE_F9);        break;
        case sf::Keyboard::Key::F10       : _execute_event(Event_type::KEYRELEASE_F10);       break;
        case sf::Keyboard::Key::F11       : _execute_event(Event_type::KEYRELEASE_F11);       break;
        case sf::Keyboard::Key::F12       : _execute_event(Event_type::KEYRELEASE_F12);       break;
        case sf::Keyboard::Key::F13       : _execute_event(Event_type::KEYRELEASE_F13);       break;
        case sf::Keyboard::Key::F14       : _execute_event(Event_type::KEYRELEASE_F14);       break;
        case sf::Keyboard::Key::F15       : _execute_event(Event_type::KEYRELEASE_F15);       break;
        case sf::Keyboard::Key::Pause     : _execute_event(Event_type::KEYRELEASE_PAUSE);     break;
        }
    }
}

} // namespace mirelight::events
