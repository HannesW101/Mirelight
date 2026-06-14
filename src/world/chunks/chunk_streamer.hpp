#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/chunks/chunk.hpp"

#include "SFML/System/Vector2.hpp"

#include <memory>
#include <string>
#include <unordered_map>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

class Tile_database;

// ============================================================================
// Structs
// ----------------------------------------------------------------------------

struct Chunk_coord_hash {

    std::size_t operator()(
        Chunk_coord const& c
        ) const {

        // Cantor-ish pack
        return (static_cast<std::size_t>(static_cast<std::uint32_t>(c.x)) << 32) ^ static_cast<std::size_t>(static_cast<std::uint32_t>(c.y));
    }
};

// ============================================================================
// Class Chunk_streamer
// ----------------------------------------------------------------------------

class Chunk_streamer {

public:
    using Chunk_map = std::unordered_map<Chunk_coord, std::unique_ptr<Chunk>, Chunk_coord_hash>;

    Chunk_streamer(Tile_database& tiles, std::string data_dir);

    void update(sf::Vector2f player_world_pos);

    Tile_id tile_at(int world_tx, int world_ty) const;

    bool is_walkable(int world_tx, int world_ty) const;

    Chunk_map const& chunks() const;

    static Chunk_coord world_to_chunk(sf::Vector2f world_pos);

private:
    Tile_database& _tiles;
    std::string    _data_dir;
    Chunk_map      _chunks;
    Tile_id        _default_tile = 1;

    void _ensure_loaded(Chunk_coord c);
};

} // namespace mirelight
