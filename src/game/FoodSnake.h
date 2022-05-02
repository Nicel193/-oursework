#ifndef FOODSNAKE_H
#define FOODSNAKE_H

#pragma once

#include "../graphics/voxel/VoxelRenderer.h"

#include "glm/glm.hpp"
using namespace glm;

class FoodSnake
{
public:
    FoodSnake(Chunk *chunk);
    ~FoodSnake();

    bool Eat(vec3 foodPos);

    Mesh *mesh;

private:
    VoxelRenderer renderer = VoxelRenderer(20 * 6);

    vec3 *foodPositions = new vec3[20];

    Chunk *chunk;

    void FindFoodPosition(int index, int count);
};

#endif