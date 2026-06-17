// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/chunks/chunk_streamer.hpp"
#include "world/tiles/tile_database.hpp"
#include "world/areas/object_spawner.hpp"
#include "world/world_config.hpp"

#include <cmath>
#include <utility>
#include <vector>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

namespace {

constexpr int N  = world_cfg::CHUNK_TILES;
constexpr int CP = world_cfg::CHUNK_PIXELS;
}

// ============================================================================
// Helper functions
// ----------------------------------------------------------------------------

namespace {

int floor_div(
    int a,
    int b
    ) {

    int q = a / b;
    int r = a % b;
    if ((r != 0) && ((r < 0) != (b < 0))) { --q; }

    return q;
}
}

// ============================================================================
// Class Chunk_streamer
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Chunk_streamer::Chunk_streamer(
    Tile_database& tiles,
    std::string data_dir,
    Object_spawner* spawner,
    titan::game::World* world
    )
    : _tiles(tiles)
    , _data_dir(std::move(data_dir))
    , _spawner(spawner)
    , _world(world)
    {

    // Default ground tile = first named "grass", else id 1
    Tile_id g = _tiles.id_of("grass");
    _default_tile = (g != 0) ? g : Tile_id{ 1 };
}

// ----------------------------------------------------------------------------
Chunk_coord Chunk_streamer::world_to_chunk(
    sf::Vector2f world_pos
    ) {

    int const px = static_cast<int>(std::floor(world_pos.x));
    int const py = static_cast<int>(std::floor(world_pos.y));

    return Chunk_coord{ floor_div(px, CP), floor_div(py, CP) };
}

// ----------------------------------------------------------------------------
void Chunk_streamer::update(
    sf::Vector2f player_world_pos
    ) {

    Chunk_coord const center = world_to_chunk(player_world_pos);
    int const R = world_cfg::STREAM_RADIUS;

    // Load any chunk in range that isn't resident
    for (int dy = -R; dy <= R; ++dy) {

        for (int dx = -R; dx <= R; ++dx) {

            _ensure_loaded(Chunk_coord{ center.x + dx, center.y + dy });
        }
    }

    // Unload chunks that drifted out of range
    std::vector<Chunk_coord> to_drop;
    for (auto const& [coord, chunk] : _chunks) {

        if (std::abs(coord.x - center.x) > R || std::abs(coord.y - center.y) > R) {

            to_drop.push_back(coord);
        }
    }

    for (auto const& c : to_drop) {

        if (_spawner && _world) { _spawner->unload_area(Area_id::chunk(c.x, c.y), *_world); }
        _chunks.erase(c);
    }
}

// ----------------------------------------------------------------------------
void Chunk_streamer::_ensure_loaded(
    Chunk_coord c
    ) {

    if (_chunks.find(c) != _chunks.end()) { return; }

    auto chunk = std::make_unique<Chunk>(c);
    chunk->load_or_generate(_data_dir, _default_tile);
    _chunks.emplace(c, std::move(chunk));

    if (_spawner && _world) {

        sf::Vector2f const origin{
            static_cast<float>(c.x * world_cfg::CHUNK_PIXELS),
            static_cast<float>(c.y * world_cfg::CHUNK_PIXELS)
            };
        _spawner->spawn_area(Area_id::chunk(c.x, c.y), origin, *_world);
    }
}

// ----------------------------------------------------------------------------
Tile_id Chunk_streamer::tile_at(
    int world_tx,
    int world_ty
    ) const {

    Chunk_coord const c{ floor_div(world_tx, N), floor_div(world_ty, N) };

    auto it = _chunks.find(c);
    if (it == _chunks.end()) { return 0; }

    int const lx = world_tx - c.x * N;
    int const ly = world_ty - c.y * N;
    return it->second->at(lx, ly);
}

// ----------------------------------------------------------------------------
bool Chunk_streamer::is_walkable(
    int world_tx,
    int world_ty
    ) const {

    return _tiles.by_id(tile_at(world_tx, world_ty)).walkable;
}

// ----------------------------------------------------------------------------
Chunk_streamer::Chunk_map const& Chunk_streamer::chunks() const {

    return _chunks;
}

} // namespace mirelight
