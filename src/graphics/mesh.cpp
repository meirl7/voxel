#include "mesh.hpp"

Mesh::Mesh(float* buffer, size_t verts) : vertices(verts)
{
	const int vertexSize = 6; // x, y, z, u, v, l

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertices, buffer, GL_STATIC_DRAW);

	int offset = 0;
	int attrs[3] = { 3, 2, 1 };

	for (int i = 0; i < 3; i++)
	{
		glVertexAttribPointer(i, attrs[i], GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += attrs[i];
	}

	glBindVertexArray(0);
}
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices);
	glBindVertexArray(0);
}