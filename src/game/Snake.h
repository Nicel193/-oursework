#ifndef SNAKE_H
#define SNAKE_H

#pragma once

#include "../graphics/voxel/VoxelRenderer.h"
#include "FoodSnake.h"
#include "GameStatistic.h"

#include "glm/glm.hpp"
using namespace glm;

class Snake
{
public:
    Snake();
    ~Snake();

    void MoveSnake(Chunk *chunk, vec3 moveVector, FoodSnake *food);

    float GetSpeedSnake();

    vec3 *GetSnakePosition();

    Mesh *mesh;

private:
    int lengthSnake;
    float speedSnake;

    VoxelRenderer renderer = VoxelRenderer(32 * 32 * 32);

    vec3 *snakePosition = new vec3[32 * 32];
    int *voxelsID = new int[32 * 32];

    vec3 moveVector;

    void PositionControl(Chunk *chunk, vec3 &moveVector, bool &canMoveForward);
    void Clash();
};

#endif