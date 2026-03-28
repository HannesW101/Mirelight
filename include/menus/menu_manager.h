#ifndef MENUS_MENU_MANAGER
#define MENUS_MENU_MANAGER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu_defs.h"
#include "menus/menu.h"

#include <SFML/Graphics.hpp>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Class Menu_manager
// ---------------------------------------------------------------------------

class Menu_manager final {

public:
    static Menu_manager& get_instance(sf::RenderWindow* window);

    void change_menu(Menu_id const menu_id);

    void draw();

    void update(float const dt);

    ~Menu_manager          (                   );
    Menu_manager           (Menu_manager const&) = delete;
    Menu_manager& operator=(Menu_manager const&) = delete;
    Menu_manager           (Menu_manager&&     ) = delete;
    Menu_manager& operator=(Menu_manager&&     ) = delete;

private:
    Menu_manager(sf::RenderWindow* window);

    Menu_id _curr_menu_id;
    Menu* _curr_menu;

    sf::RenderWindow* _window;
};

} // namespace mirelight::menus

#endif
