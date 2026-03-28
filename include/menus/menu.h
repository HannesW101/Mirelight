#ifndef MENUS_MENU
#define MENUS_MENU

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "menus/menu_defs.h"
#include "utils/logger.h"

#include <SFML/Graphics.hpp>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::menus {

// ===========================================================================
// Class Menu
// ---------------------------------------------------------------------------

class Menu {

public:
    virtual ~Menu() = default;

    Menu           (Menu const&) = delete;
    Menu& operator=(Menu const&) = delete;
    Menu           (Menu&&     ) = delete;
    Menu& operator=(Menu&&     ) = delete;

    virtual void draw() = 0;

    void update(float const dt) { _acc_dt += dt; }

protected:
    Menu(sf::RenderWindow* window)
        : _window(window)
        , _view()
        , _acc_dt(0.0f)
        {

        _window->setView(_view);
    }

    sf::RenderWindow* _window;
    sf::View          _view;

    float _acc_dt;
};

} // namespace mirelight::menus

#endif
