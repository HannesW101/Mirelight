// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "ui/cursor_manager.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/render_layer.hpp"
#include "module-resources/include/resource_manager.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Cursor_manager
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void Cursor_manager::load(
    titan::resources::Resource_manager& rm
    ) {

    _tex_default = rm.get<sf::Texture>("cursor_gauntlet");
    _tex_hover   = rm.get<sf::Texture>("cursor_magic");

    if (_tex_default) { _sprite.emplace(*_tex_default); }
}

// ----------------------------------------------------------------------------
bool Cursor_manager::set_mode(
    Cursor_mode mode
    ) {

    _prev = _mode;
    _mode = mode;
    if (_sprite) {

        auto const* tex = (_mode == Cursor_mode::HOVER && _tex_hover) ? _tex_hover.get() : _tex_default.get();
        if (tex) { _sprite->setTexture(*tex); }
    }

    return _mode == Cursor_mode::HOVER && _prev != Cursor_mode::HOVER;
}

// ----------------------------------------------------------------------------
void Cursor_manager::update(
    sf::RenderWindow const& window
    ) {

    if (!_sprite) { return; }

    auto mp = sf::Mouse::getPosition(window);
    _sprite->setPosition(sf::Vector2f{static_cast<float>(mp.x), static_cast<float>(mp.y)});
}

// ----------------------------------------------------------------------------
void Cursor_manager::render(
    titan::render::Renderer& renderer
    ) {

    if (_sprite) { renderer.submit(titan::render::Render_layer::UI_OVERLAY, *_sprite); }
}

} // namespace mirelight
