// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "core/asset_loader.hpp"

#include "module-resources/include/resource_manager.hpp"
#include "module-utils/include/logger.hpp"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Music.hpp"

#include <string>
#include <utility>
#include <vector>
#include <cstdint>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::resources;
using namespace titan::utils;

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

namespace {

char const* const ASSET_DIR = "assets/";
}

// ============================================================================
// Class Asset_loader
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Asset_loader::Asset_loader(
    Resource_manager& resources
    )
    : _resources(resources)
{}

// ----------------------------------------------------------------------------
bool Asset_loader::load_all() {

    std::string const dir = ASSET_DIR;

    // ---- Fonts ----
    auto font = _resources.load<sf::Font>("default_font", dir + "fonts/Default_font.ttf");
    if (!font) {

        LOG(Log_lvl::ERR) << "Asset_loader: FAILED to load default_font";
    } else {

        _handles.push_back(font);
        LOG(Log_lvl::INFO) << "Asset_loader: default_font loaded";
    }

    if (auto h = _resources.load<sf::Font>("title_font", dir + "fonts/FantasyRPGtitle.ttf")) { _handles.push_back(h); }
    if (auto h = _resources.load<sf::Font>("text_font",  dir + "fonts/FantasyRPGtext.ttf"))  { _handles.push_back(h); }

    // ---- Textures ----
    struct Tex { char const* key; char const* path; };
    std::vector<Tex> const textures = {

        // World tiles
        { "grass",           "textures/world/tiles/grass.png"              },
        { "water",           "textures/world/tiles/water.png"              },
        { "stone",           "textures/world/tiles/stone.png"              },

        // World entities
        { "player",          "textures/world/entities/player.png"          },

        // UI sprites
        { "btn_normal",      "textures/ui/buttons/Button_03A_Normal.png"   },
        { "btn_selected",    "textures/ui/buttons/Button_03A_Selected.png" },
        { "bg_box",          "textures/ui/panels/BGbox_03A.png"            },
        { "banner_02c",      "textures/ui/banners/BannerMedium_02C.png"    },
        { "cursor_gauntlet", "textures/ui/cursors/Gauntlet.png"            },
        { "cursor_magic",    "textures/ui/cursors/Gauntlet_Magic.png"      },

        // Backgrounds
        { "mountains_bg",    "textures/backgrounds/mountains.png"          },
    };

    int loaded = 0;
    for (auto const& t : textures) {

        auto tex = _resources.load<sf::Texture>(t.key, dir + t.path);

        if (tex) {

            _handles.push_back(tex);
            ++loaded;
        } else {

            LOG(Log_lvl::ERR) << std::string("Asset_loader: missing ") + t.path;
        }
    }

    // ---- SFX ----
    if (auto h = _resources.load<sf::SoundBuffer>("sfx_ui_hover", dir + "audio/sfx/ui/African1.wav")) { _handles.push_back(h); }
    if (auto h = _resources.load<sf::SoundBuffer>("sfx_ui_click", dir + "audio/sfx/ui/African3.wav")) { _handles.push_back(h); }

    // ---- Music (streamed; stored in resource_manager's _music map) ----
    struct Mus { char const* key; char const* path; };
    std::vector<Mus> const music_tracks = {

        { "music_ambient_1",  "audio/music/Ambient 1.ogg"  },
        { "music_ambient_2",  "audio/music/Ambient 2.ogg"  },
        { "music_ambient_3",  "audio/music/Ambient 3.ogg"  },
        { "music_ambient_4",  "audio/music/Ambient 4.ogg"  },
        { "music_ambient_5",  "audio/music/Ambient 5.ogg"  },
        { "music_ambient_6",  "audio/music/Ambient 6.ogg"  },
        { "music_ambient_7",  "audio/music/Ambient 7.ogg"  },
        { "music_ambient_8",  "audio/music/Ambient 8.ogg"  },
        { "music_ambient_9",  "audio/music/Ambient 9.ogg"  },
        { "music_ambient_10", "audio/music/Ambient 10.ogg" },
    };

    for (auto const& m : music_tracks) {

        _resources.load<sf::Music>(m.key, dir + m.path);
    }

    LOG(Log_lvl::INFO) << "Asset_loader: " + std::to_string(loaded) + " textures loaded";
    return loaded > 0;
}

} // namespace mirelight
