#include "window/window.hpp"

#include "window/input.hpp"
#include "window/time.hpp"

#include "graphics/camera.hpp"
#include "graphics/render.hpp"
#include "graphics/shader.hpp"

#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"

#include "game/world.hpp"
#include "game/player.hpp"

#include <iostream>

const char* vpath = "content/shaders/vert.vert";
const char* fpath = "content/shaders/frag.frag";

int main()
{
	try
	{
		Window window;
		Time time;
		
		Camera camera;
		Input input(window.glwindow);

		Shader shader(vpath, fpath);
		Texture* texture = load_texture("content/block.png");

		if (texture == nullptr)
		{
			delete texture;
			throw std::runtime_error("Canoot load texture");
		}

		Render renderer;
		World* world = new World;

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::vec4 bgColor(135.f, 206.f, 235.f, 255.f);
		bgColor /= 255.f;
		glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
		
		shader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)window.width / (float)window.height, 0.1f, 500.0f);
		shader.setMat4("projection", projection);
		camera.position = glm::vec3(25.0f, 25.0f, 25.0f);

		while (!window.isShouldClose())
		{
			time.updateTime(glfwGetTime());

			// Inputs
			if (input.isKeyJustPressed(GLFW_KEY_ESCAPE))
			{
				window.setShouldClose();
			}

			// Clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// Draw
			shader.use();
			shader.setMat4("view", camera.getViewMatrix());
			texture->bind();
			world->draw(renderer, shader);

			
			// Swap buffers and poll event
			window.swapBuffers();
			input.pollEvents();
		}

		delete texture;
		delete world;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return -1;
	}
	glfwTerminate();
	return 0;
}