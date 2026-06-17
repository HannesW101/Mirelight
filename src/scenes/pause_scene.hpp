#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-scene/include/scene.hpp"

#include <memory>

// ============================================================================
// Forward declarations
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
// Class Pause_scene
// ----------------------------------------------------------------------------

class Pause_scene final : public titan::scene::Scene {

public:
    explicit Pause_scene(Game_session& session);
    ~Pause_scene() override;

    void on_enter() override;
    void update(float dt) override;
    void render(titan::render::Renderer& renderer) override;

private:
    Game_session& _session;

    std::unique_ptr<titan::ui::UI_system> _ui;
};

} // namespace mirelight
