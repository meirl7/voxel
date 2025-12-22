#include "sprite.hpp"

#include <glad/glad.h>

Sprite::Sprite(Texture* t)
{
	(*this).texture = t;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Sprite::draw()
{
	if (!isVisible)
	{
		return;
	}
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices);
	glBindVertexArray(0);
}

void Sprite::move(int dx, int dy)
{
	posX += dx;
	posY += dy;
}

void Sprite::move(const glm::ivec2& delta)
{
	posX += delta.x;
	posY += delta.y;
}

void Sprite::toggleVisisble()
{
	isVisible = !isVisible;
}
