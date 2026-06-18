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

#include "world/chunks/chunk.hpp"

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
void Tilemap_renderer::_append_chunk(
    Chunk const& chunk,
    int base_tx,
    int base_ty
    ) {

    for (int ty = 0; ty < N; ++ty) {

        for (int tx = 0; tx < N; ++tx) {

            Tile_id const id = chunk.at(tx, ty);
            if (id == 0) { continue; }

            Tile_def const& def = _tiles.by_id(id);
            auto texture = _resources.get<sf::Texture>(def.texture);
            if (!texture) { continue; }

            sf::Sprite sprite(*texture);

            if (def.src_w > 0) {

                // Direct pixel rect
                sprite.setTextureRect({{def.src_x, def.src_y}, {def.src_w, def.src_h}});
                float const sx = static_cast<float>(TS) / static_cast<float>(def.src_w);
                float const sy = static_cast<float>(TS) / static_cast<float>(def.src_h);
                sprite.setScale({sx, sy});
            } else {

                // Atlas-based rect
                int const src = def.source_tile_px;
                sf::Vector2u const tex_size = texture->getSize();
                if (tex_size.x > static_cast<unsigned>(src) ||
                    tex_size.y > static_cast<unsigned>(src)
                    ) {

                    sprite.setTextureRect({{def.atlas_x * src, def.atlas_y * src}, {src, src}});
                }

                if (src != TS) {

                    float const s = static_cast<float>(TS) / static_cast<float>(src);
                    sprite.setScale({s, s});
                }
            }

            float const wx = static_cast<float>((base_tx + tx) * TS);
            float const wy = static_cast<float>((base_ty + ty) * TS);
            sprite.setPosition({ wx, wy });

            _sprite_buffer.push_back(std::move(sprite));
        }
    }
}

// ----------------------------------------------------------------------------
void Tilemap_renderer::render(
    Chunk_streamer const& streamer,
    titan::render::Renderer& renderer
    ) {

    _sprite_buffer.clear();

    // Reserve a sensible upper bound so the buffer never reallocates mid build
    // (reallocation would invalidate pointers already handed to the renderer)
    std::size_t const max_tiles = streamer.chunks().size() * static_cast<std::size_t>(N * N);
    _sprite_buffer.reserve(max_tiles);

    for (auto const& [coord, chunk] : streamer.chunks()) {

        _append_chunk(*chunk, coord.x * N, coord.y * N);
    }

    // Now submit references into the stable buffer
    for (auto const& sprite : _sprite_buffer) {

        renderer.submit(titan::render::Render_layer::WORLD_TILES, sprite);
    }
}

// ----------------------------------------------------------------------------
void Tilemap_renderer::render_grid(
    std::vector<std::unique_ptr<Chunk>> const& chunks,
    int chunk_cols,
    titan::render::Renderer& renderer
    ) {

    _sprite_buffer.clear();
    _sprite_buffer.reserve(chunks.size() * static_cast<std::size_t>(N * N));

    for (int i = 0; i < static_cast<int>(chunks.size()); ++i) {

        if (!chunks[i]) { continue; }
        int const cx = i % chunk_cols;
        int const cy = i / chunk_cols;
        _append_chunk(*chunks[i], cx * N, cy * N);
    }

    for (auto const& sprite : _sprite_buffer) {

        renderer.submit(titan::render::Render_layer::WORLD_TILES, sprite);
    }
}

// ----------------------------------------------------------------------------
void Tilemap_renderer::render_chunk(
    Chunk const& chunk,
    int chunk_x,
    int chunk_y,
    titan::render::Renderer& renderer
    ) {

    _sprite_buffer.clear();
    _sprite_buffer.reserve(static_cast<std::size_t>(N * N));

    _append_chunk(chunk, chunk_x * N, chunk_y * N);

    for (auto const& sprite : _sprite_buffer) {

        renderer.submit(titan::render::Render_layer::WORLD_TILES, sprite);
    }
}

} // namespace mirelight
