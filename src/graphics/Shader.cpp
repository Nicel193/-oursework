#include "Shader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(unsigned int id) : id(id)
{
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::uniformMatrix(std::string name, glm::mat4 matrix)
{
	GLuint transformLoc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

const char *vertex_shader1 =
	"#version 330 core\n"
	"layout (location = 0) in vec3 v_position;"
	"layout (location = 1) in vec2 v_texCoord;"
	"layout (location = 2) in float v_light;"
	"out vec4 a_color; out vec2 a_texCoord; uniform mat4 model; uniform mat4 projview;"
	"void main(){"
	"a_color = vec4(v_light,v_light,v_light,1.0f); a_texCoord = v_texCoord;"
	"gl_Position = projview * model * vec4(v_position, 1.0);}";

const char *vertex_shader2 =
	"#version 330 core\n"
	"layout (location = 0) in vec3 v_position;"
	"layout (location = 1) in vec2 v_texCoord;"
	"out vec4 a_color; out vec2 a_texCoord; uniform mat4 model;"
	"void main(){"
	"a_color = vec4(1.0f,1.0f,1.0f,1.0f); a_texCoord = v_texCoord;"
	"gl_Position = model * vec4(v_position, 1.0);}";

const char *fragment_shader =
	"#version 330 core\n"
	"in vec4 a_color;"
	"in vec2 a_texCoord;"
	"out vec4 f_color;"
	"uniform sampler2D u_texture0;"
	"void main(){"
	"f_color = a_color * texture(u_texture0, a_texCoord);}";

Shader *load_shader(int idVertexShader)
{
	const char *vertexShader = (idVertexShader == 1 ? vertex_shader1 : vertex_shader2);

	GLint success;
	GLchar infoLog[512];

	//------------------------------------------------------------------

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShader, nullptr);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, nullptr, infoLog);
		std::cerr << "SHADER::VERTEX: compilation failed" << std::endl;
		std::cerr << infoLog << std::endl;
		return nullptr;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, nullptr, infoLog);
		std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
		std::cerr << infoLog << std::endl;
		return nullptr;
	}

	GLuint id = glCreateProgram();
	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cerr << "SHADER::PROGRAM: linking failed" << std::endl;
		std::cerr << infoLog << std::endl;

		glDeleteShader(vs);
		glDeleteShader(fs);
		return nullptr;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return new Shader(id);
}
