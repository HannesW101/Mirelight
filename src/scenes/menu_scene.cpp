// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/menu_scene.hpp"
#include "scenes/home_scene.hpp"
#include "ui/ui_style.hpp"

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
#include "module-ui/include/ui_anchor.hpp"
#include "module-ui/include/ui_length.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/render_layer.hpp"

#include "module-audio/include/audio_system.hpp"
#include "module-audio/include/audio_bus.hpp"

#include "module-resources/include/resource_manager.hpp"

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
Menu_scene::Menu_scene(
    Game_session& session
    )
    : Scene("menu")
    , _session(session)
{}

// ----------------------------------------------------------------------------
Menu_scene::~Menu_scene() = default;

// ----------------------------------------------------------------------------
void Menu_scene::on_enter() {

    auto& rm = application().resources();
    _mountains_tex = rm.get<sf::Texture>("mountains_bg");

    _cursor.load(rm);

    auto& win = application().renderer().window();
    win.setMouseCursorVisible(false);

    if (_mountains_tex) {

        auto sz     = _mountains_tex->getSize();
        auto win_sz = win.getSize();
        float sx    = static_cast<float>(win_sz.x) / static_cast<float>(sz.x);
        float sy    = static_cast<float>(win_sz.y) / static_cast<float>(sz.y);
        _bg_width   = static_cast<float>(win_sz.x);

        _bg1.emplace(*_mountains_tex);
        _bg1->setScale(sf::Vector2f{sx, sy});

        _bg2.emplace(*_mountains_tex);
        _bg2->setScale(sf::Vector2f{sx, sy});
        _bg2->setPosition(sf::Vector2f{_bg_width, 0.0f});
    }

    application().audio().music().play("music_ambient_1", true);

    // ---- Build UI ----
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

    // "MIRELIGHT" title label
    auto title = std::make_unique<Label>("title");
    title->set_anchor(UI_anchor::TOP_CENTER);
    title->set_offset(0.0f, 200.0f);
    title->set_size(UI_length::pct(0.4f), UI_length::pct(0.1f));
    title->set_text("MIRELIGHT");
    title->set_align(Text_align::CENTER);
    title->set_visual_all(Visual::none());
    title->set_text_style_all(Text_appearance{"title_font", 80.0f, sf::Color::White, sf::Color::Black, 6.0f});
    gui.add(std::move(title));

    // Menu panel
    auto panel = std::make_unique<Panel>("menu_panel");
    panel->set_anchor(UI_anchor::MIDDLE_CENTER);
    panel->set_size(UI_length::pct(0.4f), UI_length::pct(0.6f));
    panel->set_offset({0.0f, 150.0f});
    panel->set_visual_all(Visual::texture("bg_box"));

    auto box = std::make_unique<V_box>("btn_box");
    box->set_anchor(UI_anchor::MIDDLE_CENTER);
    box->set_size(UI_length::pct(0.6f), UI_length::px(274.0f));
    box->set_spacing(20.0f);
    box->set_visual_all(Visual::none());

    auto new_game = std::make_unique<Button>("new_game");
    new_game->set_text("NEW GAME");
    new_game->set_text_style_all(Text_appearance{"title_font", 30.0f, sf::Color::White, sf::Color::Black, 2.25f});
    new_game->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    new_game->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        scenes().replace_with_fade(std::make_unique<Home_scene>(_session), 0.35f);
        });
    box->add_child(std::move(new_game));

    auto cont = std::make_unique<Button>("continue");
    cont->set_text("CONTINUE");
    cont->set_text_style_all(Text_appearance{"title_font", 30.0f, sf::Color::White, sf::Color::Black, 2.25f});
    cont->set_text_style(Widget_state::DISABLED, Text_appearance{
        "title_font", 30.0f, sf::Color(255, 255, 255, 120), sf::Color(0, 0, 0, 120), 2.25f});
    cont->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    cont->set_enabled(false);
    box->add_child(std::move(cont));

    auto settings = std::make_unique<Button>("settings");
    settings->set_text("SETTINGS");
    settings->set_text_style_all(Text_appearance{"title_font", 30.0f, sf::Color::White, sf::Color::Black, 2.25f});
    settings->set_text_style(Widget_state::DISABLED, Text_appearance{
        "title_font", 30.0f, sf::Color(255, 255, 255, 120), sf::Color(0, 0, 0, 120), 2.25f});
    settings->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
    settings->set_enabled(false);
    box->add_child(std::move(settings));

    auto exit_btn = std::make_unique<Button>("exit");
    exit_btn->set_text("EXIT");
    exit_btn->set_text_style_all(Text_appearance{"title_font", 30.0f, sf::Color::White, sf::Color::Black, 2.25f});
    exit_btn->set_size(UI_length::pct(1.0f), UI_length::px(58.0f));
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

    _bg_scroll -= 20.0f * dt;
    if (_bg_scroll <= -_bg_width) { _bg_scroll = 0.0f; }
    if (_bg1) { _bg1->setPosition(sf::Vector2f{_bg_scroll, 0.0f}); }
    if (_bg2) { _bg2->setPosition(sf::Vector2f{_bg_scroll + _bg_width, 0.0f}); }

    if (_ui) {

        bool any_hovered = false;
        for (char const* name : {"new_game", "continue", "settings", "exit"}) {

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
void Menu_scene::render(
    titan::render::Renderer& renderer
    ) {

    if (_bg1) { renderer.submit(Render_layer::UI, *_bg1, sf::RenderStates::Default, style::BG_DEPTH); }
    if (_bg2) { renderer.submit(Render_layer::UI, *_bg2, sf::RenderStates::Default, style::BG_DEPTH); }
    if (_ui)  { _ui->render(); }
    _cursor.render(renderer);
}

} // namespace mirelight
