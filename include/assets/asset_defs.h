#ifndef ASSETS_ASSET_DEFS
#define ASSETS_ASSET_DEFS

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

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
    BACKGROUND__MOUNTAINS,

    // Background Boxes
    BACKGROUND_BOX__03A,

    // Title banners
    TITLE_BANNER__MEDIUM_02C,

    // Cursors
    CURSOR__GAUNTLET,
    CURSOR__GAUNTLET_MAGIC
};
inline std::ostream& operator<<(std::ostream& os, Texture_id const texture_id) {

    switch (texture_id) {

        case Texture_id::DEFAULT: return os << "DEFAULT";

        case Texture_id::BACKGROUND__MOUNTAINS: return os << "BACKGROUND__MOUNTAINS";
        case Texture_id::BACKGROUND_BOX__03A: return os << "BACKGROUND_BOX__03A";
        case Texture_id::TITLE_BANNER__MEDIUM_02C: return os << "TITLE_BANNER__MEDIUM_02C";
        case Texture_id::CURSOR__GAUNTLET: return os << "CURSOR__GAUNTLET";
        case Texture_id::CURSOR__GAUNTLET_MAGIC: return os << "CURSOR__GAUNTLET_MAGIC";

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

// Background boxes
inline std::string const FILEPATH__TEXTURE__BACKGROUND_BOX__03A = "assets/textures/UI/Background boxes/BGbox_03A.png";

// Title banners
inline std::string const FILEPATH__TEXTURE__TITLE_BANNER__MEDIUM_02C = "assets/textures/UI/Title banners/BannerMedium_02C.png";

// Cursors
inline std::string const FILEPATH__TEXTURE__CURSOR__GAUNTLET = "assets/textures/UI/Cursors/Gauntlet.png";
inline std::string const FILEPATH__TEXTURE__CURSOR__GAUNTLET_MAGIC = "assets/textures/UI/Cursors/Gauntlet_Magic.png";

} // namespace mirelight::assets

#endif
