// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/components/camera_follow.hpp"

#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"

#include "module-render/include/camera.hpp"

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::render;

// ============================================================================
// Class Camera_follow
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Camera_follow::Camera_follow(
    Camera& camera
    )
    : _camera(camera)
{}

// ----------------------------------------------------------------------------
void Camera_follow::on_start() {

    // Snap to the player immediately on the first frame (no glide from origin).
    _camera.set_follow_smoothing(0.15f);
    _camera.snap_to(owner().transform().position());
    _camera.set_target_position(owner().transform().position());
}

// ----------------------------------------------------------------------------
void Camera_follow::update(
    float dt
    ) {

    static_cast<void>(dt);

    _camera.set_target_position(owner().transform().position());
}

} // namespace mirelight
