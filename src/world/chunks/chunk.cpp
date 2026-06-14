// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/chunks/chunk.hpp"

#include "module-utils/include/random.hpp"

#include <fstream>
#include <sstream>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

namespace {

constexpr int N = world_cfg::CHUNK_TILES;
}

// ============================================================================
// Class Chunk
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Chunk::Chunk(
    Chunk_coord coord
    )
    : _coord(coord)
{}

// ----------------------------------------------------------------------------
Chunk_coord Chunk::coord() const {

    return _coord;
}

// ----------------------------------------------------------------------------
int Chunk::_index(
    int tx,
    int ty
    ) {

    return ty * N + tx;
}

// ----------------------------------------------------------------------------
Tile_id Chunk::at(
    int tx,
    int ty
    ) const {

    if (tx < 0 || ty < 0 || tx >= N || ty >= N) { return 0; }

    return _tiles[static_cast<std::size_t>(_index(tx, ty))];
}

// ----------------------------------------------------------------------------
void Chunk::set(
    int tx,
    int ty,
    Tile_id id
    ) {

    if (tx < 0 || ty < 0 || tx >= N || ty >= N) { return; }

    _tiles[static_cast<std::size_t>(_index(tx, ty))] = id;
}

// ----------------------------------------------------------------------------
void Chunk::load_or_generate(
    std::string const& data_dir,
    Tile_id default_tile
    ) {

    // Chunk files are named "<x>_<y>.chunk" under data_dir/world/
    std::ostringstream path;
    path << data_dir << "/world/" << _coord.x << "_" << _coord.y << ".chunk";

    std::ifstream file(path.str());
    if (file.is_open()) {

        // Simple whitespace separated id grid
        for (int i = 0; i < N * N; ++i) {

            int v = 0;
            if (!(file >> v)) { v = default_tile; }

            _tiles[static_cast<std::size_t>(i)] = static_cast<Tile_id>(v);
        }

        return;
    }

    _generate(default_tile);
}

// ----------------------------------------------------------------------------
void Chunk::_generate(
    Tile_id default_tile
    ) {

    // No authored file: fill with the default tile so the world is always
    // walkable
    _tiles.fill(default_tile);
}

} // namespace mirelight
