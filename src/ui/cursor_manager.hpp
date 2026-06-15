#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <memory>
#include <optional>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::resources { class Resource_manager; }
namespace titan::render { class Renderer; }
namespace sf { class RenderWindow; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Enums
// ----------------------------------------------------------------------------

enum class Cursor_mode {

    DEFAULT,
    HOVER
};

// ============================================================================
// Class Cursor_manager
// ----------------------------------------------------------------------------

class Cursor_manager {

public:
    void load(titan::resources::Resource_manager& rm);
    bool set_mode(Cursor_mode mode); // returns true when transitioning to HOVER
    Cursor_mode mode() const { return _mode; }
    void update(sf::RenderWindow const& window);
    void render(titan::render::Renderer& renderer);

private:
    Cursor_mode _mode = Cursor_mode::DEFAULT;
    Cursor_mode _prev = Cursor_mode::DEFAULT;
    std::shared_ptr<sf::Texture> _tex_default;
    std::shared_ptr<sf::Texture> _tex_hover;
    std::optional<sf::Sprite> _sprite;
};

} // namespace mirelight
