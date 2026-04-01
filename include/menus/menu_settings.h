#ifndef MENUS_MENU_SETTINGS
#define MENUS_MENU_SETTINGS

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu.h"
#include "ui/label.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Class Menu_settings
// ---------------------------------------------------------------------------

class Menu_settings final
    : public Menu
    {

public:
    Menu_settings(sf::RenderWindow* window);
    ~Menu_settings();

    void draw() override;

    Menu_settings           (Menu_settings const&) = delete;
    Menu_settings& operator=(Menu_settings const&) = delete;
    Menu_settings           (Menu_settings&&     ) = delete;
    Menu_settings& operator=(Menu_settings&&     ) = delete;

private:
    void _create_backgrounds();
    void _create_background_box();
    void _create_label_resolution();
    void _create_label_vsync();
    void _create_label_fps_limit();
    void _create_label_music_volume();
    void _create_label_sfx_volume();

    void _setup_view();
    void _update_moving_background();
    void _update_following_ui_elements();

    sf::Sprite* _background_middle;
    sf::Sprite* _background_right;
    float       _background_moving_delta;

    sf::Sprite* _background_box;
    ui::Label*  _label_resolution;
    ui::Label*  _label_vsync;
    ui::Label*  _label_fps_limit;
    ui::Label*  _label_music_volume;
    ui::Label*  _label_sfx_volume;
};

} // namespace mirelight::menus

#endif
