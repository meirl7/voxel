#pragma once

#include "../mesh.hpp"
#include "../../world/world.hpp"
#include <vector>

class Render
{
public:
	Render();
	Mesh* createMesh(Chunk* chunk, Chunk* left, Chunk* right, Chunk* front, Chunk* back);
	void drawWorld(Shader& shader, World& world);
private:
	std::vector<float> buffer;
	float* newBuffer;
};