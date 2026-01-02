#pragma once

const int chunkW = 16;
const int chunkH = 256;
const int chunkVol = 65536;

class Mesh;
struct Block;

class Chunk
{
public:
	int x, z;
	bool isEdited = true;

	Block* blocks;

	Mesh* mesh;

	Chunk(int x, int z);
	~Chunk();



	void createMesh(Chunk* left, Chunk* right, Chunk* front, Chunk* back);
	void genChunkBlocks();

};