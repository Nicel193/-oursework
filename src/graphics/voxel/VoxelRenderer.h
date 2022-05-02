#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#pragma once

#include <glad/glad.h>
#include "../Mesh.h"
#include "Chunk.h"

#include "glm/glm.hpp"

class VoxelRenderer
{
public:
    VoxelRenderer(int capacity);
    ~VoxelRenderer();

    Mesh *render(Chunk *chunk);
    Mesh *render(glm::vec3 *voxelsPosition, int *voxelsID, int sizeArray, glm::vec3 diraction);
    Mesh *render(glm::vec3 *voxelsPosition, int voxelsID, int amountVoxels);

private:
    GLfloat *buffer;
    int capacity;

    void GetUV(float &u, float &v, const int id);

    float uvsize = (1.0f / 16.0f);
};

#endif