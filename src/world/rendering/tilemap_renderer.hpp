#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "SFML/Graphics/Sprite.hpp"

#include <memory>
#include <vector>

// ============================================================================
// Forward declarations (1/2)
// ----------------------------------------------------------------------------

namespace titan::render    { class Renderer; }
namespace titan::resources { class Resource_manager; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations (2/2)
// ----------------------------------------------------------------------------

class Chunk;
class Chunk_streamer;
class Tile_database;

// ============================================================================
// Class Tilemap_renderer
// ----------------------------------------------------------------------------

class Tilemap_renderer {

public:
    Tilemap_renderer(Tile_database& tiles, titan::resources::Resource_manager& resources);

    void render(Chunk_streamer const& streamer, titan::render::Renderer& renderer);

    void render_grid(
        std::vector<std::unique_ptr<Chunk>> const& chunks,
        int chunk_cols,
        titan::render::Renderer& renderer
        );

    void render_chunk(Chunk const& chunk, int chunk_x, int chunk_y, titan::render::Renderer& renderer);

private:
    Tile_database&                       _tiles;
    titan::resources::Resource_manager&  _resources;
    std::vector<sf::Sprite>              _sprite_buffer;

    void _append_chunk(Chunk const& chunk, int base_tx, int base_ty);
};

} // namespace mirelight
