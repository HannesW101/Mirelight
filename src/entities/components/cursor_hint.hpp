#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-game/include/game_component.hpp"
#include "ui/cursor_mode.hpp"

#include <functional>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Cursor_hint
// ----------------------------------------------------------------------------

class Cursor_hint final : public titan::game::Game_component {

public:
    using Condition = std::function<bool()>;

    explicit Cursor_hint(
        Cursor_mode mode,
        float radius = 48.0f
        )
        : _mode(mode)
        , _radius(radius)
    {}

    void set_condition(Condition cond) { _condition = std::move(cond); }

    bool        is_active() const { return !_condition || _condition(); }
    Cursor_mode mode()      const { return _mode; }
    float       radius()    const { return _radius; }

private:
    Cursor_mode _mode;
    float       _radius;
    Condition   _condition;
};

} // namespace mirelight
