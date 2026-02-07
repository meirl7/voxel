#include "config.hpp"

#include <fstream>

bool Config::load(const std::string& filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open()) return false;

    std::string line, currentSection;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;

        if (line.front() == '[' && line.back() == ']')
        {
            currentSection = line.substr(1, line.size() - 2);
        }
        else
        {
            size_t pos = line.find('=');
            if (pos == std::string::npos) continue;
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            data[currentSection][key] = value;
        }
    }
}
