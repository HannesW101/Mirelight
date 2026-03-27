#ifndef ASSETS_ASSET_MANAGER
#define ASSETS_ASSET_MANAGER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_defs.h"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <string>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::assets {

// ===========================================================================
// Class Asset_manager
// ---------------------------------------------------------------------------

class Asset_manager final {

public:
    static Asset_manager& get_instance();

    void init();

    sf::Font    const& get(Font_id    const font_id   ) const;
    sf::Texture const& get(Texture_id const texture_id) const;

    ~Asset_manager          (                    ) = default;
    Asset_manager           (Asset_manager const&) = delete;
    Asset_manager& operator=(Asset_manager const&) = delete;
    Asset_manager           (Asset_manager&&     ) = delete;
    Asset_manager& operator=(Asset_manager&&     ) = delete;

private:
    Asset_manager();

    bool _load_font   (Font_id    const font_id,    std::string const& file_path);
    bool _load_texture(Texture_id const texture_id, std::string const& file_path);

    bool _is_init;

    std::unordered_map<Font_id,    sf::Font   > _font_map;
    std::unordered_map<Texture_id, sf::Texture> _texture_map;
};

} // namespace mirelight::assets

#endif
