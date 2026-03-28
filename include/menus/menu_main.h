#ifndef MENUS_MENU_MAIN
#define MENUS_MENU_MAIN

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Class Menu_main
// ---------------------------------------------------------------------------

class Menu_main final : public Menu {

public:
    Menu_main(sf::RenderWindow* window);
    ~Menu_main();

    void draw();

    Menu_main           (Menu_main const&) = delete;
    Menu_main& operator=(Menu_main const&) = delete;
    Menu_main           (Menu_main&&     ) = delete;
    Menu_main& operator=(Menu_main&&     ) = delete;

private:
    void _create_backgrounds();
    void _create_background_box();
    void _create_title_banner();
    void _create_title_text();

    void _setup_view();
    void _update_moving_background();
    void _update_following_ui_elements();

    sf::Sprite* _background_middle;
    sf::Sprite* _background_right;
    float       _background_moving_delta;

    sf::Sprite* _background_box;

    sf::Sprite* _title_banner;
    sf::Text*   _title_text;

    //sf::Sprite* _btn_exit;
    //sf::Sprite* _btn_new_game;
    //sf::Sprite* _btn_continue;
    //sf::Sprite* _btn_settings;
};

} // namespace mirelight::menus

#endif
