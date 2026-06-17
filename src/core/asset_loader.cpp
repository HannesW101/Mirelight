// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "core/asset_loader.hpp"

#include "module-resources/include/resource_manager.hpp"
#include "module-resources/include/spritesheet.hpp"
#include "module-utils/include/logger.hpp"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Music.hpp"

#include <string>
#include <vector>

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
Asset_loader::Asset_loader(Resource_manager& resources)
    : _resources(resources)
{}

// ----------------------------------------------------------------------------
void Asset_loader::_tex(
    std::string const& dir,
    char const*        key,
    char const*        rel_path
    ) {

    auto h = _resources.load<sf::Texture>(key, dir + rel_path);
    if (h) {

        _handles.push_back(h);
    } else {

        LOG(Log_lvl::ERR) << std::string("Asset_loader: missing ") + rel_path;
    }
}

// ----------------------------------------------------------------------------
void Asset_loader::_anim(
    std::string const& dir,
    char const*        key,
    char const*        rel_path
    ) {

    _tex(dir, key, rel_path);

    std::string const sheet_key = std::string(key) + "_sheet";
    if (auto h = _resources.load<Spritesheet>(sheet_key, dir + rel_path)) {

        _handles.push_back(h);
    }
}

// ----------------------------------------------------------------------------
void Asset_loader::_load_fonts(
    std::string const& dir
    ) {

    struct Font { char const* key; char const* path; };
    static Font const fonts[] = {

        { "default_font", "fonts/Default_font.ttf"    },
        { "title_font",   "fonts/FantasyRPGtitle.ttf" },
        { "text_font",    "fonts/FantasyRPGtext.ttf"  },
    };

    for (auto const& f : fonts) {

        if (auto h = _resources.load<sf::Font>(f.key, dir + f.path)) {

            _handles.push_back(h);
        } else {

            LOG(Log_lvl::ERR) << std::string("Asset_loader: missing font ") + f.path;
        }
    }
}

// ----------------------------------------------------------------------------
void Asset_loader::_load_textures(
    std::string const& dir
    ) {

    // Tiles - nature
    _tex(dir, "tiles_bush",             "textures/world/tiles/nature/Bush.png"        );
    _tex(dir, "tiles_flower_1",         "textures/world/tiles/nature/Flower_1.png"    );
    _tex(dir, "tiles_flower_2",         "textures/world/tiles/nature/Flower_2.png"    );
    _tex(dir, "tiles_flower_3",         "textures/world/tiles/nature/Flower_3.png"    );
    _tex(dir, "tiles_flower_4",         "textures/world/tiles/nature/Flower_4.png"    );
    _tex(dir, "tiles_flower_5",         "textures/world/tiles/nature/Flower_5.png"    );
    _tex(dir, "tiles_flower_6",         "textures/world/tiles/nature/Flower_6.png"    );
    _tex(dir, "tiles_flower_7",         "textures/world/tiles/nature/Flower_7.png"    );
    _tex(dir, "tiles_flower_8",         "textures/world/tiles/nature/Flower_8.png"    );
    _tex(dir, "tiles_flower_9",         "textures/world/tiles/nature/Flower_9.png"    );
    _tex(dir, "tiles_leaves_1",         "textures/world/tiles/nature/Leaves_1.png"    );
    _tex(dir, "tiles_leaves_2",         "textures/world/tiles/nature/Leaves_2.png"    );
    _tex(dir, "tiles_leaves_3",         "textures/world/tiles/nature/Leaves_3.png"    );
    _tex(dir, "tiles_leaves_4",         "textures/world/tiles/nature/Leaves_4.png"    );
    _tex(dir, "tiles_rock_1",           "textures/world/tiles/nature/Rock_1.png"      );
    _tex(dir, "tiles_rock_2",           "textures/world/tiles/nature/Rock_2.png"      );
    _tex(dir, "tiles_rock_3",           "textures/world/tiles/nature/Rock_3.png"      );
    _tex(dir, "tiles_rock_4",           "textures/world/tiles/nature/Rock_4.png"      );
    _tex(dir, "tiles_stone_tile",       "textures/world/tiles/nature/Stone tile.png"  );
    _tex(dir, "tiles_tall_grass",       "textures/world/tiles/nature/Tall grass.png"  );
    _tex(dir, "tiles_tree_stump",       "textures/world/tiles/nature/Tree stump.png"  );
    _tex(dir, "tiles_wooden_logs",      "textures/world/tiles/nature/Wooden logs.png" );

    // Tiles - nature sheets
    _tex(dir, "tiles_grass",       "textures/world/tiles/nature/Grass.png"                             );
    _tex(dir, "tiles_dirt",        "textures/world/tiles/nature/Dirt.png"                              );
    _tex(dir, "tiles_coastlines",  "textures/world/tiles/nature/Coastlines.png"                        );
    _tex(dir, "tiles_forest_1",    "textures/world/tiles/nature/Forest tiles_1.png"                    );
    _tex(dir, "tiles_forest_2",    "textures/world/tiles/nature/Forest tiles_2.png"                    );
    _tex(dir, "tiles_forest_3",    "textures/world/tiles/nature/Forest tiles_3.png"                    );
    _tex(dir, "tiles_waterfall",   "textures/world/tiles/nature/Waterfall tiles (48x48 - 5 frames).png");

    // Tiles - roads sheets
    _tex(dir, "tiles_roads",       "textures/world/tiles/roads/Roads.png"      );
    _tex(dir, "tiles_roads_stone", "textures/world/tiles/roads/Roads_stone.png");

    // Tiles - interior sheets
    _tex(dir, "tiles_interior",           "textures/world/tiles/interior/Fantasy RPG Interior Pack (48x48 grid).png");
    _tex(dir, "tiles_interior_alchemy",   "textures/world/tiles/interior/Expansion_AlchemyLab.png"                 );
    _tex(dir, "tiles_interior_bath",      "textures/world/tiles/interior/Expansion_Bath.png"                       );
    _tex(dir, "tiles_interior_bedroom",   "textures/world/tiles/interior/Expansion_Bedroom.png"                    );
    _tex(dir, "tiles_interior_clockwork", "textures/world/tiles/interior/Expansion_ClockworkFactory.png"           );
    _tex(dir, "tiles_interior_music",     "textures/world/tiles/interior/Expansion_Music.png"                      );
    _tex(dir, "tiles_interior_school",    "textures/world/tiles/interior/Expansion_School.png"                     );
    _tex(dir, "tiles_interior_workshop",  "textures/world/tiles/interior/Expansion_Workshop.png"                   );

    // World objects
    _tex(dir, "tree_medium_1",         "textures/world/tiles/objects/Tree_medium_1.png"         );
    _tex(dir, "tree_medium_2",         "textures/world/tiles/objects/Tree_medium_2.png"         );
    _tex(dir, "tree_medium_3",         "textures/world/tiles/objects/Tree_medium_3.png"         );
    _tex(dir, "tree_medium_4",         "textures/world/tiles/objects/Tree_medium_4.png"         );
    _tex(dir, "tree_medium_christmas", "textures/world/tiles/objects/Tree_medium_christmas.png" );
    _tex(dir, "tree_small_1",          "textures/world/tiles/objects/Tree_small_1.png"          );
    _tex(dir, "tree_small_2",          "textures/world/tiles/objects/Tree_small_2.png"          );
    _tex(dir, "tree_small_3",          "textures/world/tiles/objects/Tree_small_3.png"          );
    _tex(dir, "tree_small_4",          "textures/world/tiles/objects/Tree_small_4.png"          );
    _tex(dir, "well_3",                "textures/world/tiles/objects/Well_3.png"                );
    _tex(dir, "well_4",                "textures/world/tiles/objects/Well_4.png"                );

    // Buildings
    _tex(dir, "house_big_3_closed", "textures/world/buildings/House_big_3 (closed).png");
    _tex(dir, "house_big_3_open",   "textures/world/buildings/House_big_3 (open).png"  );

    // UI
    _tex(dir, "btn_normal",      "textures/ui/buttons/Button_03A_Normal.png"  );
    _tex(dir, "btn_selected",    "textures/ui/buttons/Button_03A_Selected.png");
    _tex(dir, "bg_box",          "textures/ui/panels/BGbox_03A.png"           );
    _tex(dir, "banner_02c",      "textures/ui/banners/BannerMedium_02C.png"   );
    _tex(dir, "cursor_gauntlet", "textures/ui/cursors/Gauntlet.png"           );
    _tex(dir, "cursor_magic",    "textures/ui/cursors/Gauntlet_Magic.png"     );

    // Backgrounds
    _tex(dir, "mountains_bg", "textures/backgrounds/mountains.png");
}

// ----------------------------------------------------------------------------
void Asset_loader::_load_anims(
    std::string const& dir
    ) {

    // Player (Beastmaster)
    _anim(dir, "player_idle",              "textures/world/entities/player/Beastmaster_idle.png"           );
    _anim(dir, "player_walk",              "textures/world/entities/player/Beastmaster_walk.png"           );
    _anim(dir, "player_roll",              "textures/world/entities/player/Beastmaster_roll.png"           );
    _anim(dir, "player_jump",              "textures/world/entities/player/Beastmaster_jump.png"           );
    _anim(dir, "player_falling",           "textures/world/entities/player/Beastmaster_falling.png"        );
    _anim(dir, "player_cast",              "textures/world/entities/player/Beastmaster_cast.png"           );
    _anim(dir, "player_melee",             "textures/world/entities/player/Beastmaster_melee.png"          );
    _anim(dir, "player_melee_hitbox",      "textures/world/entities/player/Beastmaster_melee_hitbox.png"   );
    _anim(dir, "player_melee_no_hitbox",   "textures/world/entities/player/Beastmaster_melee_NoHitbox.png" );
    _anim(dir, "player_ranged",            "textures/world/entities/player/Beastmaster_ranged.png"         );
    _anim(dir, "player_hit",               "textures/world/entities/player/Beastmaster_hit.png"            );
    _anim(dir, "player_death",             "textures/world/entities/player/Beastmaster_death.png"          );
    _anim(dir, "player_die",               "textures/world/entities/player/Beastmaster_die.png"            );
    _anim(dir, "player_grab",              "textures/world/entities/player/Beastmaster_grab.png"           );
    _anim(dir, "player_item_got",          "textures/world/entities/player/Beastmaster_itemGot.png"        );
    _anim(dir, "player_push",              "textures/world/entities/player/Beastmaster_push.png"           );
    _anim(dir, "player_sleeping",          "textures/world/entities/player/Beastmaster_sleeping.png"       );
    _anim(dir, "player_mining",            "textures/world/entities/player/Beastmaster_mining.png"         );
    _anim(dir, "player_woodcutting",       "textures/world/entities/player/Beastmaster_woodcutting.png"    );
    _anim(dir, "player_hammering",         "textures/world/entities/player/Beastmaster_hammering.png"      );
    _anim(dir, "player_hoeing",            "textures/world/entities/player/Beastmaster_hoeing.png"         );
    _anim(dir, "player_shovelling",        "textures/world/entities/player/Beastmaster_shovelling.png"     );
    _anim(dir, "player_watering",          "textures/world/entities/player/Beastmaster_watering.png"       );
    _anim(dir, "player_fishing",           "textures/world/entities/player/Beastmaster_fishing.png"        );
    _anim(dir, "player_fishing_cast",      "textures/world/entities/player/Beastmaster_fishing_cast.png"   );
    _anim(dir, "player_fishing_jerking",   "textures/world/entities/player/Beastmaster_fishing_jerking.png");

    // Player pet (Fox)
    _anim(dir, "pet_fox_idle",            "textures/world/entities/player_pet/Fox_idle.png"          );
    _anim(dir, "pet_fox_walk",            "textures/world/entities/player_pet/Fox_walk.png"          );
    _anim(dir, "pet_fox_run",             "textures/world/entities/player_pet/Fox_run.png"           );
    _anim(dir, "pet_fox_sleeping",        "textures/world/entities/player_pet/Fox_sleeping.png"      );
    _anim(dir, "pet_fox_melee",           "textures/world/entities/player_pet/Fox_melee.png"         );
    _anim(dir, "pet_fox_melee_hitbox",    "textures/world/entities/player_pet/Fox_melee_hitbox.png"  );
    _anim(dir, "pet_fox_melee_no_hitbox", "textures/world/entities/player_pet/Fox_melee_NoHitbox.png");
    _anim(dir, "pet_fox_hit",             "textures/world/entities/player_pet/Fox_hit.png"           );
    _anim(dir, "pet_fox_death",           "textures/world/entities/player_pet/Fox_death.png"         );
    _anim(dir, "pet_fox_die",             "textures/world/entities/player_pet/Fox_die.png"           );
}

// ----------------------------------------------------------------------------
void Asset_loader::_load_sfx(
    std::string const& dir
    ) {

    struct Sfx { char const* key; char const* path; };
    static Sfx const sfx[] = {

        { "sfx_ui_hover", "audio/sfx/ui/African1.wav" },
        { "sfx_ui_click", "audio/sfx/ui/African3.wav" },
    };

    for (auto const& s : sfx) {

        if (auto h = _resources.load<sf::SoundBuffer>(s.key, dir + s.path)) { _handles.push_back(h); }
    }
}

// ----------------------------------------------------------------------------
void Asset_loader::_load_music(
    std::string const& dir
    ) {

    struct Mus { char const* key; char const* path; };
    static Mus const tracks[] = {

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

    for (auto const& m : tracks) { _resources.load<sf::Music>(m.key, dir + m.path); }
}

// ----------------------------------------------------------------------------
bool Asset_loader::load_all() {

    std::string const dir = ASSET_DIR;

    _load_fonts   (dir);
    _load_textures(dir);
    _load_anims   (dir);
    _load_sfx     (dir);
    _load_music   (dir);

    return !_handles.empty();
}

} // namespace mirelight
