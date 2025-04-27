#pragma once
#include <glm/glm.hpp>
class Collision {
public:
static bool IsCollidingVertically(const glm::vec2& starPos, const glm::vec2& starSize,
                           const glm::vec2& platformPos, const glm::vec2& platformSize);
static bool IsCollidingHorizontally(const glm::vec2& currentPos, const glm::vec2& sizeA,
    const glm::vec2& wallPos, const glm::vec2& wallSize,
    const glm::vec2& previousPos);

};