// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "entities/npcs/wife_anim_data.hpp"
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

inline sf::IntRect r(
    int x,
    int y,
    int w,
    int h
    ) {

    return sf::IntRect{sf::Vector2i{x, y}, sf::Vector2i{w, h}};
}

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

constexpr float FPS = entity_cfg::ANIM_FPS;
constexpr auto LOOP = Animation_mode::LOOP;

} // namespace

// ============================================================================
// Functions
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void register_wife_animations(
    titan::game::Animator& anim
    ) {

    anim.set_spritesheet("npc_wife_idle_sheet");

    // Row 0 — facing front (south)
    anim.add_animation(Animation{ "idle_front", {
        r(  0, 9, 48, 63), r( 48, 9, 48, 63),
        r( 97, 9, 47, 63), r(145, 9, 47, 63),
    }, FPS, LOOP });

    // Row 1 — facing back (north)
    anim.add_animation(Animation{ "idle_back", {
        r( -1, 81, 47, 63), r( 47, 81, 47, 63),
        r( 95, 81, 47, 63), r(143, 81, 47, 63),
    }, FPS, LOOP });

    // Row 2 — facing left (west)
    anim.add_animation(Animation{ "idle_left", {
        r(  1, 153, 47, 63), r( 49, 153, 47, 63),
        r( 97, 153, 47, 63), r(145, 153, 47, 63),
    }, FPS, LOOP });

    // Row 3 — facing right (east)
    anim.add_animation(Animation{ "idle_right", {
        r(  0, 225, 48, 63), r( 48, 225, 48, 63),
        r( 97, 225, 47, 63), r(145, 225, 47, 63),
    }, FPS, LOOP });
}

} // namespace mirelight
