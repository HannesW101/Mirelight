// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu_main.h"
#include "assets/asset_manager.h"
#include "settings/setting_manager.h"
#include "utils/colors.h"

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

// ===========================================================================
// Get singletons
// ---------------------------------------------------------------------------

Asset_manager& asset_manager = Asset_manager::get_instance();
Setting_manager& setting_manager = Setting_manager::get_instance();

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
    {

    _create_backgrounds();
    _create_background_box();
    _create_title_banner();
    _create_title_text();

    _setup_view();
}

// ---------------------------------------------------------------------------
Menu_main::~Menu_main() {

    if (_background_middle != nullptr) { delete _background_middle; }
    if (_background_right  != nullptr) { delete _background_right;  }
    if (_background_box  != nullptr) { delete _background_box;  }
    if (_title_banner  != nullptr) { delete _title_banner;  }
    if (_title_text  != nullptr) { delete _title_text;  }
}

// ---------------------------------------------------------------------------
void Menu_main::draw() {

    if (_background_middle != nullptr) { _window->draw(*_background_middle); }
    if (_background_right  != nullptr) { _window->draw(*_background_right); }
    if (_background_box != nullptr) { _window->draw(*_background_box); }
    if (_title_banner != nullptr) { _window->draw(*_title_banner); }
    if (_title_text != nullptr) { _window->draw(*_title_text); }

    _update_moving_background();
    _update_following_ui_elements();
}

// ---------------------------------------------------------------------------
void Menu_main::_create_backgrounds() {

    Settings const settings = setting_manager.get_settings();

    if (_background_middle == nullptr) {

        _background_middle = new sf::Sprite(asset_manager.get(Texture_id::BACKGROUND__MOUNTAINS));

        sf::Vector2u const tex_size = _background_middle->getTexture().getSize();

        _background_middle->setScale({
            settings.window_width / static_cast<float>(tex_size.x),
            settings.window_height / static_cast<float>(tex_size.y)
            });
    }

    if (_background_right == nullptr) {

        _background_right = new sf::Sprite(asset_manager.get(Texture_id::BACKGROUND__MOUNTAINS));

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

    Settings const settings = setting_manager.get_settings();

    if (_background_box == nullptr) {

        _background_box = new sf::Sprite(asset_manager.get(Texture_id::BACKGROUND_BOX__03A));

        _background_box->setScale({
            settings.window_width * 0.004f,
            settings.window_height * 0.005f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_title_banner() {

    Settings const settings = setting_manager.get_settings();

    if (_title_banner == nullptr) {

        _title_banner = new sf::Sprite(asset_manager.get(Texture_id::TITLE_BANNER__MEDIUM_02C));

        _title_banner->setScale({
            settings.window_width * 0.005f,
            settings.window_height * 0.005f
            });
    }
}

// ---------------------------------------------------------------------------
void Menu_main::_create_title_text() {

    Settings const settings = setting_manager.get_settings();

    if (_title_text == nullptr) {

        _title_text = new sf::Text(asset_manager.get(Font_id::TITLE));
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
void Menu_main::_setup_view() {

    Settings const settings = setting_manager.get_settings();

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

    Settings const settings = setting_manager.get_settings();
    sf::Vector2f const view_center = _view.getCenter();

    sf::Vector2f const background_box_size = _background_box->getGlobalBounds().size;
    sf::Vector2f const title_banner_size = _title_banner->getGlobalBounds().size;
    sf::Vector2f const title_text_size = _title_text->getGlobalBounds().size;

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
}

} // namespace mirelight::menus