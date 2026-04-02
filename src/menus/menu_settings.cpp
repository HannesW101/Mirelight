// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu_settings.h"
#include "assets/asset_manager.h"
#include "settings/setting_manager.h"
#include "utils/colors.h"
#include "events/event_handler.h"
#include "sounds/sound_manager.h"
#include "cursors/cursor_manager.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::assets;
using namespace mirelight::settings;
using namespace mirelight::utils;
using namespace mirelight::events;
using namespace mirelight::sounds;
using namespace mirelight::cursors;
using namespace mirelight::ui;

// ===========================================================================
// Class Menu_settings
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Menu_settings::Menu_settings(sf::RenderWindow* window)
    : Menu(window)
    , _background_middle(nullptr)
    , _background_right(nullptr)
    , _background_moving_delta(0.0f)
    , _background_box(nullptr)
    , _label_resolution(nullptr)
    , _label_vsync(nullptr)
    , _label_fps_limit(nullptr)
    , _label_music_volume(nullptr)
    , _label_sfx_volume(nullptr)
    , _btn_back(nullptr)
    , _btn_apply(nullptr)
    , _slider_music_volume(nullptr)
    , _slider_sfx_volume(nullptr)
    {
    _create_backgrounds();
    _create_background_box();

    _create_label_resolution();
    _create_label_vsync();
    _create_label_fps_limit();
    _create_label_music_volume();
    _create_label_sfx_volume();

    _create_btn_back();
    _create_btn_apply();

    _create_slider_music_volume();
    _create_slider_sfx_volume();

    _setup_view();

    _update_following_ui_elements();
    _update_moving_background();

    Cursor_manager::get_instance(_window).change_cursor(Texture_id::CURSOR__GAUNTLET);
}

// ---------------------------------------------------------------------------
Menu_settings::~Menu_settings() {

    if (_background_middle != nullptr) { delete _background_middle; }
    if (_background_right  != nullptr) { delete _background_right;  }
    if (_background_box  != nullptr) { delete _background_box;  }
    if (_label_resolution  != nullptr) { delete _label_resolution;  }
    if (_label_vsync  != nullptr) { delete _label_vsync;  }
    if (_label_fps_limit  != nullptr) { delete _label_fps_limit;  }
    if (_label_music_volume  != nullptr) { delete _label_music_volume;  }
    if (_label_sfx_volume  != nullptr) { delete _label_sfx_volume;  }
    if (_btn_back  != nullptr) { delete _btn_back;  }
    if (_btn_apply  != nullptr) { delete _btn_apply;  }
    if (_slider_sfx_volume  != nullptr) { delete _slider_sfx_volume;  }
    if (_slider_music_volume  != nullptr) { delete _slider_music_volume;  }
}

// ---------------------------------------------------------------------------
void Menu_settings::draw() {

    if (_background_middle != nullptr) { _window->draw(*_background_middle); }
    if (_background_right  != nullptr) { _window->draw(*_background_right); }
    if (_background_box != nullptr) { _window->draw(*_background_box); }
    if (_label_resolution != nullptr) { _label_resolution->draw(); }
    if (_label_vsync != nullptr) { _label_vsync->draw(); }
    if (_label_fps_limit != nullptr) { _label_fps_limit->draw(); }
    if (_label_music_volume != nullptr) { _label_music_volume->draw(); }
    if (_label_sfx_volume != nullptr) { _label_sfx_volume->draw(); }
    if (_btn_back != nullptr) { _btn_back->draw(); }
    if (_btn_apply != nullptr) { _btn_apply->draw(); }
    if (_slider_sfx_volume != nullptr) { _slider_sfx_volume->draw(); }
    if (_slider_music_volume != nullptr) { _slider_music_volume->draw(); }

    _update_moving_background();
    _update_following_ui_elements();
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_backgrounds() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_background_middle == nullptr) {

        _background_middle = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::BACKGROUND__MOUNTAINS));

        sf::Vector2u const tex_size = _background_middle->getTexture().getSize();

        _background_middle->setScale({
            settings.window_width / static_cast<float>(tex_size.x),
            settings.window_height / static_cast<float>(tex_size.y)
            });
    }

    if (_background_right == nullptr) {

        _background_right = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::BACKGROUND__MOUNTAINS));

        sf::Vector2u const tex_size = _background_right->getTexture().getSize();

        _background_right->setScale({
            settings.window_width / static_cast<float>(tex_size.x),
            settings.window_height / static_cast<float>(tex_size.y)
            });

        _background_right->move({
            _background_right->getGlobalBounds().size.x,
            0.f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_background_box() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_background_box == nullptr) {

        _background_box = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::BACKGROUND_BOX__03A));

        _background_box->setScale({
            settings.window_width * 0.0075f,
            settings.window_height * 0.0075f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_label_resolution() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_label_resolution == nullptr) {

        _label_resolution = new Label(Widget_type::LABEL, _window);

        _label_resolution->set_normal_texture(Texture_id::TITLE_BANNER__MEDIUM_01C);
        _label_resolution->set_text_font(Font_id::TITLE);
        _label_resolution->set_scale({
            settings.window_width * 0.0017f,
            settings.window_height * 0.0017f
            });
        _label_resolution->set_text("RESOLUTION");
        _label_resolution->set_char_size({
            static_cast<unsigned int>(settings.window_width * 0.017f)
            });
        _label_resolution->set_text_color(sf::Color::White);
        _label_resolution->set_text_border(
            COLOR__BANNER_BORDER,
            _label_resolution->get_char_size() * 0.1f
            );
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_label_vsync() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_label_vsync == nullptr) {

        _label_vsync = new Label(Widget_type::LABEL, _window);

        _label_vsync->set_normal_texture(Texture_id::TITLE_BANNER__MEDIUM_01C);
        _label_vsync->set_text_font(Font_id::TITLE);
        _label_vsync->set_scale({
            settings.window_width * 0.0017f,
            settings.window_height * 0.0017f
            });
        _label_vsync->set_text("VSYNC");
        _label_vsync->set_char_size({
            static_cast<unsigned int>(settings.window_width * 0.017f)
            });
        _label_vsync->set_text_color(sf::Color::White);
        _label_vsync->set_text_border(
            COLOR__BANNER_BORDER,
            _label_vsync->get_char_size() * 0.1f
            );
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_label_fps_limit() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_label_fps_limit == nullptr) {

        _label_fps_limit = new Label(Widget_type::LABEL, _window);

        _label_fps_limit->set_normal_texture(Texture_id::TITLE_BANNER__MEDIUM_01C);
        _label_fps_limit->set_text_font(Font_id::TITLE);
        _label_fps_limit->set_scale({
            settings.window_width * 0.0017f,
            settings.window_height * 0.0017f
            });
        _label_fps_limit->set_text("FPS LIMIT");
        _label_fps_limit->set_char_size({
            static_cast<unsigned int>(settings.window_width * 0.017f)
            });
        _label_fps_limit->set_text_color(sf::Color::White);
        _label_fps_limit->set_text_border(
            COLOR__BANNER_BORDER,
            _label_fps_limit->get_char_size() * 0.1f
            );
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_label_music_volume() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_label_music_volume == nullptr) {

        _label_music_volume = new Label(Widget_type::LABEL, _window);

        _label_music_volume->set_normal_texture(Texture_id::TITLE_BANNER__MEDIUM_01C);
        _label_music_volume->set_text_font(Font_id::TITLE);
        _label_music_volume->set_scale({
            settings.window_width * 0.0017f,
            settings.window_height * 0.0017f
            });
        _label_music_volume->set_text("MUSIC VOLUME");
        _label_music_volume->set_char_size({
            static_cast<unsigned int>(settings.window_width * 0.017f)
            });
        _label_music_volume->set_text_color(sf::Color::White);
        _label_music_volume->set_text_border(
            COLOR__BANNER_BORDER,
            _label_music_volume->get_char_size() * 0.1f
            );
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_label_sfx_volume() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_label_sfx_volume == nullptr) {

        _label_sfx_volume = new Label(Widget_type::LABEL, _window);

        _label_sfx_volume->set_normal_texture(Texture_id::TITLE_BANNER__MEDIUM_01C);
        _label_sfx_volume->set_text_font(Font_id::TITLE);
        _label_sfx_volume->set_scale({
            settings.window_width * 0.0017f,
            settings.window_height * 0.0017f
            });
        _label_sfx_volume->set_text("SFX VOLUME");
        _label_sfx_volume->set_char_size({
            static_cast<unsigned int>(settings.window_width * 0.017f)
            });
        _label_sfx_volume->set_text_color(sf::Color::White);
        _label_sfx_volume->set_text_border(
            COLOR__BANNER_BORDER,
            _label_sfx_volume->get_char_size() * 0.1f
            );
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_btn_back() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_btn_back == nullptr) {

        _btn_back = new Button(Widget_type::TEXT_BUTTON, _window);

        _btn_back->set_normal_texture(Texture_id::BUTTON__03A_NORMAL);
        _btn_back->set_hover_texture(Texture_id::BUTTON__03A_SELECTED);
        _btn_back->set_normal_cursor(Texture_id::CURSOR__GAUNTLET);
        _btn_back->set_hover_cursor(Texture_id::CURSOR__GAUNTLET_MAGIC);
        _btn_back->set_hover_sfx(Sfx_id::AFRICAN_1);
        _btn_back->set_on_click_sfx(Sfx_id::AFRICAN_3);
        _btn_back->set_text_font(Font_id::TITLE);
        _btn_back->set_scale({
            settings.window_width * 0.0013f,
            settings.window_height * 0.0017f
            });
        _btn_back->set_text("BACK");
        _btn_back->set_char_size({
            static_cast<unsigned int>(settings.window_width * 0.017f)
            });
        _btn_back->set_text_color(sf::Color::White);
        _btn_back->set_text_border(
            COLOR__BANNER_BORDER,
            _btn_back->get_char_size() * 0.1f
            );
        _btn_back->on_click([this](){

            _pending_menu_change = Menu_id::MAIN;
        });
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_btn_apply() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_btn_apply == nullptr) {

        _btn_apply = new Button(Widget_type::TEXT_BUTTON, _window);

        _btn_apply->set_normal_texture(Texture_id::BUTTON__03A_NORMAL);
        _btn_apply->set_hover_texture(Texture_id::BUTTON__03A_SELECTED);
        _btn_apply->set_normal_cursor(Texture_id::CURSOR__GAUNTLET);
        _btn_apply->set_hover_cursor(Texture_id::CURSOR__GAUNTLET_MAGIC);
        _btn_apply->set_hover_sfx(Sfx_id::AFRICAN_1);
        _btn_apply->set_on_click_sfx(Sfx_id::AFRICAN_3);
        _btn_apply->set_text_font(Font_id::TITLE);
        _btn_apply->set_scale({
            settings.window_width * 0.0013f,
            settings.window_height * 0.0017f
            });
        _btn_apply->set_text("APPLY");
        _btn_apply->set_char_size({
            static_cast<unsigned int>(settings.window_width * 0.017f)
            });
        _btn_apply->set_text_color(sf::Color::White);
        _btn_apply->set_text_border(
            COLOR__BANNER_BORDER,
            _btn_apply->get_char_size() * 0.1f
            );
        _btn_apply->on_click([this](){

            // TODO: Apply settings
        });
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_slider_music_volume() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_slider_music_volume == nullptr) {

        _slider_music_volume = new Slider(Widget_type::SLIDER, _window);

        _slider_music_volume->set_container_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BOX);
        _slider_music_volume->set_bar_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BAR04);
        _slider_music_volume->set_btn_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BUTTON);
        _slider_music_volume->set_slider_percentage(100.0f); // TODO: Replace with settings value
        _slider_music_volume->set_scale({
            settings.window_width * 0.0020f,
            settings.window_height * 0.0017f
            });
        _slider_music_volume->set_bar_offset(-(settings.window_width * 0.0477f));
        _slider_music_volume->on_stop_dragging([this](){

            float const music_volume = _slider_music_volume->get_slider_percentage();
            Sound_manager::get_instance().set_music_volume(music_volume); // TODO: Make not apply when leave menu
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_create_slider_sfx_volume() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_slider_sfx_volume == nullptr) {

        _slider_sfx_volume = new Slider(Widget_type::SLIDER, _window);

        _slider_sfx_volume->set_container_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BOX);
        _slider_sfx_volume->set_bar_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BAR04);
        _slider_sfx_volume->set_btn_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BUTTON);
        _slider_sfx_volume->set_slider_percentage(100.0f); // TODO: Replace with settings value
        _slider_sfx_volume->set_scale({
            settings.window_width * 0.0020f,
            settings.window_height * 0.0017f
            });
        _slider_sfx_volume->set_bar_offset(-(settings.window_width * 0.0477f));

        _slider_sfx_volume->on_stop_dragging([this](){

            float const sfx_volume = _slider_sfx_volume->get_slider_percentage();
            Sound_manager::get_instance().play_sfx(Sfx_id::AFRICAN_2, sfx_volume);
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_settings::_setup_view() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    _view.setSize({
        settings.window_width,
        settings.window_height
        });

    _view.setCenter({
        settings.window_width / 2.0f,
        settings.window_height / 2.0f
        });

    _window->setView(_view);
}

// ---------------------------------------------------------------------------
void Menu_settings::_update_moving_background() {

    float const speed     = 20.0f;
    float const threshold = 0.01f;

    if (_acc_dt >= threshold) {

        _acc_dt -= threshold;

        float const delta             = speed * threshold;
        float const background_size_x = _background_middle->getGlobalBounds().size.x;

        _background_moving_delta += delta;

        if (_background_moving_delta >= background_size_x) {

            _view.move({
                -_background_moving_delta,
                0.0f
                });

            _background_moving_delta = 0.0f;
        } else {

            _view.move({
                delta,
                0.0f
                });
        }
    }

    _window->setView(_view);
}

// ---------------------------------------------------------------------------
void Menu_settings::_update_following_ui_elements() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    sf::Vector2f const view_center = _view.getCenter();

    sf::Vector2f const background_box_size = _background_box->getGlobalBounds().size;

    sf::Vector2f const label_resolution_size = _label_resolution->get_sprite_global_bounds().size;
    sf::Vector2f const label_resolution_text_size = _label_resolution->get_text_global_bounds().size;

    sf::Vector2f const label_vsync_size = _label_vsync->get_sprite_global_bounds().size;
    sf::Vector2f const label_vsync_text_size = _label_vsync->get_text_global_bounds().size;

    sf::Vector2f const label_fps_limit_size = _label_fps_limit->get_sprite_global_bounds().size;
    sf::Vector2f const label_fps_limit_text_size = _label_fps_limit->get_text_global_bounds().size;

    sf::Vector2f const label_music_volume_size = _label_music_volume->get_sprite_global_bounds().size;
    sf::Vector2f const label_music_volume_text_size = _label_music_volume->get_text_global_bounds().size;

    sf::Vector2f const label_sfx_volume_size = _label_sfx_volume->get_sprite_global_bounds().size;
    sf::Vector2f const label_sfx_volume_text_size = _label_sfx_volume->get_text_global_bounds().size;

    sf::Vector2f const btn_back_size = _btn_back->get_sprite_global_bounds().size;
    sf::Vector2f const btn_back_text_size = _btn_back->get_text_global_bounds().size;

    sf::Vector2f const btn_apply_size = _btn_apply->get_sprite_global_bounds().size;
    sf::Vector2f const btn_apply_text_size = _btn_apply->get_text_global_bounds().size;

    sf::Vector2f const slider_sfx_volume_size = _slider_sfx_volume->get_slider_global_bounds().size;

    sf::Vector2f const slider_music_volume_size = _slider_music_volume->get_slider_global_bounds().size;

    _background_box->setPosition({
        view_center.x - (background_box_size.x / 2.0f),
        view_center.y - (background_box_size.y / 2.0f)
        });

    _label_resolution->set_sprite_position({
        view_center.x - (label_resolution_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_resolution_size.y / 2.0f) - settings.window_height * 0.25f
        });
    _label_resolution->set_text_position({
        view_center.x - (label_resolution_text_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_resolution_text_size.y / 2.0f) - settings.window_height * 0.27f
        });

    _label_vsync->set_sprite_position({
        view_center.x - (label_vsync_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_vsync_size.y / 2.0f) - settings.window_height * 0.14f
        });
    _label_vsync->set_text_position({
        view_center.x - (label_vsync_text_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_vsync_text_size.y / 2.0f) - settings.window_height * 0.16f
        });

    _label_fps_limit->set_sprite_position({
        view_center.x - (label_fps_limit_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_fps_limit_size.y / 2.0f) - settings.window_height * 0.03f
        });
    _label_fps_limit->set_text_position({
        view_center.x - (label_fps_limit_text_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_fps_limit_text_size.y / 2.0f) - settings.window_height * 0.05f
        });

    _label_music_volume->set_sprite_position({
        view_center.x - (label_music_volume_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_music_volume_size.y / 2.0f) + settings.window_height * 0.08f
        });
    _label_music_volume->set_text_position({
        view_center.x - (label_music_volume_text_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_music_volume_text_size.y / 2.0f) + settings.window_height * 0.06f
        });

    _label_sfx_volume->set_sprite_position({
        view_center.x - (label_sfx_volume_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_sfx_volume_size.y / 2.0f) + settings.window_height * 0.19f
        });
    _label_sfx_volume->set_text_position({
        view_center.x - (label_sfx_volume_text_size.x / 2.0f) - settings.window_width * 0.18f,
        view_center.y - (label_sfx_volume_text_size.y / 2.0f) + settings.window_height * 0.17f
        });

    _btn_back->set_sprite_position({
        view_center.x - (btn_back_size.x / 2.0f) - settings.window_width * 0.1f,
        view_center.y - (btn_back_size.y / 2.0f) + settings.window_height * 0.28f
        });
    _btn_back->set_text_position({
        view_center.x - (btn_back_text_size.x / 2.0f) - settings.window_width * 0.1f,
        view_center.y - (btn_back_text_size.y / 2.0f) + settings.window_height * 0.27f
        });

    _btn_apply->set_sprite_position({
        view_center.x - (btn_apply_size.x / 2.0f) + settings.window_width * 0.1f,
        view_center.y - (btn_apply_size.y / 2.0f) + settings.window_height * 0.28f
        });
    _btn_apply->set_text_position({
        view_center.x - (btn_apply_text_size.x / 2.0f) + settings.window_width * 0.1f,
        view_center.y - (btn_apply_text_size.y / 2.0f) + settings.window_height * 0.27f
        });

    _slider_sfx_volume->set_position({
        view_center.x - (slider_sfx_volume_size.x / 2.0f) + settings.window_width * 0.1f,
        view_center.y - (slider_sfx_volume_size.y / 2.0f) + settings.window_height * 0.179f
        });

    _slider_music_volume->set_position({
        view_center.x - (slider_music_volume_size.x / 2.0f) + settings.window_width * 0.1f,
        view_center.y - (slider_music_volume_size.y / 2.0f) + settings.window_height * 0.07f
        });
}

} // namespace mirelight::menus