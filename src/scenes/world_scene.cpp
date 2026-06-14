// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/world_scene.hpp"
#include "scenes/pause_scene.hpp"
#include "world/chunks/chunk_streamer.hpp"
#include "world/rendering/tilemap_renderer.hpp"
#include "world/world_config.hpp"
#include "entities/player/player_factory.hpp"

#include "module-app/include/application.hpp"
#include "module-scene/include/scene_manager.hpp"

#include "module-game/include/world.hpp"
#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/camera.hpp"

#include "module-ui/include/ui_system.hpp"
#include "module-ui/include/ui_manager.hpp"
#include "module-ui/include/label.hpp"
#include "module-ui/include/ui_anchor.hpp"
#include "module-ui/include/ui_length.hpp"

#include "module-audio/include/audio_system.hpp"

#include "SFML/Window/Keyboard.hpp"

#include <memory>
#include <string>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::game;
using namespace titan::ui;

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

namespace {

char const* const DATA_DIR = "data"; // TODO maybe move constants like these to a shared location file
}

// ============================================================================
// Class World_scene
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
World_scene::World_scene()
    : Scene("world")
{}

// ----------------------------------------------------------------------------
World_scene::~World_scene() = default;

// ----------------------------------------------------------------------------
void World_scene::on_enter() {

    // Tile definitions
    _tiles.load(std::string(DATA_DIR) + "/tiles.json");

    _streamer = std::make_unique<Chunk_streamer>(_tiles, DATA_DIR);
    _tilemap  = std::make_unique<Tilemap_renderer>(_tiles, application().resources());
    _world    = std::make_unique<World>();

    _player_factory = std::make_unique<Player_factory>(*_world, *_streamer, application().renderer().world_camera());

    // Spawn the player near the origin and stream the first chunks around it.
    sf::Vector2f const start{ 4.0f * world_cfg::TILE_SIZE, 4.0f * world_cfg::TILE_SIZE };
    _streamer->update(start);
    _player = _player_factory->create(start);

    // Crossfade to a different ambient track for the world
    application().audio().music().crossfade_to("music_ambient_2", 2.0f, true);

    // HUD
    _ui = std::make_unique<UI_system>(application());
    auto coords = std::make_unique<Label>("hud_coords");
    coords->set_anchor(UI_anchor::TOP_LEFT);
    coords->set_offset(12.0f, 12.0f);
    coords->set_size(UI_length::px(360.0f), UI_length::px(24.0f));
    coords->set_text("Mirelight");
    _ui->manager().add(std::move(coords));
}

// ----------------------------------------------------------------------------
void World_scene::fixed_update(
    float fixed_dt
    ) {

    if (_world) { _world->fixed_update(fixed_dt); }
}

// ----------------------------------------------------------------------------
void World_scene::update(
    float dt
    ) {

    if (!_world) { return; }

    _world->update(dt);

    application().renderer().world_camera().tick(dt);

    // Stream chunks around the player's new position
    if (_player) {

        _streamer->update(_player->transform().position());

        if (auto* label = static_cast<Label*>(_ui->manager().find("hud_coords"))) {

            sf::Vector2f const p = _player->transform().position();
            int const tx = static_cast<int>(p.x) / world_cfg::TILE_SIZE;
            int const ty = static_cast<int>(p.y) / world_cfg::TILE_SIZE;

            label->set_text("Tile (" + std::to_string(tx) + ", " + std::to_string(ty) + ")   Chunks: " + std::to_string(_streamer->chunks().size()));
        }
    }

    _ui->update(dt);

    // Pause overlay on Escape
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) { // TODO same comment for events

        if (!_pause_latch) {

            _pause_latch = true;
            scenes().push(std::make_unique<Pause_scene>());
        }
    } else {

        _pause_latch = false;
    }
}

// ----------------------------------------------------------------------------
void World_scene::render(
    titan::render::Renderer& renderer
    ) {

    if (_tilemap && _streamer) { _tilemap->render(*_streamer, renderer); }
    if (_world) { _world->render(renderer); }
    if (_ui) { _ui->render(); }
}

} // namespace mirelight
