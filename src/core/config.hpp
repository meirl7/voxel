#pragma once

#include <string>
#include <unordered_map>

class Config
{
public:
	bool load(const std::string& filepath);
	bool save(const std::string& filepath);

	std::string getString(const std::string& section, const std::string& key, const std::string& defaultVal = "");
	int getInt(const std::string& section, const std::string& key, int defaultVal = 0);
	float getFloat(const std::string& section, const std::string& key, float defaultVal = 0.0f);

	void setString();
	void setInt();
	void setFloat();
private:
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
};