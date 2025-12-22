#pragma once

#include "../texture.hpp"
#include "../shader.hpp"

/*
The difference between * and &, ptr and adress:
ptr can be nullptr
adress must be exsist, and cannot be nullptr
*/

struct UV
{
	float u1, v1, u2, v2;
	UV(float u1, float v1, float u2, float v2)
	{
		this->u1 = u1;
		this->v1 = v1;
		this->u2 = u2;
		this->v2 = v2;
	}
	UV(float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f)
	{
		this->u1 = u1;
		this->v1 = v1;
		this->u2 = u2;
		this->v2 = v2;
	}
};

class Sprite
{
private:
	float* buffer;
	unsigned int VAO, VBO;
	int vertices;

	int width, height; // in pixels
	int posX, posY;

	bool isVisible = true;
	int rotation = 0; // in degress

	glm::vec4 color;

public:
	Sprite(Texture* t);
	~Sprite();


	void draw();

	void move(int dx, int dy);
	void move(const glm::ivec2& delta);

	void toggleVisisble();
};