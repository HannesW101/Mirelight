#ifndef ASSETS_ASSET_MANAGER
#define ASSETS_ASSET_MANAGER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_defs.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

    sf::Font        const& get(Font_id    const font_id   ) const;
    sf::Texture     const& get(Texture_id const texture_id) const;
    sf::Music            & get(Music_id   const music_id  );
    sf::SoundBuffer      & get(Sfx_id     const sfx_id    );

    ~Asset_manager          (                    ) = default;
    Asset_manager           (Asset_manager const&) = delete;
    Asset_manager& operator=(Asset_manager const&) = delete;
    Asset_manager           (Asset_manager&&     ) = delete;
    Asset_manager& operator=(Asset_manager&&     ) = delete;

private:
    Asset_manager();

    bool _load_font   (Font_id    const font_id,    std::string const& file_path);
    bool _load_texture(Texture_id const texture_id, std::string const& file_path);
    bool _load_music  (Music_id   const music_id,   std::string const& file_path);
    bool _load_sfx    (Sfx_id     const sfx_id,     std::string const& file_path);

    bool _is_init;

    std::unordered_map<Font_id, sf::Font> _font_map;
    std::unordered_map<Texture_id, sf::Texture> _texture_map;
    std::unordered_map<Music_id, sf::Music> _music_map;
    std::unordered_map<Sfx_id, sf::SoundBuffer> _sfx_map;
};

} // namespace mirelight::assets

#endif
