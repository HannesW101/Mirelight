// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "ui/slider.h"
#include "utils/logger.h"
#include "events/event_handler.h"
#include "assets/asset_manager.h"
#include "utils/colors.h"
#include "settings/setting_manager.h"
#include "sounds/sound_manager.h"

#include <format>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::events;
using namespace mirelight::assets;
using namespace mirelight::utils;
using namespace mirelight::settings;
using namespace mirelight::sounds;

// ===========================================================================
// Constants
// ---------------------------------------------------------------------------

inline float constexpr TRACK_START_RATIO = 0.1655f;
inline float constexpr TRACK_END_RATIO   = 0.855f;

// ===========================================================================
// Class Slider
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Slider::Slider(Widget_type const widget_type, sf::RenderWindow* window)
    : Widget(widget_type, window)
    , _container(nullptr)
    , _bar(nullptr)
    , _btn(nullptr)
    , _lbl(nullptr)
    , _container_texture()
    , _bar_texture()
    , _btn_texture()
    , _slider_percentage(0.0f)
    , _btn_clicked_pos()
    , _bar_texture_rect()
    , _bar_offset(0.0f)
    {

    _container = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::DEFAULT));
    _bar = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::DEFAULT));
    _btn = new sf::Sprite(Asset_manager::get_instance().get(Texture_id::DEFAULT));
    _lbl = new sf::Text(Asset_manager::get_instance().get(Font_id::DEFAULT));

    _lbl->setOutlineColor(COLOR__BANNER_BORDER);
    _lbl->setOutlineThickness(_lbl->getCharacterSize() * 0.1f);

    _register_events();
}

// ---------------------------------------------------------------------------
Slider::~Slider() {

    if (_container != nullptr) { delete _container; }
    if (_bar != nullptr) { delete _bar; }
    if (_btn != nullptr) { delete _btn; }
    if (_lbl != nullptr) { delete _lbl; }

    Event_handler::get_instance().deregister_event(_get_caller_id());
}

// ---------------------------------------------------------------------------
void Slider::draw() {

    _update();

    if (_container != nullptr) { _window->draw(*_container); }
    if (_bar != nullptr) { _window->draw(*_bar); }
    if (_btn != nullptr) { _window->draw(*_btn); }
    if (_lbl != nullptr) { _window->draw(*_lbl); }
}

// ---------------------------------------------------------------------------
void Slider::on_stop_dragging(std::function<void()> const& callback) {

    { // SLIDER STOPPED DRAGGING
        Event_id const event_id = { _get_caller_id(), Event_type::MOUSE_BUTTON_LEFT_RELEASE };
        Event_handler::get_instance().register_event(event_id, [this, callback]() {
            if (_state != Widget_state::NORMAL) {

                _state = Widget_state::NORMAL;
                callback();
            }
        });
    }
}

// ---------------------------------------------------------------------------
void Slider::set_container_texture(assets::Texture_id const texture) {

    if (_container == nullptr) {

        LOG(ERROR) << "_container is nullptr";
    } else {

        _container_texture = texture;
        _container->setTexture(Asset_manager::get_instance().get(texture), true);
    }
}

// ---------------------------------------------------------------------------
void Slider::set_bar_texture(assets::Texture_id const texture) {

    if (_bar == nullptr) {

        LOG(ERROR) << "_bar is nullptr";
    } else {

        _bar_texture = texture;
        _bar->setTexture(Asset_manager::get_instance().get(texture), true);
        _bar->setOrigin({0.0f, 0.0f});
        _bar_texture_rect = _bar->getTextureRect();
        _bar_texture_rect.position.x = 0;
    }
}

// ---------------------------------------------------------------------------
void Slider::set_btn_texture(assets::Texture_id const texture) {

    if (_btn == nullptr) {

        LOG(ERROR) << "_btn is nullptr";
    } else {

        _btn_texture = texture;
        _btn->setTexture(Asset_manager::get_instance().get(texture), true);
    }
}

// ---------------------------------------------------------------------------
void Slider::set_slider_percentage(float const percentage) {

    float const clamped_percentage = std::clamp(percentage, 0.0f, 100.0f);
    _slider_percentage = clamped_percentage;

    _lbl->setString(std::format("{:.0f}", _slider_percentage));
}

// ---------------------------------------------------------------------------
void Slider::set_scale(sf::Vector2f const& scale) {

    Settings const settings = Setting_manager::get_instance().get_settings();

    if (_container == nullptr || _bar == nullptr || _btn == nullptr) {

        LOG(ERROR) << "_container or _bar or _btn is nullptr";
    } else {

        _container->setScale(scale);
        _bar->setScale(scale);
        _btn->setScale(scale);
        _lbl->setCharacterSize(static_cast<unsigned int>(settings.window_width * 0.017f));
    }
}

// ---------------------------------------------------------------------------
void Slider::set_bar_offset(float const offset) {

    _bar_offset = offset;
}

// ---------------------------------------------------------------------------
void Slider::set_position(sf::Vector2f const& pos) {

    if (_container == nullptr || _bar == nullptr || _btn == nullptr) {

        LOG(ERROR) << "_container or _bar or _btn is nullptr";
        return;
    }

    _container->setPosition(pos);

    sf::FloatRect const container_bounds = _container->getGlobalBounds();
    float const track_start = container_bounds.position.x + container_bounds.size.x * TRACK_START_RATIO;
    float const track_end   = container_bounds.position.x + container_bounds.size.x * TRACK_END_RATIO;
    float const track_width = track_end - track_start;

    float const scale_x       = _btn->getScale().x;
    float const btn_tex_width = static_cast<float>(_btn->getLocalBounds().size.x);
    float const btn_x = track_start + (_slider_percentage / 100.0f) * track_width - (btn_tex_width / 2.0f) * scale_x;
    _btn->setPosition({ btn_x, pos.y });

    _bar->setPosition({ track_start + _bar_offset, pos.y });

    float const label_width  = _lbl->getGlobalBounds().size.x;
    float const label_height = _lbl->getGlobalBounds().size.y;
    float const container_center_x = container_bounds.position.x + container_bounds.size.x / 2.0f;
    float const label_x = container_center_x - label_width / 2.0f;
    float const label_y = container_bounds.position.y - label_height - (container_bounds.size.y * 0.00f);

    _lbl->setPosition({ label_x, label_y });
}

// ---------------------------------------------------------------------------
sf::FloatRect Slider::get_slider_global_bounds() const {

    if (_container == nullptr) {

        LOG(ERROR) << "_container is nullptr";
        return {};
    }

    return _container->getGlobalBounds();
}

// ---------------------------------------------------------------------------
float Slider::get_slider_percentage() const {

    return _slider_percentage;
}

// ---------------------------------------------------------------------------
void Slider::_update() {

    if (_bar == nullptr || _btn == nullptr || _container == nullptr) {

        LOG(ERROR) << "_bar or _btn or _container is nullptr";
        return;
    }

    float const btn_center_x = _btn->getGlobalBounds().position.x + (_btn->getGlobalBounds().size.x / 2.0f);
    float const bar_scale_x = _bar->getScale().x;

    sf::FloatRect const container_bounds = _container->getGlobalBounds();
    float const track_start_world = container_bounds.position.x + container_bounds.size.x * TRACK_START_RATIO;

    float const bar_left_world = track_start_world + _bar_offset;
    int const new_rect_size_x = std::max(0, static_cast<int>(
        (btn_center_x - bar_left_world) / bar_scale_x
        ));

    sf::IntRect const new_rect(
        { 0, _bar_texture_rect.position.y },
        { new_rect_size_x, _bar_texture_rect.size.y }
        );

    _bar->setTextureRect(new_rect);
}

// ---------------------------------------------------------------------------
void Slider::_update_slider_percentage(sf::Vector2f const& mouse_pos) {

    sf::FloatRect const container_bounds = _container->getGlobalBounds();
    float const track_start = container_bounds.position.x + container_bounds.size.x * TRACK_START_RATIO;
    float const track_end   = container_bounds.position.x + container_bounds.size.x * TRACK_END_RATIO;
    float const track_width = track_end - track_start;

    float mouse_x = std::clamp(mouse_pos.x, track_start, track_end);
    float percent = (mouse_x - track_start) / track_width * 100.0f;
    _slider_percentage = std::clamp(percent, 0.0f, 100.0f);

    _lbl->setString(std::format("{:.0f}", _slider_percentage));
}

// ---------------------------------------------------------------------------
void Slider::_register_events() {

    { // SLIDER DRAGGING
        Event_id const event_id = { _get_caller_id(), Event_type::MOUSE_BUTTON_LEFT_PRESS };
        Event_handler::get_instance().register_event(event_id, [this]() {
            if (_state != Widget_state::SLIDER_DRAGGING) {

                sf::Vector2i mouse_pixel = sf::Mouse::getPosition(*_window);
                sf::Vector2f mouse_world = _window->mapPixelToCoords(mouse_pixel);

                if (_btn->getGlobalBounds().contains(mouse_world)) {

                    _state = Widget_state::SLIDER_DRAGGING;
                    _btn_clicked_pos = mouse_world;
                }
            }
        });
    }

    { // MOUSE MOVED WHILE SLIDER IS DRAGGING
        Event_id const event_id = { _get_caller_id(), Event_type::MOUSE_MOVED };
        Event_handler::get_instance().register_event(event_id, [this]() {
            if (_state == Widget_state::SLIDER_DRAGGING) {

                sf::Vector2i mouse_pixel = sf::Mouse::getPosition(*_window);
                sf::Vector2f mouse_world = _window->mapPixelToCoords(mouse_pixel);

                _update_slider_percentage(mouse_world);
                sf::Vector2f const current_pos = _container->getPosition();
                set_position(current_pos);
                _btn_clicked_pos = mouse_world;
            }
        });
    }
}

} // namespace mirelight::ui