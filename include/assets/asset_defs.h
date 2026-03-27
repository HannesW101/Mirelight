#ifndef ASSETS_ASSET_DEFS
#define ASSETS_ASSET_DEFS

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include <string>
#include <ostream>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::assets {

// ===========================================================================
// Enums
// ---------------------------------------------------------------------------

enum class Font_id {

    // Default
    DEFAULT,

    // Other
    TEXT,
    TITLE,
    TITLE_OUTLINE,
};
inline std::ostream& operator<<(std::ostream& os, Font_id const font_id) {

    switch (font_id) {

        case Font_id::DEFAULT: return os << "DEFAULT";

        case Font_id::TEXT: return os << "TEXT";
        case Font_id::TITLE: return os << "TITLE";
        case Font_id::TITLE_OUTLINE: return os << "TITLE_OUTLINE";

        default: return os << "UNKNOW_FONT_ID";
    }
}

enum class Texture_id {

    // Default
    DEFAULT,

    // Backgrounds
    BACKGROUND__MOUNTAINS
};
inline std::ostream& operator<<(std::ostream& os, Texture_id const texture_id) {

    switch (texture_id) {

        case Texture_id::DEFAULT: return os << "DEFAULT";

        case Texture_id::BACKGROUND__MOUNTAINS: return os << "BACKGROUND__MOUNTAINS";

        default: return os << "UNKNOW_TEXTURE_ID";
    }
}

// ===========================================================================
// Filepaths
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Font filepaths
// ---------------------------------------------------------------------------
// Default
inline std::string const FILEPATH__FONT__FONT_DEFAULT = "assets/fonts/Default_font.ttf";

// Other
inline std::string const FILEPATH__FONT__TEXT = "assets/fonts/FantasyRPGtext.ttf";
inline std::string const FILEPATH__FONT__TITLE = "assets/fonts/FantasyRPGtitle.ttf";
inline std::string const FILEPATH__FONT__TITLE_OUTLINE = "assets/fonts/FantasyRPGtitleOutline.ttf";

// ---------------------------------------------------------------------------
// Texture filepaths
// ---------------------------------------------------------------------------
// Default
inline std::string const FILEPATH__TEXTURE__DEFAULT_TEXTURE = "assets/textures/Default_texture.png";

// Backgrounds
inline std::string const FILEPATH__TEXTURE__BACKGROUNDS__MOUNTAINS = "assets/textures/background/mountains.png";

// Background

} // namespace mirelight::assets

#endif
