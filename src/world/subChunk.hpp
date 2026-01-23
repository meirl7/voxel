#pragma once

#include "block.hpp"

class SubChunk
{
public:
	Block* blocks;
	
	uint8_t y;

	uint16_t blockCnt;

	SubChunk();
	~SubChunk();
};