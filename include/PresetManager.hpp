#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct MIDIMapping {
    uint8_t cc_number = 0;
    uint8_t midi_channel = 0;
    bool is_assigned = false;
};

struct ModSlot {
    std::string slot_name;
    std::string param_name_x;
    std::string param_name_y;
    float min_val = 0.0f;
    float max_val = 100.0f;
    bool invert_x = false;
    bool invert_y = false;
    float smoothing = 0.15f;
    int mode = 0;
    MIDIMapping midi_map;
};

inline void to_json(json& j, const MIDIMapping& m) { j = json{{"cc_number", m.cc_number}, {"midi_channel", m.midi_channel}, {"is_assigned", m.is_assigned}}; }
inline void from_json(const json& j, MIDIMapping& m) { j.at("cc_number").get_to(m.cc_number); j.at("midi_channel").get_to(m.midi_channel); j.at("is_assigned").get_to(m.is_assigned); }

inline void to_json(json& j, const ModSlot& s) { j = json{{"slot_name", s.slot_name}, {"param_name_x", s.param_name_x}, {"param_name_y", s.param_name_y}, {"min_val", s.min_val}, {"max_val", s.max_val}, {"invert_x", s.invert_x}, {"invert_y", s.invert_y}, {"smoothing", s.smoothing}, {"mode", s.mode}, {"midi_map", s.midi_map}}; }
inline void from_json(const json& j, ModSlot& s) { j.at("slot_name").get_to(s.slot_name); j.at("param_name_x").get_to(s.param_name_x); j.at("param_name_y").get_to(s.param_name_y); j.at("min_val").get_to(s.min_val); j.at("max_val").get_to(s.max_val); j.at("invert_x").get_to(s.invert_x); j.at("invert_y").get_to(s.invert_y); j.at("smoothing").get_to(s.smoothing); j.at("mode").get_to(s.mode); j.at("midi_map").get_to(s.midi_map); }

class PresetManager {
public:
    static bool save_preset(const std::string& filepath, const std::vector<ModSlot>& slots) {
        try {
            json j = slots;
            std::ofstream file(filepath);
            if (!file.is_open()) return false;
            file << j.dump(4);
            return true;
        } catch (...) { return false; }
    }
    static bool load_preset(const std::string& filepath, std::vector<ModSlot>& slots) {
        try {
            std::ifstream file(filepath);
            if (!file.is_open()) return false;
            json j; file >> j;
            slots = j.get<std::vector<ModSlot>>();
            return true;
        } catch (...) { return false; }
    }
};