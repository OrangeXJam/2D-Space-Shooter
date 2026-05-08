#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"

unsigned int createTextureToMesh(const char* imgFilePath, int textureSlot)
{
    int textureWidth, textureHeight, textureChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureDataPointer = stbi_load(imgFilePath, &textureWidth, &textureHeight, &textureChannels, 4);
    if(textureDataPointer == nullptr)
    {
        std::cout << "Failed to load image texture" << std::endl;
        return 0;
    }
    unsigned int textureObject;
    glGenTextures(1, &textureObject);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, textureObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth,textureHeight ,0 ,GL_RGBA, GL_UNSIGNED_BYTE, textureDataPointer);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureDataPointer);
    return textureObject;
}

#endif // TEXTUREHANDLER_H