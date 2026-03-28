#ifndef CURSORS_CURSOR_MANAGER
#define CURSORS_CURSOR_MANAGER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_defs.h"
#include "events/event_user.h"

#include <SFML/Graphics.hpp>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::cursors {

// ===========================================================================
// Class Cursor_manager
// ---------------------------------------------------------------------------

class Cursor_manager final {

public:
    static Cursor_manager& get_instance(sf::RenderWindow* window);

    void change_cursor(assets::Texture_id const cursor_id);

    void draw();

    ~Cursor_manager          (                     );
    Cursor_manager           (Cursor_manager const&) = delete;
    Cursor_manager& operator=(Cursor_manager const&) = delete;
    Cursor_manager           (Cursor_manager&&     ) = delete;
    Cursor_manager& operator=(Cursor_manager&&     ) = delete;

private:
    Cursor_manager(sf::RenderWindow* window);

    void _create_curr_cursor();

    void _update_cursor_pos();

    sf::RenderWindow* _window;

    sf::Sprite*        _curr_cursor;
    assets::Texture_id _curr_cursor_id;
};

} // namespace mirelight::cursors

#endif
