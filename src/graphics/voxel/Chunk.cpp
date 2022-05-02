#include "Chunk.h"
#include <math.h>
#include <glm/gtc/noise.hpp>

Chunk::Chunk()
{
    this->voxels = new Voxel[CHUNK_VOL];

    for (int y = 0; y < CHUNK_H; y++)
    {
        for (int x = 0; x < CHUNK_W; x++)
        {
            for (int z = 0; z < CHUNK_D; z++)
            {
                float height = glm::perlin(glm::vec3(x * 0.2f, y * 0.2f, z * 0.2f));

                int id = 0, newY = (y + height * 3);

                if (newY <= 6)
                {
                    id = 1;
                }

                if (newY <= 5)
                {
                    int randomRelief = rand() % 100;

                    if (randomRelief <= 80)
                    {
                        id = 2;
                    }
                    else
                    {
                        id = 6;
                    }
                }

                if (newY <= 4)
                {
                    id = 6;
                }

                voxels[(y * CHUNK_D + z) * CHUNK_W + x].id = id;
            }
        }
    }
}

Chunk::~Chunk()
{
    delete[] this->voxels;
}