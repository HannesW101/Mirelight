// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_manager.h"
#include "utils/logger.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::assets {

// ===========================================================================
// Class Asset_manager
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Asset_manager& Asset_manager::get_instance() {

    static Asset_manager instance;
    return instance;
}

// ---------------------------------------------------------------------------
void Asset_manager::init() {

    bool success = true;

    if (_is_init) {

        LOG(WARNING) << "Attempting to reinitialize Asset_manager";
        success = false;
    } else {

        // Fonts
        if (success) { success = _load_font(Font_id::DEFAULT, FILEPATH__FONT__FONT_DEFAULT); }
        if (success) { success = _load_font(Font_id::TEXT, FILEPATH__FONT__TEXT); }
        if (success) { success = _load_font(Font_id::TITLE, FILEPATH__FONT__TITLE); }
        if (success) { success = _load_font(Font_id::TITLE_OUTLINE, FILEPATH__FONT__TITLE_OUTLINE); }

        // Textures
        if (success) { success = _load_texture(Texture_id::DEFAULT, FILEPATH__TEXTURE__DEFAULT_TEXTURE); }
        if (success) { success = _load_texture(Texture_id::BACKGROUND__MOUNTAINS, FILEPATH__TEXTURE__BACKGROUNDS__MOUNTAINS); }
        if (success) { success = _load_texture(Texture_id::BACKGROUND_BOX__03A, FILEPATH__TEXTURE__BACKGROUND_BOX__03A); }
        if (success) { success = _load_texture(Texture_id::TITLE_BANNER__MEDIUM_02C, FILEPATH__TEXTURE__TITLE_BANNER__MEDIUM_02C); }
        if (success) { success = _load_texture(Texture_id::CURSOR__GAUNTLET, FILEPATH__TEXTURE__CURSOR__GAUNTLET); }
        if (success) { success = _load_texture(Texture_id::CURSOR__GAUNTLET_MAGIC, FILEPATH__TEXTURE__CURSOR__GAUNTLET_MAGIC); }
        if (success) { success = _load_texture(Texture_id::BUTTON__03A_NORMAL, FILEPATH__TEXTURE__BUTTON__03A_NORMAL); }
        if (success) { success = _load_texture(Texture_id::BUTTON__03A_SELECTED, FILEPATH__TEXTURE__BUTTON__03A_SELECTED); }
        if (success) { success = _load_texture(Texture_id::TITLE_BANNER__MEDIUM_01C, FILEPATH__TEXTURE__TITLE_BANNER__MEDIUM_01C); }
        if (success) { success = _load_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BAR04, FILEPATH__TEXTURE__SLIDERS_AND_BARS__SLIDER_03_BAR04); }
        if (success) { success = _load_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BOX, FILEPATH__TEXTURE__SLIDERS_AND_BARS__SLIDER_03_BOX); }
        if (success) { success = _load_texture(Texture_id::SLIDERS_AND_BARS__SLIDER_03_BUTTON, FILEPATH__TEXTURE__SLIDERS_AND_BARS__SLIDER_03_BUTTON); }

        // Music
        if (success) { success = _load_music(Music_id::AMBIENT_1,  FILEPATH__MUSIC__AMBIENT_1);  }
        if (success) { success = _load_music(Music_id::AMBIENT_2,  FILEPATH__MUSIC__AMBIENT_2);  }
        if (success) { success = _load_music(Music_id::AMBIENT_3,  FILEPATH__MUSIC__AMBIENT_3);  }
        if (success) { success = _load_music(Music_id::AMBIENT_4,  FILEPATH__MUSIC__AMBIENT_4);  }
        if (success) { success = _load_music(Music_id::AMBIENT_5,  FILEPATH__MUSIC__AMBIENT_5);  }
        if (success) { success = _load_music(Music_id::AMBIENT_6,  FILEPATH__MUSIC__AMBIENT_6);  }
        if (success) { success = _load_music(Music_id::AMBIENT_7,  FILEPATH__MUSIC__AMBIENT_7);  }
        if (success) { success = _load_music(Music_id::AMBIENT_8,  FILEPATH__MUSIC__AMBIENT_8);  }
        if (success) { success = _load_music(Music_id::AMBIENT_9,  FILEPATH__MUSIC__AMBIENT_9);  }
        if (success) { success = _load_music(Music_id::AMBIENT_10, FILEPATH__MUSIC__AMBIENT_10); }

        // SFX
        if (success) { success = _load_sfx(Sfx_id::AFRICAN_1, FILEPATH__SFX__AFRICAN_1); }
        if (success) { success = _load_sfx(Sfx_id::AFRICAN_2, FILEPATH__SFX__AFRICAN_2); }
        if (success) { success = _load_sfx(Sfx_id::AFRICAN_3, FILEPATH__SFX__AFRICAN_3); }
    }

    // Check if Asset_manager is initialized successfully
    if (success) {

        _is_init = true;
        LOG(INFO) << "Successfully initialized Asset_manager";
    }
}

// ---------------------------------------------------------------------------
sf::Font const& Asset_manager::get(Font_id const font_id) const {

    if (!_is_init) {

        LOG(WARNING) << "Attempting to use Asset_manager before initialization";
        return _font_map.at(Font_id::DEFAULT);
    }

    auto const it = _font_map.find(font_id);

    if (it == _font_map.cend()) {

        LOG(WARNING) << "Failed to get font [" << it->first << ']';
        return _font_map.at(Font_id::DEFAULT);
    } else {

        return it->second;
    }
}

// ---------------------------------------------------------------------------
sf::Texture const& Asset_manager::get(Texture_id const texture_id) const {

    if (!_is_init) {

        LOG(WARNING) << "Attempting to use Asset_manager before initialization";
        return _texture_map.at(Texture_id::DEFAULT);
    }

    auto const it = _texture_map.find(texture_id);

    if (it == _texture_map.cend()) {

        LOG(WARNING) << "Failed to get texture [" << it->first << ']';
        return _texture_map.at(Texture_id::DEFAULT);
    } else {

        return it->second;
    }
}

// ---------------------------------------------------------------------------
sf::Music& Asset_manager::get(Music_id const music_id) {

    if (!_is_init) {

        LOG(WARNING) << "Attempting to use Asset_manager before initialization";
        return _music_map[Music_id::AMBIENT_1];
    }

    auto const it = _music_map.find(music_id);

    if (it == _music_map.cend()) {

        LOG(WARNING) << "Failed to get music [" << it->first << ']';
        return _music_map[Music_id::AMBIENT_1];
    } else {

        return it->second;
    }
}

// ---------------------------------------------------------------------------
sf::SoundBuffer& Asset_manager::get(Sfx_id const sfx_id) {

    if (!_is_init) {

        LOG(WARNING) << "Attempting to use Asset_manager before initialization";
        return _sfx_map[Sfx_id::AFRICAN_1];
    }

    auto const it = _sfx_map.find(sfx_id);

    if (it == _sfx_map.cend()) {

        LOG(WARNING) << "Failed to get SFX [" << it->first << ']';
        return _sfx_map[Sfx_id::AFRICAN_1];
    } else {

        return it->second;
    }
}

// ---------------------------------------------------------------------------
Asset_manager::Asset_manager()
    : _is_init(false)
    , _font_map()
    , _texture_map()
    , _music_map()
    , _sfx_map()
{}

// ---------------------------------------------------------------------------
bool Asset_manager::_load_font(Font_id const font_id, std::string const& file_path) {

    sf::Font font;

    if (font.openFromFile(file_path)) {

        _font_map[font_id] = std::move(font);
        return true;
    } else {

        LOG(WARNING) << "Failed to load font [" << font_id << ']';
        return false;
    }
}

// ---------------------------------------------------------------------------
bool Asset_manager::_load_texture(Texture_id const texture_id, std::string const& file_path) {

    sf::Texture texture;

    if (texture.loadFromFile(file_path)) {

        _texture_map[texture_id] = std::move(texture);
        return true;
    } else {

        LOG(WARNING) << "Failed to load texture [" << texture_id << ']';
        return false;
    }
}

// ---------------------------------------------------------------------------
bool Asset_manager::_load_music(Music_id const music_id, std::string const& file_path) {

    sf::Music& music = _music_map[music_id];

    if (music.openFromFile(file_path)) {

        return true;
    } else {

        LOG(WARNING) << "Failed to load music [" << music_id << ']';
        _music_map.erase(music_id);
        return false;
    }
}

// ---------------------------------------------------------------------------
bool Asset_manager::_load_sfx(Sfx_id const sfx_id, std::string const& file_path) {

    sf::SoundBuffer sound_buffer;

    if (sound_buffer.loadFromFile(file_path)) {

        _sfx_map[sfx_id] = std::move(sound_buffer);
        return true;
    } else {

        LOG(WARNING) << "Failed to load SFX [" << sfx_id << ']';
        return false;
    }
}

} // namespace mirelight::assets
