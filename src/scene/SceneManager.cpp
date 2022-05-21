#include "SceneManager.h"

Scene *SceneManager::scenes[AmountScenes];

int SceneManager::currentScene = 0;

void SceneManager::NextScene(int nextSceneID)
{
    scenes[currentScene]->End();

    currentScene = nextSceneID;
    scenes[currentScene]->Start();
}

void SceneManager::EndGame()
{
    scenes[currentScene]->End();

    for (int i = 0; i < AmountScenes; i++)
    {
        delete scenes[i];
    }
}

void SceneManager::Initialization(Scene *allScenes[AmountScenes])
{
    for (int i = 0; i < AmountScenes; i++)
    {
        scenes[i] = allScenes[i];
    }
}
