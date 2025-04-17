#pragma once

#include <map>
#include <string>
#include <glm/glm.hpp>
#include "Shader.h"

struct Character {
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class TextRenderer {
public:
    TextRenderer(unsigned int width, unsigned int height);
    void Load(std::string fontPath, unsigned int fontSize);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    Shader shader; // Persistent shader object
    unsigned int VAO, VBO;
    std::map<char, Character> Characters;
};
