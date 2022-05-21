#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#pragma once

#include "Scene.h"

#define AmountScenes 2

class SceneManager
{
public:
    static void NextScene(int nextSceneID);
    static void EndGame();
    static void Initialization(Scene *allScenes[AmountScenes]);

    static Scene *scenes[AmountScenes];

    static int currentScene;

private:
};

#endif