#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "chunk.hpp"
#include "../graphics/shader.hpp"

#include <unordered_map>

#define WORLD_SIZE_X 20
#define WORLD_SIZE_Y 8
#define WORLD_SIZE_Z 20

class World
{
public:
	std::unordered_map<glm::ivec3, Chunk> chunks; // chunk pos is in ivec3 (x, y, z)

	World();
	
	Chunk* getChunk(int x, int y, int z);
	Chunk* getChunk(const glm::ivec3& pos);

	Block* getBlock(int x, int y, int z);
	Block* getBlock(const glm::ivec3& pos);

private:
	void gen();
};