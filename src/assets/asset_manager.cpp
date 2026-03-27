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
Asset_manager::Asset_manager()
    : _is_init(false)
    , _font_map({})
    , _texture_map({})
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

} // namespace mirelight::assets
