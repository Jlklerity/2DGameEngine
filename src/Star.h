#ifndef STAR_H
#define STAR_H
#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Star {
    unsigned int VAO, VBO, EBO;
public:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 size;
    float gravity;  // Add gravity factor

    Star(glm::vec2 pos, glm::vec2 vel, glm::vec2 sz, float gravity);
     
    void Update(float dt);
    void Draw(const Shader& shader, const Texture& texture,  float aspectRatio, float scale, float angle);

    void BounceIfCollidingWith(const glm::vec2& platformPos, const glm::vec2& platformSize);
    void ResetStar();
    ~Star();

};

#endif