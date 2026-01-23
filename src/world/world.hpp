#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "chunk.hpp"
#include "../graphics/shader.hpp"

#include <unordered_map>
#include <memory>

#define WORLD_SIZE_X 5
#define WORLD_SIZE_Z 5

class World
{
public:
	std::unordered_map<glm::ivec2, Chunk*> chunks;
	std::unordered_map<glm::ivec2, Mesh*> meshes;

	World();
	~World();

	void genMesh(const glm::ivec2& p);
	
	Chunk* getChunk(int x, int z);
	Block* getBlock(int x, int y, int z);

	Block* raycast(glm::vec3 a, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend);
private:
	void gen();
};