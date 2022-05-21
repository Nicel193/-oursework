#include <iostream>

#include "window/Events.h"
#include "window/Camera.h"

#include "scene/Scene.h"
#include "scene/SceneManager.h"

int windowSizeX = 1280;
int windowSizeY = 720;

int main()
{
	srand(time(NULL));

	Window::Initialization("CubeSnake", windowSizeX, windowSizeY);
	Events::Initialization();
	Time::Initialization();

	Scene *scenes[AmountScenes] = {new LogoScene, new SnakeScene};
	SceneManager::Initialization(scenes);

	SceneManager::scenes[SceneManager::currentScene]->Start();

	while (!Window::isShouldClose())
	{
		Time::Update();
		
		SceneManager::scenes[SceneManager::currentScene]->Update();

		Events::pullEvents();

		Window::swapBuffers();
	}

	Window::terminate();

	return 0;
}