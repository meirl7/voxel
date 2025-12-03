#pragma once

#include "mesh.hpp"
#include "../game/world.hpp"
#include <vector>

class Render
{
public:
	Render();
	Mesh* createMesh(Chunk* chunk, Chunk* left, Chunk* right, Chunk* front, Chunk* back, Chunk* top, Chunk* bottom);
	void drawWorld(Shader& shader, World& world);
private:
	std::vector<float> buffer;

};