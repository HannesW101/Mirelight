#ifndef UI_BUTTON
#define UI_BUTTON

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_defs.h"
#include "ui/widget.h"
#include "events/event_user.h"

#include <SFML/Graphics.hpp>

#include <string>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Class Button
// ---------------------------------------------------------------------------

class Button final
    : public Widget
    , public events::Event_user
    {

public:
    Button(Widget_type const widget_type, sf::RenderWindow* window);
    ~Button();

    void draw() override;

    bool is_hovered();
    bool contains(sf::Vector2f const& point) const;

    void on_click(std::function<void()> const& callback);

    void set_normal_texture(assets::Texture_id const texture);
    void set_hover_texture(assets::Texture_id const texture);
    void set_normal_cursor(assets::Texture_id const texture);
    void set_hover_cursor(assets::Texture_id const texture);
    void set_hover_sfx(assets::Sfx_id const sfx_id);
    void set_on_click_sfx(assets::Sfx_id const sfx_id);
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
    assets::Texture_id _hover_texture;
    assets::Texture_id _normal_cursor;
    assets::Texture_id _hover_cursor;
    assets::Sfx_id _hover_sfx;
    assets::Sfx_id _on_click_sfx;
};

} // namespace mirelight::ui

#endif
