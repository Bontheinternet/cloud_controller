#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

class PresetManager {
public:
    static void savePreset(const std::string& filepath, const nlohmann::json& data) {
        std::ofstream file(filepath);
        if (file.is_open()) {
            file << data.dump(4);
        }
    }

    static nlohmann::json loadPreset(const std::string& filepath) {
        std::ifstream file(filepath);
        if (file.is_open()) {
            nlohmann::json data;
            file >> data;
            return data;
        }
        return {};
    }
};