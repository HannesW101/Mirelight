#ifndef UI_SLIDER
#define UI_SLIDER

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
// Class Slider
// ---------------------------------------------------------------------------

class Slider final
    : public Widget
    , public events::Event_user
    {

public:
    Slider(Widget_type const widget_type, sf::RenderWindow* window);
    ~Slider();

    void draw() override;

    void on_stop_dragging(std::function<void()> const& callback);

    void set_container_texture(assets::Texture_id const texture);
    void set_bar_texture(assets::Texture_id const texture);
    void set_btn_texture(assets::Texture_id const texture);
    void set_slider_percentage(float const percentage);
    void set_scale(sf::Vector2f const& scale);
    void set_bar_offset(float const offset);
    void set_position(sf::Vector2f const& pos);

    sf::FloatRect get_slider_global_bounds() const;
    float get_slider_percentage() const;

private:
    void _update() override;
    void _update_slider_percentage(sf::Vector2f const& mouse_pos);

    void _register_events();

    sf::Sprite* _container;
    sf::Sprite* _bar;
    sf::Sprite* _btn;

    sf::Text* _lbl;

    assets::Texture_id _container_texture;
    assets::Texture_id _bar_texture;
    assets::Texture_id _btn_texture;

    float _slider_percentage;
    sf::Vector2f _btn_clicked_pos;
    sf::IntRect _bar_texture_rect;
    float _bar_offset;
};

} // namespace mirelight::ui

#endif
