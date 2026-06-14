#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/tiles/tile.hpp"
#include "world/world_config.hpp"

#include <array>
#include <cstdint>
#include <string>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Structs
// ----------------------------------------------------------------------------

struct Chunk_coord {

    int x = 0;
    int y = 0;

    bool operator==(Chunk_coord const& o) const { return x == o.x && y == o.y; }
};

// ============================================================================
// Class Chunk
// ----------------------------------------------------------------------------

class Chunk {

public:
    explicit Chunk(Chunk_coord coord);

    Chunk_coord coord() const;

    Tile_id at(int tx, int ty) const;
    void set(int tx, int ty, Tile_id id);

    void load_or_generate(std::string const& data_dir, Tile_id default_tile);

private:
    Chunk_coord _coord;
    std::array<Tile_id, world_cfg::CHUNK_TILES * world_cfg::CHUNK_TILES> _tiles{};

    static int _index(int tx, int ty);
    void _generate(Tile_id default_tile);
};

} // namespace mirelight
