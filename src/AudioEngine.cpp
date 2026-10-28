#include "AudioEngine.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

bool AudioEngine::init(const std::string& device_name) {
    int err = snd_pcm_open(&pcm_handle, device_name.c_str(), SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) return false;
    snd_pcm_set_params(pcm_handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 48000, 1, 50000);
    return true;
}

void AudioEngine::load_wav(const std::string& filepath) {
    sample_buffer.resize(48000 * 2);
    for(size_t i = 0; i < sample_buffer.size(); ++i) {
        sample_buffer[i] = std::sin(i * 0.01f) * 0.5f;
    }
}

void AudioEngine::spawn_grain() {
    if (sample_buffer.empty()) return;
    for (int i = 0; i < MAX_VOICES; ++i) {
        if (!voices[i].active) {
            voices[i].active = true;
            voices[i].position = std::clamp(param_position.load() + ((static_cast<float>(rand()) / RAND_MAX - 0.5f) * 0.1f), 0.0f, 1.0f);
            voices[i].speed = 1.0f;
            voices[i].phase = 0.0f;
            voices[i].duration_samples = 48000.0f * param_size.load();
            voices[i].amplitude = 0.8f;
            break;
        }
    }
}

void AudioEngine::process_audio(float* output_buffer, snd_pcm_uframes_t frames) {
    for (snd_pcm_uframes_t i = 0; i < frames * 2; ++i) output_buffer[i] = 0.0f;
    if (sample_buffer.empty()) return;

    float dt = static_cast<float>(frames) / 48000.0f;
    spawn_timer += dt;
    float interval = 1.0f / param_density.load();
    while (spawn_timer >= interval) {
        spawn_timer -= interval;
        spawn_grain();
    }
}