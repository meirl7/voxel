#include "input.hpp"

double Input::mousePosX = 0.0;
double Input::mousePosY = 0.0;
double Input::lastMouseX = 0.0;
double Input::lastMouseY = 0.0;
double Input::mouseOffsetX = 0.0;
double Input::mouseOffsetY = 0.0;
bool Input::firstMouse = true;
bool Input::isMouseMoving = false;

bool Input::keys[1024] = {false};
bool Input::prevKeys[1024] = { false };

Input::Input(GLFWwindow* window)
{
	attachCallbacks(window);
}

void Input::attachCallbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetKeyCallback(window, keyCallback);
}

bool Input::isKeyJustPressed(int keyCode)
{
	return keys[keyCode] && !prevKeys[keyCode];
}

bool Input::isKeyPressed(int keyCode)
{
	return keys[keyCode];
}

void Input::pollEvents()
{
	for (int i = 0; i < 1024; ++i)
	{
		prevKeys[i] = keys[i];
	}
	mouseOffsetX = 0.0f;
	mouseOffsetY = 0.0f;
	isMouseMoving = false;
	glfwPollEvents();
}

void Input::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	mousePosX = xpos;
	mousePosY = ypos;
	
	if (firstMouse)
	{
		lastMouseX = xpos;
		lastMouseY = ypos;

		firstMouse = false;
	}

	mouseOffsetX = xpos - lastMouseX;
	mouseOffsetY = lastMouseY - ypos;

	isMouseMoving = true;

	lastMouseX = xpos;
	lastMouseY = ypos;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void Input::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

