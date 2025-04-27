#include "Collision.h"
#include <iostream>

bool Collision:: IsCollidingVertically(const glm::vec2& starPos, const glm::vec2& starSize,
                           const glm::vec2& platformPos, const glm::vec2& platformSize) {
    float starBottom = starPos.y;
    float starTop = starPos.y + starSize.y;
    float platformBottom = platformPos.y;
    float platformTop = platformPos.y + platformSize.y;

    return starBottom <= platformTop && starTop >= platformBottom;
}
bool Collision:: IsCollidingHorizontally(const glm::vec2& currentPos, const glm::vec2& sizeA,
    const glm::vec2& wallPos, const glm::vec2& wallSize,
    const glm::vec2& previousPos) {

float currentRight = currentPos.x + sizeA.x;
float previousRight = previousPos.x + sizeA.x;

float currentLeft = currentPos.x;
float previousLeft = previousPos.x;

bool verticallyOverlapping =
currentPos.y + sizeA.y > wallPos.y &&
currentPos.y < wallPos.y + wallSize.y;

bool movingRight = currentPos.x > previousPos.x;
bool movingLeft  = currentPos.x < previousPos.x;

bool hitRightSide =
movingRight &&
currentRight >= wallPos.x &&
previousRight < wallPos.x &&
verticallyOverlapping;

bool hitLeftSide =
movingLeft &&
currentLeft <= wallPos.x + wallSize.x &&
previousLeft > wallPos.x + wallSize.x &&
verticallyOverlapping;

if (hitLeftSide) std::cout << "Left wall hit!\n";
if (hitRightSide) std::cout << "Right wall hit!\n";
return hitLeftSide || hitRightSide;
}

