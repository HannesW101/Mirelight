// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/pause_scene.hpp"
#include "scenes/menu_scene.hpp"
#include "ui/ui_style.hpp"

#include "module-app/include/application.hpp"
#include "module-scene/include/scene_manager.hpp"

#include "module-audio/include/audio_system.hpp"
#include "module-audio/include/audio_bus.hpp"

#include "module-ui/include/ui_system.hpp"
#include "module-ui/include/ui_manager.hpp"
#include "module-ui/include/panel.hpp"
#include "module-ui/include/boxes.hpp"
#include "module-ui/include/label.hpp"
#include "module-ui/include/button.hpp"
#include "module-ui/include/image.hpp"
#include "module-ui/include/visual.hpp"
#include "module-ui/include/ui_anchor.hpp"
#include "module-ui/include/ui_length.hpp"

#include "module-render/include/renderer.hpp"

#include <memory>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::ui;
using namespace titan::audio;

// ============================================================================
// Class Pause_scene
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Pause_scene::Pause_scene(Game_session& session)
    : Scene("pause")
    , _session(session)
    {

    set_renders_below(true);
    set_updates_below(false);
}

// ----------------------------------------------------------------------------
Pause_scene::~Pause_scene() = default;

// ----------------------------------------------------------------------------
void Pause_scene::on_enter() {

    _cursor.load(application().resources());
    application().renderer().window().setMouseCursorVisible(false);

    _ui = std::make_unique<UI_system>(application());
    _ui->manager().set_theme(style::mirelight_theme());
    UI_manager& gui = _ui->manager();

    // Title banner image
    auto banner = std::make_unique<Image>("banner");
    banner->set_anchor(UI_anchor::TOP_CENTER);
    banner->set_offset(0.0f, 60.0f);
    banner->set_size(UI_length::px(1200.0f), UI_length::px(400.0f));
    banner->set_texture("banner_02c");
    banner->set_preserve_aspect(false);
    gui.add(std::move(banner));

    // "PAUSED" title label
    auto title = std::make_unique<Label>("title");
    title->set_anchor(UI_anchor::TOP_CENTER);
    title->set_offset(0.0f, 200.0f);
    title->set_size(UI_length::pct(0.4f), UI_length::pct(0.1f));
    title->set_text("PAUSED");
    title->set_align(Text_align::CENTER);
    title->set_visual_all(Visual::none());
    title->set_text_style_all(Text_appearance{"title_font", 80.0f, sf::Color::White, sf::Color::Black, 6.0f});
    gui.add(std::move(title));

    // Menu panel
    auto panel = std::make_unique<Panel>("pause_panel");
    panel->set_anchor(UI_anchor::MIDDLE_CENTER);
    panel->set_size(UI_length::pct(0.4f), UI_length::pct(0.6f));
    panel->set_offset({0.0f, 150.0f});
    panel->set_visual_all(Visual::texture("bg_box"));

    auto box = std::make_unique<V_box>("pause_box");
    box->set_anchor(UI_anchor::MIDDLE_CENTER);
    box->set_size(UI_length::pct(0.6f), UI_length::px(274.0f));
    box->set_spacing(20.0f);
    box->set_visual_all(Visual::none());

    auto resume = std::make_unique<Button>("resume");
    resume->set_text("RESUME");
    resume->set_text_style_all(Text_appearance{"title_font", 30.0f, sf::Color::White, sf::Color::Black, 2.25f});
    resume->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    resume->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        scenes().pop();
        });
    box->add_child(std::move(resume));

    auto settings = std::make_unique<Button>("settings");
    settings->set_text("SETTINGS");
    settings->set_text_style_all(Text_appearance{"title_font", 30.0f, sf::Color::White, sf::Color::Black, 2.25f});
    settings->set_text_style(Widget_state::DISABLED, Text_appearance{
        "title_font", 30.0f, sf::Color(255, 255, 255, 120), sf::Color(0, 0, 0, 120), 2.25f});
    settings->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    settings->set_enabled(false);
    box->add_child(std::move(settings));

    auto to_menu = std::make_unique<Button>("to_menu");
    to_menu->set_text("QUIT TO MENU");
    to_menu->set_text_style_all(Text_appearance{"title_font", 30.0f, sf::Color::White, sf::Color::Black, 2.25f});
    to_menu->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    to_menu->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        scenes().clear();
        scenes().push(std::make_unique<Menu_scene>(_session));
        });
    box->add_child(std::move(to_menu));

    panel->add_child(std::move(box));
    gui.add(std::move(panel));
}

// ----------------------------------------------------------------------------
void Pause_scene::on_exit() {

    application().renderer().window().setMouseCursorVisible(true);
}

// ----------------------------------------------------------------------------
void Pause_scene::update(
    float dt
    ) {

    if (_ui) {

        bool any_hovered = false;
        for (char const* name : {"resume", "settings", "to_menu"}) {

            auto* w = _ui->manager().find(name);
            if (w && w->is_hovered()) { any_hovered = true; break; }
        }

        Cursor_mode const new_mode = any_hovered ? Cursor_mode::GAUNTLET_MAGIC : Cursor_mode::GAUNTLET;

        if (_cursor.set_mode(new_mode)) {

            application().audio().play_sfx("sfx_ui_hover", Audio_bus::UI);
        }

        _cursor.update(application().renderer().window());
        _ui->update(dt);
    }
}

// ----------------------------------------------------------------------------
void Pause_scene::render(
    titan::render::Renderer& renderer
    ) {

    if (_ui) { _ui->render(); }
    _cursor.render(renderer);
}

} // namespace mirelight
