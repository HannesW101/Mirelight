#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include "module-audio/include/audio_system.hpp"

#include <string>

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Ambient_music_controller
// ----------------------------------------------------------------------------

class Ambient_music_controller {

public:
    static constexpr int   FIRST   = 2;
    static constexpr int   LAST    = 10;
    static constexpr float SILENCE = 120.0f;

    void update(
        float dt,
        titan::audio::Audio_system& audio
        ) {

        auto& music = audio.music();
        auto const& track = music.current_track();

        // Not a game-mode ambient track so leave everything alone
        if (track.empty() || track == "music_ambient_1") {

            _mode = Mode::IDLE;
            return;
        }

        int const parsed = _parse_index(track);

        // Detect externally-initiated track change (new scene or initial entry)
        if (_mode == Mode::IDLE || parsed != _index) {

            _index       = parsed;
            _mode        = Mode::PLAYING;
            _was_playing = music.is_playing();
            return;
        }

        if (_mode == Mode::PLAYING) {

            bool const playing = music.is_playing();
            if (_was_playing && !playing) {

                _silence_remaining = SILENCE;
                _mode = Mode::SILENCE;
            }

            _was_playing = playing;

        } else if (_mode == Mode::SILENCE) {

            _silence_remaining -= dt;
            if (_silence_remaining <= 0.0f) {

                _index = (_index < LAST) ? _index + 1 : FIRST;
                music.crossfade_to("music_ambient_" + std::to_string(_index), 2.0f, false);
                _was_playing = false;
                _mode        = Mode::PLAYING;
            }
        }
    }

private:
    enum class Mode { IDLE, PLAYING, SILENCE };

    int   _index             = FIRST;
    float _silence_remaining = 0.0f;
    bool  _was_playing       = false;
    Mode  _mode              = Mode::IDLE;

    static int _parse_index(
        std::string const& track
        ) {

        auto const pos = track.rfind('_');
        if (pos == std::string::npos || pos + 1 >= track.size()) { return FIRST; }

        try   { return std::stoi(track.substr(pos + 1)); }
        catch (...) { return FIRST; }
    }
};

} // namespace mirelight
