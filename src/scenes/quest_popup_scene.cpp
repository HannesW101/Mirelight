// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "scenes/quest_popup_scene.hpp"
#include "ui/ui_style.hpp"
#include "world/areas/game_session.hpp"
#include "quests/quest.hpp"

#include "module-app/include/application.hpp"
#include "module-scene/include/scene_manager.hpp"

#include "module-audio/include/audio_system.hpp"
#include "module-audio/include/audio_bus.hpp"

#include "module-ui/include/ui_system.hpp"
#include "module-ui/include/ui_manager.hpp"
#include "module-ui/include/panel.hpp"
#include "module-ui/include/boxes.hpp"
#include "module-ui/include/label.hpp"
#include "module-ui/include/button.hpp"
#include "module-ui/include/image.hpp"
#include "module-ui/include/scroll_view.hpp"
#include "module-ui/include/visual.hpp"
#include "module-ui/include/ui_anchor.hpp"
#include "module-ui/include/ui_length.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/render_layer.hpp"

#include "module-core/events/include/sfml_event_manager.hpp"
#include "module-core/events/include/event_type.hpp"

#include "SFML/Graphics/Color.hpp"

#include <memory>
#include <string>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::ui;
using namespace titan::audio;
using namespace titan::render;
using namespace titan::events;

// ============================================================================
// Helpers
// ----------------------------------------------------------------------------

namespace {

// Selects the gold icon based on the coin count.
char const* gold_icon_key(
    int count
    ) {

    if (count >= 10000) { return "icon_gold_5"; }
    else if (count >= 1000) { return "icon_gold_4"; }
    else if (count >= 100) { return "icon_gold_3"; }
    else if (count >= 10) { return "icon_gold_2"; }
    else { return "icon_gold_1"; }
}

// Panel layout constants
constexpr float PANEL_W      = 540.0f;
constexpr float PANEL_H      = 820.0f;
constexpr float BORDER_X     = 120.0f;   // horizontal inset each side
constexpr float BORDER_TOP   = 200.0f;   // top inset for title
constexpr float BORDER_BOTTOM = 20.0f;  // bottom inset for buttons
constexpr float INNER_PCT    = (PANEL_W - BORDER_X * 2.0f) / PANEL_W;
constexpr float TITLE_H         =  52.0f;   // 2-line capacity for long titles
constexpr float BTN_H           =  54.0f;
constexpr float GAP             =  20.0f;
constexpr float REWARDS_H       = 160.0f;   // hdr(32) + gap(12) + slots(116)
constexpr float BTN_TO_REWARDS  = 120.0f;   // clearance above buttons
constexpr float SCROLL_H        = PANEL_H - BORDER_TOP - BORDER_BOTTOM - TITLE_H - GAP * 2.0f - REWARDS_H - BTN_TO_REWARDS - BTN_H;
constexpr float CONTENT_H       = 2000.0f;  // Label height

} // namespace

// ============================================================================
// Class Quest_popup_scene
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Quest_popup_scene::Quest_popup_scene(
    Game_session& session,
    int           quest_id
    )
    : Scene("quest_popup")
    , _session(session)
    , _quest_id(quest_id)
    {

    set_renders_below(true);
    set_updates_below(true); // game keeps running
}

// ----------------------------------------------------------------------------
Quest_popup_scene::~Quest_popup_scene() = default;

// ----------------------------------------------------------------------------
void Quest_popup_scene::on_enter() {

    _cursor.load(application().resources());
    application().renderer().window().setMouseCursorVisible(false);

    Quest const* quest = _session.quests().quest(_quest_id);
    if (!quest) { scenes().pop(); return; }

    Quest_state const q_state   = _session.quests().state(_quest_id);
    bool const        is_avail  = (q_state == Quest_state::AVAILABLE);
    bool const        is_ready  = (q_state == Quest_state::READY_TO_HAND_IN);

    // Escape declines/closes without any state change.
    _escape_cb_id = SFML_event_manager::instance().register_callback(
        SFML_event_type::KEYPRESS_ESCAPE,
        [this](SFML_event_data const&) {
            application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
            scenes().pop();
        },
        listener_id()
        );

    _ui = std::make_unique<UI_system>(application());
    _ui->manager().set_theme(style::mirelight_theme());
    UI_manager& gui = _ui->manager();

    // ---- Panel: left side, partial width --------------------------------

    auto panel = std::make_unique<Panel>("quest_panel");
    panel->set_anchor(UI_anchor::MIDDLE_LEFT);
    panel->set_offset(20.0f, 0.0f);
    panel->set_size(UI_length::px(PANEL_W), UI_length::px(PANEL_H));
    panel->set_visual_all(Visual::texture("bg_box_quest"));

    // ---- Title -------------------------------------------------------

    std::string const title_text = is_ready ? "Quest Complete!" : quest->title;
    auto title = std::make_unique<Label>("quest_title");
    title->set_anchor(UI_anchor::TOP_CENTER);
    title->set_offset(0.0f, BORDER_TOP);
    title->set_size(UI_length::pct(INNER_PCT), UI_length::px(TITLE_H));
    title->set_text(title_text);
    title->set_align(Text_align::CENTER);
    title->set_visual_all(Visual::none());
    title->set_text_style_all(Text_appearance{"title_font", 20.0f, sf::Color(255, 215, 0), sf::Color::Black, 2.5f});
    title->set_wrap(true);
    panel->add_child(std::move(title));

    // ---- Scrollable description -------------------------------------------

    std::string const desc = is_ready ? quest->hand_in_text : quest->description;

    auto scroll = std::make_unique<Scroll_view>("quest_scroll");
    scroll->set_anchor(UI_anchor::TOP_CENTER);
    scroll->set_offset(0.0f, BORDER_TOP + TITLE_H + GAP);
    scroll->set_size(UI_length::pct(INNER_PCT), UI_length::px(SCROLL_H));
    scroll->set_dir(Scroll_view::Dir::VERTICAL);
    scroll->set_speed(40.0f);
    scroll->set_visual_all(Visual::none());
    // content_size is auto-derived each frame from Label::content_height()

    auto desc_lbl = std::make_unique<Label>("quest_desc");
    desc_lbl->set_size(UI_length::pct(1.0f), UI_length::px(CONTENT_H));
    desc_lbl->set_text(desc);
    desc_lbl->set_align(Text_align::LEFT);
    desc_lbl->set_wrap(true);
    desc_lbl->set_visual_all(Visual::none());
    desc_lbl->set_text_style_all(Text_appearance{"title_font", 16.0f, sf::Color::White, sf::Color::Black, 2.0f});
    scroll->add_child(std::move(desc_lbl));
    panel->add_child(std::move(scroll));

    // ---- Rewards: fixed panel above buttons, never scrolls away ---------

    if (!quest->rewards.empty()) {

        float const n_r     = static_cast<float>(quest->rewards.size());
        float const slots_w = n_r * 80.0f + (n_r > 1.0f ? (n_r - 1.0f) * 16.0f : 0.0f);

        auto rewards_panel = std::make_unique<Panel>("rewards_panel");
        rewards_panel->set_anchor(UI_anchor::BOTTOM_CENTER);
        rewards_panel->set_offset(0.0f, -(BORDER_BOTTOM + BTN_H + BTN_TO_REWARDS));
        rewards_panel->set_size(UI_length::pct(INNER_PCT), UI_length::px(REWARDS_H));
        rewards_panel->set_visual_all(Visual::none());

        auto hdr = std::make_unique<Label>("rewards_hdr");
        hdr->set_size(UI_length::pct(1.0f), UI_length::px(32.0f));
        hdr->set_text("Rewards:");
        hdr->set_align(Text_align::LEFT);
        hdr->set_visual_all(Visual::none());
        hdr->set_text_style_all(Text_appearance{"title_font", 20.0f, sf::Color(255, 215, 0), sf::Color::Black, 2.0f});
        rewards_panel->add_child(std::move(hdr));

        // slots_wrapper offset below header (32 hdr + 12 gap = 44px).
        auto slots_wrapper = std::make_unique<Panel>("slots_wrapper");
        slots_wrapper->set_offset(0.0f, 44.0f);
        slots_wrapper->set_size(UI_length::pct(1.0f), UI_length::px(116.0f));
        slots_wrapper->set_visual_all(Visual::none());

        auto slots = std::make_unique<H_box>("reward_slots");
        slots->set_anchor(UI_anchor::MIDDLE_CENTER);
        slots->set_size(UI_length::px(slots_w), UI_length::px(116.0f));
        slots->set_spacing(16.0f);
        slots->set_visual_all(Visual::none());

        for (int i = 0; i < static_cast<int>(quest->rewards.size()); ++i) {

            auto const& r  = quest->rewards[static_cast<std::size_t>(i)];
            std::string si = std::to_string(i);

            std::string inner_key;
            std::string reward_text;
            if (r.type == "gold") {

                inner_key   = gold_icon_key(r.count);
                reward_text = std::to_string(r.count) + " Gold";
            } else if (r.type == "skill") {

                reward_text = r.name;
            } else {

                reward_text = r.name + " x" + std::to_string(r.count);
            }

            auto slot = std::make_unique<Panel>("reward_slot_" + si);
            slot->set_size(UI_length::px(80.0f), UI_length::px(116.0f));
            slot->set_visual_all(Visual::none());

            auto box = std::make_unique<Panel>("reward_box_" + si);
            box->set_offset(8.0f, 0.0f);
            box->set_size(UI_length::px(64.0f), UI_length::px(64.0f));
            box->set_visual_all(Visual::texture("icon_reward"));

            if (!inner_key.empty()) {

                auto inner = std::make_unique<Image>("reward_inner_" + si);
                inner->set_anchor(UI_anchor::MIDDLE_CENTER);
                inner->set_size(UI_length::px(42.0f), UI_length::px(42.0f));
                inner->set_texture(inner_key);
                inner->set_preserve_aspect(true);
                inner->set_visual_all(Visual::none());
                box->add_child(std::move(inner));
            }

            slot->add_child(std::move(box));

            auto lbl = std::make_unique<Label>("reward_lbl_" + si);
            lbl->set_offset(0.0f, 70.0f);
            lbl->set_size(UI_length::px(80.0f), UI_length::px(46.0f));
            lbl->set_text(reward_text);
            lbl->set_align(Text_align::CENTER);
            lbl->set_wrap(true);
            lbl->set_visual_all(Visual::none());
            lbl->set_text_style_all(Text_appearance{"title_font", 14.0f, sf::Color::White, sf::Color::Black, 1.5f});
            slot->add_child(std::move(lbl));

            slots->add_child(std::move(slot));
        }

        slots_wrapper->add_child(std::move(slots));
        rewards_panel->add_child(std::move(slots_wrapper));
        panel->add_child(std::move(rewards_panel));
    }

    // ---- Buttons: small, side by side -----------------------------------

    bool const has_primary = (is_avail || is_ready);

    auto btn_row = std::make_unique<H_box>("btn_row");
    btn_row->set_anchor(UI_anchor::BOTTOM_CENTER);
    btn_row->set_offset(0.0f, -BORDER_BOTTOM);
    btn_row->set_size(UI_length::pct(INNER_PCT + 0.25f), UI_length::px(BTN_H));
    btn_row->set_spacing(8.0f);
    btn_row->set_visual_all(Visual::none());

    if (has_primary) {

        std::string const primary_text = is_ready ? "HAND IN" : "ACCEPT";
        auto primary = std::make_unique<Button>("btn_primary");
        primary->set_text(primary_text);
        primary->set_text_style_all(Text_appearance{"title_font", 24.0f, sf::Color::White, sf::Color::Black, 2.0f});
        primary->set_size(UI_length::pct(0.48f), UI_length::pct(1.0f));
        primary->set_on_click([this, is_ready] {
            application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
            if (is_ready) { _session.quests().hand_in(_quest_id); }
            else          { _session.quests().accept(_quest_id);  }
            scenes().pop();
            });
        btn_row->add_child(std::move(primary));
    }

    std::string const secondary_text = is_avail ? "DECLINE" : "CLOSE";
    auto secondary = std::make_unique<Button>("btn_secondary");
    secondary->set_text(secondary_text);
    secondary->set_text_style_all(Text_appearance{"title_font", 24.0f, sf::Color::White, sf::Color::Black, 2.0f});
    secondary->set_size(
        has_primary ? UI_length::pct(0.48f) : UI_length::pct(1.0f),
        UI_length::pct(1.0f)
        );
    secondary->set_on_click([this] {
        application().audio().play_sfx("sfx_ui_click", Audio_bus::UI);
        scenes().pop();
        });
    btn_row->add_child(std::move(secondary));

    panel->add_child(std::move(btn_row));
    gui.add(std::move(panel));
}

// ----------------------------------------------------------------------------
void Quest_popup_scene::on_exit() {

    if (_escape_cb_id != 0) {

        SFML_event_manager::instance().deregister_callback(_escape_cb_id);
        _escape_cb_id = 0;
    }

    application().renderer().window().setMouseCursorVisible(true);
}

// ----------------------------------------------------------------------------
void Quest_popup_scene::update(
    float dt
    ) {

    if (!_ui) { return; }

    bool any_hovered = false;
    for (char const* name : {"btn_primary", "btn_secondary"}) {

        auto* w = _ui->manager().find(name);
        if (w && w->is_hovered()) { any_hovered = true; break; }
    }

    Cursor_mode const mode = any_hovered ? Cursor_mode::GAUNTLET_MAGIC : Cursor_mode::GAUNTLET;
    if (_cursor.set_mode(mode)) {

        application().audio().play_sfx("sfx_ui_hover", Audio_bus::UI);
    }

    _cursor.update(application().renderer().window());
    _ui->update(dt);
}

// ----------------------------------------------------------------------------
void Quest_popup_scene::render(
    titan::render::Renderer& renderer
    ) {

    if (_ui) { _ui->render(); }
    _cursor.render(renderer);
}

} // namespace mirelight
