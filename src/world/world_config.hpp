#pragma once

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight::world_cfg {

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

inline constexpr int TILE_SIZE = 32;   // pixels per tile (square) // TODO: Not std::size_t??
inline constexpr int CHUNK_TILES = 16;   // tiles per chunk side // TODO: Not std::size_t??
inline constexpr int CHUNK_PIXELS = TILE_SIZE * CHUNK_TILES; // TODO: Not std::size_t??

// How many chunks around the player stay loaded
inline constexpr int STREAM_RADIUS = 2;  // TODO: Not std::size_t??

} // namespace mirelight::world_cfg
