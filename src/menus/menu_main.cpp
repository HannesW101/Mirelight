// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu_main.h"
#include "assets/asset_manager.h"
#include "settings/setting_manager.h"
#include "utils/colors.h"
#include "events/event_handler.h"
#include "cursors/cursor_manager.h"
#include "sounds/sound_manager.h"

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
using namespace mirelight::cursors;
using namespace mirelight::sounds;
using namespace mirelight::ui;

// ===========================================================================
// Class Menu_main
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Menu_main::Menu_main(sf::RenderWindow* window)
    : Menu(window)
    , _background_middle(nullptr)
    , _background_right(nullptr)
    , _background_moving_delta(0.0f)
    , _background_box(nullptr)
    , _title_banner(nullptr)
    , _title_text(nullptr)
    , _btn_new_game(nullptr)
    , _btn_continue(nullptr)
    , _btn_settings(nullptr)
    , _btn_exit(nullptr)
    {

    _create_backgrounds();
    _create_background_box();
    _create_title_banner();
    _create_title_text();
    _create_btn_new_game();
    _create_btn_continue();
    _create_btn_settings();
    _create_btn_exit();

    _setup_view();

    _register_events();

    Sound_manager::get_instance().play_music(Music_id::AMBIENT_1);
}

// ---------------------------------------------------------------------------
Menu_main::~Menu_main() {

    if (_background_middle != nullptr) { delete _background_middle; }
    if (_background_right  != nullptr) { delete _background_right;  }
    if (_background_box  != nullptr) { delete _background_box;  }
    if (_title_banner  != nullptr) { delete _title_banner;  }
    if (_title_text  != nullptr) { delete _title_text;  }
    if (_btn_new_game  != nullptr) { delete _btn_new_game;  }
    if (_btn_continue  != nullptr) { delete _btn_continue;  }
    if (_btn_settings  != nullptr) { delete _btn_settings;  }
    if (_btn_exit  != nullptr) { delete _btn_exit;  }

    Event_handler::get_instance().deregister_event(_get_caller_id());
    Sound_manager::get_instance().stop_music(Music_id::AMBIENT_1);
}

// ---------------------------------------------------------------------------
void Menu_main::draw() {

    if (_background_middle != nullptr) { _window->draw(*_background_middle); }
    if (_background_right  != nullptr) { _window->draw(*_background_right); }
    if (_background_box != nullptr) { _window->draw(*_background_box); }
    if (_title_banner != nullptr) { _window->draw(*_title_banner); }
    if (_title_text != nullptr) { _window->draw(*_title_text); }
    if (_btn_new_game != nullptr) { _btn_new_game->draw(); }
    if (_btn_continue != nullptr) { _btn_continue->draw(); }
    if (_btn_settings != nullptr) { _btn_settings->draw(); }
    if (_btn_exit != nullptr) { _btn_exit->draw(); }

    _update_moving_background();
    _update_following_ui_elements();
}

// ---------------------------------------------------------------------------
void Menu_main::_create_backgrounds() {

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
void Menu_main::_create_background_box() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_background_box == nullptr) {

        _background_box = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::BACKGROUND_BOX__03A));

        _background_box->setScale({
            settings.window_width * 0.004f,
            settings.window_height * 0.005f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_title_banner() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_title_banner == nullptr) {

        _title_banner = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::TITLE_BANNER__MEDIUM_02C));

        _title_banner->setScale({
            settings.window_width * 0.005f,
            settings.window_height * 0.005f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_title_text() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_title_text == nullptr) {

        _title_text = new sf::Text(Asset_manager::get_instance().get(Font_id::TITLE));
        _title_text->setString("MIRELIGHT");

        _title_text->setCharacterSize({
            static_cast<unsigned int>(settings.window_width * 0.070f)
            });

        _title_text->setFillColor(sf::Color::White);

        _title_text->setOutlineColor(COLOR__BANNER_BORDER);
        _title_text->setOutlineThickness({
            _title_text->getCharacterSize() * 0.1f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_btn_new_game() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_btn_new_game == nullptr) {

        _btn_new_game = new UI_button("_btn_new_game", _window);

        _btn_new_game->set_normal_texture(Texture_id::BUTTON__03A_NORMAL);
        _btn_new_game->set_hover_texture(Texture_id::BUTTON__03A_SELECTED);
        _btn_new_game->set_text_font(Font_id::TITLE);
        _btn_new_game->get_sprite()->setScale({
            settings.window_width * 0.002f,
            settings.window_height * 0.002f
            });

        _btn_new_game->get_text()->setString("NEW GAME");
        _btn_new_game->get_text()->setCharacterSize({
            static_cast<unsigned int>(settings.window_width * 0.030f)
            });
        _btn_new_game->get_text()->setFillColor(sf::Color::White);
        _btn_new_game->get_text()->setOutlineColor(COLOR__BANNER_BORDER);
        _btn_new_game->get_text()->setOutlineThickness({
            _btn_new_game->get_text()->getCharacterSize() * 0.1f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_btn_continue() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_btn_continue == nullptr) {

        _btn_continue = new UI_button("_btn_continue", _window);

        _btn_continue->set_normal_texture(Texture_id::BUTTON__03A_NORMAL);
        _btn_continue->set_hover_texture(Texture_id::BUTTON__03A_SELECTED);
        _btn_continue->set_text_font(Font_id::TITLE);
        _btn_continue->get_sprite()->setScale({
            settings.window_width * 0.002f,
            settings.window_height * 0.002f
            });

        _btn_continue->get_text()->setString("CONTINUE");
        _btn_continue->get_text()->setCharacterSize({
            static_cast<unsigned int>(settings.window_width * 0.030f)
            });
        _btn_continue->get_text()->setFillColor(sf::Color::White);
        _btn_continue->get_text()->setOutlineColor(COLOR__BANNER_BORDER);
        _btn_continue->get_text()->setOutlineThickness({
            _btn_continue->get_text()->getCharacterSize() * 0.1f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_btn_settings() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_btn_settings == nullptr) {

        _btn_settings = new UI_button("_btn_settings", _window);

        _btn_settings->set_normal_texture(Texture_id::BUTTON__03A_NORMAL);
        _btn_settings->set_hover_texture(Texture_id::BUTTON__03A_SELECTED);
        _btn_settings->set_text_font(Font_id::TITLE);
        _btn_settings->get_sprite()->setScale({
            settings.window_width * 0.002f,
            settings.window_height * 0.002f
            });

        _btn_settings->get_text()->setString("SETTINGS");
        _btn_settings->get_text()->setCharacterSize({
            static_cast<unsigned int>(settings.window_width * 0.030f)
            });
        _btn_settings->get_text()->setFillColor(sf::Color::White);
        _btn_settings->get_text()->setOutlineColor(COLOR__BANNER_BORDER);
        _btn_settings->get_text()->setOutlineThickness({
            _btn_settings->get_text()->getCharacterSize() * 0.1f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_btn_exit() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_btn_exit == nullptr) {

        _btn_exit = new UI_button("_btn_exit", _window);

        _btn_exit->set_normal_texture(Texture_id::BUTTON__03A_NORMAL);
        _btn_exit->set_hover_texture(Texture_id::BUTTON__03A_SELECTED);
        _btn_exit->set_text_font(Font_id::TITLE);
        _btn_exit->get_sprite()->setScale({
            settings.window_width * 0.002f,
            settings.window_height * 0.002f
            });

        _btn_exit->get_text()->setString("EXIT");
        _btn_exit->get_text()->setCharacterSize({
            static_cast<unsigned int>(settings.window_width * 0.030f)
            });
        _btn_exit->get_text()->setFillColor(sf::Color::White);
        _btn_exit->get_text()->setOutlineColor(COLOR__BANNER_BORDER);
        _btn_exit->get_text()->setOutlineThickness({
            _btn_exit->get_text()->getCharacterSize() * 0.1f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_setup_view() {

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
void Menu_main::_update_moving_background() {

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
void Menu_main::_update_following_ui_elements() {

    Settings const settings = Setting_manager::get_instance().get_settings();
    sf::Vector2f const view_center = _view.getCenter();

    sf::Vector2f const background_box_size = _background_box->getGlobalBounds().size;
    sf::Vector2f const title_banner_size = _title_banner->getGlobalBounds().size;
    sf::Vector2f const title_text_size = _title_text->getGlobalBounds().size;
    sf::Vector2f const btn_new_game_size = _btn_new_game->get_sprite()->getGlobalBounds().size;
    sf::Vector2f const btn_continue_size = _btn_continue->get_sprite()->getGlobalBounds().size;
    sf::Vector2f const btn_settings_size = _btn_settings->get_sprite()->getGlobalBounds().size;
    sf::Vector2f const btn_exit_size = _btn_exit->get_sprite()->getGlobalBounds().size;
    sf::Vector2f const new_game_text_size = _btn_new_game->get_text()->getGlobalBounds().size;
    sf::Vector2f const continue_text_size = _btn_continue->get_text()->getGlobalBounds().size;
    sf::Vector2f const settings_text_size = _btn_settings->get_text()->getGlobalBounds().size;
    sf::Vector2f const exit_text_size = _btn_exit->get_text()->getGlobalBounds().size;

    _background_box->setPosition({
        view_center.x - (background_box_size.x / 2.0f),
        view_center.y - (background_box_size.y / 2.0f) + settings.window_height * 0.16f
        });

    _title_banner->setPosition({
        view_center.x - (title_banner_size.x / 2.0f),
        view_center.y - (title_banner_size.y / 2.0f) - settings.window_height * 0.33f
        });

    _title_text->setPosition({
        view_center.x - (title_text_size.x / 2.0f) + settings.window_width * 0.007f,
        view_center.y - (title_text_size.y / 2.0f) - settings.window_height * 0.39f
        });

    _btn_new_game->get_sprite()->setPosition({
        view_center.x - (btn_new_game_size.x / 2.0f),
        view_center.y - (btn_new_game_size.y / 2.0f) + settings.window_height * 0.02f
        });

    _btn_continue->get_sprite()->setPosition({
        view_center.x - (btn_continue_size.x / 2.0f),
        view_center.y - (btn_continue_size.y / 2.0f) + settings.window_height * 0.12f
        });

    _btn_settings->get_sprite()->setPosition({
        view_center.x - (btn_settings_size.x / 2.0f),
        view_center.y - (btn_settings_size.y / 2.0f) + settings.window_height * 0.22f
        });

    _btn_exit->get_sprite()->setPosition({
        view_center.x - (btn_exit_size.x / 2.0f),
        view_center.y - (btn_exit_size.y / 2.0f) + settings.window_height * 0.32f
        });

    _btn_new_game->get_text()->setPosition({
        view_center.x - (new_game_text_size.x / 2.0f),
        view_center.y - (new_game_text_size.y / 2.0f) + settings.window_height * 0.006f
        });

    _btn_continue->get_text()->setPosition({
        view_center.x - (continue_text_size.x / 2.0f),
        view_center.y - (continue_text_size.y / 2.0f) + settings.window_height * 0.106f
        });

    _btn_settings->get_text()->setPosition({
        view_center.x - (settings_text_size.x / 2.0f),
        view_center.y - (settings_text_size.y / 2.0f) + settings.window_height * 0.206f
        });

    _btn_exit->get_text()->setPosition({
        view_center.x - (exit_text_size.x / 2.0f),
        view_center.y - (exit_text_size.y / 2.0f) + settings.window_height * 0.306f
        });
}

// ---------------------------------------------------------------------------
void Menu_main::_register_events() {

    { // MOUSE_MOVED
        Event_id const event_id = { _get_caller_id(), Event_type::MOUSE_MOVED };
        Event_handler::get_instance().register_event(event_id, [this](){

            _event__btn_hovered();
        });
    }

    { // MOUSE_BUTTON_LEFT_RELEASE
        Event_id const event_id = { _get_caller_id(), Event_type::MOUSE_BUTTON_LEFT_RELEASE };
        Event_handler::get_instance().register_event(event_id, [this](){

            if (_btn_new_game->is_hovered()) { _event__btn_clicked__new_game(); }
            if (_btn_continue->is_hovered()) { _event__btn_clicked__continue(); }
            if (_btn_settings->is_hovered()) { _event__btn_clicked__settings(); }
            if (_btn_exit->is_hovered())     { _event__btn_clicked__exit(); }
        });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_event__btn_hovered() {

    Cursor_manager& cursor_manager = Cursor_manager::get_instance(_window);

    bool is_something_hovered = false;

    if (_btn_new_game->is_hovered()) { is_something_hovered = true; }
    if (_btn_continue->is_hovered()) { is_something_hovered = true; }
    if (_btn_settings->is_hovered()) { is_something_hovered = true; }
    if (_btn_exit->is_hovered())     { is_something_hovered = true; }

    if (is_something_hovered) {

        cursor_manager.change_cursor(Texture_id::CURSOR__GAUNTLET_MAGIC);
    } else {

        cursor_manager.change_cursor(Texture_id::CURSOR__GAUNTLET);
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_event__btn_clicked__new_game() {

    Sound_manager::get_instance().play_sfx(Sfx_id::AFRICAN_2);
}

// ---------------------------------------------------------------------------
void Menu_main::_event__btn_clicked__continue() {

    Sound_manager::get_instance().play_sfx(Sfx_id::AFRICAN_2);
}

// ---------------------------------------------------------------------------
void Menu_main::_event__btn_clicked__settings() {

    Sound_manager::get_instance().play_sfx(Sfx_id::AFRICAN_2);
    _pending_menu_change = Menu_id::SETTINGS;
}

// ---------------------------------------------------------------------------
void Menu_main::_event__btn_clicked__exit() {

    Sound_manager::get_instance().play_sfx(Sfx_id::AFRICAN_2);
    _window->close();
}

} // namespace mirelight::menus