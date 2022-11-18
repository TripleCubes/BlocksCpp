#include "vectormath.h"

Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z){}

Vec3 Vec3::operator + (Vec3 vec)
{
    return Vec3(x + vec.x, y + vec.y, z + vec.z);
}
Vec3 Vec3::operator - (Vec3 vec)
{
    return Vec3(x - vec.x, y - vec.y, z - vec.z);
}
Vec3 Vec3::operator * (float num)
{
    return Vec3(x * num, y * num, z * num);
}
Vec3 Vec3::operator / (float num)
{
    return Vec3(x / num, y / num, z / num);
}
bool Vec3::operator == (Vec3 vec)
{
    if (x != vec.x || y != vec.y || z != vec.z)
    {
        return false;
    }
    return true;
}

void Vec3::rotateX(float deg)
{
    glm::vec3 glmVec = glm::vec3(x, y, z);
    glmVec = glm::rotateX(glmVec, deg);
    x = glmVec.x;
    y = glmVec.y;
    z = glmVec.z;
}

void Vec3::rotateY(float deg)
{
    glm::vec3 glmVec = glm::vec3(x, y, z);
    glmVec = glm::rotateY(glmVec, deg);
    x = glmVec.x;
    y = glmVec.y;
    z = glmVec.z;
}

Vec3 cross(Vec3 vec_a, Vec3 vec_b)
{
    glm::vec3 glmVec_a = toGlmVec3(vec_a);
    glm::vec3 glmVec_b = toGlmVec3(vec_b);
    return toVec3(glm::cross(glmVec_a, glmVec_b));
}

float dot(Vec3 vec_a, Vec3 vec_b)
{
    return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
}

float distance(Vec3 pos1, Vec3 pos2)
{
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
}

glm::vec3 toGlmVec3(Vec3 vec)
{
    return glm::vec3(vec.x, vec.y, vec.z);
}

Vec3 toVec3(glm::vec3 vec)
{
    Vec3 returnVec = {vec.x, vec.y, vec.z};
    return returnVec;
}

Vec3 toVec3(Pos pos)
{
    return Vec3((float)pos.x, (float)pos.y, (float)pos.z);
}