#include "texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture(const std::string& path)
{
    if (!loadTexture(path))
    {
        // if cannot load texture do this:

    }
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

bool Texture::loadTexture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);

    int channels;
    unsigned char* data = stbi_load(path.c_str(), &(*this).width, &(*this).height, &channels, 0);

    if (!data)
    {
        return false;
    }
    GLenum format;
    switch (channels)
    {
    case 1:
        format = GL_RED;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        format = GL_RGB;
        break;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return true;
}
