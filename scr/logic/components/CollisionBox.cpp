#include "CollisionBox.h"

void CollisionBox::setBounds(const glm::vec3 & minBound, const glm::vec3 & maxBound) {
    bounds.first = minBound;
    bounds.second = maxBound;
}

bool CollisionBox::intersect(glm::vec3 rayOrigin, glm::vec3 rayDir) {
    glm::vec3 tMin = (bounds.first - rayOrigin) / rayDir;
    glm::vec3 tMax = (bounds.second - rayOrigin) / rayDir;
    glm::vec3 t1 = min(tMin, tMax);
    glm::vec3 t2 = max(tMin, tMax);
    float tNear = std::max(std::max(t1.x, t1.y), t1.z);
    float tFar = std::min(std::min(t2.x, t2.y), t2.z);
    return tNear <= tFar;
}
