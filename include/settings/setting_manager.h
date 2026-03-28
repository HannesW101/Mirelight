#ifndef SETTINGS_SETTING_MANAGER
#define SETTINGS_SETTING_MANAGER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::settings {

// ===========================================================================
// Structs
// ---------------------------------------------------------------------------

struct Settings {

    // Window section
    float window_width = 0.0f;
    float window_height = 0.0f;
    bool vsync = false;
    unsigned int fps_cap = 0u;
};

// ===========================================================================
// Class Setting_manager
// ---------------------------------------------------------------------------

class Setting_manager final {

public:
    static Setting_manager& get_instance();

    Settings get_settings() const;

    void update_settings(Settings const& settings);

    ~Setting_manager          (                      ) = default;
    Setting_manager           (Setting_manager const&) = delete;
    Setting_manager& operator=(Setting_manager const&) = delete;
    Setting_manager           (Setting_manager&&     ) = delete;
    Setting_manager& operator=(Setting_manager&&     ) = delete;

private:
    Setting_manager();

    void _load_settings();
    void _fill_gaps_with_defaults();
    void _write_settings();

    Settings _settings;
};

} // namespace mirelight::settings

#endif
