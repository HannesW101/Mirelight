#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-scene/include/scene.hpp"
#include "module-core/events/include/event_listener.hpp"
#include "ui/cursor_manager.hpp"

#include <cstdint>
#include <memory>

// ============================================================================
// Forward declarations (1/2)
// ----------------------------------------------------------------------------

namespace titan::ui { class UI_system; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Forward declarations (2/2)
// ----------------------------------------------------------------------------

class Game_session;

// ============================================================================
// Class Quest_popup_scene
// ----------------------------------------------------------------------------

class Quest_popup_scene final
    : public titan::scene::Scene
    , public titan::events::Event_listener
    {

public:
    Quest_popup_scene(Game_session& session, int quest_id);
    ~Quest_popup_scene() override;

    void on_enter() override;
    void on_exit()  override;
    void update(float dt) override;
    void render(titan::render::Renderer& renderer) override;

private:
    Game_session& _session;
    int           _quest_id;

    std::unique_ptr<titan::ui::UI_system> _ui;
    Cursor_manager                        _cursor;
    std::uint64_t                         _escape_cb_id = 0;
};

} // namespace mirelight
