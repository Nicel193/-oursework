#include "Scene.h"
#include "SceneManager.h"

void Scene::Start()
{
}

void Scene::Update()
{
}

void Scene::End()
{
    delete shader;
    delete texture;
    delete mesh;
}

//--------------------------------------------------------------------------------------------------------------

float SnakeScene::lerp(float a, float b, float f)
{
    return (a * (1.0 - f)) + (b * f);
}

void SnakeScene::Start()
{
    shader = load_shader(1);
    if (shader == nullptr)
    {
        std::cerr << "failed to load shader" << std::endl;
        Window::terminate();
        return;
    }

    texture = load_texture("E:\\Projects\\C++\\Coursework\\res\\textures\\TextureAtlas.png");
    if (texture == nullptr)
    {
        std::cerr << "failed to load texture" << std::endl;
        delete shader;
        Window::terminate();
        return;
    }

    camera = new Camera(vec3(0, 0, 1), radians(40.0f));

    this->matrix = glm::translate(mat4(1.0f), vec3(0.0f, -20.0f, 0.0f));

    camera->Rotate(radians(-70.0f), 0.0f, 0.0f);

    VoxelRenderer renderer(32 * 32 * 32);
    mesh = renderer.render(chunk);

    this->food.GenerateMesh(chunk);

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void SnakeScene::Update()
{
    Time += (Time::GetDelta() * snake.GetSpeedSnake());

    if (Time >= 1.0f)
    {
        snake.MoveSnake(chunk, snakeMoveVector, &food);

        Time = 0;
    }

    camera->position.x = lerp(snake.GetSnakePosition()[1].x, snake.GetSnakePosition()[0].x, Time);
    camera->position.z = lerp(snake.GetSnakePosition()[1].z, snake.GetSnakePosition()[0].z, Time) + 5.0f;

    Input(Time::GetDelta());

    if (isLastFrame)
    {
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->uniformMatrix("model", matrix);
    shader->uniformMatrix("projview", camera->GetProjection() * camera->GetView());
    texture->bind();
    mesh->Draw(GL_TRIANGLES);
    snake.mesh->Draw(GL_TRIANGLES);
    food.mesh->Draw(GL_TRIANGLES);
}

void SnakeScene::End()
{
    delete camera;
}

void SnakeScene::Input(float delta)
{
    if (Events::justPressed(GLFW_KEY_ESCAPE))
    {
        GameStatistic::SaveStatistic();
        SceneManager::EndGame();
        Window::setShouldClose(true);

        isLastFrame = true;
    }

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

    if (Events::isPressed(GLFW_KEY_E))
    {
        camera->position -= camera->front * (cameraSpeed + 5) * delta;
    }

    if (Events::isPressed(GLFW_KEY_Q))
    {
        camera->position += camera->front * (cameraSpeed + 5) * delta;
    }
}

//--------------------------------------------------------------------------------------------------------------

float vertices[] = {
    // x    y     z     u     v
    -1.0f,
    -1.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    -1.0f,
    0.0f,
    1.0f,
    0.0f,
    -1.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,

    1.0f,
    -1.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
    -1.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
};

int attrs[] = {3, 2, 0};

void LogoScene::Start()
{
    shader = load_shader(2);
    if (shader == nullptr)
    {
        std::cerr << "failed to load shader" << std::endl;
        Window::terminate();
        return;
    }

    texture = load_texture("E:\\Projects\\C++\\Coursework\\res\\textures\\NGameLogo.png");
    if (texture == nullptr)
    {
        std::cerr << "failed to load texture" << std::endl;
        delete shader;
        Window::terminate();
        return;
    }

    mesh = new Mesh(vertices, attrs, 6);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void LogoScene::Update()
{
    time += Time::GetDelta();

    if (time >= sceneEndTime)
    {
        SceneManager::NextScene(1);
        return;
    }

    logoSize += 0.01f * Time::GetDelta();

    mat4 matrix = glm::scale(mat4(1.0f), vec3(logoSize, logoSize, 1.0f));

    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    shader->uniformMatrix("model", matrix);
    texture->bind();
    mesh->Draw(GL_TRIANGLES);
}

void LogoScene::End()
{
}
