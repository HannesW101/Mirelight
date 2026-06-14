// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "core/game_settings.hpp"

#include "module-core/config/include/config.hpp"

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Using directives
// ----------------------------------------------------------------------------

using namespace titan::core;

// ============================================================================
// CLass Game_settings
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
Game_settings::Game_settings(
    Config& config
    ) : _config(config)
{}

// ----------------------------------------------------------------------------
Settings const& Game_settings::values() const {

    return _values;
}

// ----------------------------------------------------------------------------
void Game_settings::set(
    Settings const& s
    ) {

    _values = s;
}

// ----------------------------------------------------------------------------
void Game_settings::load() {

    Settings d; // defaults

    _values.window_width  = _config.get_or<int>("video", "width",  d.window_width);
    _values.window_height = _config.get_or<int>("video", "height", d.window_height);
    _values.fullscreen    = _config.get_or<bool>("video", "fullscreen", d.fullscreen);
    _values.vsync         = _config.get_or<bool>("video", "vsync", d.vsync);
    _values.fps_cap       = _config.get_or<int>("video", "fps_cap", d.fps_cap);
    _values.music_volume  = _config.get_or<double>("audio", "music", d.music_volume) > 0
                          ? static_cast<float>(_config.get_or<double>("audio", "music", d.music_volume))
                          : d.music_volume;
    _values.sfx_volume    = static_cast<float>(_config.get_or<double>("audio", "sfx", d.sfx_volume));
}

// ----------------------------------------------------------------------------
void Game_settings::save() {

    _config.set<int>("video", "width",  _values.window_width);
    _config.set<int>("video", "height", _values.window_height);
    _config.set<bool>("video", "fullscreen", _values.fullscreen);
    _config.set<bool>("video", "vsync", _values.vsync);
    _config.set<int>("video", "fps_cap", _values.fps_cap);
    _config.set<double>("audio", "music", _values.music_volume);
    _config.set<double>("audio", "sfx",   _values.sfx_volume);
}

} // namespace mirelight
