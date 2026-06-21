#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-scene/include/scene.hpp"
#include "module-core/events/include/event_listener.hpp"
#include "ui/cursor_manager.hpp"

#include "world/tiles/tile_database.hpp"
#include "world/chunks/chunk.hpp"
#include "world/walkable_provider.hpp"
#include "world/world_config.hpp"
#include "world/areas/object_factory.hpp"
#include "world/areas/object_spawner.hpp"

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <cstdint>
#include <memory>
#include <vector>

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
    Room_walkable(
        std::vector<std::unique_ptr<Chunk>> const& chunks,
        Tile_database const& tiles,
        int chunk_cols,
        int chunk_rows
        )
        : _chunks(chunks)
        , _tiles(tiles)
        , _chunk_cols(chunk_cols)
        , _chunk_rows(chunk_rows)
    {}

    bool is_walkable(
        int world_tx,
        int world_ty
        ) const override {

        if (world_tx < 0 || world_ty < 0) { return false; }

        constexpr int N = world_cfg::CHUNK_TILES;
        int const cx = world_tx / N;
        int const cy = world_ty / N;
        if (cx >= _chunk_cols || cy >= _chunk_rows) { return false; }

        int const idx = cy * _chunk_cols + cx;
        if (idx >= static_cast<int>(_chunks.size()) || !_chunks[idx]) { return false; }

        return _tiles.by_id(_chunks[idx]->at(world_tx % N, world_ty % N)).walkable;
    }

private:
    std::vector<std::unique_ptr<Chunk>> const& _chunks;
    Tile_database const& _tiles;
    int _chunk_cols;
    int _chunk_rows;
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

    // Chunk grid dimensions, if changed then
    // add matching N_M.chunk files under data/areas/home/.
    static constexpr int CHUNK_COLS = 4;
    static constexpr int CHUNK_ROWS = 2;

private:
    Game_session& _session;

    Tile_database                          _tiles;
    std::vector<std::unique_ptr<Chunk>>    _chunks;
    Room_walkable                          _walkable{ _chunks, _tiles, CHUNK_COLS, CHUNK_ROWS };
    Object_factory                         _object_factory;
    std::unique_ptr<Object_spawner>        _spawner;
    std::unique_ptr<Tilemap_renderer>      _tilemap;
    std::unique_ptr<titan::game::World>    _world;
    std::unique_ptr<Player_factory>        _player_factory;
    std::unique_ptr<titan::ui::UI_system>  _ui;

    titan::game::Game_object* _player = nullptr;
    titan::game::Game_object* _wife   = nullptr;
    std::uint64_t _escape_cb_id = 0;
    Cursor_manager _cursor;
    bool           _is_top = false;
    std::uint64_t _rmb_cb_id    = 0;
    sf::VertexArray    _wall_mesh;
    sf::Texture const* _interior_tex = nullptr;

    void _register_escape();
    void _deregister_escape();
    void _register_rmb();
    void _deregister_rmb();
    void _build_wall_mesh();
    void _spawn_quest_indicator();
};

} // namespace mirelight
