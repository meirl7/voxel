#pragma once

#include <stdint.h>

/*		north
		z-
		|
west	|
----------------x+ east
		|
		|
		z+
		south
*/

enum Face
{
	XPOS,
	XNEG,
	YPOS,
	YNEG,
	ZPOS,
	ZNEG
};

struct Block
{
	uint16_t id;
	//uint16_t data;
};

void setFaceData(Face face, Block& block)
{
	
}

// data
// 0000000000000000
// 6 for rotation
// 10 for data