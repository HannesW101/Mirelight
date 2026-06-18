#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include <cstdint>
#include <string>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using Tile_id = std::uint64_t;

// ============================================================================
// Structs
// ----------------------------------------------------------------------------

struct Tile_def {

    Tile_id     id = 0;
    std::string name;
    std::string texture;
    bool        walkable = true;
    int         atlas_x = 0;
    int         atlas_y = 0;
    int         source_tile_px = 32;

    // Optional direct pixel rect: overrides atlas_x/y when src_w > 0.
    // Use when the source tile is not on the sheet's regular grid
    // (e.g. non-square, non-aligned, or odd-sized art).
    int src_x = 0;
    int src_y = 0;
    int src_w = 0;
    int src_h = 0;
};

} // namespace mirelight
