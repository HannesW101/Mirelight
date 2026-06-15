// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/world_scene.hpp"
#include "scenes/pause_scene.hpp"
#include "core/paths.hpp"
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
#include "module-audio/include/audio_bus.hpp"

#include "module-core/events/include/sfml_event_manager.hpp"
#include "module-core/events/include/event_type.hpp"

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
using namespace titan::events;

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
void World_scene::_register_escape() {

    _escape_cb_id = SFML_event_manager::instance().register_callback(
        SFML_event_type::KEYPRESS_ESCAPE,
        [this](SFML_event_data const&) {
            application().audio().play_sfx("sfx_ui_click", titan::audio::Audio_bus::UI);
            scenes().push(std::make_unique<Pause_scene>());
            },
        listener_id()
        );
}

// ----------------------------------------------------------------------------
void World_scene::_deregister_escape() {

    if (_escape_cb_id != 0) {

        SFML_event_manager::instance().deregister_callback(_escape_cb_id);
        _escape_cb_id = 0;
    }
}

// ----------------------------------------------------------------------------
void World_scene::on_enter() {

    std::string const data_dir{paths::DATA};
    _tiles.load(data_dir + "/tiles.json");

    _streamer = std::make_unique<Chunk_streamer>(_tiles, data_dir);
    _tilemap  = std::make_unique<Tilemap_renderer>(_tiles, application().resources());
    _world    = std::make_unique<World>();

    _player_factory = std::make_unique<Player_factory>(
        *_world,
        *_streamer,
        application().renderer().world_camera()
        );

    sf::Vector2f const start{4.0f * world_cfg::TILE_SIZE, 4.0f * world_cfg::TILE_SIZE};
    _streamer->update(start);
    _player = _player_factory->create(start);

    application().audio().music().crossfade_to("music_ambient_2", 2.0f, true);

    _ui = std::make_unique<UI_system>(application());
    auto coords = std::make_unique<Label>("hud_coords");
    coords->set_anchor(UI_anchor::TOP_LEFT);
    coords->set_offset(12.0f, 12.0f);
    coords->set_size(UI_length::px(360.0f), UI_length::px(24.0f));
    coords->set_text("Mirelight");
    _ui->manager().add(std::move(coords));

    _register_escape();
}

// ----------------------------------------------------------------------------
void World_scene::on_exit() {

    _deregister_escape();
}

// ----------------------------------------------------------------------------
void World_scene::on_pause() {

    _deregister_escape();
}

// ----------------------------------------------------------------------------
void World_scene::on_resume() {

    _register_escape();
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
