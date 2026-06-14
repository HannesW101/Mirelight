// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/rendering/tilemap_renderer.hpp"
#include "world/chunks/chunk_streamer.hpp"
#include "world/tiles/tile_database.hpp"
#include "world/world_config.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/render_layer.hpp"
#include "module-resources/include/resource_manager.hpp"

#include "SFML/Graphics/Texture.hpp"

#include <memory>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

namespace {

constexpr int N  = world_cfg::CHUNK_TILES;
constexpr int TS = world_cfg::TILE_SIZE;
}

// ============================================================================
// Class Tilemap_renderer
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Tilemap_renderer::Tilemap_renderer(
    Tile_database& tiles,
    titan::resources::Resource_manager& resources
    )
    : _tiles(tiles)
    , _resources(resources)
{}

// ----------------------------------------------------------------------------
void Tilemap_renderer::render(
    Chunk_streamer const& streamer,
    titan::render::Renderer& renderer
    ) {

    _sprite_buffer.clear();

    // Reserve a sensible upper bound so the buffer never reallocates mid-build
    // (reallocation would invalidate pointers already handed to the renderer)
    std::size_t const max_tiles = streamer.chunks().size() * static_cast<std::size_t>(N * N);
    _sprite_buffer.reserve(max_tiles);

    for (auto const& [coord, chunk] : streamer.chunks()) {

        int const base_tx = coord.x * N;
        int const base_ty = coord.y * N;

        for (int ty = 0; ty < N; ++ty) {

            for (int tx = 0; tx < N; ++tx) {

                Tile_id const id = chunk->at(tx, ty);
                if (id == 0) { continue; }

                Tile_def const& def = _tiles.by_id(id);
                auto texture = _resources.get<sf::Texture>(def.texture);
                if (!texture) { continue; }

                sf::Sprite sprite(*texture);

                sf::Vector2u const tex_size = texture->getSize();
                if (tex_size.x > static_cast<unsigned>(TS) ||
                    tex_size.y > static_cast<unsigned>(TS)) {

                    sprite.setTextureRect({
                        { def.atlas_x * TS, def.atlas_y * TS },
                        { TS, TS }
                        });
                }

                float const wx = static_cast<float>((base_tx + tx) * TS);
                float const wy = static_cast<float>((base_ty + ty) * TS);
                sprite.setPosition({ wx, wy });

                _sprite_buffer.push_back(std::move(sprite));
            }
        }
    }

    // Now submit references into the stable buffer
    for (auto const& sprite : _sprite_buffer) {

        renderer.submit(titan::render::Render_layer::WORLD_TILES, sprite);
    }
}

} // namespace mirelight
