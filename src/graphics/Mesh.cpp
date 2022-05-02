#include "Mesh.h"

Mesh::Mesh(const GLfloat *buffer, const int *attributes, int vertices) : vertices(vertices)
{
    int vertex_size = 0;

    for (int i = 0; attributes[i]; i++)
    {
        vertex_size += attributes[i];
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

    // attributes
    int offset = 0;
    for (int i = 0; attributes[i]; i++)
    {
        int size = attributes[i];
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(int), (GLvoid *)(offset * sizeof(int)));
        glEnableVertexAttribArray(i);
        offset += size;
    }

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::Draw(unsigned int primitive)
{
    glBindVertexArray(VAO);
    glDrawArrays(primitive, 0, vertices);
    glBindVertexArray(0);
}

void Mesh::Delete()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}