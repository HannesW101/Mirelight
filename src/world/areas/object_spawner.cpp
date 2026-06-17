// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "world/areas/object_spawner.hpp"
#include "world/areas/area_state.hpp"
#include "world/areas/game_session.hpp"
#include "world/world_config.hpp"

#include "module-game/include/world.hpp"
#include "module-game/include/game_object.hpp"

#include <utility>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::game;

// ============================================================================
// Class Object_spawner
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Object_spawner::Object_spawner(
    Spawn_table_loader loader,
    Object_factory const& factory,
    Area_state_store& store,
    Game_session const& session
    )
    : _loader(std::move(loader))
    , _factory(factory)
    , _store(store)
    , _session(session)
{}

// ----------------------------------------------------------------------------
void Object_spawner::spawn_area(
    Area_id const& area,
    sf::Vector2f area_origin_world,
    World& world
    ) {

    if (_spawned_ids.find(area) != _spawned_ids.end()) { return; } // already spawned

    auto table_it = _table_cache.find(area);
    if (table_it == _table_cache.end()) {

        table_it = _table_cache.emplace(area, _loader.load(area)).first;
    }

    _store.load_area(area, _session.save_dir());

    std::vector<std::uint64_t> ids;
    float const ts = static_cast<float>(world_cfg::TILE_SIZE);

    for (auto const& entry : table_it->second.objects) {

        if (_store.is_destroyed_and_unexpired(area, entry.spawn_id, _session.world_time(), entry.respawn_seconds)) {

            continue; // still on cooldown
        }

        sf::Vector2f const pos{
            area_origin_world.x + entry.local_x * ts,
            area_origin_world.y + entry.local_y * ts
            };

        if (Game_object* obj = _factory.build(pos, entry, area, world, _store, _session)) {

            ids.push_back(obj->id());
        }
    }

    _spawned_ids.emplace(area, std::move(ids));
}

// ----------------------------------------------------------------------------
void Object_spawner::unload_area(
    Area_id const& area,
    World& world
    ) {

    auto it = _spawned_ids.find(area);
    if (it != _spawned_ids.end()) {

        for (std::uint64_t id : it->second) {

            if (Game_object* obj = world.find_by_id(id)) { obj->destroy(); }
        }
        _spawned_ids.erase(it);
    }

    _store.save_area(area, _session.save_dir());
    _store.forget_area(area);
    _table_cache.erase(area);
}

} // namespace mirelight
