#pragma once

#include "../base/base_inc.h"
#include "../world/chunk.h"

struct R_Camera
{
    glm::vec3 pos = glm::vec3(0.0f, CHUNK_HEIGHT, 0.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 right = glm::normalize(glm::cross(DIRECTION_UP, direction));

    glm::vec3 direction = glm::normalize(pos - target);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
};