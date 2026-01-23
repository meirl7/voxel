#include "subChunk.hpp"

SubChunk::SubChunk()
{
	blocks = new Block[4096];
	blockCnt = 0;
}

SubChunk::~SubChunk()
{
	delete[] blocks;
}