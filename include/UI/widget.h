#ifndef UI_WIDGET
#define UI_WIDGET

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "ui/ui_defs.h"
#include "assets/asset_defs.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <functional>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::ui {

// ===========================================================================
// Class Widget
// ---------------------------------------------------------------------------

class Widget {

public:
    Widget(Widget_type const widget_type, sf::RenderWindow* window)
        : _type(widget_type)
        , _window(window)
        , _state(Widget_state::NORMAL)
    {}

    virtual ~Widget() = default;

    virtual void draw() = 0;

protected:
    virtual void _update() = 0;

    Widget_type _type;
    sf::RenderWindow* _window;

    Widget_state _state;
};

} // namespace mirelight::ui

#endif
