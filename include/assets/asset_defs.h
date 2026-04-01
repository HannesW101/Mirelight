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
    TITLE_BANNER__MEDIUM_01C,

    // Cursors
    CURSOR__GAUNTLET,
    CURSOR__GAUNTLET_MAGIC,

    // Buttons
    BUTTON__03A_NORMAL,
    BUTTON__03A_SELECTED
};
inline std::ostream& operator<<(std::ostream& os, Texture_id const texture_id) {

    switch (texture_id) {

        case Texture_id::DEFAULT: return os << "DEFAULT";

        case Texture_id::BACKGROUND__MOUNTAINS: return os << "BACKGROUND__MOUNTAINS";
        case Texture_id::BACKGROUND_BOX__03A: return os << "BACKGROUND_BOX__03A";
        case Texture_id::TITLE_BANNER__MEDIUM_02C: return os << "TITLE_BANNER__MEDIUM_02C";
        case Texture_id::CURSOR__GAUNTLET: return os << "CURSOR__GAUNTLET";
        case Texture_id::CURSOR__GAUNTLET_MAGIC: return os << "CURSOR__GAUNTLET_MAGIC";
        case Texture_id::BUTTON__03A_NORMAL: return os << "BUTTON__03A_NORMAL";
        case Texture_id::BUTTON__03A_SELECTED: return os << "BUTTON__03A_SELECTED";

        default: return os << "UNKNOW_TEXTURE_ID";
    }
}

enum class Music_id {

    AMBIENT_1,
    AMBIENT_2,
    AMBIENT_3,
    AMBIENT_4,
    AMBIENT_5,
    AMBIENT_6,
    AMBIENT_7,
    AMBIENT_8,
    AMBIENT_9,
    AMBIENT_10
};
inline std::ostream& operator<<(std::ostream& os, Music_id const music_id) {

    switch (music_id) {

        case Music_id::AMBIENT_1: return os << "AMBIENCE_1";
        case Music_id::AMBIENT_2: return os << "AMBIENCE_2";
        case Music_id::AMBIENT_3: return os << "AMBIENCE_3";
        case Music_id::AMBIENT_4: return os << "AMBIENCE_4";
        case Music_id::AMBIENT_5: return os << "AMBIENCE_5";
        case Music_id::AMBIENT_6: return os << "AMBIENCE_6";
        case Music_id::AMBIENT_7: return os << "AMBIENCE_7";
        case Music_id::AMBIENT_8: return os << "AMBIENCE_8";
        case Music_id::AMBIENT_9: return os << "AMBIENCE_9";
        case Music_id::AMBIENT_10: return os << "AMBIENCE_10";

        default: return os << "UNKNOW_MUSIC_ID";
    }
}

enum class Sfx_id {

    AFRICAN_1,
    AFRICAN_2,
    AFRICAN_3
};
inline std::ostream& operator<<(std::ostream& os, Sfx_id const sfx_id) {

    switch (sfx_id) {

        case Sfx_id::AFRICAN_1: return os << "AFRICAN_1";
        case Sfx_id::AFRICAN_2: return os << "AFRICAN_2";
        case Sfx_id::AFRICAN_3: return os << "AFRICAN_3";

        default: return os << "UNKNOW_SFX_ID";
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
inline std::string const FILEPATH__TEXTURE__TITLE_BANNER__MEDIUM_01C = "assets/textures/UI/Title banners/BannerMedium_01C.png";

// Cursors
inline std::string const FILEPATH__TEXTURE__CURSOR__GAUNTLET = "assets/textures/UI/Cursors/Gauntlet.png";
inline std::string const FILEPATH__TEXTURE__CURSOR__GAUNTLET_MAGIC = "assets/textures/UI/Cursors/Gauntlet_Magic.png";

// Buttons
inline std::string const FILEPATH__TEXTURE__BUTTON__03A_NORMAL = "assets/textures/UI/Buttons/Button_03A_Normal.png";
inline std::string const FILEPATH__TEXTURE__BUTTON__03A_SELECTED = "assets/textures/UI/Buttons/Button_03A_Selected.png";

// ---------------------------------------------------------------------------
// Music filepaths
// ---------------------------------------------------------------------------

inline std::string const FILEPATH__MUSIC__AMBIENT_1 = "assets/sounds/music/Ambient 1.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_2 = "assets/sounds/music/Ambient 2.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_3 = "assets/sounds/music/Ambient 3.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_4 = "assets/sounds/music/Ambient 4.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_5 = "assets/sounds/music/Ambient 5.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_6 = "assets/sounds/music/Ambient 6.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_7 = "assets/sounds/music/Ambient 7.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_8 = "assets/sounds/music/Ambient 8.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_9 = "assets/sounds/music/Ambient 9.ogg";
inline std::string const FILEPATH__MUSIC__AMBIENT_10 = "assets/sounds/music/Ambient 10.ogg";

// ---------------------------------------------------------------------------
// SFX filepaths
// ---------------------------------------------------------------------------

inline std::string const FILEPATH__SFX__AFRICAN_1 = "assets/sounds/sfx/UI/African1.wav";
inline std::string const FILEPATH__SFX__AFRICAN_2 = "assets/sounds/sfx/UI/African2.wav";
inline std::string const FILEPATH__SFX__AFRICAN_3 = "assets/sounds/sfx/UI/African3.wav";

} // namespace mirelight::assets

#endif
