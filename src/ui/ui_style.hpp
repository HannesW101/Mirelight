#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-ui/include/theme.hpp"
#include "module-ui/include/visual_set.hpp"
#include "module-ui/include/visual.hpp"
#include "module-ui/include/widget_state.hpp"

#include "SFML/Graphics/Color.hpp"

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight::style {

// ============================================================================
// Constants
// ----------------------------------------------------------------------------

// ---- Colors ----------------------------------------------------------------
inline constexpr sf::Color CLEAR_COLOR   = sf::Color( 20,  24,  28);
inline constexpr sf::Color BTN_TEXT      = sf::Color( 40,  15,   5);
inline constexpr sf::Color PRESSED_TINT  = sf::Color(200, 185, 160);
inline constexpr sf::Color DISABLED_TINT = sf::Color(160, 160, 160, 120);
inline constexpr sf::Color SCROLL_THUMB_COLOR  = sf::Color(210, 170, 90, 210);

// ---- Depth -----------------------------------------------------------------
inline constexpr float BG_DEPTH = -1000.0f;

// ============================================================================
// Functions
// ----------------------------------------------------------------------------

// ---- Game theme ------------------------------------------------------------
inline titan::ui::Theme mirelight_theme() {

    using namespace titan::ui;

    Visual_set btn;
    btn.normal  (Visual::texture("btn_normal"));
    btn.hovered (Visual::texture("btn_selected"));
    btn.pressed (Visual::texture("btn_selected", PRESSED_TINT  ));
    btn.disabled(Visual::texture("btn_normal",DISABLED_TINT ));
    btn.set_text(Widget_state::NORMAL, Text_appearance{"title_font", 20.0f, BTN_TEXT});
    btn.set_text(Widget_state::DISABLED, Text_appearance{
        "title_font", 20.0f,
        sf::Color(BTN_TEXT.r, BTN_TEXT.g, BTN_TEXT.b, DISABLED_TINT.a)
        });

    Visual_set thumb;
    thumb.normal(Visual::color(SCROLL_THUMB_COLOR));

    Theme theme;
    theme.set("button", btn);
    theme.set("scroll_thumb", thumb);
    return theme;
}

} // namespace mirelight::style
