// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu_manager.h"
#include "utils/logger.h"
#include "menus/menu_main.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Class Menu_manager
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Menu_manager& Menu_manager::get_instance(sf::RenderWindow* window) {

    static Menu_manager instance(window);
    return instance;
}

// ---------------------------------------------------------------------------
void Menu_manager::change_menu(Menu_id const menu_id) {

    if (_curr_menu_id == menu_id) {

        LOG(WARNING) << "Attempting to change to current menu [" << menu_id << ']';
        return;
    }

    if (_curr_menu != nullptr) {

        delete _curr_menu;
    }

    switch (menu_id) {

        case Menu_id::MAIN: { _curr_menu = new Menu_main(_window); _curr_menu_id = menu_id; break; }

        default: LOG(WARNING) << "Could not change menu, unknown menu ID [" << menu_id << ']';
    }
}

// ---------------------------------------------------------------------------
void Menu_manager::draw() {

    if (_curr_menu == nullptr) {

        LOG(ERROR) << "Cannot draw menu, nullptr";
    } else {

        _curr_menu->draw();
    }
}

// ---------------------------------------------------------------------------
void Menu_manager::update(float const dt) {

    if (_curr_menu == nullptr) {

        LOG(ERROR) << "Cannot update menu, nullptr";
    } else {

        _curr_menu->update(dt);
    }
}

// ---------------------------------------------------------------------------
Menu_manager::~Menu_manager() {

    if (_curr_menu != nullptr) {

        delete _curr_menu;
    }
}

// ---------------------------------------------------------------------------
Menu_manager::Menu_manager(sf::RenderWindow* window)
    : _curr_menu_id(Menu_id::UNDEFINED)
    , _curr_menu(nullptr)
    , _window(window)
    {

    _curr_menu = new Menu_main(_window);
    _curr_menu_id = Menu_id::MAIN;
}

} // namespace mirelight::menus
