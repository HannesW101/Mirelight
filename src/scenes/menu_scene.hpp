#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-scene/include/scene.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <memory>
#include <optional>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::ui { class UI_system; }
namespace titan::render { class Renderer; }

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Menu_scene
// ----------------------------------------------------------------------------

class Menu_scene final : public titan::scene::Scene {

public:
    Menu_scene();
    ~Menu_scene() override;

    void on_enter() override;
    void on_exit()  override;
    void update(float dt) override;
    void render(titan::render::Renderer& renderer) override;

private:
    std::unique_ptr<titan::ui::UI_system> _ui;

    std::shared_ptr<sf::Texture> _mountains_tex;
    std::optional<sf::Sprite>    _bg1;
    std::optional<sf::Sprite>    _bg2;
    float                        _bg_scroll = 0.0f;
    float                        _bg_width  = 1280.0f;

    // Custom cursor
    std::shared_ptr<sf::Texture> _cursor_n_tex;
    std::shared_ptr<sf::Texture> _cursor_h_tex;
    std::optional<sf::Sprite>    _cursor;
    bool                         _cursor_hovering = false;
};

} // namespace mirelight
