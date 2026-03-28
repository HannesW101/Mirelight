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
// Get singletons
// ---------------------------------------------------------------------------

Asset_manager& asset_manager = Asset_manager::get_instance();
Setting_manager& setting_manager = Setting_manager::get_instance();
Event_handler& event_handler = Event_handler::get_instance();

// ===========================================================================
// Functions
// ---------------------------------------------------------------------------
int main() {

    asset_manager.init();

    sf::ContextSettings ctx_settings;
    ctx_settings.antiAliasingLevel = 8u;

    Settings settings = setting_manager.get_settings();

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

            if (auto key_press = event->getIf<sf::Event::KeyReleased>()) { // TODO: Remove

                if (key_press->code == sf::Keyboard::Key::Escape) { window.close(); }
            }

            event_handler.handle_events(event);
        }

        menu_manager.update(dt);

        window.clear();

        menu_manager.draw();
        cursor_manager.draw();

        window.display();
    }

    return 0;
}