#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "SFML/Graphics/Sprite.hpp"

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

class Chunk_streamer;
class Tile_database;

// ============================================================================
// Class Tilemap_renderer
// ----------------------------------------------------------------------------

class Tilemap_renderer {

public:
    Tilemap_renderer(Tile_database& tiles, titan::resources::Resource_manager& resources);

    void render(Chunk_streamer const& streamer, titan::render::Renderer& renderer);

private:
    Tile_database&                       _tiles;
    titan::resources::Resource_manager&  _resources;
    std::vector<sf::Sprite>              _sprite_buffer;
};

} // namespace mirelight
