#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
	Mesh(float* buffer, size_t verts);

	~Mesh();

	void draw() const;
private:
	unsigned int VAO;
	unsigned int VBO;
	size_t vertices;
};