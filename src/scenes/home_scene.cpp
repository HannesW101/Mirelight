// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/home_scene.hpp"
#include "scenes/pause_scene.hpp"
#include "scenes/quest_popup_scene.hpp"
#include "core/paths.hpp"
#include "world/rendering/tilemap_renderer.hpp"
#include "world/world_config.hpp"
#include "world/areas/object_spawner.hpp"
#include "world/areas/game_session.hpp"
#include "entities/player/player_factory.hpp"
#include "entities/npcs/wife_anim_data.hpp"
#include "quests/quest.hpp"

#include "module-app/include/application.hpp"
#include "module-scene/include/scene_manager.hpp"

#include "module-game/include/world.hpp"
#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"
#include "module-game/components/include/sprite_renderer.hpp"
#include "module-game/components/include/animator.hpp"
#include "module-game/components/include/script.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/render_layer.hpp"
#include "module-render/include/camera.hpp"

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Color.hpp"

#include "module-ui/include/ui_system.hpp"

#include "module-audio/include/audio_system.hpp"
#include "module-audio/include/audio_bus.hpp"

#include "module-core/events/include/sfml_event_manager.hpp"
#include "module-core/events/include/event_type.hpp"

#include "module-utils/include/math.hpp"

#include <cmath>
#include <memory>
#include <string>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::game;
using namespace titan::ui;
using namespace titan::events;
using namespace titan::render;
using namespace titan::utils;

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

namespace {

constexpr int ROOM_COLS      = 63;
constexpr int WALL_ROWS      = 2;
constexpr int WALL_UNIT_COLS = 3;
constexpr int TS             = world_cfg::TILE_SIZE;

constexpr int WALL_SRC_X = 288;
constexpr int WALL_SRC_Y = 0;
constexpr int WALL_SRC_W = 144;
constexpr int WALL_SRC_H = 96;

constexpr float INTERACT_RADIUS = 96.0f; // 3 tiles
constexpr float NPC_HALF_HEIGHT = 31.5f; // half height of 63px NPC sprite

constexpr char const* WIFE_ID = "wife"; // shared key: game object name + quest npc field

} // namespace

// ============================================================================
// Class Home_scene
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Home_scene::Home_scene(
    Game_session& session
    )
    : Scene("home")
    , _session(session)
{}

// ----------------------------------------------------------------------------
Home_scene::~Home_scene() = default;

// ----------------------------------------------------------------------------
void Home_scene::_register_escape() {

    _escape_cb_id = SFML_event_manager::instance().register_callback(
        SFML_event_type::KEYPRESS_ESCAPE,
        [this](SFML_event_data const&) {
            application().audio().play_sfx("sfx_ui_click", titan::audio::Audio_bus::UI);
            scenes().push(std::make_unique<Pause_scene>(_session));
            },
        listener_id()
        );
}

// ----------------------------------------------------------------------------
void Home_scene::_deregister_escape() {

    if (_escape_cb_id != 0) {

        SFML_event_manager::instance().deregister_callback(_escape_cb_id);
        _escape_cb_id = 0;
    }
}

// ----------------------------------------------------------------------------
void Home_scene::_register_rmb() {

    _rmb_cb_id = SFML_event_manager::instance().register_callback(
        SFML_event_type::MOUSE_BUTTON_RIGHT_PRESS,
        [this](SFML_event_data const&) {

            if (!_wife || !_player) { return; }

            auto const wp = _wife->transform().position();
            auto const pp = _player->transform().position();
            float const dx = wp.x - pp.x;
            float const dy = wp.y - pp.y;

            if (dx * dx + dy * dy >= INTERACT_RADIUS * INTERACT_RADIUS) { return; }

            Quest const* q = _session.quests().ready_for(WIFE_ID);
            if (!q) { q = _session.quests().available_for(WIFE_ID); }

            if (q) { scenes().push(std::make_unique<Quest_popup_scene>(_session, q->id)); }
        },
        listener_id()
        );
}

// ----------------------------------------------------------------------------
void Home_scene::_deregister_rmb() {

    if (_rmb_cb_id != 0) {

        SFML_event_manager::instance().deregister_callback(_rmb_cb_id);
        _rmb_cb_id = 0;
    }
}

// ----------------------------------------------------------------------------
void Home_scene::_build_wall_mesh() {

    float const unit_w = static_cast<float>(WALL_UNIT_COLS * TS);
    float const unit_h = static_cast<float>(WALL_ROWS * TS);
    float const tx0    = static_cast<float>(WALL_SRC_X);
    float const ty0    = static_cast<float>(WALL_SRC_Y);
    float const tx1    = tx0 + static_cast<float>(WALL_SRC_W);
    float const ty1    = ty0 + static_cast<float>(WALL_SRC_H);

    _wall_mesh.clear();
    _wall_mesh.setPrimitiveType(sf::PrimitiveType::Triangles);

    int const units = ROOM_COLS / WALL_UNIT_COLS;
    for (int i = 0; i < units; ++i) {

        float const x0 = static_cast<float>(i) * unit_w;
        float const x1 = x0 + unit_w;
        float const y0 = 0.0f;
        float const y1 = unit_h;

        auto v = [&](
            float px,
            float py,
            float u,
            float tv
            ) {

            sf::Vertex vert;
            vert.position  = {px, py};
            vert.texCoords = {u, tv};
            _wall_mesh.append(vert);
        };

        v(x0, y0, tx0, ty0);  v(x1, y0, tx1, ty0);  v(x1, y1, tx1, ty1);
        v(x0, y0, tx0, ty0);  v(x1, y1, tx1, ty1);  v(x0, y1, tx0, ty1);
    }
}

// ----------------------------------------------------------------------------
void Home_scene::_spawn_quest_indicator() {

    auto* indicator = _world->spawn("quest_indicator");

    auto* sr = indicator->add_component<Sprite_renderer>();
    sr->set_origin_centered(true);
    sr->set_layer(Render_layer::FOREGROUND);
    sr->set_color(sf::Color::Transparent); // hidden until a quest is available

    auto* script = indicator->add_component<Script>();
    script->set_update_fn(
        [this, sr,
         bounce_time = 0.0f,
         cur_key = std::string{}
        ](Game_object& self, float dt) mutable
        {
            if (!_wife) { return; }

            Quest const* q_ready = _session.quests().ready_for(WIFE_ID);
            Quest const* q_avail = _session.quests().available_for(WIFE_ID);

            std::string new_key;
            if (q_ready) {

                new_key = (q_ready->type == Quest_type::MAIN) ? "quest_main_ready" : "quest_side_ready";
            } else if (q_avail) {

                new_key = (q_avail->type == Quest_type::MAIN) ? "quest_main_avail" : "quest_side_avail";
            }

            if (new_key.empty()) {

                sr->set_color(sf::Color::Transparent);
                return;
            }

            if (new_key != cur_key) {

                cur_key = new_key;
                sr->set_texture(new_key);
                sr->set_color(sf::Color::White);
            }

            bounce_time += dt;
            constexpr float HZ  = 1.0f;
            constexpr float AMP = 6.0f;
            float const bounce = std::sin(bounce_time * TAU * HZ) * AMP;

            auto const wife_pos = _wife->transform().position();
            self.transform().set_position({wife_pos.x, wife_pos.y - NPC_HALF_HEIGHT - 30.0f + bounce});
        }
        );
}

// ----------------------------------------------------------------------------
void Home_scene::on_enter() {

    std::string const data_dir{paths::DATA};
    _tiles.load(data_dir + "/tiles.json");

    _chunks.clear();
    for (int cy = 0; cy < CHUNK_ROWS; ++cy) {

        for (int cx = 0; cx < CHUNK_COLS; ++cx) {

            auto chunk = std::make_unique<Chunk>(Chunk_coord{cx, cy});
            chunk->load_from_path(data_dir + "/areas/home/" + std::to_string(cx) + "_" + std::to_string(cy) + ".chunk", 0);
            _chunks.push_back(std::move(chunk));
        }
    }

    register_default_object_types(_object_factory);
    _world   = std::make_unique<World>();
    _spawner = std::make_unique<Object_spawner>(
        Spawn_table_loader(data_dir),
        _object_factory,
        _session.state_store(),
        _session
        );
    _spawner->spawn_area(Area_id::interior("home"), sf::Vector2f{0.0f, 0.0f}, *_world);

    _tilemap = std::make_unique<Tilemap_renderer>(_tiles, application().resources());

    if (auto h = application().resources().get<sf::Texture>("tiles_interior")) {

        _interior_tex = h.get();
    }
    _build_wall_mesh();

    _player_factory = std::make_unique<Player_factory>(*_world, _walkable, application().renderer().world_camera());

    // Wife NPC
    _wife = _world->spawn(WIFE_ID);
    _wife->transform().set_position({20.0f * world_cfg::TILE_SIZE, 12.0f * world_cfg::TILE_SIZE});
    {
        auto* sprite = _wife->add_component<Sprite_renderer>();
        sprite->set_texture("npc_wife_idle");
        sprite->set_origin_centered(true);
        sprite->set_layer(Render_layer::ENTITIES);

        auto* anim = _wife->add_component<Animator>();
        register_wife_animations(*anim);
        anim->play("idle_front");
    }

    _session.quests().load(data_dir + "/quests.json");
    _spawn_quest_indicator();

    sf::Vector2f const start{32.0f * world_cfg::TILE_SIZE, 15.0f * world_cfg::TILE_SIZE};
    _player = _player_factory->create(start);

    application().audio().music().crossfade_to("music_ambient_2", 2.0f, true);

    _ui = std::make_unique<UI_system>(application());

    _register_escape();
    _register_rmb();
}

// ----------------------------------------------------------------------------
void Home_scene::on_exit() {

    _deregister_escape();
    _deregister_rmb();

    if (_spawner && _world) { _spawner->unload_area(Area_id::interior("home"), *_world); }
}

// ----------------------------------------------------------------------------
void Home_scene::on_pause() {

    _deregister_escape();
    _deregister_rmb();
}

// ----------------------------------------------------------------------------
void Home_scene::on_resume() {

    _register_escape();
    _register_rmb();
}

// ----------------------------------------------------------------------------
void Home_scene::fixed_update(
    float fixed_dt
    ) {

    if (_world) { _world->fixed_update(fixed_dt); }
}

// ----------------------------------------------------------------------------
void Home_scene::update(
    float dt
    ) {

    if (!_world) { return; }

    _world->update(dt);
    application().renderer().world_camera().tick(dt);

    if (_ui) { _ui->update(dt); }
}

// ----------------------------------------------------------------------------
void Home_scene::render(
    titan::render::Renderer& renderer
    ) {

    if (_tilemap) { _tilemap->render_grid(_chunks, CHUNK_COLS, renderer); }
    if (_world)   { _world->render(renderer); }

    if (_interior_tex && _wall_mesh.getVertexCount() > 0) {

        sf::RenderStates states;
        states.texture = _interior_tex;
        renderer.submit(Render_layer::WORLD_OBJECTS, _wall_mesh, states);
    }

    if (_ui) { _ui->render(); }
}

} // namespace mirelight
