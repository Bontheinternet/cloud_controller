#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

#include "AudioEngine.hpp"
#include "ALSAMIDIManager.hpp"
#include "FilePicker.hpp"
#include "PresetManager.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void render_full_interface(SDL_Renderer* renderer, TTF_Font* font_small, TTF_Font* font_large, const std::vector<float>& audio_buffer);

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0 || TTF_Init() < 0) return -1;

    SDL_Window* window = SDL_CreateWindow("Cloud Controller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    AudioEngine audio_engine;
    audio_engine.init("default");
    audio_engine.load_wav("default_sample.wav");

    std::atomic<bool> audio_running(true);
    std::thread audio_thread([&]() {
        const int frames = 512;
        std::vector<float> audio_out(frames * 2);
        while (audio_running.load()) {
            audio_engine.process_audio(audio_out.data(), frames);
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    });

    ALSAMIDIManager midi_manager;
    if (midi_manager.init()) {
        midi_manager.start([](uint8_t ch, uint8_t n, uint8_t v, bool on){}, [](uint8_t ch, uint8_t cc, uint8_t v){});
    }

    FilePicker file_picker;
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        render_full_interface(renderer, nullptr, nullptr, audio_engine.sample_buffer);
        SDL_RenderPresent(renderer);
    }

    audio_running.store(false);
    if (audio_thread.joinable()) audio_thread.join();
    midi_manager.stop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}