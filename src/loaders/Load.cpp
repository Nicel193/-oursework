#include "Load.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <glad/glad.h>

#include "../graphics/Texture.h"

int LoadPNG(std::string imagePath, int *textureWidth, int *textureHeight)
{
    stbi_set_flip_vertically_on_load(true);

    int channels;
    GLuint texture;

    unsigned char *pixels = stbi_load(std::string(imagePath).c_str(), textureWidth, textureHeight, &channels, 0);

    if (!pixels)
    {
        std::cout << "LoadPNG Error";
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *textureWidth, *textureHeight, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(pixels);

    return texture;
}

Texture *load_texture(std::string filename)
{
    int width, height;

    GLuint texture = LoadPNG(filename.c_str(), &width, &height);

    if (texture == 0)
    {
        std::cerr << "Could not load texture " << filename << std::endl;
        return nullptr;
    }

    return new Texture(texture, width, height);
}