#include "VoxelRenderer.h"

#define VERTEX_SIZE (3 + 2 + 1)

#define IS_IN(X, Y, Z) ((X) >= 0 && (X) < CHUNK_W && (Y) >= 0 && (Y) < CHUNK_H && (Z) >= 0 && (Z) < CHUNK_D)
#define VOXEL(X, Y, Z) (chunk->voxels[((Y)*CHUNK_D + (Z)) * CHUNK_W + (X)])
#define IS_BLOCKED(X, Y, Z) ((IS_IN(X, Y, Z)) && VOXEL(X, Y, Z).id)

#define VERTEX(INDEX, X, Y, Z, U, V, L) \
    buffer[INDEX + 0] = (X);            \
    buffer[INDEX + 1] = (Y);            \
    buffer[INDEX + 2] = (Z);            \
    buffer[INDEX + 3] = (U);            \
    buffer[INDEX + 4] = (V);            \
    buffer[INDEX + 5] = (L);            \
    INDEX += VERTEX_SIZE;

VoxelRenderer::VoxelRenderer(int capacity)
{
    buffer = new GLfloat[capacity * VERTEX_SIZE * 6];
}

VoxelRenderer::~VoxelRenderer()
{
    delete[] buffer;
}

void VoxelRenderer::GetUV(float &u, float &v, const int id)
{
    u = (id % 16) * uvsize;
    v = 1 - ((1 + id / 16) * uvsize);
}

Mesh *VoxelRenderer::render(Chunk *chunk)
{
    int chunk_attrs[] = {3, 2, 1, 0};

    int index = 0;

    float l, u, v;

    for (int y = 0; y < CHUNK_H; y++)
    {
        for (int z = 0; z < CHUNK_D; z++)
        {
            for (int x = 0; x < CHUNK_W; x++)
            {
                Voxel vox = chunk->voxels[(y * CHUNK_D + z) * CHUNK_W + x];
                unsigned int id = vox.id;

                if (!id)
                {
                    continue;
                }

                GetUV(u, v, id);

                if (!IS_BLOCKED(x, y + 1, z))
                {
                    l = 1.0f;
                    VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
                    VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

                    VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v, l);
                }
                if (!IS_BLOCKED(x, y - 1, z))
                {
                    l = 0.65f;
                    VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
                    VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
                    VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvsize, l);

                    VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
                    VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
                    VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
                }

                if (!IS_BLOCKED(x + 1, y, z))
                {
                    l = 0.85f;
                    VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

                    VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
                    VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v, l);
                }
                if (!IS_BLOCKED(x - 1, y, z))
                {
                    l = 0.85f;
                    VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
                    VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
                    VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

                    VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
                    VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
                    VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
                }

                if (!IS_BLOCKED(x, y, z + 1))
                {
                    l = 0.8f;
                    VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
                    VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

                    VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
                    VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
                }
                if (!IS_BLOCKED(x, y, z - 1))
                {
                    l = 0.8f;
                    VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
                    VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

                    VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
                    VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
                    VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u, v, l);
                }
            }
        }
    }

    return new Mesh(buffer, chunk_attrs, index / VERTEX_SIZE);
}

Mesh *VoxelRenderer::render(glm::vec3 *voxelsPosition, int *voxelsID, int amountVoxels, glm::vec3 diraction)
{
    int chunk_attrs[] = {3, 2, 1, 0};

    int index = 0;

    float l, u, v;

    for (int i = 0; i < amountVoxels; i++)
    {
        unsigned int id = voxelsID[i];

        int x = voxelsPosition[i].x;
        int y = voxelsPosition[i].y;
        int z = voxelsPosition[i].z;

        GetUV(u, v, id);

        l = 1.0f;

        if (diraction.x == -1)
        {
            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v, l);

            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
            VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
        }

        if (diraction.x == 1)
        {
            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);

            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
            VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v, l);
        }

        if (diraction.z == 1)
        {
            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
            VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v, l);

            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v, l);
        }

        if (diraction.z == -1)
        {
            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);

            VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
            VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v, l);
            VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
        }

        if (id == 4)
        {
            id = 3;
            GetUV(u, v, id);
        }

        l = 0.65f;
        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v + uvsize, l);
        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);

        l = 0.85f;
        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v, l);

        l = 0.85f;
        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);

        l = 0.8f;
        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);

        l = 0.8f;
        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u, v, l);
    }

    return new Mesh(buffer, chunk_attrs, index / VERTEX_SIZE);
}

Mesh *VoxelRenderer::render(glm::vec3 *voxelsPosition, int voxelsID, int amountVoxels)
{
    int chunk_attrs[] = {3, 2, 1, 0};

    int index = 0;

    float l, u, v;

    for (int i = 0; i < amountVoxels; i++)
    {
        unsigned int id = voxelsID;

        int x = voxelsPosition[i].x;
        int y = voxelsPosition[i].y;
        int z = voxelsPosition[i].z;

        GetUV(u, v, id);

        l = 1.0f;
        VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v, l);

        VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

        l = 0.65f;
        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v + uvsize, l);
        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);

        l = 0.75f;
        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v, l);

        l = 0.75f;
        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);

        l = 0.7f;
        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);

        l = 0.7f;
        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

        VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
        VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
        VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u, v, l);
    }

    return new Mesh(buffer, chunk_attrs, index / VERTEX_SIZE);
}