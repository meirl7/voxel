#pragma once

#include <string>

class Texture
{
public:
	unsigned int id;
	int width;
	int height;

	Texture(const std::string& path);
	~Texture();

	void bind();
private:
	bool loadTexture(const std::string& path);
};