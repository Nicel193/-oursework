#ifndef SCENE_H
#define SCENE_H

#pragma once

#include "../window/Events.h"
#include "../window/Camera.h"
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../graphics/voxel/VoxelRenderer.h"
#include "../graphics/Mesh.h"
#include "../loaders/Load.h"

#include "../game/Snake.h"

#include "Time.h"

#include <glm/ext/matrix_transform.hpp>

class Scene
{
public:
    virtual void Start();
    virtual void Update();
    virtual void End();

protected:
    Mesh *mesh;
    Shader *shader;
    Texture *texture;
};

class SnakeScene : public Scene
{
public:
    void Start() override;
    void Update() override;
    void End() override;

private:
    float lerp(float a, float b, float f);
    void Input(float delta);

    float Time = 0.0f;

    float cameraSpeed = 10.0f;

    bool isLastFrame = false;

    Chunk *chunk = new Chunk();

    Camera *camera;
    Snake snake;
    FoodSnake food;

    mat4 matrix;

    vec3 snakeMoveVector = vec3(1, 0, 0);
};

class LogoScene : public Scene
{
public:
    void Start() override;
    void Update() override;
    void End() override;

private:
    float sceneEndTime = 2.5f;
    float time = 0.0f;

    float logoSize = 0.15f;
};
#endif