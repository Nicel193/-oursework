#ifndef MESH_H
#define MESH_H

#pragma once

#include <glad/glad.h>

class Mesh
{
public:
    Mesh(const GLfloat *buffer, const int *attributes, int vertices);
    ~Mesh();

    void Draw(unsigned int primitive);
    void Delete(); 

private:
    GLuint VBO, VAO;
    int vertices;
};

#endif