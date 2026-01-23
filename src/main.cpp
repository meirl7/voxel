#include "window/window.hpp"

#include "input/input.hpp"
#include "window/time.hpp"

#include "graphics/camera.hpp"
#include "graphics/render/render.hpp"
#include "graphics/shader.hpp"

#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"

#include "world/world.hpp"

#include <iostream>

const char* vpath = "content/shaders/vert.vert";
const char* fpath = "content/shaders/frag.frag";
const char* texAtlasPath = "content/block.png";

int main()
{
	Window window;
	try
	{
		window.init();
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		window.terminate();
		return -1;
	}


	Texture* texture = new Texture(texAtlasPath);

	Time time;

	Camera camera;
	Input input(window.glwindow);

	Shader shader(vpath, fpath);
	
	Render renderer;
	World* world = new World;

	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)window.width / (float)window.height, 0.1f, 500.0f);
	shader.setMat4("projection", projection);

	while (!window.isShouldClose())
	{
		time.updateTime(glfwGetTime());

		if (input.isKeyJustPressed(GLFW_KEY_ESCAPE))
		{
			window.setShouldClose();
		}

		if (input.isKeyJustPressed(GLFW_KEY_F))
		{
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			Block* vox = world->raycast(camera.position, camera.front, 10.0f, end, norm, iend);
			if (vox != nullptr) {
				std::cout << vox->id << std::endl;
			}
		}

		camera.processInput(input);

		shader.setMat4("view", camera.getViewMatrix());
		texture->bind();
		renderer.drawWorld(shader, *world);

		window.swapBuffers();
		input.pollEvents();
	}

	delete texture;
	delete world;
	
	glfwTerminate();
	return 0;
}