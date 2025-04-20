#ifndef PLATFORM_H
#define PLATFORM_H

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Platform {
    GLuint VAO, VBO, EBO;
public:
    glm::vec2 position;
    glm::vec2 size;

    Platform(glm::vec2 pos, glm::vec2 sz);
    void Update(const glm::vec2& pos);
    void Draw(const Shader& shader, const Texture& texture, float aspectRatio);
    void ResetPlatform();
    ~Platform();
};

#endif
