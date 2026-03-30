#ifndef MENUS_MENU_DEFS
#define MENUS_MENU_DEFS

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include <ostream>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Enums
// ---------------------------------------------------------------------------

enum class Menu_id {

    UNDEFINED,
    MAIN,
    SETTINGS
};
inline std::ostream& operator<<(std::ostream& os, Menu_id const menu_id) {

    switch (menu_id) {

        case Menu_id::MAIN: return os << "MAIN";
        case Menu_id::SETTINGS: return os << "SETTINGS";

        default: return os << "UNKNOW_MENU_ID";
    }
}

} // namespace mirelight::menus

#endif
