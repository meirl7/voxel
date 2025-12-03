#include "chunk.hpp"
#include <cmath>

#include "../utils/perlinNoise.hpp"

Chunk::Chunk()
{
	blocks.resize(CHUNK_VOL);
}

Chunk::~Chunk()
{
	delete mesh;
}

/*
global coords:
	gx = x + xp * CHUNK_W
	gy = y + yp * CHUNK_H
	gz = z + zp * CHUNK_W
here gx - global coord
x - local chunk coord
xp - global chunk coord
*/

void Chunk::genChunkBlocks()
{
	int i = 0;
	for (int z = 0; z < CHUNK_W; z++)
	{
		for (int x = 0; x < CHUNK_W; x++)
		{
			float h = heightNoise(float(x + (xp * CHUNK_W)), float(z + (zp * CHUNK_W))) * 30.f;

			for (int y = 0; y < CHUNK_H; y++)
			{
				if (y + (yp * CHUNK_W) <= h)
				{
					i = 1;
				}
				blocks[(y * CHUNK_W + z) * CHUNK_W + x].id = i;
				i = 0;
			}
		}
	}
}