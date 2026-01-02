#include "render.hpp"

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


void Render::drawWorld(Shader& shader, World& world)
{
	glm::mat4 model(1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& p : world.chunks)
	{
		Chunk* ch = p.second.get();
		if (ch->isEdited)
		{
			//// REWRITE !!! THIS CANNOT BE NULLPTR IF NOT FINDED
			int x = ch->x, z = ch->z;
			Chunk* left = world.chunks[glm::ivec2(x - 1, z)].get();
			Chunk* right = world.chunks[glm::ivec2(x + 1, z)].get();
			Chunk* front = world.chunks[glm::ivec2(x, z + 1)].get();
			Chunk* back = world.chunks[glm::ivec2(x, z - 1)].get();
			ch->mesh = createMesh(ch, left, right, front, back);
			ch->isEdited = false;
		}
		model = glm::translate(glm::mat4(1.0f), glm::vec3(ch->x * chunkW, 0.f, ch->z * chunkW));
		shader.setMat4("model", model);
		ch->mesh->draw();
	}
}