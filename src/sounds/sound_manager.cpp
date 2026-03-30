// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "sounds/sound_manager.h"
#include "assets/asset_manager.h"
#include "utils/logger.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::sounds {

// ===========================================================================
// Using directives
// ---------------------------------------------------------------------------

using namespace mirelight::assets;

// ===========================================================================
// Class Sound_manager
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
Sound_manager& Sound_manager::get_instance() {

    static Sound_manager instance;
    return instance;
}

// ---------------------------------------------------------------------------
void Sound_manager::play_music(assets::Music_id const music_id) {

    sf::Music& music = Asset_manager::get_instance().get(music_id);
    music.setLooping(true);
    music.setVolume(_music_volume);
    music.play();

    _active_music.insert(music_id);
}

// ---------------------------------------------------------------------------
void Sound_manager::stop_music(assets::Music_id const music_id) {

    sf::Music& music = Asset_manager::get_instance().get(music_id);
    music.stop();

    _active_music.erase(music_id);
}

// ---------------------------------------------------------------------------
void Sound_manager::play_sfx(assets::Sfx_id const sfx_id) {

    std::erase_if(_active_sfx, [](sf::Sound const& sound) {

        return sound.getStatus() == sf::Sound::Status::Stopped;
        });

    sf::Sound& sound = _active_sfx.emplace_back(Asset_manager::get_instance().get(sfx_id));
    sound.setVolume(_sfx_volume);
    sound.play();
}

// ---------------------------------------------------------------------------
void Sound_manager::set_music_volume(float const volume) {

    _music_volume = std::clamp(volume, 0.0f, 100.0f);

    for (auto const id : _active_music) {

        sf::Music& music = Asset_manager::get_instance().get(id);
        music.setVolume(_music_volume);
    }
}

// ---------------------------------------------------------------------------
void Sound_manager::set_sfx_volume(float const volume) {

    _sfx_volume = std::clamp(volume, 0.0f, 100.0f);

    for (sf::Sound& sound : _active_sfx) {

        sound.setVolume(_sfx_volume);
    }
}

// ---------------------------------------------------------------------------
Sound_manager::Sound_manager()
    : _music_volume(100.0f)
    , _sfx_volume(100.0f)
    , _active_music()
    , _active_sfx()
{}

} // namespace mirelight::sounds
