#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "chunk.hpp"
#include "../graphics/shader.hpp"

#include <unordered_map>
#include <memory>

#define WORLD_SIZE_X 5
#define WORLD_SIZE_Z 5

// (x, z)

class World
{
public:
	std::unordered_map<glm::ivec2, std::unique_ptr<Chunk>> chunks; // chunk pos is in ivec2 (x, z)

	World();
	
	Chunk* getChunk(int x, int z);
	Chunk* getChunk(const glm::ivec2& pos);

	Block* getBlock(int x, int y, int z);
	Block* getBlock(const glm::ivec3& pos);

private:
	void gen();
};