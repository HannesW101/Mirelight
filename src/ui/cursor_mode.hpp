#pragma once

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Enum Cursor_mode
// ----------------------------------------------------------------------------

enum class Cursor_mode {

    GAUNTLET, // default in-game
    INSPECT, // chest, pickup, interactable item
    TRADE, // merchant NPC
    DIALOG, // quest-giver NPC
    ATTACK, // attackable enemy
    GAUNTLET_MAGIC // hovering over a UI element
};

} // namespace mirelight
