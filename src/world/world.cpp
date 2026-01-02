#include "world.hpp"

World::World()
{
	gen();
}


void World::gen()
{
	for (int dx = 0; dx < WORLD_SIZE_X; ++dx)
	{
		for (int dz = 0; dz < WORLD_SIZE_Z; ++dz)
		{
			glm::ivec2 xz(dx, dz);
			if (!chunks.contains(xz))
			{
				chunks[xz] = std::make_unique<Chunk>(xz.x, xz.y);
				chunks[xz]->genChunkBlocks();
			}
		}
	}
}

Chunk* World::getChunk(int x, int z)
{
	glm::ivec2 c(x, z);
	if (chunks.contains(c))
	{
		return chunks[c].get();
	}
	return nullptr;
}

Chunk* World::getChunk(const glm::ivec2& pos)
{
	if (chunks.contains(pos))
	{
		return chunks[pos].get();
	}
	return nullptr;
}

Block* World::getBlock(int x, int y, int z)
{
	int dx = x / 16;
	int dy = y / 16;
	int dz = z / 16;

	if (x < 0)
		dx--;
	if (y < 0)
		dy--;
	if (z < 0)
		dz--;

	return nullptr;
}

Block* World::getBlock(const glm::ivec3& pos)
{
	int dx = pos.x / 16;
	int dy = pos.y / 16;
	int dz = pos.z / 16;

	if (pos.x < 0)
		dx--;
	if (pos.y < 0)
		dy--;
	if (pos.z < 0)
		dz--;

	return nullptr;
}


