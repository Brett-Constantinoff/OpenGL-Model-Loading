#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct{
    glm::vec3 mPos;
    glm::vec3 mColour;
    float mStrength;
    float mN;
}Light;

#endif