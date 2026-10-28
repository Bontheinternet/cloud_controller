#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <algorithm>

void render_granular_display(SDL_Renderer* renderer, const std::vector<float>& audio_buffer, float playhead_pos, int w, int h) {
    SDL_Rect wave_box = { 40, 120, w - 80, 240 };
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 22, 27, 34, 255);
    SDL_RenderFillRect(renderer, &wave_box);
    SDL_SetRenderDrawColor(renderer, 48, 54, 61, 255);
    SDL_RenderDrawRect(renderer, &wave_box);
}

void render_full_interface(SDL_Renderer* renderer, TTF_Font* font_small, TTF_Font* font_large, const std::vector<float>& audio_buffer) {
    SDL_SetRenderDrawColor(renderer, 10, 12, 16, 255);
    SDL_RenderClear(renderer);
    render_granular_display(renderer, audio_buffer, 0.5f, 640, 480);
}