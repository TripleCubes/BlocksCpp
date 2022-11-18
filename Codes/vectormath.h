#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "globals.h"

struct Vec3
{
    float x = 0;
    float y = 0;
    float z = 0;

    Vec3(float x, float y, float z);

    Vec3 operator + (Vec3 vec);
    Vec3 operator - (Vec3 vec);
    Vec3 operator * (float num);
    Vec3 operator / (float num);
    bool operator == (Vec3 vec);
    void rotateX(float deg);
    void rotateY(float deg);
};

Vec3 cross(Vec3 vec_a, Vec3 vec_b);
float dot(Vec3 vec_a, Vec3 vec_b);
float distance(Vec3 pos1, Vec3 pos2);
glm::vec3 toGlmVec3(Vec3 vec);
Vec3 toVec3(glm::vec3 vec);
Vec3 toVec3(Pos pos);

#endif