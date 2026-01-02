#pragma once

#include "../mesh.hpp"
#include "../../world/world.hpp"
#include <vector>

class Render
{
public:
	Render();
	void drawWorld(Shader& shader, World& world);

};