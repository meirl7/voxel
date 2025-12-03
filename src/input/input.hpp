#pragma once

#include "../window/window.hpp"

class Input
{
public:
	static double mousePosX;
	static double mousePosY;
	static double mouseOffsetX;
	static double mouseOffsetY;

	static bool firstMouse;
	static bool isMouseMoving;

	Input(GLFWwindow* window);

	
	static bool isKeyJustPressed(int keyCode);
	static bool isKeyPressed(int keyCode);
	void pollEvents();
private:
	static bool keys[1024];
	static bool prevKeys[1024];
	static double lastMouseX;
	static double lastMouseY;

	void attachCallbacks(GLFWwindow* window);

	static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
