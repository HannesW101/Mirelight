#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "ui/cursor_mode.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

#include <memory>
#include <optional>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::resources { class Resource_manager; }
namespace titan::render    { class Renderer; }
namespace titan::game      { class World; }
namespace sf               { class RenderWindow; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Cursor_manager
// ----------------------------------------------------------------------------

class Cursor_manager {

public:
    void load(titan::resources::Resource_manager& rm);

    // Sets the active cursor mode. Returns true on the frame a transition
    // to GAUNTLET_MAGIC occurs (used to trigger UI hover SFX).
    bool set_mode(Cursor_mode mode);

    Cursor_mode mode() const { return _mode; }

    // Scans world objects for Cursor_hint components near the current mouse
    // position, picks the highest-priority hint in range, sets mode, and
    // updates sprite position. Call this in game-scene update() when _is_top.
    void update_from_world(
        titan::game::World const&  world,
        titan::render::Renderer&   renderer
        );

    void update(sf::RenderWindow const& window);
    void render(titan::render::Renderer& renderer);

private:
    Cursor_mode _mode = Cursor_mode::GAUNTLET;
    Cursor_mode _prev = Cursor_mode::GAUNTLET;

    std::shared_ptr<sf::Texture> _tex_gauntlet;
    std::shared_ptr<sf::Texture> _tex_attack;
    std::shared_ptr<sf::Texture> _tex_dialog;
    std::shared_ptr<sf::Texture> _tex_inspect;
    std::shared_ptr<sf::Texture> _tex_trade;
    std::shared_ptr<sf::Texture> _tex_magic;

    std::optional<sf::Sprite> _sprite;

    sf::Texture const* _tex_for(Cursor_mode m) const;
};

} // namespace mirelight
