#pragma once

#include "../graphics/mesh.hpp"
#include "block.hpp"

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_VOL CHUNK_W * CHUNK_W * CHUNK_H

class Chunk
{
public:
	int xp, yp, zp;

	std::vector<Block> blocks;

	Mesh* mesh; // from bottom to top
	bool isEdited = true; // for gen chunks

	Chunk();
	~Chunk();

	void genChunkBlocks();
};