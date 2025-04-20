#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& filepath)
    : ID(0), width(0), height(0), channels(0), aspectRatio(1.0f)
{
   
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    std::cout<<filepath.c_str()<<"\n";
    if (data) {
        // Determine format based on channel count
        GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
         
        // Upload texture to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    
        glGenerateMipmap(GL_TEXTURE_2D);

        // Calculate aspect ratio based on width and height
        aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        
        std::cout << "Texture loaded: " << filepath << " (" << width << "x" << height << ", " << channels << " channels)\n";
    } else {
        std::cerr << "Failed to load texture: " << stbi_failure_reason() << std::endl;
    }

    // Free the loaded texture data
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::Bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

float Texture::GetAspectRatio() const {
    return aspectRatio;
}

GLuint Texture::GetID() const {
    return ID;
}
