// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "cursors/cursor_manager.h"
#include "assets/asset_manager.h"
#include "settings/setting_manager.h"
#include "events/event_handler.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::cursors {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::assets;
using namespace mirelight::settings;
using namespace mirelight::events;

// ===========================================================================
// Class Cursor_manager
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Cursor_manager& Cursor_manager::get_instance(sf::RenderWindow* window) {

    static Cursor_manager instance(window);
    return instance;
}

// ---------------------------------------------------------------------------
void Cursor_manager::change_cursor(assets::Texture_id const cursor_id) {

    if (_curr_cursor_id == cursor_id) {

        // Do nothing
    } else {

        _curr_cursor_id = cursor_id;
        _curr_cursor->setTexture(Asset_manager::get_instance().get(cursor_id));
    }
}

// ---------------------------------------------------------------------------
void Cursor_manager::draw() {

    if (_curr_cursor != nullptr) {

        _update_cursor_pos();
        _window->draw(*_curr_cursor);
    }
}

// ---------------------------------------------------------------------------
Cursor_manager::~Cursor_manager() {

    if (_curr_cursor != nullptr) { delete _curr_cursor; }
}

// ---------------------------------------------------------------------------
Cursor_manager::Cursor_manager(sf::RenderWindow* window)
    : _window(window)
    , _curr_cursor(nullptr)
    , _curr_cursor_id(Texture_id::CURSOR__GAUNTLET)
    {

    _window->setMouseCursorVisible(false);
    _create_curr_cursor();
}

// ---------------------------------------------------------------------------
void Cursor_manager::_create_curr_cursor() {

    Settings const settings = Setting_manager::get_instance().get_settings();

    _curr_cursor = new sf::Sprite(Asset_manager::get_instance().get(_curr_cursor_id));

    _curr_cursor->setScale({
        settings.window_width  * 0.001f,
        settings.window_height * 0.001f
        });

    sf::Vector2u const tex_size = _curr_cursor->getTexture().getSize();

    _curr_cursor->setOrigin({
        tex_size.x / 2.0f,
        tex_size.y / 2.0f
        });
}

// ---------------------------------------------------------------------------
void Cursor_manager::_update_cursor_pos() {

    sf::Vector2i const pixel_coords = sf::Mouse::getPosition(*_window);
    sf::Vector2f const world_coords = _window->mapPixelToCoords(pixel_coords);

    if (_curr_cursor != nullptr) {

        _curr_cursor->setPosition({
            world_coords.x,
            world_coords.y
            });
    }
}

} // namespace mirelight::cursors
