// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/player/player_anim_data.hpp"
#include "entities/entity_config.hpp"

#include "module-game/components/include/animator.hpp"
#include "module-resources/include/animation.hpp"

#include "SFML/Graphics/Rect.hpp"

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::resources;

// ============================================================================
// Helpers
// ----------------------------------------------------------------------------

namespace {

// Shorthand so frame tables stay readable.
inline sf::IntRect r(
    int x,
    int y,
    int w,
    int h
    ) {

    return sf::IntRect{sf::Vector2i{x, y}, sf::Vector2i{w, h}};
}

constexpr float FPS  = entity_cfg::ANIM_FPS;
constexpr auto LOOP = Animation_mode::LOOP;
constexpr auto ONCE = Animation_mode::ONE_SHOT;

} // namespace

// ============================================================================
// Functions
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void register_player_animations(
    titan::game::Animator& anim
    ) {

    // -------------------------------------------------------------------------
    // Idle
    // -------------------------------------------------------------------------
    anim.set_spritesheet("player_idle_sheet");

    anim.add_animation(Animation{ "idle_front", {
        r( 48,  47, 45, 49), r(192,  48, 45, 49),
        r(336,  48, 45, 49), r(480,  48, 45, 49),
    }, FPS, LOOP });

    anim.add_animation(Animation{ "idle_back", {
        r( 51, 480, 45, 49), r(195, 480, 45, 49),
        r(339, 480, 45, 49), r(483, 480, 45, 49),
    }, FPS, LOOP });

    anim.add_animation(Animation{ "idle_left", {
        r( 48, 192, 45, 49), r(192, 192, 45, 49),
        r(336, 192, 45, 49), r(480, 192, 45, 49),
    }, FPS, LOOP });

    anim.add_animation(Animation{ "idle_right", {
        r( 51, 336, 45, 49), r(195, 336, 45, 49),
        r(339, 336, 45, 49), r(483, 336, 45, 49),
    }, FPS, LOOP });

    // -------------------------------------------------------------------------
    // Walk
    // -------------------------------------------------------------------------
    anim.set_spritesheet("player_walk_sheet");

    anim.add_animation(Animation{ "walk_front", {
        r( 51,  47, 45, 52), r(195,  48, 45, 52),
        r(339,  48, 45, 52), r(483,  48, 45, 52),
    }, FPS, LOOP });

    anim.add_animation(Animation{ "walk_back", {
        r( 50, 480, 45, 52), r(194, 480, 45, 52),
        r(338, 480, 45, 52), r(482, 480, 45, 52),
    }, FPS, LOOP });

    anim.add_animation(Animation{ "walk_left", {
        r( 48, 191, 45, 52), r(192, 191, 45, 52),
        r(336, 191, 45, 52), r(480, 191, 45, 52),
    }, FPS, LOOP });

    anim.add_animation(Animation{ "walk_right", {
        r( 51, 336, 45, 52), r(195, 336, 45, 52),
        r(339, 336, 45, 52), r(483, 336, 45, 52),
    }, FPS, LOOP });

    // Leave the spritesheet set to idle so the first play() call finds it.
    anim.set_spritesheet("player_idle_sheet");
}

} // namespace mirelight
