#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include "glm/glm.hpp"
using namespace glm;

class Camera
{
    void updateVectors();

public:
    Camera(vec3 position, float fov);

    void Rotate(float x, float y, float z);

    mat4 GetProjection();
    mat4 GetView();

    vec3 position;

    vec3 front;
    vec3 up;
    vec3 right;

private:
    float fov;

    mat4 rotation;
};

#endif