// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/pause_scene.hpp"
#include "scenes/menu_scene.hpp"

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
#include "module-ui/include/visual.hpp"
#include "module-ui/include/visual_set.hpp"
#include "module-ui/include/widget_state.hpp"
#include "module-ui/include/ui_anchor.hpp"
#include "module-ui/include/ui_length.hpp"

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
Pause_scene::Pause_scene()
    : Scene("pause")
    {

    set_renders_below(true);
    set_updates_below(false);
}

// ----------------------------------------------------------------------------
Pause_scene::~Pause_scene() = default;

// ----------------------------------------------------------------------------
void Pause_scene::on_enter() {

    _ui = std::make_unique<UI_system>(application());
    UI_manager& gui = _ui->manager();

    // Shared button visual set
    Visual_set btn_vs;
    btn_vs.normal(Visual::texture("btn_normal"));
    btn_vs.hovered(Visual::texture("btn_selected"));
    btn_vs.pressed(Visual::texture("btn_selected", sf::Color(200, 185, 160))); // TODO: Same comment
    btn_vs.set_text(Widget_state::NORMAL, Text_appearance{"title_font", 20.0f, sf::Color(40, 15, 5)}); // TODO: Same comment

    // "PAUSED" banner label
    auto banner_lbl = std::make_unique<Label>("pause_banner");
    banner_lbl->set_anchor(UI_anchor::TOP_CENTER);
    banner_lbl->set_offset(0.0f, 18.0f);
    banner_lbl->set_size(UI_length::px(360.0f), UI_length::px(90.0f));
    banner_lbl->set_text("PAUSED");
    banner_lbl->set_align(Text_align::CENTER);
    banner_lbl->set_visual_all(Visual::texture("banner_02c"));
    banner_lbl->set_text_style_all(Text_appearance{"title_font", 36.0f, sf::Color::White});
    gui.add(std::move(banner_lbl));

    // Pause panel
    auto panel = std::make_unique<Panel>("pause_panel");
    panel->set_anchor(UI_anchor::MIDDLE_CENTER);
    panel->set_offset(0.0f, 40.0f);
    panel->set_size(UI_length::px(340.0f), UI_length::px(190.0f));
    panel->set_padding(20.0f);
    panel->set_visual_all(Visual::texture("bg_box"));

    auto box = std::make_unique<V_box>("pause_box");
    box->set_size(UI_length::pct(1.0f), UI_length::pct(1.0f));
    box->set_spacing(16.0f);
    box->set_visual_all(Visual::none());

    auto resume = std::make_unique<Button>("resume");
    resume->set_text("RESUME");
    resume->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    resume->set_visuals(btn_vs);
    resume->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        scenes().pop();
        });
    box->add_child(std::move(resume));

    auto to_menu = std::make_unique<Button>("to_menu");
    to_menu->set_text("QUIT TO MENU");
    to_menu->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    to_menu->set_visuals(btn_vs);
    to_menu->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        scenes().clear();
        scenes().push(std::make_unique<Menu_scene>());
        });
    box->add_child(std::move(to_menu));

    panel->add_child(std::move(box));
    gui.add(std::move(panel));
}

// ----------------------------------------------------------------------------
void Pause_scene::update(
    float dt
    ) {

    if (_ui) { _ui->update(dt); }
}

// ----------------------------------------------------------------------------
void Pause_scene::render(
    titan::render::Renderer&
    ) {

    if (_ui) { _ui->render(); }
}

} // namespace mirelight
