#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
	Mesh(std::vector<float>& buffer, size_t vertices, const int* attrs);
	~Mesh();

	void draw() const;
private:
	unsigned int VAO;
	unsigned int VBO;
	size_t vertices;
};