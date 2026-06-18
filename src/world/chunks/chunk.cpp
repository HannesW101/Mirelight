// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/chunks/chunk.hpp"

#include "module-utils/include/random.hpp"
#include "module-utils/include/logger.hpp"

#include <fstream>
#include <sstream>
#include <string>

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

    if (load_from_path(path.str(), default_tile)) { return; }

    _generate(default_tile);
}

// ----------------------------------------------------------------------------
bool Chunk::load_from_path(
    std::string const& path,
    Tile_id default_tile
    ) {

    std::ifstream file(path);
    if (!file.is_open()) { return false; }

    // Whitespace-separated id grid. Lines whose first non-whitespace
    // character is '#' are treated as comments and skipped entirely,
    // so chunk files can carry authoring notes, e.g.:
    //
    //   # home interior  (40=floor)
    //   0  0  0  0 ...
    //   40 40 40 ...
    int i = 0;
    std::string line;
    while (i < N * N && std::getline(file, line)) {

        std::istringstream iss(line);
        char peek = 0;
        while (iss.get(peek) && (peek == ' ' || peek == '\t')) {}
        if (!iss || peek == '#') { continue; }
        iss.putback(peek);

        int v = 0;
        while (i < N * N && iss >> v) {

            _tiles[static_cast<std::size_t>(i++)] = static_cast<Tile_id>(v);
        }
    }

    // Any tiles not covered by the file keep the default
    for (; i < N * N; ++i) { _tiles[static_cast<std::size_t>(i)] = default_tile; }

    return true;
}

// ----------------------------------------------------------------------------
void Chunk::_generate(
    Tile_id default_tile
    ) {

    LOG(titan::utils::Log_lvl::WARN)
        << "Chunk (" + std::to_string(_coord.x) + "," + std::to_string(_coord.y)
        + "): no authored .chunk file found, filling with default tile id "
        + std::to_string(default_tile);

    _tiles.fill(default_tile);
}

} // namespace mirelight
