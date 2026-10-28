#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct FileEntry {
    std::string name;
    std::string full_path;
    bool is_directory;
};

class FilePicker {
public:
    std::string current_path = "/userdata/roms/granular_samples/";
    std::vector<FileEntry> entries;
    int selected_index = 0;
    int scroll_offset = 0;
    const int max_visible_rows = 10;
    bool is_active = false;

    void open(const std::string& start_path) {
        current_path = start_path;
        refresh_directory();
        selected_index = 0;
        scroll_offset = 0;
        is_active = true;
    }

    void refresh_directory() {
        entries.clear();
        if (current_path != "/" && current_path != "/userdata/roms/") {
            entries.push_back({"..", get_parent_path(current_path), true});
        }
        DIR* dir = opendir(current_path.c_str());
        if (!dir) return;
        struct dirent* ent;
        while ((ent = readdir(dir)) != nullptr) {
            std::string name(ent->d_name);
            if (name == "." || name == "..") continue;
            std::string full_path = current_path + (current_path.back() == '/' ? "" : "/") + name;
            struct stat st;
            if (stat(full_path.c_str(), &st) == 0) {
                if (S_ISDIR(st.st_mode)) {
                    entries.push_back({name, full_path, true});
                } else if (S_ISREG(st.st_mode)) {
                    if (name.length() >= 4 && name.substr(name.length() - 4) == ".wav") {
                        entries.push_back({name, full_path, false});
                    }
                }
            }
        }
        closedir(dir);
        std::sort(entries.begin(), entries.end(), [](const FileEntry& a, const FileEntry& b) {
            if (a.is_directory != b.is_directory) return a.is_directory > b.is_directory;
            return a.name < b.name;
        });
    }

    void handle_input(uint8_t button) {
        if (!is_active || entries.empty()) return;
        if (button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
            selected_index = (selected_index + 1) % entries.size();
            if (selected_index >= scroll_offset + max_visible_rows) scroll_offset = selected_index - max_visible_rows + 1;
        } else if (button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
            selected_index = (selected_index - 1 + entries.size()) % entries.size();
            if (selected_index < scroll_offset) scroll_offset = selected_index;
        } else if (button == SDL_CONTROLLER_BUTTON_A) {
            if (entries[selected_index].is_directory) {
                current_path = entries[selected_index].full_path;
                refresh_directory();
                selected_index = 0;
                scroll_offset = 0;
            } else {
                is_active = false;
            }
        } else if (button == SDL_CONTROLLER_BUTTON_B) {
            is_active = false;
        }
    }

    void render(SDL_Renderer* renderer, TTF_Font* font) {
        if (!is_active) return;
        SDL_Rect modal = { 70, 50, 500, 380 };
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 13, 17, 23, 245);
        SDL_RenderFillRect(renderer, &modal);
        SDL_SetRenderDrawColor(renderer, 0, 229, 255, 255);
        SDL_RenderDrawRect(renderer, &modal);
    }

private:
    std::string get_parent_path(const std::string& path) {
        size_t last = path.find_last_of('/', path.length() - 2);
        return (last == std::string::npos) ? "/" : path.substr(0, last + 1);
    }
};