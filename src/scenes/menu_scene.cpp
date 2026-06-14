// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/menu_scene.hpp"
#include "scenes/world_scene.hpp"

#include "module-app/include/application.hpp"
#include "module-scene/include/scene_manager.hpp"
#include "module-utils/include/logger.hpp"

#include "module-ui/include/ui_system.hpp"
#include "module-ui/include/ui_manager.hpp"
#include "module-ui/include/panel.hpp"
#include "module-ui/include/boxes.hpp"
#include "module-ui/include/label.hpp"
#include "module-ui/include/button.hpp"
#include "module-ui/include/image.hpp"
#include "module-ui/include/visual.hpp"
#include "module-ui/include/visual_set.hpp"
#include "module-ui/include/widget_state.hpp"
#include "module-ui/include/ui_anchor.hpp"
#include "module-ui/include/ui_length.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/render_layer.hpp"

#include "module-audio/include/audio_system.hpp"
#include "module-audio/include/audio_bus.hpp"

#include "module-resources/include/resource_manager.hpp"

#include "SFML/Window/Mouse.hpp"

#include <memory>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::ui;
using namespace titan::render;
using namespace titan::audio;

// ============================================================================
// Class Menu_scene
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Menu_scene::Menu_scene()
    : Scene("menu")
{}

// ----------------------------------------------------------------------------
Menu_scene::~Menu_scene() = default;

// ----------------------------------------------------------------------------
void Menu_scene::on_enter() {

    auto& win = application().renderer().window();
    win.setMouseCursorVisible(false);

    auto& rm = application().resources();
    _mountains_tex = rm.get<sf::Texture>("mountains_bg");
    _cursor_n_tex = rm.get<sf::Texture>("cursor_gauntlet");
    _cursor_h_tex = rm.get<sf::Texture>("cursor_magic");

    // Background
    if (_mountains_tex) {

        auto const sz = _mountains_tex->getSize();
        auto const win_sz = win.getSize();
        float const sx = static_cast<float>(win_sz.x) / static_cast<float>(sz.x);
        float const sy = static_cast<float>(win_sz.y) / static_cast<float>(sz.y);
        _bg_width = static_cast<float>(win_sz.x);

        _bg1.emplace(*_mountains_tex);
        _bg1->setScale({sx, sy});

        _bg2.emplace(*_mountains_tex);
        _bg2->setScale({sx, sy});
        _bg2->setPosition({_bg_width, 0.0f});
    }

    // Cursor
    if (_cursor_n_tex) {

        _cursor.emplace(*_cursor_n_tex);
    }

    // Music
    application().audio().music().play("music_ambient_1", true);

    // Build UI
    _ui = std::make_unique<UI_system>(application());
    UI_manager& gui = _ui->manager();

    // Shared button visual set
    Visual_set btn_vs;
    btn_vs.normal(Visual::texture("btn_normal"));
    btn_vs.hovered(Visual::texture("btn_selected"));
    btn_vs.pressed(Visual::texture("btn_selected", sf::Color(200, 185, 160))); // TODO: What is this? rather have shared file for colors that makes sense other than this magic color
    btn_vs.disabled(Visual::texture("btn_normal", sf::Color(160, 160, 160, 120))); // TODO: What is this? rather have shared file for colors that makes sense other than this magic color
    btn_vs.set_text(Widget_state::NORMAL, Text_appearance{"title_font", 20.0f, sf::Color(40, 15, 5)}); // // TODO: What is this? rather have shared file for colors that makes sense other than this magic color

    // Title banner image
    auto banner = std::make_unique<Image>("banner");
    banner->set_anchor(UI_anchor::TOP_CENTER);
    banner->set_offset(0.0f, 18.0f);
    banner->set_size(UI_length::px(440.0f), UI_length::px(110.0f));
    banner->set_texture("banner_02c");
    banner->set_preserve_aspect(false);
    gui.add(std::move(banner));

    // "MIRELIGHT" title label overlaid on the banner
    auto title = std::make_unique<Label>("title");
    title->set_anchor(UI_anchor::TOP_CENTER);
    title->set_offset(0.0f, 36.0f);
    title->set_size(UI_length::px(440.0f), UI_length::px(68.0f));
    title->set_text("MIRELIGHT");
    title->set_align(Text_align::CENTER);
    title->set_visual_all(Visual::none());
    title->set_text_style_all(Text_appearance{"title_font", 48.0f, sf::Color::White});
    gui.add(std::move(title));

    // Menu panel holding the four buttons
    auto panel = std::make_unique<Panel>("menu_panel");
    panel->set_anchor(UI_anchor::MIDDLE_CENTER);
    panel->set_offset(0.0f, 62.0f);
    panel->set_size(UI_length::px(380.0f), UI_length::px(318.0f));
    panel->set_padding(18.0f);
    panel->set_visual_all(Visual::texture("bg_box"));

    auto box = std::make_unique<V_box>("btn_box");
    box->set_size(UI_length::pct(1.0f), UI_length::pct(1.0f));
    box->set_spacing(14.0f);
    box->set_visual_all(Visual::none());

    // New Game
    auto new_game = std::make_unique<Button>("new_game");
    new_game->set_text("NEW GAME");
    new_game->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    new_game->set_visuals(btn_vs);
    new_game->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        scenes().replace(std::make_unique<World_scene>());
        });
    box->add_child(std::move(new_game));

    // Continue
    auto cont = std::make_unique<Button>("continue");
    cont->set_text("CONTINUE");
    cont->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    cont->set_visuals(btn_vs);
    cont->set_enabled(false);
    box->add_child(std::move(cont));

    // Settings
    auto settings = std::make_unique<Button>("settings");
    settings->set_text("SETTINGS");
    settings->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    settings->set_visuals(btn_vs);
    settings->set_enabled(false);
    box->add_child(std::move(settings));

    // Exit
    auto exit_btn = std::make_unique<Button>("exit");
    exit_btn->set_text("EXIT");
    exit_btn->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    exit_btn->set_visuals(btn_vs);
    exit_btn->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        application().quit();
        });
    box->add_child(std::move(exit_btn));

    panel->add_child(std::move(box));
    gui.add(std::move(panel));
}

// ----------------------------------------------------------------------------
void Menu_scene::on_exit() {

    application().renderer().window().setMouseCursorVisible(true);
}

// ----------------------------------------------------------------------------
void Menu_scene::update(
    float dt
    ) {

    // Scroll background
    _bg_scroll -= 20.0f * dt;
    if (_bg_scroll <= -_bg_width) { _bg_scroll = 0.0f; }
    if (_bg1) { _bg1->setPosition({_bg_scroll, 0.0f}); }
    if (_bg2) { _bg2->setPosition({_bg_scroll + _bg_width, 0.0f}); }

    // Custom cursor
    if (_cursor && _ui) { // TODO: I am sure we will use many cursors should we not have a better way to handle it? SHould it be in library or in our game?

        auto mpos = sf::Mouse::getPosition(application().renderer().window());
        _cursor->setPosition(
            {static_cast<float>(mpos.x),
            static_cast<float>(mpos.y)}
            );

        bool any_hovered = false;
        for (char const* name : {"new_game", "continue", "settings", "exit"}) {

            auto* w = _ui->manager().find(name);
            if (w && w->is_hovered()) { any_hovered = true; break; }
        }

        if (any_hovered && !_cursor_hovering) {

            application().audio().play_sfx("sfx_ui_hover", Audio_bus::UI);
        }

        _cursor_hovering = any_hovered;

        auto* tex = any_hovered ? _cursor_h_tex.get() : _cursor_n_tex.get();
        if (tex) { _cursor->setTexture(*tex); }
    }

    if (_ui) { _ui->update(dt); }
}

// ----------------------------------------------------------------------------
void Menu_scene::render(
    titan::render::Renderer& renderer
    ) {

    // Mountains background drawn first
    if (_bg1) { renderer.submit(Render_layer::UI, *_bg1, sf::RenderStates::Default, -1000.0f); } // TODO: More magic numbers?
    if (_bg2) { renderer.submit(Render_layer::UI, *_bg2, sf::RenderStates::Default, -1000.0f); } // TODO: More magic numbers?

    if (_ui) { _ui->render(); }

    // Cursor always on top
    if (_cursor) { renderer.submit(Render_layer::UI_OVERLAY, *_cursor); }
}

} // namespace mirelight
