#include "world.hpp"

World::World()
{
	for (int dx = 0; dx < WORLD_SIZE_X; ++dx)
	{
		for (int dz = 0; dz < WORLD_SIZE_Z; ++dz)
		{
			glm::ivec2 xz(dx, dz);
			if (!chunks.contains(xz))
			{
				chunks[xz] = new Chunk(xz.x, xz.y);
				chunks[xz]->genChunkBlocks();
			}
		}
	}
	gen();
}

World::~World()
{
	for (auto& ch : chunks)
	{
		delete ch.second;
	}
}

void World::genMesh(const glm::ivec2& p)
{

}


void World::gen()
{
	for (auto& p : chunks)
	{
		Chunk* ch = p.second;
        if (ch != nullptr && ch->isEdited)
		{
			int x = ch->x, z = ch->z;

			Chunk* left = chunks[glm::ivec2(x - 1, z)];
			Chunk* right = chunks[glm::ivec2(x + 1, z)];
			Chunk* front = chunks[glm::ivec2(x, z + 1)];
			Chunk* back = chunks[glm::ivec2(x, z - 1)];

			ch->createMesh(left, right, front, back);
			ch->isEdited = false;
		}
	}
}

Chunk* World::getChunk(int x, int z)
{
	glm::ivec2 c(x, z);
	if (chunks.contains(c))
	{
		return chunks[c];
	}
	return nullptr;
}

Block* World::getBlock(int x, int y, int z)
{
	int dx = x / chunkW;
	int dz = z / chunkW;
	if (x < 0) dx--;
	if (z < 0) dz--;
	glm::ivec2 c(dx, dz);
	if (chunks.contains(c))
	{
		return &chunks[c]->blocks[((y)*chunkW + (z - dz * chunkW)) * chunkW + (x - dx * chunkW)];
	}
	return nullptr;
}

Block* World::raycast(glm::vec3 a, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend)
{
	float px = a.x;
	float py = a.y;
	float pz = a.z;

	float dx = dir.x;
	float dy = dir.y;
	float dz = dir.z;

	float t = 0.0f;
	int ix = floor(px);
	int iy = floor(py);
	int iz = floor(pz);

	float stepx = (dx > 0.0f) ? 1.0f : -1.0f;
	float stepy = (dy > 0.0f) ? 1.0f : -1.0f;
	float stepz = (dz > 0.0f) ? 1.0f : -1.0f;

	constexpr float infinity = std::numeric_limits<float>::infinity();

	float txDelta = (dx == 0.0f) ? infinity : abs(1.0f / dx);
	float tyDelta = (dy == 0.0f) ? infinity : abs(1.0f / dy);
	float tzDelta = (dz == 0.0f) ? infinity : abs(1.0f / dz);

	float xdist = (stepx > 0) ? (ix + 1 - px) : (px - ix);
	float ydist = (stepy > 0) ? (iy + 1 - py) : (py - iy);
	float zdist = (stepz > 0) ? (iz + 1 - pz) : (pz - iz);

	float txMax = (txDelta < infinity) ? txDelta * xdist : infinity;
	float tyMax = (tyDelta < infinity) ? tyDelta * ydist : infinity;
	float tzMax = (tzDelta < infinity) ? tzDelta * zdist : infinity;

	int steppedIndex = -1;

	while (t <= maxDist) {
		Block* voxel = getBlock(ix, iy, iz);
		if (voxel == nullptr || getBlock(ix, iy, iz)->id) {
			end.x = px + t * dx;
			end.y = py + t * dy;
			end.z = pz + t * dz;

			iend.x = ix;
			iend.y = iy;
			iend.z = iz;

			norm.x = norm.y = norm.z = 0.0f;
			if (steppedIndex == 0) norm.x = -stepx;
			if (steppedIndex == 1) norm.y = -stepy;
			if (steppedIndex == 2) norm.z = -stepz;
			return voxel;
		}
		if (txMax < tyMax) {
			if (txMax < tzMax) {
				ix += stepx;
				t = txMax;
				txMax += txDelta;
				steppedIndex = 0;
			}
			else {
				iz += stepz;
				t = tzMax;
				tzMax += tzDelta;
				steppedIndex = 2;
			}
		}
		else {
			if (tyMax < tzMax) {
				iy += stepy;
				t = tyMax;
				tyMax += tyDelta;
				steppedIndex = 1;
			}
			else {
				iz += stepz;
				t = tzMax;
				tzMax += tzDelta;
				steppedIndex = 2;
			}
		}
	}
	iend.x = ix;
	iend.y = iy;
	iend.z = iz;

	end.x = px + t * dx;
	end.y = py + t * dy;
	end.z = pz + t * dz;
	norm.x = norm.y = norm.z = 0.0f;
	return nullptr;
}
