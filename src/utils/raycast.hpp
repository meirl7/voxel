#pragma once
#include <glm/vec3.hpp>
#include "../game/world.hpp"

struct RaycastHit
{
	int x, y, z;
	bool hit;
};

inline static bool checkBlockIsAir(int x, int y, int z, World& world)
{
	int chx = x / 16;
	int chy = y / 16;
	int chz = z / 16;

	if (x < 0)
		chx--;
	if (y < 0)
		chy--;
	if (z < 0)
		chz--;

	return world.getBlock(x, y, z);
}

RaycastHit raycast(glm::vec3& pos, glm::vec3& dir, float maxDist)
{
	int x = floor(pos.x);
	int y = floor(pos.y);
	int z = floor(pos.z);

	int stepX = (dir.x > 0) ? 1 : -1;
	int stepY = (dir.y > 0) ? 1 : -1;
	int stepZ = (dir.z > 0) ? 1 : -1;

	float tMaxX = ((x + (dir.x > 0)) - pos.x) / dir.x;
	float tMaxY = ((y + (dir.y > 0)) - pos.y) / dir.y;
	float tMaxZ = ((z + (dir.z > 0)) - pos.z) / dir.z;

	float dist = 0.0f;

	while (dist <= maxDist)
	{

	}
}