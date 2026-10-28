#pragma once
#include <vector>
#include <atomic>
#include <string>
#include <alsa/asoundlib.h>

struct GrainVoice {
    bool active = false;
    float position = 0.0f;
    float speed = 1.0f;
    float phase = 0.0f;
    float duration_samples = 0.0f;
    float amplitude = 1.0f;
};

class AudioEngine {
public:
    static constexpr int MAX_VOICES = 32;
    GrainVoice voices[MAX_VOICES];
    
    std::vector<float> sample_buffer;
    std::atomic<float> param_position{0.5f};
    std::atomic<float> param_size{0.2f};
    std::atomic<float> param_density{10.0f};
    
    bool init(const std::string& device_name = "default");
    void load_wav(const std::string& filepath);
    void process_audio(float* output_buffer, snd_pcm_uframes_t frames);

private:
    snd_pcm_t* pcm_handle = nullptr;
    float spawn_timer = 0.0f;
    void spawn_grain();
};