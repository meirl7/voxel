#pragma once

#include <memory>
#include "block.hpp"

const int chunkW = 16;
const int chunkH = 256;
const int chunkVol = 65536;

class Chunk
{
public:
	int x, z;

	Block* blocks;

	Chunk(int x, int z);
	~Chunk();

	//void createMesh(Chunk* left, Chunk* right, Chunk* front, Chunk* back);
	void genChunkBlocks();

	Block* getBlock(int x, int y, int z); // in local coord

};