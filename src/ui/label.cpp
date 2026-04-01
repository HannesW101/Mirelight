// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "ui/label.h"
#include "assets/asset_manager.h"
#include "utils/logger.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::assets;

// ===========================================================================
// Class Label
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Label::Label(Widget_type const widget_type, sf::RenderWindow* window)
    : Widget(widget_type, window)
    , _sprite(nullptr)
    , _text(nullptr)
    , _normal_texture()
    {

    _sprite = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::DEFAULT));
    _text = new sf::Text(Asset_manager::get_instance().get(Font_id::DEFAULT));
}

// ---------------------------------------------------------------------------
Label::~Label() {

    if (_sprite != nullptr) { delete _sprite; }
    if (_text != nullptr) { delete _text; }
}

// ---------------------------------------------------------------------------
void Label::draw() {

    _update();

    if (_sprite != nullptr) { _window->draw(*_sprite); }
    if (_text != nullptr) { _window->draw(*_text); }
}

// ---------------------------------------------------------------------------
void Label::set_normal_texture(assets::Texture_id const texture) {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
    } else {

        _normal_texture = texture;
        _sprite->setTexture(Asset_manager::get_instance().get(texture), true);
    }
}

// ---------------------------------------------------------------------------
void Label::set_text_font(assets::Font_id const font_id) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setFont(Asset_manager::get_instance().get(font_id));
    }
}

// ---------------------------------------------------------------------------
void Label::set_scale(sf::Vector2f const& scale) {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
    } else {

        _sprite->setScale(scale);
    }
}

// ---------------------------------------------------------------------------
void Label::set_text(std::string const& text) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setString(text);
    }
}

// ---------------------------------------------------------------------------
void Label::set_char_size(unsigned int const size) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setCharacterSize(size);
    }
}

// ---------------------------------------------------------------------------
void Label::set_text_color(sf::Color const& color) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setFillColor(color);
    }
}

// ---------------------------------------------------------------------------
void Label::set_sprite_position(sf::Vector2f const& pos) {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
    } else {

        _sprite->setPosition(pos);
    }
}

// ---------------------------------------------------------------------------
void Label::set_text_position(sf::Vector2f const& pos) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
        return;
    }

    _text->setPosition(pos);
}

// ---------------------------------------------------------------------------
void Label::set_text_border(sf::Color const& color, float const thickness) {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
    } else {

        _text->setOutlineColor(color);
        _text->setOutlineThickness(thickness);
    }
}

// ---------------------------------------------------------------------------
unsigned int Label::get_char_size() const {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
        return 0u;
    } else {

        return _text->getCharacterSize();
    }
}

// ---------------------------------------------------------------------------
sf::FloatRect Label::get_sprite_global_bounds() const {

    if (_sprite == nullptr) {

        LOG(ERROR) << "_sprite is nullptr";
        return {};
    } else {

        return _sprite->getGlobalBounds();
    }
}

// ---------------------------------------------------------------------------
sf::FloatRect Label::get_text_global_bounds() const {

    if (_text == nullptr) {

        LOG(ERROR) << "_text is nullptr";
        return {};
    } else {

        return _text->getGlobalBounds();
    }
}

// ---------------------------------------------------------------------------
void Label::_update() {

}

} // namespace mirelight::ui
