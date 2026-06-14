// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/menu_scene.hpp"
#include "core/asset_loader.hpp"

#include "module-app/include/application.hpp"
#include "module-app/include/application_config.hpp"
#include "module-scene/include/scene_manager.hpp"
#include "module-render/include/renderer.hpp"
#include "module-resources/include/resource_manager.hpp"
#include "module-audio/include/audio_system.hpp"
#include "module-audio/include/audio_bus.hpp"
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
    cfg.clear_color = sf::Color(20, 24, 28); // TODO: Magic color

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

    scene::Scene_manager scenes;
    app.set_on_start([&] {
        scenes.attach(app);

        // Restore audio volumes from saved config
        if (cfg_mgr.has("settings")) {

            auto const& s = cfg_mgr.get("settings");
            auto const music_vol = static_cast<float>(s.get_or<double>("audio", "music", 0.7));
            auto const sfx_vol   = static_cast<float>(s.get_or<double>("audio", "sfx",   0.8));
            app.audio().set_bus_volume(audio::Audio_bus::MUSIC, music_vol);
            app.audio().set_bus_volume(audio::Audio_bus::SFX, sfx_vol);
        }

        scenes.push(std::make_unique<Menu_scene>());
        });

    app.set_fixed_update([&](float dt) { scenes.fixed_update(dt); });
    app.set_update([&](float dt) { scenes.update(dt); });
    app.set_render([&](render::Renderer& r) { scenes.render(r); });

    return app.run();
}
