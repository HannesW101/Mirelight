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
// Struct Area_id
// ----------------------------------------------------------------------------

struct Area_id {

    enum class Kind : std::uint8_t { CHUNK, INTERIOR };

    Kind        kind = Kind::CHUNK;
    int         chunk_x = 0;
    int         chunk_y = 0;
    std::string interior_name;

    static Area_id chunk(
        int x,
        int y
        ) {

        Area_id a;
        a.kind = Kind::CHUNK;
        a.chunk_x = x;
        a.chunk_y = y;
        return a;
    }

    static Area_id interior(
        std::string name
        ) {

        Area_id a;
        a.kind = Kind::INTERIOR;
        a.interior_name = std::move(name);
        return a;
    }

    bool operator==(
        Area_id const& o
        ) const {

        if (kind != o.kind) { return false; }

        return kind == Kind::CHUNK
            ? (chunk_x == o.chunk_x && chunk_y == o.chunk_y)
            : (interior_name == o.interior_name);
    }

    std::string to_key() const {

        if (kind == Kind::CHUNK) {

            return "chunk_" + std::to_string(chunk_x) + "_" + std::to_string(chunk_y);
        }

        return "interior_" + interior_name;
    }
};

struct Area_id_hash {

    std::size_t operator()(
        Area_id const& a
        ) const {

        return std::hash<std::string>{}(a.to_key());
    }
};

} // namespace mirelight
