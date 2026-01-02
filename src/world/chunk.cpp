#include "chunk.hpp"

#include <cmath>

#include "block.hpp"
#include "../graphics/mesh.hpp"
#include "../utils/perlinNoise.hpp"


#define isBlockInChunk(x, y, z) ((x < chunkW) && (y < chunkH) && (z < chunkW))
#define getBlock(x, y, z) (blocks[((y)*chunkW + (z)) * chunkW + (x)])
#define isItBlocked(x, y, z) (isBlockInChunk(x, y, z) && (getBlock(x, y, z).id != 0))
#define addVertex(x, y, z, u, v, l) buffer[size] = x;\
									buffer[size + 1] = y;\
									buffer[size + 2] = z;\
									buffer[size + 3] = u;\
									buffer[size + 4] = v;\
									buffer[size + 5] = l;\
									size += 6


Chunk::Chunk(int x, int z) : x(x), z(z)
{
	blocks = new Block[chunkVol];
}

Chunk::~Chunk()
{
	delete[] blocks;
	delete mesh;
}

void Chunk::createMesh(Chunk* left, Chunk* right, Chunk* front, Chunk* back)
{
	float* buffer = new float[chunkVol];
	size_t size = 0;

	float u;
	float v;
	float uvSize = 1.f / 32.f;

	bool blocked = false;

	float light;

	u = (1 % 16) * uvSize;
	v = 1 - ((1 + 1.f / 16) * uvSize);

	for (int y = 0; y < chunkH; y++)
	{
		for (int z = 0; z < chunkW; z++)
		{
			for (int x = 0; x < chunkW; x++)
			{
				int index = (y * chunkW + z) * chunkW + x;

				if (!blocks[index].id) continue;

				if (y + 1 < chunkH)
				{
					blocked = isItBlocked(x, y + 1, z);
				}
				if (!blocked)
				{
					light = 1.0f;

					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v, light);
				}
				blocked = false;


				if (y - 1 >= 0)
				{
					blocked = isItBlocked(x, y - 1, z);
				}
				if (!blocked)
				{
					light = 0.75f;

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
				}
				blocked = false;


				if (x - 1 >= 0)
				{
					blocked = isItBlocked(x - 1, y, z);
				}
				else if (left)
				{
					blocked = left->blocks[(y * chunkW + z) * chunkW + 15].id != 0;
				}
				if (!blocked)
				{
					light = 0.85f;

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
				}
				blocked = false;


				if (x + 1 < chunkW)
				{
					blocked = isItBlocked(x + 1, y, z);
				}
				else if (right) {
					blocked = right->blocks[(y * chunkW + z) * chunkW].id != 0;
				}
				if (!blocked)
				{
					light = 0.95f;

					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u, v, light);
				}
				blocked = false;


				if (z + 1 < chunkW)
				{
					blocked = isItBlocked(x, y, z + 1);
				}
				else if (front)
				{
					blocked = front->blocks[(y * chunkW * chunkW + x)].id != 0;
				}
				if (!blocked)
				{
					light = 0.9f;
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
				}
				blocked = false;


				if (z - 1 >= 0)
				{
					blocked = isItBlocked(x, y, z - 1);
				}
				else if (back)
				{
					blocked = back->blocks[(y * chunkW + 15) * chunkW + x].id != 0;
				}
				if (!blocked) {
					light = 0.8f;

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);
					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u, v, light);
				}
				blocked = false;
			}
		}
	}

	mesh = new Mesh(buffer, size);
	delete[] buffer;
}