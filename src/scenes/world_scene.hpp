#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-scene/include/scene.hpp"

#include "world/tiles/tile_database.hpp"

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

// ============================================================================
// Class World_scene
// ----------------------------------------------------------------------------

class World_scene final : public titan::scene::Scene {

public:
    World_scene();
    ~World_scene() override;

    void on_enter() override;
    void update(float dt) override;
    void fixed_update(float fixed_dt) override;
    void render(titan::render::Renderer& renderer) override;

private:
    Tile_database                          _tiles;
    std::unique_ptr<Chunk_streamer>        _streamer;
    std::unique_ptr<Tilemap_renderer>      _tilemap;
    std::unique_ptr<titan::game::World>    _world;
    std::unique_ptr<Player_factory>        _player_factory;
    std::unique_ptr<titan::ui::UI_system>  _ui;

    titan::game::Game_object* _player = nullptr;
    bool                      _pause_latch = false;
};

} // namespace mirelight
