#ifndef MENUS_MENU_MAIN
#define MENUS_MENU_MAIN

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu.h"
#include "events/event_user.h"
#include "UI/ui_button.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Class Menu_main
// ---------------------------------------------------------------------------

class Menu_main final
    : public Menu
    , public events::Event_user
    {

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
    void _create_btn_new_game();
    void _create_btn_continue();
    void _create_btn_settings();
    void _create_btn_exit();

    void _setup_view();
    void _update_moving_background();
    void _update_following_ui_elements();

    void _register_events();
    void _event__btn_hovered();
    void _event__btn_clicked__new_game();
    void _event__btn_clicked__continue();
    void _event__btn_clicked__settings();
    void _event__btn_clicked__exit();

    sf::Sprite* _background_middle;
    sf::Sprite* _background_right;
    float       _background_moving_delta;

    sf::Sprite* _background_box;

    sf::Sprite* _title_banner;
    sf::Text*   _title_text;

    ui::UI_button* _btn_new_game;
    ui::UI_button* _btn_continue;
    ui::UI_button* _btn_settings;
    ui::UI_button* _btn_exit;
};

} // namespace mirelight::menus

#endif
