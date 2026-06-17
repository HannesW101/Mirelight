#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/chunks/chunk.hpp"
#include "world/areas/area_id.hpp"
#include "world/walkable_provider.hpp"

#include "SFML/System/Vector2.hpp"

#include <memory>
#include <string>
#include <unordered_map>

// ============================================================================
// Forward declarations (1/2)
// ----------------------------------------------------------------------------

namespace titan::game { class World; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations (2/2)
// ----------------------------------------------------------------------------

class Tile_database;
class Object_spawner;

// ============================================================================
// Structs
// ----------------------------------------------------------------------------

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

class Chunk_streamer final : public Walkable_provider {

public:
    using Chunk_map = std::unordered_map<Chunk_coord, std::unique_ptr<Chunk>, Chunk_coord_hash>;

    Chunk_streamer(
        Tile_database& tiles,
        std::string data_dir,
        Object_spawner* spawner = nullptr,
        titan::game::World* world = nullptr
        );

    void update(sf::Vector2f player_world_pos);

    Tile_id tile_at(int world_tx, int world_ty) const;

    bool is_walkable(int world_tx, int world_ty) const override;

    Chunk_map const& chunks() const;

    static Chunk_coord world_to_chunk(sf::Vector2f world_pos);

private:
    Tile_database&      _tiles;
    std::string          _data_dir;
    Chunk_map            _chunks;
    Tile_id               _default_tile = 1;
    Object_spawner*      _spawner = nullptr;
    titan::game::World*  _world   = nullptr;

    void _ensure_loaded(Chunk_coord c);
};

} // namespace mirelight
