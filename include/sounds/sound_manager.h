#ifndef SOUNDS_SOUND_MANAGER
#define SOUNDS_SOUND_MANAGER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "assets/asset_defs.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <unordered_set>
#include <vector>

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::sounds {

// ===========================================================================
// Class Sound_manager
// ---------------------------------------------------------------------------

class Sound_manager final {

public:
    static Sound_manager& get_instance();

    void play_music(assets::Music_id const music_id);
    void stop_music(assets::Music_id const music_id);

    void play_sfx(assets::Sfx_id const sfx_id);
    void play_sfx(assets::Sfx_id const sfx_id, float const volume);

    void set_music_volume(float const volume);
    void set_sfx_volume(float const volume);

    float get_music_volume() const;
    float get_sfx_volume() const;

    ~Sound_manager          (                    ) = default;
    Sound_manager           (Sound_manager const&) = delete;
    Sound_manager& operator=(Sound_manager const&) = delete;
    Sound_manager           (Sound_manager&&     ) = delete;
    Sound_manager& operator=(Sound_manager&&     ) = delete;

private:
    Sound_manager();

    float _music_volume;
    float _sfx_volume;

    std::unordered_set<assets::Music_id> _active_music;
    std::vector<sf::Sound> _active_sfx;
};

} // namespace mirelight::sounds

#endif
