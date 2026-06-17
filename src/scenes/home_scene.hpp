#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-scene/include/scene.hpp"
#include "module-core/events/include/event_listener.hpp"

#include "world/tiles/tile_database.hpp"
#include "world/chunks/chunk.hpp"
#include "world/walkable_provider.hpp"
#include "world/areas/object_factory.hpp"
#include "world/areas/object_spawner.hpp"

#include <memory>

// ============================================================================
// Forward declarations (1/2)
// ----------------------------------------------------------------------------

namespace titan::game {

class World;
class Game_object;
}

namespace titan::ui   { class UI_system; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations (2/2)
// ----------------------------------------------------------------------------

class Tilemap_renderer;
class Player_factory;
class Game_session;

// ============================================================================
// Class Room_walkable
// ----------------------------------------------------------------------------

class Room_walkable final : public Walkable_provider {

public:
    Room_walkable(Chunk const& room, Tile_database const& tiles) : _room(room), _tiles(tiles) {}

    bool is_walkable(
        int world_tx,
        int world_ty
        ) const override {

        return _tiles.by_id(_room.at(world_tx, world_ty)).walkable;
    }

private:
    Chunk const& _room;
    Tile_database const& _tiles;
};

// ============================================================================
// Class Home_scene
// ----------------------------------------------------------------------------

class Home_scene final
    : public titan::scene::Scene
    , public titan::events::Event_listener
    {

public:
    explicit Home_scene(Game_session& session);
    ~Home_scene() override;

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
    Chunk                                  _room{ Chunk_coord{0, 0} };
    Room_walkable                          _walkable{ _room, _tiles }; // must follow _room/_tiles
    Object_factory                         _object_factory;
    std::unique_ptr<Object_spawner>        _spawner;
    std::unique_ptr<Tilemap_renderer>      _tilemap;
    std::unique_ptr<titan::game::World>    _world;
    std::unique_ptr<Player_factory>        _player_factory;
    std::unique_ptr<titan::ui::UI_system>  _ui;

    titan::game::Game_object* _player = nullptr;
    std::uint64_t             _escape_cb_id = 0;

    void _register_escape();
    void _deregister_escape();
};

} // namespace mirelight
