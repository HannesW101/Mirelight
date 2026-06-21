#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-scene/include/scene.hpp"
#include "module-core/events/include/event_listener.hpp"

#include "world/tiles/tile_database.hpp"
#include "world/areas/object_factory.hpp"
#include "ui/cursor_manager.hpp"

#include <memory>

// ============================================================================
// Forward declarations (1/2)
// ----------------------------------------------------------------------------

namespace titan::game { class World; class Game_object; }
namespace titan::ui   { class UI_system; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations (2/2)
// ----------------------------------------------------------------------------

class Chunk_streamer;
class Tilemap_renderer;
class Player_factory;
class Object_spawner;
class Game_session;

// ============================================================================
// Class World_scene
// ----------------------------------------------------------------------------

class World_scene final
    : public titan::scene::Scene
    , public titan::events::Event_listener
    {

public:
    explicit World_scene(Game_session& session);
    ~World_scene() override;

    void on_enter()  override;
    void on_exit()   override;
    void on_pause()  override;
    void on_resume() override;
    void update(float dt) override;
    void fixed_update(float fixed_dt) override;
    void render(titan::render::Renderer& renderer) override;

private:
    Game_session& _session;

    Tile_database                          _tiles;
    Object_factory                         _object_factory;
    std::unique_ptr<Object_spawner>        _spawner;
    std::unique_ptr<Chunk_streamer>        _streamer;
    std::unique_ptr<Tilemap_renderer>      _tilemap;
    std::unique_ptr<titan::game::World>    _world;
    std::unique_ptr<Player_factory>        _player_factory;
    std::unique_ptr<titan::ui::UI_system>  _ui;

    titan::game::Game_object* _player = nullptr;
    std::uint64_t             _escape_cb_id = 0;
    Cursor_manager            _cursor;
    bool                      _is_top = false;

    void _register_escape();
    void _deregister_escape();
};

} // namespace mirelight
