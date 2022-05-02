#include "Snake.h"

#include <iostream>

Snake::Snake()
{
    this->lengthSnake = 4;
    this->speedSnake = 1.0f;

    for (int i = 0; i < lengthSnake; i++)
    {
        this->snakePosition[i] = vec3(16, 7, 16);
    }

    for (int i = 1; i < (32 * 32); i++)
    {
        voxelsID[i] = 3;
    }

    voxelsID[0] = 4;

    this->mesh = renderer.render(snakePosition, voxelsID, lengthSnake, vec3(1, 0, 0));
}

Snake::~Snake()
{
    delete this->mesh;
    delete[] this->snakePosition;
    delete[] this->voxelsID;
}

void Snake::PositionControl(Chunk *chunk, vec3 &moveVector, bool &canMoveForward)
{
    canMoveForward = true;

    if (snakePosition[0].x + (int)moveVector.x >= CHUNK_W)
        snakePosition[0].x -= (CHUNK_W);

    if (snakePosition[0].x + (int)moveVector.x < 0)
        snakePosition[0].x += CHUNK_W;

    if (snakePosition[0].z + (int)moveVector.z >= CHUNK_D)
        snakePosition[0].z -= (CHUNK_D);

    if (snakePosition[0].z + (int)moveVector.z < 0)
        snakePosition[0].z += CHUNK_D;

    //----------------------------------------------------------------------------------------

    if (chunk->voxels[(((int)snakePosition[0].y - 1) * CHUNK_D + ((int)snakePosition[0].z + (int)moveVector.z)) * CHUNK_W + ((int)snakePosition[0].x + (int)moveVector.x)].id <= 0)
    {
        moveVector.y -= 1;

        return;
    }

    if (chunk->voxels[(((int)snakePosition[0].y + 1) * CHUNK_D + ((int)snakePosition[0].z + (int)moveVector.z)) * CHUNK_W + ((int)snakePosition[0].x + (int)moveVector.x)].id > 0)
    {
        moveVector.y += 1;

        canMoveForward = false;

        return;
    }

    if (chunk->voxels[(((int)snakePosition[0].y) * CHUNK_D + ((int)snakePosition[0].z + (int)moveVector.z)) * CHUNK_W + ((int)snakePosition[0].x + (int)moveVector.x)].id > 0)
    {
        moveVector.y += 1;
    }
}

void Snake::Clash()
{
    // if (chunk->voxels[(((int)snakePosition[0].y - 1) * CHUNK_D + ((int)snakePosition[0].z + (int)moveVector.z)) * CHUNK_W + ((int)snakePosition[0].x + (int)moveVector.x)].id != 6)
    //     return;

    for (int i = lengthSnake; i > 0; i--)
    {
        if (snakePosition[0].x == snakePosition[i].x && snakePosition[0].y == snakePosition[i].y && snakePosition[0].z == snakePosition[i].z)
        {
            this->speedSnake = 0.0f;

            std::cout << "Вмер";

            return;
        }
    }
}

void Snake::MoveSnake(Chunk *chunk, vec3 moveVector, FoodSnake *food)
{
    if (food->Eat(snakePosition[0]))
    {
        lengthSnake++;

        GameStatistic::GameScore = (lengthSnake - 4);

        GameStatistic::ShowStatistic();
    }

    for (int i = lengthSnake; i > 0; i--)
    {
        snakePosition[i].x = snakePosition[i - 1].x;
        snakePosition[i].y = snakePosition[i - 1].y;
        snakePosition[i].z = snakePosition[i - 1].z;
    }

    bool canMoveForward;
    PositionControl(chunk, moveVector, canMoveForward);

    snakePosition[0].y += moveVector.y;
    if (canMoveForward)
    {
        snakePosition[0].x += moveVector.x;
        snakePosition[0].z += moveVector.z;
    }

    Clash();

    this->mesh = renderer.render(snakePosition, voxelsID, lengthSnake, moveVector);
}

float Snake::GetSpeedSnake()
{
    return this->speedSnake;
}

vec3 *Snake::GetSnakePosition()
{
    return this->snakePosition;
}