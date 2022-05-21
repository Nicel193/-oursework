#include "FoodSnake.h"

#include <time.h>

void FoodSnake::SetFoodPosition(int index, int count)
{
    for (int y = 6; y < CHUNK_H; y++)
    {
        for (int x = 0; x < CHUNK_W; x++)
        {
            for (int z = 0; z < CHUNK_D; z++)
            {
                int randomPosition = rand() % 100;

                if (index >= count)
                    return;

                if (chunk->voxels[((y + 1) * CHUNK_D + z) * CHUNK_W + x].id == 0 &&
                    chunk->voxels[(y * CHUNK_D + z) * CHUNK_W + x].id != 0 && randomPosition >= 98)
                {
                    this->foodPositions[index++] = vec3(x, y + 1, z);
                }
            }
        }
    }
}

FoodSnake::FoodSnake()
{

}

void FoodSnake::GenerateMesh(Chunk *chunk)
{
    this->chunk = chunk;

    SetFoodPosition(0, 20);

    this->mesh = this->renderer.render(foodPositions, 5, 20);
}

FoodSnake::~FoodSnake()
{
    delete mesh;
}

bool FoodSnake::Eat(vec3 snakePosition)
{
    bool isEat = false;

    srand(time(NULL));

    for (int i = 0; i < 20; i++)
    {
        if (this->foodPositions[i].x == snakePosition.x && this->foodPositions[i].y == snakePosition.y && this->foodPositions[i].z == snakePosition.z)
        {
            isEat = true;
            SetFoodPosition(i, i + 1);
        }
    }

    this->mesh = this->renderer.render(foodPositions, 5, 20);

    return isEat;
}
