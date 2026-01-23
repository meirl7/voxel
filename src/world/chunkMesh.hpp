#pragma once

class Mesh;
class Chunk;

class ChunkMesh
{
public:
	Mesh* subMeshes; // size - 16x16x16
	
	void genSubMesh(Chunk& ch, Chunk& left, Chunk& right, Chunk& front, Chunk& back);
};