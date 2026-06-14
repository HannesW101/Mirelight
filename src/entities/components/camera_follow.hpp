#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-game/include/game_component.hpp"

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::render { class Camera; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Camera_follow
// ----------------------------------------------------------------------------

class Camera_follow final : public titan::game::Game_component {

public:
    explicit Camera_follow(titan::render::Camera& camera);

    void on_start() override;
    void update(float dt) override;

private:
    titan::render::Camera& _camera;
};

} // namespace mirelight
