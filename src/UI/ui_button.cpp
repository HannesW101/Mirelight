// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "UI/UI_button.h"
#include "assets/asset_manager.h"
#include "sounds/sound_manager.h"
#include "utils/logger.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::assets;
using namespace mirelight::sounds;

// ===========================================================================
// Class UI_button
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
UI_button::UI_button(std::string const& id_string, sf::RenderWindow* window)
    : _id_string(id_string)
    , _window(window)
    , _sprite(nullptr)
    , _text(nullptr)
    , _hover_sfx()
    , _normal_texture()
    , _hover_texture()
    , _is_hovered(false)
    {

    _sprite = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::DEFAULT));
    _text = new sf::Text(Asset_manager::get_instance().get(Font_id::DEFAULT));
}

// ---------------------------------------------------------------------------
UI_button::~UI_button() {

    if (_sprite != nullptr) { delete _sprite; }
    if (_text != nullptr) { delete _text; }
}

// ---------------------------------------------------------------------------
void UI_button::draw() {

    _update();

    if (_sprite != nullptr) { _window->draw(*_sprite); }
    if (_text != nullptr) { _window->draw(*_text); }
}

// ---------------------------------------------------------------------------
sf::Sprite* UI_button::get_sprite(){

    if (_sprite == nullptr) { LOG(ERROR) << "Returning nullptr"; }
    return _sprite;
}

// ---------------------------------------------------------------------------
sf::Text* UI_button::get_text() {

    if (_text == nullptr) { LOG(ERROR) << "Returning nullptr"; }
    return _text;
}

// ---------------------------------------------------------------------------
bool UI_button::contains(sf::Vector2f const& point) const {

    if (_sprite == nullptr) { LOG(ERROR) << "_sprite is nullptr"; }

    if (_sprite->getGlobalBounds().contains(point)) {

        return true;
    } else {

        return false;
    }
}

// ---------------------------------------------------------------------------
bool UI_button::is_hovered() const {

    return _is_hovered;
}

// ---------------------------------------------------------------------------
void UI_button::set_hover_sfx(assets::Sfx_id const sfx_id) {

    _hover_sfx = sfx_id;
}

// ---------------------------------------------------------------------------
void UI_button::set_normal_texture(assets::Texture_id const texture) {

    _normal_texture = texture;
    _sprite->setTexture(Asset_manager::get_instance().get(texture), true);
}

// ---------------------------------------------------------------------------
void UI_button::set_hover_texture(assets::Texture_id const texture) {

    _hover_texture = texture;
}

// ---------------------------------------------------------------------------
void UI_button::set_text_font(assets::Font_id const font_id) {

    if (_text == nullptr) { LOG(ERROR) << "_text is nullptr"; }
    _text->setFont(Asset_manager::get_instance().get(font_id));
}

// ---------------------------------------------------------------------------
void UI_button::_update() {

    sf::Vector2i const mouse_pixel_coords = sf::Mouse::getPosition(*_window);
    sf::Vector2f const mouse_world_coords = _window->mapPixelToCoords(mouse_pixel_coords);

    bool const hovered_now = contains(mouse_world_coords);

    // ENTER HOVER
    if (hovered_now && !_is_hovered) {

        _is_hovered = true;
        if (_sprite == nullptr) { LOG(ERROR) << "_sprite is nullptr"; }
        _sprite->setTexture(Asset_manager::get_instance().get(_hover_texture), true);
        Sound_manager::get_instance().play_sfx(_hover_sfx);
    }
    // EXIT HOVER
    else if (!hovered_now && _is_hovered) {

        _is_hovered = false;
        if (_sprite == nullptr) { LOG(ERROR) << "_sprite is nullptr"; }
        _sprite->setTexture(Asset_manager::get_instance().get(_normal_texture), true);
    }
}

} // namespace mirelight::ui
