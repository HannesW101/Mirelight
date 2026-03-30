// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_manager.h"
#include "menus/menu_manager.h"
#include "settings/setting_manager.h"
#include "cursors/cursor_manager.h"
#include "events/event_handler.h"

#include <SFML/Graphics.hpp>

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::assets;
using namespace mirelight::menus;
using namespace mirelight::settings;
using namespace mirelight::cursors;
using namespace mirelight::events;

// ===========================================================================
// Functions
// ---------------------------------------------------------------------------
int main() {

    Asset_manager::get_instance().init();

    sf::ContextSettings ctx_settings;
    ctx_settings.antiAliasingLevel = 8u;

    Settings settings = Setting_manager::get_instance().get_settings();

    sf::RenderWindow window(
        sf::VideoMode({
            static_cast<unsigned int>(settings.window_width),
            static_cast<unsigned int>(settings.window_height)
            }),
        "Mirelight",
        sf::Style::Default,
        sf::State::Fullscreen,
        ctx_settings
        );

    if (settings.vsync) {

        window.setVerticalSyncEnabled(settings.vsync);
    } else {

        window.setFramerateLimit(settings.fps_cap);
    }

    Menu_manager& menu_manager = Menu_manager::get_instance(&window);
    Cursor_manager& cursor_manager = Cursor_manager::get_instance(&window);

    sf::Clock clock;

    while (window.isOpen()) {

        float const dt = clock.restart().asSeconds();

        while (std::optional<sf::Event> const event = window.pollEvent()) {

            Event_handler::get_instance().handle_events(event);
        }

        menu_manager.update(dt);

        window.clear();

        menu_manager.draw();
        cursor_manager.draw();

        window.display();
    }

    return 0;
}