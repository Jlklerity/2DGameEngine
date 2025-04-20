#pragma once
#include <glad/glad.h>
#include <string>

class Texture {
public:
    Texture(const std::string& filepath);
    ~Texture();

    void Bind() const;
    float GetAspectRatio() const;
    GLuint GetID() const;

private:
    GLuint ID;
    int width, height, channels;
    float aspectRatio;
};
