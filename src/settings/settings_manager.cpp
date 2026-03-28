// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "settings/setting_manager.h"
#include "utils/logger.h"

#include <mini/ini.h>

#include <filesystem>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::settings {

// ===========================================================================
// Constants
// ---------------------------------------------------------------------------

char const* SETTINGS_FILEPATH = "data/settings.ini";

// ===========================================================================
// Class Setting_manager
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Setting_manager& Setting_manager::get_instance() {

    static Setting_manager instance;
    return instance;
}

// ---------------------------------------------------------------------------
Settings Setting_manager::get_settings() const {

    return _settings;
}

// ---------------------------------------------------------------------------
void Setting_manager::update_settings(Settings const& settings) {

    _settings = settings;
    _fill_gaps_with_defaults();
    _write_settings();
}

// ---------------------------------------------------------------------------
Setting_manager::Setting_manager()
    : _settings({})
    {

    _load_settings();
    _fill_gaps_with_defaults();
    _write_settings();
}

// ---------------------------------------------------------------------------
void Setting_manager::_load_settings() {

    mINI::INIFile const file(SETTINGS_FILEPATH);
    mINI::INIStructure ini;

    if (!file.read(ini)) {

        LOG(ERROR) << "Failed to load settings, file does not exist";
        return;
    }

    // Window section
    auto& window = ini["window"];
    if (window.has("width"))  { _settings.window_width  = std::stof(window["width"]); }
    if (window.has("height")) { _settings.window_height = std::stof(window["height"]); }
    if (window.has("vsync")) { _settings.vsync = std::stoi(window["vsync"]); }
    if (window.has("fps_cap")) { _settings.fps_cap = std::stoi(window["fps_cap"]); }
}

// ---------------------------------------------------------------------------
void Setting_manager::_fill_gaps_with_defaults() {

    // Window section
    sf::VideoMode const video_mode            = sf::VideoMode::getFullscreenModes()[0u];
    float         const default_window_size_x = video_mode.size.x;
    float         const default_window_size_y = video_mode.size.y;

    if (_settings.window_width  == 0.0f) { _settings.window_width  = default_window_size_x; }
    if (_settings.window_height == 0.0f) { _settings.window_height = default_window_size_y; }
    if (_settings.vsync == false) { _settings.vsync = false; }
    if (_settings.fps_cap == 0.0f) { _settings.fps_cap = 60u; }
}

// ---------------------------------------------------------------------------
void Setting_manager::_write_settings() {

    std::filesystem::create_directories("data");

    mINI::INIFile const file(SETTINGS_FILEPATH);
    mINI::INIStructure ini;
    bool const pretty_output = true;

    // Window section
    ini["window"]["width"]  = std::to_string(_settings.window_width);
    ini["window"]["height"] = std::to_string(_settings.window_height);
    ini["window"]["vsync"] = std::to_string(_settings.vsync);
    ini["window"]["fps_cap"] = std::to_string(_settings.fps_cap);

    bool const success = file.generate(ini, pretty_output);

    if (!success) {

        LOG(ERROR) << "Failed to write settings";
    }
}

} // namespace mirelight::settings