// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/home_scene.hpp"
#include "scenes/pause_scene.hpp"
#include "core/paths.hpp"
#include "world/rendering/tilemap_renderer.hpp"
#include "world/world_config.hpp"
#include "world/areas/object_spawner.hpp"
#include "world/areas/game_session.hpp"
#include "entities/player/player_factory.hpp"

#include "module-app/include/application.hpp"
#include "module-scene/include/scene_manager.hpp"

#include "module-game/include/world.hpp"
#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/camera.hpp"

#include "module-ui/include/ui_system.hpp"

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
// Class Home_scene
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Home_scene::Home_scene(
    Game_session& session
    )
    : Scene("home")
    , _session(session)
{}

// ----------------------------------------------------------------------------
Home_scene::~Home_scene() = default;

// ----------------------------------------------------------------------------
void Home_scene::_register_escape() {

    _escape_cb_id = SFML_event_manager::instance().register_callback(
        SFML_event_type::KEYPRESS_ESCAPE,
        [this](SFML_event_data const&) {
            application().audio().play_sfx("sfx_ui_click", titan::audio::Audio_bus::UI);
            scenes().push(std::make_unique<Pause_scene>(_session));
            },
        listener_id()
        );
}

// ----------------------------------------------------------------------------
void Home_scene::_deregister_escape() {

    if (_escape_cb_id != 0) {

        SFML_event_manager::instance().deregister_callback(_escape_cb_id);
        _escape_cb_id = 0;
    }
}

// ----------------------------------------------------------------------------
void Home_scene::on_enter() {

    std::string const data_dir{paths::DATA};
    _tiles.load(data_dir + "/tiles.json");

    _room.load_from_path(data_dir + "/areas/home/0_0.chunk", 0);

    register_default_object_types(_object_factory);
    _world   = std::make_unique<World>();
    _spawner = std::make_unique<Object_spawner>(
        Spawn_table_loader(data_dir),
        _object_factory,
        _session.state_store(),
        _session
        );
    _spawner->spawn_area(
        Area_id::interior("home"),
        sf::Vector2f{0.0f, 0.0f},
        *_world
        );

    _tilemap = std::make_unique<Tilemap_renderer>(_tiles, application().resources());

    _player_factory = std::make_unique<Player_factory>(
        *_world,
        _walkable,
        application().renderer().world_camera()
        );

    sf::Vector2f const start{4.0f * world_cfg::TILE_SIZE, 3.0f * world_cfg::TILE_SIZE};
    _player = _player_factory->create(start);

    application().audio().music().crossfade_to("music_ambient_1", 2.0f, true);

    _ui = std::make_unique<UI_system>(application());

    _register_escape();
}

// ----------------------------------------------------------------------------
void Home_scene::on_exit() {

    _deregister_escape();

    if (_spawner && _world) { _spawner->unload_area(Area_id::interior("home"), *_world); }
}

// ----------------------------------------------------------------------------
void Home_scene::on_pause() {

    _deregister_escape();
}

// ----------------------------------------------------------------------------
void Home_scene::on_resume() {

    _register_escape();
}

// ----------------------------------------------------------------------------
void Home_scene::fixed_update(
    float fixed_dt
    ) {

    if (_world) { _world->fixed_update(fixed_dt); }
}

// ----------------------------------------------------------------------------
void Home_scene::update(
    float dt
    ) {

    if (!_world) { return; }

    _world->update(dt);
    application().renderer().world_camera().tick(dt);

    if (_ui) { _ui->update(dt); }
}

// ----------------------------------------------------------------------------
void Home_scene::render(
    titan::render::Renderer& renderer
    ) {

    if (_tilemap) { _tilemap->render_chunk(_room, 0, 0, renderer); }
    if (_world) { _world->render(renderer); }
    if (_ui) { _ui->render(); }
}

} // namespace mirelight
