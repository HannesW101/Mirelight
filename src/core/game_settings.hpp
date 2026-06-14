#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include <string>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::core { class Config; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Structs
// ----------------------------------------------------------------------------

struct Settings {

    int   window_width  = 1280;
    int   window_height = 720;
    bool  fullscreen    = false;
    bool  vsync         = true;
    int   fps_cap       = 144;
    float music_volume  = 0.7f;
    float sfx_volume    = 0.8f;
};

// ============================================================================
// Class Game_settings
// ----------------------------------------------------------------------------

class Game_settings {

public:
    explicit Game_settings(titan::core::Config& config);

    Settings const& values() const;
    void set(Settings const& s);

    void load();
    void save();

private:
    titan::core::Config& _config;
    Settings             _values;
};

} // namespace mirelight
