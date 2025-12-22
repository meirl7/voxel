#include "render.hpp"
#include <iostream>

#define index (y * CHUNK_W + z) * CHUNK_W + x
#define isBlockInChunk(x, y, z) ((x < CHUNK_W) && (y < CHUNK_H) && (z < CHUNK_W))
#define getBlock(x, y, z) (chunk->blocks[((y)*CHUNK_W + (z)) * CHUNK_W + (x)])
#define isItBlocked(x, y, z) (isBlockInChunk(x, y, z) && (getBlock(x, y, z).id != 0))
#define addVertex(x, y, z, u, v, l) buffer.push_back(x);\
									buffer.push_back(y);\
									buffer.push_back(z);\
									buffer.push_back(u);\
									buffer.push_back(v);\
									buffer.push_back(l)
int chunk_attrs[] = {3,2,1, 0};

Render::Render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::vec4 bgColor(135.f, 206.f, 235.f, 255.f);
	bgColor /= 255.f;
	glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
}

Mesh* Render::createMesh(Chunk* chunk, Chunk* left, Chunk* right, Chunk* front, Chunk* back, Chunk* top, Chunk* bottom)
{
	buffer.clear();
	float uvSize = 1.f / 32.f;
	float u;
	float v;
	float light;
	bool blocked = false;

	for (int y = 0; y < CHUNK_H; y++)
	{
		for (int z = 0; z < CHUNK_W; z++)
		{
			for (int x = 0; x < CHUNK_W; x++)
			{
				if (chunk->blocks[index].id == 0)
				{
					continue;
				}

				u = (chunk->blocks[index].id % 16) * uvSize;
				v = 1 - ((1 + chunk->blocks[index].id / 16) * uvSize);
				
				if (y + 1 < CHUNK_H)
				{
					blocked = isItBlocked(x, y + 1, z);
				}
				else if (top)
				{
					blocked = top->blocks[z * CHUNK_W + x].id != 0;
				}
				if (!blocked)
				{
					light = 1.0f;

					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v, light);
				}
				blocked = false;


				if (y - 1 >= 0)
				{
					blocked = isItBlocked(x, y - 1, z);
				}
				else if (bottom)
				{
					blocked = bottom->blocks[(15 * CHUNK_H + z) * CHUNK_W + x].id != 0;
				}
				if (!blocked)
				{
					light = 0.75f;

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
				}
				blocked = false;


				if (x - 1 >= 0)
				{
					blocked = isItBlocked(x - 1, y, z);
				}
				else if (left)
				{
					blocked = left->blocks[(y * CHUNK_W + z) * CHUNK_W + 15].id != 0;
				}
				if (!blocked)
				{
					light = 0.85f;

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
				}
				blocked = false;


				if (x + 1 < CHUNK_W)
				{
					blocked = isItBlocked(x + 1, y, z);
				}
				else if (right) {
					blocked = right->blocks[(y * CHUNK_W + z) * CHUNK_W].id != 0;
				}
				if (!blocked)
				{
					light = 0.95f;

					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u, v, light);
				}
				blocked = false;


				if (z + 1 < CHUNK_W)
				{
					blocked = isItBlocked(x, y, z + 1);
				}
				else if (front)
				{
					blocked = front->blocks[(y * CHUNK_W * CHUNK_W + x)].id != 0;
				}
				if (!blocked)
				{
					light = 0.9f;
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light);
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
				}
				blocked = false;


				if (z - 1 >= 0)
				{
					blocked = isItBlocked(x, y, z - 1);
				}
				else if (back)
				{
					blocked = back->blocks[(y * CHUNK_W + 15) * CHUNK_W + x].id != 0;
				}
				if (!blocked) {
					light = 0.8f;

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);
					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u, v, light);
				}
				blocked = false;
			}
		}
	}

	return new Mesh(buffer, buffer.size() / 6, chunk_attrs);
}

void Render::drawWorld(Shader& shader, World& world)
{
	glm::mat4 model(1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& p : world.chunks)
	{
		Chunk* ch = &p.second;
		if (ch->isEdited)
		{
			//// REWRITE !!! THIS CANNOT BE NULLPTR IF NOT FINDED
			int x = ch->xp, y = ch->yp, z = ch->zp;
			Chunk* left = &world.chunks[glm::ivec3(x - 1, y, z)];
			Chunk* right = &world.chunks[glm::ivec3(x + 1, y, z)];
			Chunk* front = &world.chunks[glm::ivec3(x, y, z + 1)];
			Chunk* back = &world.chunks[glm::ivec3(x, y, z - 1)];
			Chunk* bottom = &world.chunks[glm::ivec3(x, y - 1, z)];
			Chunk* top = &world.chunks[glm::ivec3(x, y + 1, z)];
			ch->mesh = createMesh(ch, left, right, front, back, top, bottom);
			ch->isEdited = false;
		}
		model = glm::translate(glm::mat4(1.0f), glm::vec3(ch->xp * CHUNK_W, ch->yp * CHUNK_H, ch->zp * CHUNK_W));
		shader.setMat4("model", model);
		ch->mesh->draw();
	}
}

//-----------------AMBIENT OCCLUSION-----------------
/*

float a = 0.0f, b = 0.0f, c = 0.0f, d = 0.0f, e = 0.0f, f = 0.0f, g = 0.0f, h = 0.0f;

				if (!isItBlocked(x, y + 1, z))
				{
					light = 1.0f;

					if (isAOEnabled)
					{
						a = isItBlocked(x + 1, y + 1, z) * aoFactor;
						b = isItBlocked(x, y + 1, z + 1) * aoFactor;
						c = isItBlocked(x - 1, y + 1, z) * aoFactor;
						d = isItBlocked(x, y + 1, z - 1) * aoFactor;
						e = isItBlocked(x - 1, y + 1, z - 1) * aoFactor;
						f = isItBlocked(x - 1, y + 1, z + 1) * aoFactor;
						g = isItBlocked(x + 1, y + 1, z + 1) * aoFactor;
						h = isItBlocked(x + 1, y + 1, z - 1) * aoFactor;
					}

					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light * (1.0f - c - d - e));
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light * (1.0f - c - b - f));
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light * (1.0f - a - b - g));

					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light * (1.0f - a - b - g));
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v, light * (1.0f - a - d - h));
				}

				if (!isItBlocked(x, y - 1, z))
				{
					light = 0.75f;

					if (isAOEnabled)
					{
						a = isItBlocked(x + 1, y - 1, z) * aoFactor;
						b = isItBlocked(x, y - 1, z + 1) * aoFactor;
						c = isItBlocked(x - 1, y - 1, z) * aoFactor;
						d = isItBlocked(x, y - 1, z - 1) * aoFactor;
						e = isItBlocked(x - 1, y - 1, z - 1) * aoFactor;
						f = isItBlocked(x - 1, y - 1, z + 1) * aoFactor;
						g = isItBlocked(x + 1, y - 1, z + 1) * aoFactor;
						h = isItBlocked(x + 1, y - 1, z - 1) * aoFactor;
					}

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light * (1.0f - a - b - g));
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvSize, light * (1.0f - c - b - f));

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light * (1.0f - a - b - g));
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light * (1.0f - a - d - h));
				}

				if (!isItBlocked(x + 1, y, z))
				{
					light = 0.95f;

					if (isAOEnabled)
					{
						a = isItBlocked(x + 1, y + 1, z) * aoFactor;
						b = isItBlocked(x + 1, y, z + 1) * aoFactor;
						c = isItBlocked(x + 1, y - 1, z) * aoFactor;
						d = isItBlocked(x + 1, y, z - 1) * aoFactor;

						e = isItBlocked(x + 1, y - 1, z - 1) * aoFactor;
						f = isItBlocked(x + 1, y - 1, z + 1) * aoFactor;
						g = isItBlocked(x + 1, y + 1, z + 1) * aoFactor;
						h = isItBlocked(x + 1, y + 1, z - 1) * aoFactor;
					}

					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light * (1.0f - d - a -h));
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light * (1.0f - a - b - g));

					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light * (1.0f - a - b - g));
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u, v, light * (1.0f - b - c - f));
				}

				if (!isItBlocked(x - 1, y, z))
				{
					light = 0.85f;

					if (isAOEnabled)
					{
						a = isItBlocked(x - 1, y + 1, z) * aoFactor;
						b = isItBlocked(x - 1, y, z + 1) * aoFactor;
						c = isItBlocked(x - 1, y - 1, z) * aoFactor;
						d = isItBlocked(x - 1, y, z - 1) * aoFactor;

						e = isItBlocked(x - 1, y - 1, z - 1) * aoFactor;
						f = isItBlocked(x - 1, y - 1, z + 1) * aoFactor;
						g = isItBlocked(x - 1, y + 1, z + 1) * aoFactor;
						h = isItBlocked(x - 1, y + 1, z - 1) * aoFactor;
					}

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light * (1.0f - c - d - e));
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light * (1.0f - a - b - g));
					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light * (1.0f - d - a - h));

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light * (1.0f - c - d - e));
					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light * (1.0f - b - c - f));
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light * (1.0f - a - b - g));
				}

				if (!isItBlocked(x, y, z + 1))
				{
					light = 0.9f;

					if (isAOEnabled)
					{
						a = isItBlocked(x, y + 1, z + 1) * aoFactor;
						b = isItBlocked(x + 1, y, z + 1) * aoFactor;
						c = isItBlocked(x, y - 1, z + 1) * aoFactor;
						d = isItBlocked(x - 1, y, z + 1) * aoFactor;

						e = isItBlocked(x - 1, y - 1, z + 1) * aoFactor;
						f = isItBlocked(x + 1, y - 1, z + 1) * aoFactor;
						g = isItBlocked(x + 1, y + 1, z + 1) * aoFactor;
						h = isItBlocked(x - 1, y + 1, z + 1) * aoFactor;
					}

					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light * (1.0f - a - b - g));
					addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light * (1.0f - a - d - h));

					addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light * (1.0f - b - c - f));
					addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light * (1.0f - a - b - g));
				}

				if (!isItBlocked(x, y, z - 1))
				{
					light = 0.8f;

					if (isAOEnabled)
					{
						a = isItBlocked(x, y + 1, z - 1) * aoFactor;
						b = isItBlocked(x + 1, y, z - 1) * aoFactor;
						c = isItBlocked(x, y - 1, z - 1) * aoFactor;
						d = isItBlocked(x - 1, y, z - 1) * aoFactor;

						e = isItBlocked(x - 1, y - 1, z - 1) * aoFactor;
						f = isItBlocked(x + 1, y - 1, z - 1) * aoFactor;
						g = isItBlocked(x + 1, y + 1, z - 1) * aoFactor;
						h = isItBlocked(x - 1, y + 1, z - 1) * aoFactor;
					}

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light * (1.0f - c - d - e));
					addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light * (1.0f - a - d - h));
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light * (1.0f - a - d - h));

					addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light * (1.0f - c - d - e));
					addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light * (1.0f - a - d - h));
					addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u, v, light * (1.0f - b - c - f));
				}

*/


// -----------------------WITHOUT AO------------------
/*
if (y + 1 < CHUNK_H)
{
	blocked = isItBlocked(x, y + 1, z);
}
else if (top)
{
	blocked = top->blocks[z * CHUNK_W + x].id != 0;
}
if (!blocked)
{
	light = 1.0f;

	addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light);
	addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
	addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

	addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, light);
	addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);
	addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v, light);
}
blocked = false;


if (y - 1 >= 0)
{
	blocked = isItBlocked(x, y - 1, z);
}
else if (bottom)
{
	blocked = bottom->blocks[(15 * CHUNK_H + z) * CHUNK_W + x].id != 0;
}
if (!blocked)
{
	light = 0.75f;

	addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
	addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
	addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvSize, light);

	addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
	addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
	addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
}
blocked = false;


if (x + 1 < CHUNK_W)
{
	blocked = isItBlocked(x + 1, y, z);
}
else if (right) {
	blocked = right->blocks[(y * CHUNK_W + z) * CHUNK_W].id != 0;
}
if (!blocked)
{
	light = 0.95f;

	addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
	addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light);
	addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

	addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
	addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);
	addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u, v, light);
}
blocked = false;


if (x - 1 >= 0)
{
	blocked = isItBlocked(x - 1, y, z);
}
else if (left)
{
	blocked = left->blocks[(y * CHUNK_W + z) * CHUNK_W + 15].id != 0;
}
if (!blocked)
{
	light = 0.85f;

	addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
	addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
	addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);

	addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u, v, light);
	addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light);
	addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
}
blocked = false;


if (z + 1 < CHUNK_W)
{
	blocked = isItBlocked(x, y, z + 1);
}
else if (front)
{
	blocked = front->blocks[(y * CHUNK_W * CHUNK_W + x)].id != 0;
}
if (!blocked)
{
	light = 0.9f;
	addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light);
	addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
	addVertex(x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, light);

	addVertex(x - 0.5f, y - 0.5f, z + 0.5f, u, v, light);
	addVertex(x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, light);
	addVertex(x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, light);
}
blocked = false;


if (z - 1 >= 0)
{
	blocked = isItBlocked(x, y, z - 1);
}
else if (back)
{
	blocked = back->blocks[(y * CHUNK_W + 15) * CHUNK_W + x].id != 0;
}
if (!blocked) {
	light = 0.8f;

	addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
	addVertex(x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, light);
	addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);

	addVertex(x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, light);
	addVertex(x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, light);
	addVertex(x + 0.5f, y - 0.5f, z - 0.5f, u, v, light);
}
blocked = false;
*/