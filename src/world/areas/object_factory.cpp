// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/object_factory.hpp"
#include "world/areas/area_state.hpp"
#include "world/areas/game_session.hpp"
#include "world/world_config.hpp"
#include "entities/components/respawn_timer.hpp"

#include "module-game/include/world.hpp"
#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"
#include "module-game/components/include/sprite_renderer.hpp"

#include "module-render/include/render_layer.hpp"
#include "module-resources/include/resource_manager.hpp"
#include "module-utils/include/logger.hpp"

#include "SFML/Graphics/Texture.hpp"

#include <utility>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::game;
using namespace titan::render;
using namespace titan::utils;

// ============================================================================
// Class Object_factory
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void Object_factory::register_type(
    std::string type,
    Builder builder
    ) {

    _builders[std::move(type)] = std::move(builder);
}

// ----------------------------------------------------------------------------
Game_object* Object_factory::build(
    sf::Vector2f world_pos,
    Spawn_entry const& entry,
    Area_id const& area,
    World& world,
    Area_state_store& store,
    Game_session const& session
    ) const {

    auto it = _builders.find(entry.type);
    if (it == _builders.end()) {

        LOG(Log_lvl::ERR) << "Object_factory: unknown spawn type '" + entry.type + "'";
        return nullptr;
    }

    return it->second(world, world_pos, entry, area, store, session);
}

// ============================================================================
// Default object types
// ----------------------------------------------------------------------------

namespace {

Game_object* spawn_decoration(
    World& world,
    sf::Vector2f world_pos,
    Spawn_entry const& entry,
    Area_id const& area,
    Area_state_store& store,
    Game_session const& session,
    Render_layer layer
    ) {

    Game_object* obj = world.spawn(entry.type);
    obj->transform().set_position(world_pos);

    auto* sprite = obj->add_component<Sprite_renderer>();
    sprite->set_texture(entry.variant);
    sprite->set_origin_centered(true);
    sprite->set_layer(layer);

    try {

        auto tex = titan::resources::Resource_manager::instance().get<sf::Texture>(entry.variant);
        if (tex) {

            auto const sz = tex->getSize();
            float const target_w = entry.footprint_w * static_cast<float>(world_cfg::TILE_SIZE);
            float const target_h = entry.footprint_h * static_cast<float>(world_cfg::TILE_SIZE);
            if (sz.x > 0 && sz.y > 0) {

                obj->transform().set_scale(target_w / static_cast<float>(sz.x), target_h / static_cast<float>(sz.y));
            }
        }
    } catch (std::exception const& e) {

        LOG(Log_lvl::WARN) << std::string("Object_factory: could not read texture size for '") + entry.variant + "': " + e.what();
    }

    obj->add_component<Respawn_timer>(area, entry.spawn_id, entry.respawn_seconds, store, session);
    return obj;
}

} // anonymous namespace

// ----------------------------------------------------------------------------
void register_default_object_types(
    Object_factory& factory
    ) {

    factory.register_type(
        "tree",
        [](
            World& world,
            sf::Vector2f pos,
            Spawn_entry const& e,
            Area_id const& area,
            Area_state_store& store,
            Game_session const& session
            ) -> Game_object* {

            return spawn_decoration(world, pos, e, area, store, session, Render_layer::WORLD_OBJECTS);
            });

    factory.register_type(
        "rock",
        [](
            World& world,
            sf::Vector2f pos,
            Spawn_entry const& e,
            Area_id const& area,
            Area_state_store& store,
            Game_session const& session
            ) -> Game_object* {

            return spawn_decoration(world, pos, e, area, store, session, Render_layer::WORLD_OBJECTS);
            });
}

} // namespace mirelight
