#include <iostream>

#include "window/Events.h"
#include "window/Camera.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/voxel/VoxelRenderer.h"
#include "graphics/Mesh.h"
#include "loaders/Load.h"

#include "game/Snake.h"

#include <glm/ext/matrix_transform.hpp>

#include <time.h>

void Input(float delta, Camera *camera, vec3 *moveVector);

int g_windowSizeX = 1280;
int g_windowSizeY = 720;

float speed = 10.0f;

float lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}

int main()
{
	srand(time(NULL));

	Window::Initialization("Engine", g_windowSizeX, g_windowSizeY);
	Events::Initialization();

	Shader *shader = load_shader("res/main.glslv", "res/main.glslf");
	if (shader == nullptr)
	{
		std::cerr << "failed to load shader" << std::endl;
		Window::terminate();
		return 1;
	}

	Texture *texture = load_texture("E:\\Projects\\C++\\Coursework\\res\\textures\\TextureAtlas.png");
	if (texture == nullptr)
	{
		std::cerr << "failed to load texture" << std::endl;
		delete shader;
		Window::terminate();
		return 1;
	}

	Texture *textureText = load_texture("E:\\Projects\\C++\\Coursework\\res\\textures\\Verdana.png");
	if (texture == nullptr)
	{
		std::cerr << "failed to load texture" << std::endl;
		delete shader;
		Window::terminate();
		return 1;
	}

	Camera *camera = new Camera(vec3(0, 0, 1), radians(40.0f));

	mat4 matrix(1.0f);
	matrix = glm::translate(matrix, vec3(0.0f, -20.0f, 0.0f));

	camera->Rotate(radians(-70.0f), 0.0f, 0.0f);

	float lastTime = glfwGetTime();
	float delta = 0.0f;
	float Time = 0.0f;

	VoxelRenderer renderer(32 * 32 * 32);
	Chunk *chunk = new Chunk();
	Mesh *mesh = renderer.render(chunk);

	Snake snake;
	vec3 snakeMoveVector = vec3(1, 0, 0);

	FoodSnake food(chunk);

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	while (!Window::isShouldClose())
	{
		float currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;

		Time += (delta * snake.GetSpeedSnake());

		if (Time >= 1.0f)
		{
			snake.MoveSnake(chunk, snakeMoveVector, &food);

			Time = 0;
		}

		camera->position.x = lerp(snake.GetSnakePosition()[1].x, snake.GetSnakePosition()[0].x, Time);
		camera->position.z = lerp(snake.GetSnakePosition()[1].z, snake.GetSnakePosition()[0].z, Time) + 5.0f;

		if (Events::isPressed(GLFW_KEY_W))
		{
			snakeMoveVector = vec3(0, 0, -1);
		}

		if (Events::isPressed(GLFW_KEY_S))
		{
			snakeMoveVector = vec3(0, 0, 1);
		}

		if (Events::isPressed(GLFW_KEY_D))
		{
			snakeMoveVector = vec3(1, 0, 0);
		}

		if (Events::isPressed(GLFW_KEY_A))
		{
			snakeMoveVector = vec3(-1, 0, 0);
		}

		Events::pullEvents();

		Input(delta, camera, &snakeMoveVector);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();
		shader->uniformMatrix("model", matrix);
		shader->uniformMatrix("projview", camera->GetProjection() * camera->GetView());
		texture->bind();
		mesh->Draw(GL_TRIANGLES);
		snake.mesh->Draw(GL_TRIANGLES);
		food.mesh->Draw(GL_TRIANGLES);

		Window::swapBuffers();
	}

	Window::terminate();

	delete shader;
	delete texture;
	delete textureText;
	delete camera;
	delete mesh;

	return 0;
}

void Input(float delta, Camera *camera, vec3 *snakeMoveVector)
{
	if (Events::justPressed(GLFW_KEY_ESCAPE))
	{
		GameStatistic::SaveStatistic();

		Window::setShouldClose(true);
	}

	if (Events::isPressed(GLFW_KEY_E))
	{
		camera->position -= camera->front * (speed + 5) * delta;
	}

	if (Events::isPressed(GLFW_KEY_Q))
	{
		camera->position += camera->front * (speed + 5) * delta;
	}
}