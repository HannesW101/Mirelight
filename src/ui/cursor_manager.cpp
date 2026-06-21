// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "ui/cursor_manager.hpp"
#include "entities/components/cursor_hint.hpp"

#include "module-render/include/renderer.hpp"
#include "module-render/include/render_layer.hpp"
#include "module-resources/include/resource_manager.hpp"
#include "module-game/include/world.hpp"
#include "module-game/include/game_object.hpp"
#include "module-game/components/include/transform.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"

#include <limits>

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

    _tex_gauntlet = rm.get<sf::Texture>("cursor_gauntlet");
    _tex_attack   = rm.get<sf::Texture>("cursor_attack");
    _tex_dialog   = rm.get<sf::Texture>("cursor_dialog");
    _tex_inspect  = rm.get<sf::Texture>("cursor_inspect");
    _tex_trade    = rm.get<sf::Texture>("cursor_trade");
    _tex_magic    = rm.get<sf::Texture>("cursor_magic");

    if (_tex_gauntlet) { _sprite.emplace(*_tex_gauntlet); }
}

// ----------------------------------------------------------------------------
sf::Texture const* Cursor_manager::_tex_for(
    Cursor_mode m
    ) const {

    switch (m) {
        case Cursor_mode::ATTACK:        return _tex_attack  ? _tex_attack.get()  : _tex_gauntlet.get();
        case Cursor_mode::DIALOG:        return _tex_dialog  ? _tex_dialog.get()  : _tex_gauntlet.get();
        case Cursor_mode::INSPECT:       return _tex_inspect ? _tex_inspect.get() : _tex_gauntlet.get();
        case Cursor_mode::TRADE:         return _tex_trade   ? _tex_trade.get()   : _tex_gauntlet.get();
        case Cursor_mode::GAUNTLET_MAGIC:return _tex_magic   ? _tex_magic.get()   : _tex_gauntlet.get();
        default:                         return _tex_gauntlet ? _tex_gauntlet.get() : nullptr;
    }
}

// ----------------------------------------------------------------------------
bool Cursor_manager::set_mode(
    Cursor_mode mode
    ) {

    _prev = _mode;
    _mode = mode;

    if (_sprite) {

        if (auto const* tex = _tex_for(_mode)) {

            _sprite->setTexture(*tex);
        }
    }

    return _mode == Cursor_mode::GAUNTLET_MAGIC && _prev != Cursor_mode::GAUNTLET_MAGIC;
}

// ----------------------------------------------------------------------------
void Cursor_manager::update_from_world(
    titan::game::World const& world,
    titan::render::Renderer&  renderer
    ) {

    auto& win  = renderer.window();
    auto& cam  = renderer.world_camera();
    sf::Vector2f const mouse_world = cam.window_to_world(
        sf::Mouse::getPosition(win), win.getSize());

    Cursor_mode hint     = Cursor_mode::GAUNTLET;
    int         best_pri = -1;
    float       best_d2  = std::numeric_limits<float>::max();

    for (auto const& obj : world.objects()) {

        if (obj->is_destroyed()) { continue; }

        auto* ch = obj->get_component<Cursor_hint>();
        if (!ch || !ch->is_active()) { continue; }

        sf::Vector2f const d  = obj->transform().position() - mouse_world;
        float const        d2 = d.x * d.x + d.y * d.y;
        float const        r  = ch->radius();
        int const          pri = static_cast<int>(ch->mode());

        if (d2 <= r * r && (pri > best_pri || (pri == best_pri && d2 < best_d2))) {

            best_pri = pri;
            best_d2  = d2;
            hint     = ch->mode();
        }
    }

    set_mode(hint);
    update(win);
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
