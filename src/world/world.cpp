#include "world.hpp"

World::World()
{
	gen();
}


void World::gen()
{
	for (int dx = 0; dx < WORLD_SIZE_X; ++dx)
	{
		for (int dy = 0; dy < WORLD_SIZE_Y; ++dy)
		{
			for (int dz = 0; dz < WORLD_SIZE_Z; ++dz)
			{
				glm::ivec3 c(dx, dy, dz);
				if (!chunks.contains(c))
				{
					Chunk ch;
					ch.xp = dx;
					ch.yp = dy;
					ch.zp = dz;
					ch.genChunkBlocks();
					chunks[c] = ch;
				}
			}
		}
	}
}

Chunk* World::getChunk(int x, int y, int z)
{
	glm::ivec3 c(x, y, z);
	if (chunks.contains(c))
	{
		return &chunks[c];
	}
	return nullptr;
}

Chunk* World::getChunk(const glm::ivec3& pos)
{
	if (chunks.contains(pos))
	{
		return &chunks[pos];
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

	return &getChunk(dx, dy, dz)->blocks.at((y * CHUNK_W + z) * CHUNK_W + x);
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

	return &getChunk(dx, dy, dz)->blocks.at((pos.y * CHUNK_W + pos.z) * CHUNK_W + pos.x);
}


