// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/menu_scene.hpp"
#include "core/asset_loader.hpp"
#include "core/ambient_music_controller.hpp"
#include "ui/ui_style.hpp"
#include "world/areas/game_session.hpp"

#include "module-app/include/application.hpp"
#include "module-app/include/application_config.hpp"
#include "module-scene/include/scene_manager.hpp"
#include "module-render/include/renderer.hpp"
#include "module-resources/include/resource_manager.hpp"
#include "module-audio/include/audio_system.hpp"
#include "module-core/config/include/config_manager.hpp"

#include "SFML/Window/VideoMode.hpp"

#include <filesystem>
#include <memory>

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan;
using namespace mirelight;

// ============================================================================
// Main
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
int main() {

    // Load persistent settings
    auto& cfg_mgr = core::Config_manager::instance();
    if (std::filesystem::exists("data/settings.json")) {

        cfg_mgr.load_auto("settings", "data/settings.json");
    }

    app::Application_config cfg;
    cfg.title = "Mirelight";
    cfg.clear_color = style::CLEAR_COLOR;

    if (cfg_mgr.has("settings")) {

        cfg.load_from_config(cfg_mgr.get("settings"));
    } else {

        // No settings file, default to native fullscreen
        auto const desktop = sf::VideoMode::getDesktopMode();
        cfg.width = desktop.size.x;
        cfg.height = desktop.size.y;
        cfg.fullscreen = true;
        cfg.vsync = true;
    }

    app::Application app(cfg);

    // Load every asset
    Asset_loader loader(resources::Resource_manager::instance());
    loader.load_all();

    scene::Scene_manager          scenes;
    Game_session                  session;
    Ambient_music_controller      ambient_music;

    app.set_on_start([&] {
        scenes.attach(app);

        // Restore audio mix from saved config
        if (cfg_mgr.has("settings")) {
            app.audio().load_mix(cfg_mgr.get("settings"));
        }

        scenes.push(std::make_unique<Menu_scene>(session));
        });

    app.set_on_stop([&] {
        // Safety net flush: persist every resident area's state on exit,
        // covering areas that never unloaded normally this session.
        session.state_store().save_all(session.save_dir());
        });

    app.set_fixed_update([&](float dt) { scenes.fixed_update(dt); });
    app.set_update([&](float dt) { session.update(dt); ambient_music.update(dt, app.audio()); scenes.update(dt); });
    app.set_render([&](render::Renderer& r) { scenes.render(r); });

    return app.run();
}
