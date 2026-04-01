#ifndef UI_LABEL
#define UI_LABEL

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_defs.h"
#include "ui/widget.h"

#include <SFML/Graphics.hpp>

#include <string>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Class Label
// ---------------------------------------------------------------------------

class Label final : public Widget {

public:
    Label(Widget_type const widget_type, sf::RenderWindow* window);
    ~Label();

    void draw() override;

    void set_normal_texture(assets::Texture_id const texture);
    void set_text_font(assets::Font_id const font_id);
    void set_scale(sf::Vector2f const& scale);
    void set_text(std::string const& text);
    void set_char_size(unsigned int const size);
    void set_text_color(sf::Color const& color);
    void set_sprite_position(sf::Vector2f const& pos);
    void set_text_position(sf::Vector2f const& pos);
    void set_text_border(sf::Color const& color, float const thickness);

    unsigned int get_char_size() const;
    sf::FloatRect get_sprite_global_bounds() const;
    sf::FloatRect get_text_global_bounds() const;

private:
    void _update() override;

    sf::Sprite* _sprite;
    sf::Text* _text;

    assets::Texture_id _normal_texture;
};

} // namespace mirelight::ui

#endif
