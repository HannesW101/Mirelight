// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "ui/button.h"
#include "assets/asset_manager.h"
#include "sounds/sound_manager.h"
#include "utils/logger.h"
#include "events/event_handler.h"
#include "cursors/cursor_manager.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::assets;
using namespace mirelight::sounds;
using namespace mirelight::events;
using namespace mirelight::cursors;

// ===========================================================================
// Class Button
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Button::Button(Widget_type const widget_type, sf::RenderWindow* window)
    : Widget(widget_type, window)
    , _sprite(nullptr)
    , _text(nullptr)
    , _normal_texture()
    , _hover_texture()
    , _normal_cursor()
    , _hover_cursor()
    , _hover_sfx()
    , _on_click_sfx()
    {

    _sprite = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::DEFAULT));
    if (widget_type == Widget_type::TEXT_BUTTON) { _text = new sf::Text(Asset_manager::get_instance().get(Font_id::DEFAULT)); }
}

// ---------------------------------------------------------------------------
Button::~Button() {

    if (_sprite != nullptr) { delete _sprite; }
    if (_text != nullptr) { delete _text; }

    Event_handler::get_instance().deregister_event(_get_caller_id());
}

// ---------------------------------------------------------------------------
void Button::draw() {

    _update();

    if (_sprite != nullptr) { _window->draw(*_sprite); }
    if (_text != nullptr) { _window->draw(*_text); }
}

// ---------------------------------------------------------------------------
bool Button::is_hovered() {

    if (_state == Widget_state::HOVERED) {

        return true;
    } else {

        return false;
    }
}

// ---------------------------------------------------------------------------
bool Button::contains(sf::Vector2f const& point) const {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
        return false;
    }

    if (_sprite->getGlobalBounds().contains(point)) {

        return true;
    } else {

        return false;
    }
}

// ---------------------------------------------------------------------------
void Button::on_click(std::function<void()> const& callback) {

    Event_id const event_id = { _get_caller_id(), Event_type::MOUSE_BUTTON_LEFT_RELEASE };
    Event_handler::get_instance().register_event(event_id, [this, callback]() {

        sf::Vector2i mouse_pixel = sf::Mouse::getPosition(*_window);
        sf::Vector2f mouse_world = _window->mapPixelToCoords(mouse_pixel);

        if (contains(mouse_world)) {

            Sound_manager::get_instance().play_sfx(_on_click_sfx);
            callback();
        }
    });
}

// ---------------------------------------------------------------------------
void Button::set_normal_texture(assets::Texture_id const texture) {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
    } else {

        _normal_texture = texture;
        _sprite->setTexture(Asset_manager::get_instance().get(texture), true);
    }
}

// ---------------------------------------------------------------------------
void Button::set_hover_texture(assets::Texture_id const texture) {

    _hover_texture = texture;
}

// ---------------------------------------------------------------------------
void Button::set_normal_cursor(assets::Texture_id const texture) {

    _normal_cursor = texture;
}

// ---------------------------------------------------------------------------
void Button::set_hover_cursor(assets::Texture_id const texture) {

    _hover_cursor = texture;
}

// ---------------------------------------------------------------------------
void Button::set_hover_sfx(assets::Sfx_id const sfx_id) {

    _hover_sfx = sfx_id;
}

// ---------------------------------------------------------------------------
void Button::set_on_click_sfx(assets::Sfx_id const sfx_id) {

    _on_click_sfx = sfx_id;
}

// ---------------------------------------------------------------------------
void Button::set_text_font(assets::Font_id const font_id) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setFont(Asset_manager::get_instance().get(font_id));
    }
}

// ---------------------------------------------------------------------------
void Button::set_scale(sf::Vector2f const& scale) {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
    } else {

        _sprite->setScale(scale);
    }
}

// ---------------------------------------------------------------------------
void Button::set_text(std::string const& text) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setString(text);
    }
}

// ---------------------------------------------------------------------------
void Button::set_char_size(unsigned int const size) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setCharacterSize(size);
    }
}

// ---------------------------------------------------------------------------
void Button::set_text_color(sf::Color const& color) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setFillColor(color);
    }
}

// ---------------------------------------------------------------------------
void Button::set_sprite_position(sf::Vector2f const& pos) {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
    } else {

        _sprite->setPosition(pos);
    }
}

// ---------------------------------------------------------------------------
void Button::set_text_position(sf::Vector2f const& pos) {

    if (_type != Widget_type::TEXT_BUTTON) {

        LOG(ERROR) << "button is not a text button";
        return;
    }

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
        return;
    }

    _text->setPosition(pos);
}

// ---------------------------------------------------------------------------
void Button::set_text_border(sf::Color const& color, float const thickness) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setOutlineColor(color);
        _text->setOutlineThickness(thickness);
    }
}

// ---------------------------------------------------------------------------
unsigned int Button::get_char_size() const {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
        return 0u;
    } else {

        return _text->getCharacterSize();
    }
}

// ---------------------------------------------------------------------------
sf::FloatRect Button::get_sprite_global_bounds() const {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
        return {};
    } else {

        return _sprite->getGlobalBounds();
    }
}

// ---------------------------------------------------------------------------
sf::FloatRect Button::get_text_global_bounds() const {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
        return {};
    } else {

        return _text->getGlobalBounds();
    }
}

// ---------------------------------------------------------------------------
void Button::_update() {

    sf::Vector2i const mouse_pixel_coords = sf::Mouse::getPosition(*_window);
    sf::Vector2f const mouse_world_coords = _window->mapPixelToCoords(mouse_pixel_coords);
    bool         const hovered_now        = contains(mouse_world_coords);

    // Enter hover
    if (_state == Widget_state::NORMAL && hovered_now) {

        _state = Widget_state::HOVERED;

        if (_sprite == nullptr) {

            LOG(ERROR) << "_sprite is nullptr";
        } else {

            _sprite->setTexture(Asset_manager::get_instance().get(_hover_texture), true);
            Cursor_manager::get_instance(_window).change_cursor(_hover_cursor);
            Sound_manager::get_instance().play_sfx(_hover_sfx);
        }
    }
    // Exit hover
    else if (_state == Widget_state::HOVERED && !hovered_now) {

        _state = Widget_state::NORMAL;

        if (_sprite == nullptr) {

            LOG(ERROR) << "_sprite is nullptr";
        } else {

            _sprite->setTexture(Asset_manager::get_instance().get(_normal_texture), true);
            Cursor_manager::get_instance(_window).change_cursor(_normal_cursor);
        }
    }
}

} // namespace mirelight::ui
