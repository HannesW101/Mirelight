#ifndef EVENTS_EVENT_DEFS
#define EVENTS_EVENT_DEFS

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include <ostream>
#include <vector>
#include <functional>
#include <typeindex>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::events {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using Event_vec = std::vector<std::function<void()> >;

// ===========================================================================
// Enums
// ---------------------------------------------------------------------------

enum class Event_type {

    // ===========================================================================
    // Non-keyboard events
    // ---------------------------------------------------------------------------
    WINDOW_CLOSED,
    WINDOW_RESIZED,
    WINDOW_LOST_FOCUS,
    WINDOW_GAINED_FOCUS,
    WINDOW_TEXT_ENTERED,

    MOUSE_MOVED,
    MOUSE_BUTTON_LEFT_PRESS,
    MOUSE_BUTTON_RIGHT_PRESS,
    MOUSE_BUTTON_MIDDLE_PRESS,
    MOUSE_BUTTON_EXTRA_1_PRESS,
    MOUSE_BUTTON_EXTRA_2_PRESS,
    MOUSE_BUTTON_LEFT_RELEASE,
    MOUSE_BUTTON_RIGHT_RELEASE,
    MOUSE_BUTTON_MIDDLE_RELEASE,
    MOUSE_BUTTON_EXTRA_1_RELEASE,
    MOUSE_BUTTON_EXTRA_2_RELEASE,
    MOUSE_WHEEL_UP,
    MOUSE_WHEEL_DOWN,
    MOUSE_ENTER_WINDOW,
    MOUSE_LEAVE_WINDOW,

    JOYSTICK_BUTTON_PRESSED,
    JOYSTICK_BUTTON_RELEASED,
    JOYSTICK_MOVED,
    JOYSTICK_CONNECTED,
    JOYSTICK_DISCONNECTED,

    TOUCH_BEGAN,
    TOUCH_MOVED,
    TOUCH_ENDED,

    SENSOR_CHANGED,

    // ===========================================================================
    // Keyboard pressed events
    // ---------------------------------------------------------------------------
    KEYPRESS_A,
    KEYPRESS_B,
    KEYPRESS_C,
    KEYPRESS_D,
    KEYPRESS_E,
    KEYPRESS_F,
    KEYPRESS_G,
    KEYPRESS_H,
    KEYPRESS_I,
    KEYPRESS_J,
    KEYPRESS_K,
    KEYPRESS_L,
    KEYPRESS_M,
    KEYPRESS_N,
    KEYPRESS_O,
    KEYPRESS_P,
    KEYPRESS_Q,
    KEYPRESS_R,
    KEYPRESS_S,
    KEYPRESS_T,
    KEYPRESS_U,
    KEYPRESS_V,
    KEYPRESS_W,
    KEYPRESS_X,
    KEYPRESS_Y,
    KEYPRESS_Z,

    KEYPRESS_NUM0,
    KEYPRESS_NUM1,
    KEYPRESS_NUM2,
    KEYPRESS_NUM3,
    KEYPRESS_NUM4,
    KEYPRESS_NUM5,
    KEYPRESS_NUM6,
    KEYPRESS_NUM7,
    KEYPRESS_NUM8,
    KEYPRESS_NUM9,

    KEYPRESS_ESCAPE,
    KEYPRESS_LCONTROL,
    KEYPRESS_LSHIFT,
    KEYPRESS_LALT,
    KEYPRESS_LSYSTEM,
    KEYPRESS_RCONTROL,
    KEYPRESS_RSHIFT,
    KEYPRESS_RALT,
    KEYPRESS_RSYSTEM,
    KEYPRESS_MENU,
    KEYPRESS_LBRACKET,
    KEYPRESS_RBRACKET,
    KEYPRESS_SEMICOLON,
    KEYPRESS_COMMA,
    KEYPRESS_PERIOD,
    KEYPRESS_QUOTE,
    KEYPRESS_SLASH,
    KEYPRESS_BACKSLASH,
    KEYPRESS_TILDE,
    KEYPRESS_EQUAL,
    KEYPRESS_DASH,
    KEYPRESS_SPACE,
    KEYPRESS_RETURN,
    KEYPRESS_BACKSPACE,
    KEYPRESS_TAB,
    KEYPRESS_PAGEUP,
    KEYPRESS_PAGEDOWN,
    KEYPRESS_END,
    KEYPRESS_HOME,
    KEYPRESS_INSERT,
    KEYPRESS_DELETE,
    KEYPRESS_ADD,
    KEYPRESS_SUBTRACT,
    KEYPRESS_MULTIPLY,
    KEYPRESS_DIVIDE,
    KEYPRESS_LEFT,
    KEYPRESS_RIGHT,
    KEYPRESS_UP,
    KEYPRESS_DOWN,
    KEYPRESS_NUMPAD0,
    KEYPRESS_NUMPAD1,
    KEYPRESS_NUMPAD2,
    KEYPRESS_NUMPAD3,
    KEYPRESS_NUMPAD4,
    KEYPRESS_NUMPAD5,
    KEYPRESS_NUMPAD6,
    KEYPRESS_NUMPAD7,
    KEYPRESS_NUMPAD8,
    KEYPRESS_NUMPAD9,
    KEYPRESS_F1,
    KEYPRESS_F2,
    KEYPRESS_F3,
    KEYPRESS_F4,
    KEYPRESS_F5,
    KEYPRESS_F6,
    KEYPRESS_F7,
    KEYPRESS_F8,
    KEYPRESS_F9,
    KEYPRESS_F10,
    KEYPRESS_F11,
    KEYPRESS_F12,
    KEYPRESS_F13,
    KEYPRESS_F14,
    KEYPRESS_F15,
    KEYPRESS_PAUSE,

    // ===========================================================================
    // Keyboard released events
    // ---------------------------------------------------------------------------
    KEYRELEASE_A,
    KEYRELEASE_B,
    KEYRELEASE_C,
    KEYRELEASE_D,
    KEYRELEASE_E,
    KEYRELEASE_F,
    KEYRELEASE_G,
    KEYRELEASE_H,
    KEYRELEASE_I,
    KEYRELEASE_J,
    KEYRELEASE_K,
    KEYRELEASE_L,
    KEYRELEASE_M,
    KEYRELEASE_N,
    KEYRELEASE_O,
    KEYRELEASE_P,
    KEYRELEASE_Q,
    KEYRELEASE_R,
    KEYRELEASE_S,
    KEYRELEASE_T,
    KEYRELEASE_U,
    KEYRELEASE_V,
    KEYRELEASE_W,
    KEYRELEASE_X,
    KEYRELEASE_Y,
    KEYRELEASE_Z,

    KEYRELEASE_NUM0,
    KEYRELEASE_NUM1,
    KEYRELEASE_NUM2,
    KEYRELEASE_NUM3,
    KEYRELEASE_NUM4,
    KEYRELEASE_NUM5,
    KEYRELEASE_NUM6,
    KEYRELEASE_NUM7,
    KEYRELEASE_NUM8,
    KEYRELEASE_NUM9,

    KEYRELEASE_ESCAPE,
    KEYRELEASE_LCONTROL,
    KEYRELEASE_LSHIFT,
    KEYRELEASE_LALT,
    KEYRELEASE_LSYSTEM,
    KEYRELEASE_RCONTROL,
    KEYRELEASE_RSHIFT,
    KEYRELEASE_RALT,
    KEYRELEASE_RSYSTEM,
    KEYRELEASE_MENU,
    KEYRELEASE_LBRACKET,
    KEYRELEASE_RBRACKET,
    KEYRELEASE_SEMICOLON,
    KEYRELEASE_COMMA,
    KEYRELEASE_PERIOD,
    KEYRELEASE_QUOTE,
    KEYRELEASE_SLASH,
    KEYRELEASE_BACKSLASH,
    KEYRELEASE_TILDE,
    KEYRELEASE_EQUAL,
    KEYRELEASE_DASH,
    KEYRELEASE_SPACE,
    KEYRELEASE_RETURN,
    KEYRELEASE_BACKSPACE,
    KEYRELEASE_TAB,
    KEYRELEASE_PAGEUP,
    KEYRELEASE_PAGEDOWN,
    KEYRELEASE_END,
    KEYRELEASE_HOME,
    KEYRELEASE_INSERT,
    KEYRELEASE_DELETE,
    KEYRELEASE_ADD,
    KEYRELEASE_SUBTRACT,
    KEYRELEASE_MULTIPLY,
    KEYRELEASE_DIVIDE,
    KEYRELEASE_LEFT,
    KEYRELEASE_RIGHT,
    KEYRELEASE_UP,
    KEYRELEASE_DOWN,
    KEYRELEASE_NUMPAD0,
    KEYRELEASE_NUMPAD1,
    KEYRELEASE_NUMPAD2,
    KEYRELEASE_NUMPAD3,
    KEYRELEASE_NUMPAD4,
    KEYRELEASE_NUMPAD5,
    KEYRELEASE_NUMPAD6,
    KEYRELEASE_NUMPAD7,
    KEYRELEASE_NUMPAD8,
    KEYRELEASE_NUMPAD9,
    KEYRELEASE_F1,
    KEYRELEASE_F2,
    KEYRELEASE_F3,
    KEYRELEASE_F4,
    KEYRELEASE_F5,
    KEYRELEASE_F6,
    KEYRELEASE_F7,
    KEYRELEASE_F8,
    KEYRELEASE_F9,
    KEYRELEASE_F10,
    KEYRELEASE_F11,
    KEYRELEASE_F12,
    KEYRELEASE_F13,
    KEYRELEASE_F14,
    KEYRELEASE_F15,
    KEYRELEASE_PAUSE,

    // ===========================================================================
    // Special events
    // ---------------------------------------------------------------------------
    HOVER,
    STOP_HOVER
};
inline std::ostream& operator<<(std::ostream& os, Event_type const menu_id) {

    switch (menu_id) {

        //case Menu_id::MAIN: return os << "MAIN";
    case Event_type::WINDOW_CLOSED: return os << "WINDOW_CLOSED";
    case Event_type::WINDOW_RESIZED: return os << "WINDOW_RESIZED";
    case Event_type::WINDOW_LOST_FOCUS: return os << "WINDOW_LOST_FOCUS";
    case Event_type::WINDOW_GAINED_FOCUS: return os << "WINDOW_GAINED_FOCUS";
    case Event_type::WINDOW_TEXT_ENTERED: return os << "WINDOW_TEXT_ENTERED";
    case Event_type::MOUSE_MOVED: return os << "MOUSE_MOVED";
    case Event_type::MOUSE_BUTTON_LEFT_PRESS: return os << "MOUSE_BUTTON_LEFT_PRESS";
    case Event_type::MOUSE_BUTTON_RIGHT_PRESS: return os << "MOUSE_BUTTON_RIGHT_PRESS";
    case Event_type::MOUSE_BUTTON_MIDDLE_PRESS: return os << "MOUSE_BUTTON_MIDDLE_PRESS";
    case Event_type::MOUSE_BUTTON_EXTRA_1_PRESS: return os << "MOUSE_BUTTON_EXTRA_1_PRESS";
    case Event_type::MOUSE_BUTTON_EXTRA_2_PRESS: return os << "MOUSE_BUTTON_EXTRA_2_PRESS";
    case Event_type::MOUSE_BUTTON_LEFT_RELEASE: return os << "MOUSE_BUTTON_LEFT_RELEASE";
    case Event_type::MOUSE_BUTTON_RIGHT_RELEASE: return os << "MOUSE_BUTTON_RIGHT_RELEASE";
    case Event_type::MOUSE_BUTTON_MIDDLE_RELEASE: return os << "MOUSE_BUTTON_MIDDLE_RELEASE";
    case Event_type::MOUSE_BUTTON_EXTRA_1_RELEASE: return os << "MOUSE_BUTTON_EXTRA_1_RELEASE";
    case Event_type::MOUSE_BUTTON_EXTRA_2_RELEASE: return os << "MOUSE_BUTTON_EXTRA_2_RELEASE";
    case Event_type::MOUSE_WHEEL_UP: return os << "MOUSE_WHEEL_UP";
    case Event_type::MOUSE_WHEEL_DOWN: return os << "MOUSE_WHEEL_DOWN";
    case Event_type::MOUSE_ENTER_WINDOW: return os << "MOUSE_ENTER_WINDOW";
    case Event_type::MOUSE_LEAVE_WINDOW: return os << "MOUSE_LEAVE_WINDOW";
    case Event_type::JOYSTICK_BUTTON_PRESSED: return os << "JOYSTICK_BUTTON_PRESSED";
    case Event_type::JOYSTICK_BUTTON_RELEASED: return os << "JOYSTICK_BUTTON_RELEASED";
    case Event_type::JOYSTICK_MOVED: return os << "JOYSTICK_MOVED";
    case Event_type::JOYSTICK_CONNECTED: return os << "JOYSTICK_CONNECTED";
    case Event_type::JOYSTICK_DISCONNECTED: return os << "JOYSTICK_DISCONNECTED";
    case Event_type::TOUCH_BEGAN: return os << "TOUCH_BEGAN";
    case Event_type::TOUCH_MOVED: return os << "TOUCH_MOVED";
    case Event_type::TOUCH_ENDED: return os << "TOUCH_ENDED";
    case Event_type::SENSOR_CHANGED: return os << "SENSOR_CHANGED";
    case Event_type::KEYPRESS_A: return os << "KEYPRESS_A";
    case Event_type::KEYPRESS_B: return os << "KEYPRESS_B";
    case Event_type::KEYPRESS_C: return os << "KEYPRESS_C";
    case Event_type::KEYPRESS_D: return os << "KEYPRESS_D";
    case Event_type::KEYPRESS_E: return os << "KEYPRESS_E";
    case Event_type::KEYPRESS_F: return os << "KEYPRESS_F";
    case Event_type::KEYPRESS_G: return os << "KEYPRESS_G";
    case Event_type::KEYPRESS_H: return os << "KEYPRESS_H";
    case Event_type::KEYPRESS_I: return os << "KEYPRESS_I";
    case Event_type::KEYPRESS_J: return os << "KEYPRESS_J";
    case Event_type::KEYPRESS_K: return os << "KEYPRESS_K";
    case Event_type::KEYPRESS_L: return os << "KEYPRESS_L";
    case Event_type::KEYPRESS_M: return os << "KEYPRESS_M";
    case Event_type::KEYPRESS_N: return os << "KEYPRESS_N";
    case Event_type::KEYPRESS_O: return os << "KEYPRESS_O";
    case Event_type::KEYPRESS_P: return os << "KEYPRESS_P";
    case Event_type::KEYPRESS_Q: return os << "KEYPRESS_Q";
    case Event_type::KEYPRESS_R: return os << "KEYPRESS_R";
    case Event_type::KEYPRESS_S: return os << "KEYPRESS_S";
    case Event_type::KEYPRESS_T: return os << "KEYPRESS_T";
    case Event_type::KEYPRESS_U: return os << "KEYPRESS_U";
    case Event_type::KEYPRESS_V: return os << "KEYPRESS_V";
    case Event_type::KEYPRESS_W: return os << "KEYPRESS_W";
    case Event_type::KEYPRESS_X: return os << "KEYPRESS_X";
    case Event_type::KEYPRESS_Y: return os << "KEYPRESS_Y";
    case Event_type::KEYPRESS_Z: return os << "KEYPRESS_Z";
    case Event_type::KEYPRESS_NUM0: return os << "KEYPRESS_NUM0";
    case Event_type::KEYPRESS_NUM1: return os << "KEYPRESS_NUM1";
    case Event_type::KEYPRESS_NUM2: return os << "KEYPRESS_NUM2";
    case Event_type::KEYPRESS_NUM3: return os << "KEYPRESS_NUM3";
    case Event_type::KEYPRESS_NUM4: return os << "KEYPRESS_NUM4";
    case Event_type::KEYPRESS_NUM5: return os << "KEYPRESS_NUM5";
    case Event_type::KEYPRESS_NUM6: return os << "KEYPRESS_NUM6";
    case Event_type::KEYPRESS_NUM7: return os << "KEYPRESS_NUM7";
    case Event_type::KEYPRESS_NUM8: return os << "KEYPRESS_NUM8";
    case Event_type::KEYPRESS_NUM9: return os << "KEYPRESS_NUM9";
    case Event_type::KEYPRESS_ESCAPE: return os << "KEYPRESS_ESCAPE";
    case Event_type::KEYPRESS_LCONTROL: return os << "KEYPRESS_LCONTROL";
    case Event_type::KEYPRESS_LSHIFT: return os << "KEYPRESS_LSHIFT";
    case Event_type::KEYPRESS_LALT: return os << "KEYPRESS_LALT";
    case Event_type::KEYPRESS_LSYSTEM: return os << "KEYPRESS_LSYSTEM";
    case Event_type::KEYPRESS_RCONTROL: return os << "KEYPRESS_RCONTROL";
    case Event_type::KEYPRESS_RSHIFT: return os << "KEYPRESS_RSHIFT";
    case Event_type::KEYPRESS_RALT: return os << "KEYPRESS_RALT";
    case Event_type::KEYPRESS_RSYSTEM: return os << "KEYPRESS_RSYSTEM";
    case Event_type::KEYPRESS_MENU: return os << "KEYPRESS_MENU";
    case Event_type::KEYPRESS_LBRACKET: return os << "KEYPRESS_LBRACKET";
    case Event_type::KEYPRESS_RBRACKET: return os << "KEYPRESS_RBRACKET";
    case Event_type::KEYPRESS_SEMICOLON: return os << "KEYPRESS_SEMICOLON";
    case Event_type::KEYPRESS_COMMA: return os << "KEYPRESS_COMMA";
    case Event_type::KEYPRESS_PERIOD: return os << "KEYPRESS_PERIOD";
    case Event_type::KEYPRESS_QUOTE: return os << "KEYPRESS_QUOTE";
    case Event_type::KEYPRESS_SLASH: return os << "KEYPRESS_SLASH";
    case Event_type::KEYPRESS_BACKSLASH: return os << "KEYPRESS_BACKSLASH";
    case Event_type::KEYPRESS_TILDE: return os << "KEYPRESS_TILDE";
    case Event_type::KEYPRESS_EQUAL: return os << "KEYPRESS_EQUAL";
    case Event_type::KEYPRESS_DASH: return os << "KEYPRESS_DASH";
    case Event_type::KEYPRESS_SPACE: return os << "KEYPRESS_SPACE";
    case Event_type::KEYPRESS_RETURN: return os << "KEYPRESS_RETURN";
    case Event_type::KEYPRESS_BACKSPACE: return os << "KEYPRESS_BACKSPACE";
    case Event_type::KEYPRESS_TAB: return os << "KEYPRESS_TAB";
    case Event_type::KEYPRESS_PAGEUP: return os << "KEYPRESS_PAGEUP";
    case Event_type::KEYPRESS_PAGEDOWN: return os << "KEYPRESS_PAGEDOWN";
    case Event_type::KEYPRESS_END: return os << "KEYPRESS_END";
    case Event_type::KEYPRESS_HOME: return os << "KEYPRESS_HOME";
    case Event_type::KEYPRESS_INSERT: return os << "KEYPRESS_INSERT";
    case Event_type::KEYPRESS_DELETE: return os << "KEYPRESS_DELETE";
    case Event_type::KEYPRESS_ADD: return os << "KEYPRESS_ADD";
    case Event_type::KEYPRESS_SUBTRACT: return os << "KEYPRESS_SUBTRACT";
    case Event_type::KEYPRESS_MULTIPLY: return os << "KEYPRESS_MULTIPLY";
    case Event_type::KEYPRESS_DIVIDE: return os << "KEYPRESS_DIVIDE";
    case Event_type::KEYPRESS_LEFT: return os << "KEYPRESS_LEFT";
    case Event_type::KEYPRESS_RIGHT: return os << "KEYPRESS_RIGHT";
    case Event_type::KEYPRESS_UP: return os << "KEYPRESS_UP";
    case Event_type::KEYPRESS_DOWN: return os << "KEYPRESS_DOWN";
    case Event_type::KEYPRESS_NUMPAD0: return os << "KEYPRESS_NUMPAD0";
    case Event_type::KEYPRESS_NUMPAD1: return os << "KEYPRESS_NUMPAD1";
    case Event_type::KEYPRESS_NUMPAD2: return os << "KEYPRESS_NUMPAD2";
    case Event_type::KEYPRESS_NUMPAD3: return os << "KEYPRESS_NUMPAD3";
    case Event_type::KEYPRESS_NUMPAD4: return os << "KEYPRESS_NUMPAD4";
    case Event_type::KEYPRESS_NUMPAD5: return os << "KEYPRESS_NUMPAD5";
    case Event_type::KEYPRESS_NUMPAD6: return os << "KEYPRESS_NUMPAD6";
    case Event_type::KEYPRESS_NUMPAD7: return os << "KEYPRESS_NUMPAD7";
    case Event_type::KEYPRESS_NUMPAD8: return os << "KEYPRESS_NUMPAD8";
    case Event_type::KEYPRESS_NUMPAD9: return os << "KEYPRESS_NUMPAD9";
    case Event_type::KEYPRESS_F1: return os << "KEYPRESS_F1";
    case Event_type::KEYPRESS_F2: return os << "KEYPRESS_F2";
    case Event_type::KEYPRESS_F3: return os << "KEYPRESS_F3";
    case Event_type::KEYPRESS_F4: return os << "KEYPRESS_F4";
    case Event_type::KEYPRESS_F5: return os << "KEYPRESS_F5";
    case Event_type::KEYPRESS_F6: return os << "KEYPRESS_F6";
    case Event_type::KEYPRESS_F7: return os << "KEYPRESS_F7";
    case Event_type::KEYPRESS_F8: return os << "KEYPRESS_F8";
    case Event_type::KEYPRESS_F9: return os << "KEYPRESS_F9";
    case Event_type::KEYPRESS_F10: return os << "KEYPRESS_F10";
    case Event_type::KEYPRESS_F11: return os << "KEYPRESS_F11";
    case Event_type::KEYPRESS_F12: return os << "KEYPRESS_F12";
    case Event_type::KEYPRESS_F13: return os << "KEYPRESS_F13";
    case Event_type::KEYPRESS_F14: return os << "KEYPRESS_F14";
    case Event_type::KEYPRESS_F15: return os << "KEYPRESS_F15";
    case Event_type::KEYPRESS_PAUSE: return os << "KEYPRESS_PAUSE";
    case Event_type::KEYRELEASE_A: return os << "KEYRELEASE_A";
    case Event_type::KEYRELEASE_B: return os << "KEYRELEASE_B";
    case Event_type::KEYRELEASE_C: return os << "KEYRELEASE_C";
    case Event_type::KEYRELEASE_D: return os << "KEYRELEASE_D";
    case Event_type::KEYRELEASE_E: return os << "KEYRELEASE_E";
    case Event_type::KEYRELEASE_F: return os << "KEYRELEASE_F";
    case Event_type::KEYRELEASE_G: return os << "KEYRELEASE_G";
    case Event_type::KEYRELEASE_H: return os << "KEYRELEASE_H";
    case Event_type::KEYRELEASE_I: return os << "KEYRELEASE_I";
    case Event_type::KEYRELEASE_J: return os << "KEYRELEASE_J";
    case Event_type::KEYRELEASE_K: return os << "KEYRELEASE_K";
    case Event_type::KEYRELEASE_L: return os << "KEYRELEASE_L";
    case Event_type::KEYRELEASE_M: return os << "KEYRELEASE_M";
    case Event_type::KEYRELEASE_N: return os << "KEYRELEASE_N";
    case Event_type::KEYRELEASE_O: return os << "KEYRELEASE_O";
    case Event_type::KEYRELEASE_P: return os << "KEYRELEASE_P";
    case Event_type::KEYRELEASE_Q: return os << "KEYRELEASE_Q";
    case Event_type::KEYRELEASE_R: return os << "KEYRELEASE_R";
    case Event_type::KEYRELEASE_S: return os << "KEYRELEASE_S";
    case Event_type::KEYRELEASE_T: return os << "KEYRELEASE_T";
    case Event_type::KEYRELEASE_U: return os << "KEYRELEASE_U";
    case Event_type::KEYRELEASE_V: return os << "KEYRELEASE_V";
    case Event_type::KEYRELEASE_W: return os << "KEYRELEASE_W";
    case Event_type::KEYRELEASE_X: return os << "KEYRELEASE_X";
    case Event_type::KEYRELEASE_Y: return os << "KEYRELEASE_Y";
    case Event_type::KEYRELEASE_Z: return os << "KEYRELEASE_Z";
    case Event_type::KEYRELEASE_NUM0: return os << "KEYRELEASE_NUM0";
    case Event_type::KEYRELEASE_NUM1: return os << "KEYRELEASE_NUM1";
    case Event_type::KEYRELEASE_NUM2: return os << "KEYRELEASE_NUM2";
    case Event_type::KEYRELEASE_NUM3: return os << "KEYRELEASE_NUM3";
    case Event_type::KEYRELEASE_NUM4: return os << "KEYRELEASE_NUM4";
    case Event_type::KEYRELEASE_NUM5: return os << "KEYRELEASE_NUM5";
    case Event_type::KEYRELEASE_NUM6: return os << "KEYRELEASE_NUM6";
    case Event_type::KEYRELEASE_NUM7: return os << "KEYRELEASE_NUM7";
    case Event_type::KEYRELEASE_NUM8: return os << "KEYRELEASE_NUM8";
    case Event_type::KEYRELEASE_NUM9: return os << "KEYRELEASE_NUM9";
    case Event_type::KEYRELEASE_ESCAPE: return os << "KEYRELEASE_ESCAPE";
    case Event_type::KEYRELEASE_LCONTROL: return os << "KEYRELEASE_LCONTROL";
    case Event_type::KEYRELEASE_LSHIFT: return os << "KEYRELEASE_LSHIFT";
    case Event_type::KEYRELEASE_LALT: return os << "KEYRELEASE_LALT";
    case Event_type::KEYRELEASE_LSYSTEM: return os << "KEYRELEASE_LSYSTEM";
    case Event_type::KEYRELEASE_RCONTROL: return os << "KEYRELEASE_RCONTROL";
    case Event_type::KEYRELEASE_RSHIFT: return os << "KEYRELEASE_RSHIFT";
    case Event_type::KEYRELEASE_RALT: return os << "KEYRELEASE_RALT";
    case Event_type::KEYRELEASE_RSYSTEM: return os << "KEYRELEASE_RSYSTEM";
    case Event_type::KEYRELEASE_MENU: return os << "KEYRELEASE_MENU";
    case Event_type::KEYRELEASE_LBRACKET: return os << "KEYRELEASE_LBRACKET";
    case Event_type::KEYRELEASE_RBRACKET: return os << "KEYRELEASE_RBRACKET";
    case Event_type::KEYRELEASE_SEMICOLON: return os << "KEYRELEASE_SEMICOLON";
    case Event_type::KEYRELEASE_COMMA: return os << "KEYRELEASE_COMMA";
    case Event_type::KEYRELEASE_PERIOD: return os << "KEYRELEASE_PERIOD";
    case Event_type::KEYRELEASE_QUOTE: return os << "KEYRELEASE_QUOTE";
    case Event_type::KEYRELEASE_SLASH: return os << "KEYRELEASE_SLASH";
    case Event_type::KEYRELEASE_BACKSLASH: return os << "KEYRELEASE_BACKSLASH";
    case Event_type::KEYRELEASE_TILDE: return os << "KEYRELEASE_TILDE";
    case Event_type::KEYRELEASE_EQUAL: return os << "KEYRELEASE_EQUAL";
    case Event_type::KEYRELEASE_DASH: return os << "KEYRELEASE_DASH";
    case Event_type::KEYRELEASE_SPACE: return os << "KEYRELEASE_SPACE";
    case Event_type::KEYRELEASE_RETURN: return os << "KEYRELEASE_RETURN";
    case Event_type::KEYRELEASE_BACKSPACE: return os << "KEYRELEASE_BACKSPACE";
    case Event_type::KEYRELEASE_TAB: return os << "KEYRELEASE_TAB";
    case Event_type::KEYRELEASE_PAGEUP: return os << "KEYRELEASE_PAGEUP";
    case Event_type::KEYRELEASE_PAGEDOWN: return os << "KEYRELEASE_PAGEDOWN";
    case Event_type::KEYRELEASE_END: return os << "KEYRELEASE_END";
    case Event_type::KEYRELEASE_HOME: return os << "KEYRELEASE_HOME";
    case Event_type::KEYRELEASE_INSERT: return os << "KEYRELEASE_INSERT";
    case Event_type::KEYRELEASE_DELETE: return os << "KEYRELEASE_DELETE";
    case Event_type::KEYRELEASE_ADD: return os << "KEYRELEASE_ADD";
    case Event_type::KEYRELEASE_SUBTRACT: return os << "KEYRELEASE_SUBTRACT";
    case Event_type::KEYRELEASE_MULTIPLY: return os << "KEYRELEASE_MULTIPLY";
    case Event_type::KEYRELEASE_DIVIDE: return os << "KEYRELEASE_DIVIDE";
    case Event_type::KEYRELEASE_LEFT: return os << "KEYRELEASE_LEFT";
    case Event_type::KEYRELEASE_RIGHT: return os << "KEYRELEASE_RIGHT";
    case Event_type::KEYRELEASE_UP: return os << "KEYRELEASE_UP";
    case Event_type::KEYRELEASE_DOWN: return os << "KEYRELEASE_DOWN";
    case Event_type::KEYRELEASE_NUMPAD0: return os << "KEYRELEASE_NUMPAD0";
    case Event_type::KEYRELEASE_NUMPAD1: return os << "KEYRELEASE_NUMPAD1";
    case Event_type::KEYRELEASE_NUMPAD2: return os << "KEYRELEASE_NUMPAD2";
    case Event_type::KEYRELEASE_NUMPAD3: return os << "KEYRELEASE_NUMPAD3";
    case Event_type::KEYRELEASE_NUMPAD4: return os << "KEYRELEASE_NUMPAD4";
    case Event_type::KEYRELEASE_NUMPAD5: return os << "KEYRELEASE_NUMPAD5";
    case Event_type::KEYRELEASE_NUMPAD6: return os << "KEYRELEASE_NUMPAD6";
    case Event_type::KEYRELEASE_NUMPAD7: return os << "KEYRELEASE_NUMPAD7";
    case Event_type::KEYRELEASE_NUMPAD8: return os << "KEYRELEASE_NUMPAD8";
    case Event_type::KEYRELEASE_NUMPAD9: return os << "KEYRELEASE_NUMPAD9";
    case Event_type::KEYRELEASE_F1: return os << "KEYRELEASE_F1";
    case Event_type::KEYRELEASE_F2: return os << "KEYRELEASE_F2";
    case Event_type::KEYRELEASE_F3: return os << "KEYRELEASE_F3";
    case Event_type::KEYRELEASE_F4: return os << "KEYRELEASE_F4";
    case Event_type::KEYRELEASE_F5: return os << "KEYRELEASE_F5";
    case Event_type::KEYRELEASE_F6: return os << "KEYRELEASE_F6";
    case Event_type::KEYRELEASE_F7: return os << "KEYRELEASE_F7";
    case Event_type::KEYRELEASE_F8: return os << "KEYRELEASE_F8";
    case Event_type::KEYRELEASE_F9: return os << "KEYRELEASE_F9";
    case Event_type::KEYRELEASE_F10: return os << "KEYRELEASE_F10";
    case Event_type::KEYRELEASE_F11: return os << "KEYRELEASE_F11";
    case Event_type::KEYRELEASE_F12: return os << "KEYRELEASE_F12";
    case Event_type::KEYRELEASE_F13: return os << "KEYRELEASE_F13";
    case Event_type::KEYRELEASE_F14: return os << "KEYRELEASE_F14";
    case Event_type::KEYRELEASE_F15: return os << "KEYRELEASE_F15";
    case Event_type::KEYRELEASE_PAUSE: return os << "KEYRELEASE_PAUSE";
    case Event_type::HOVER: return os << "HOVER";
    case Event_type::STOP_HOVER: return os << "STOP_HOVER";

    default: return os << "UNKNOW_EVENT_TYPE";
    }
}

// ===========================================================================
// Structs
// ---------------------------------------------------------------------------

struct Event_id {

    std::type_index caller_id;
    Event_type      event_type;

    auto operator<=>(Event_id const& other) const = default;
};

} // namespace mirelight::events

#endif
