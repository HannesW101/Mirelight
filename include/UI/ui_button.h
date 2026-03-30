#ifndef UI_UI_BUTTON
#define UI_UI_BUTTON

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_defs.h"

#include <SFML/Graphics.hpp>

#include <string>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Class UI_button
// ---------------------------------------------------------------------------

class UI_button final {

public:
    UI_button(std::string const& id_string, sf::RenderWindow* window);

    ~UI_button();

    void draw();

    sf::Sprite* get_sprite();
    sf::Text* get_text();

    bool contains(sf::Vector2f const& point) const;
    bool is_hovered() const;

    void set_hover_sfx(assets::Sfx_id const sfx_id);
    void set_normal_texture(assets::Texture_id const texture);
    void set_hover_texture(assets::Texture_id const texture);
    void set_text_font(assets::Font_id const font_id);

private:
    void _update();

    std::string _id_string;
    sf::RenderWindow* _window;

    sf::Sprite* _sprite;
    sf::Text* _text;

    assets::Sfx_id _hover_sfx;
    assets::Texture_id _normal_texture;
    assets::Texture_id _hover_texture;

    bool _is_hovered;
};

} // namespace mirelight::ui

#endif
