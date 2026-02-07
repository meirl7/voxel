#include "mouse.hpp"

#include <GLFW/glfw3.h>

Mouse::Mouse(GLFWwindow* window) : window(window)
{
	
}

void Mouse::update()
{
	for (int i = 0; i < 3; i++)
	{
		prevButtons[i] = buttons[i];
	}
}

void Mouse::setMouseMode(MouseMode m)
{
	int md;
	switch (m)
	{
	case MouseMode::Captured:
		md = GLFW_CURSOR_CAPTURED;
		break;
	
	default:
		break;
	}
	glfwSetInputMode(window, GLFW_CURSOR, md);
}

bool Mouse::isButtonPressed(int i)
{
	return buttons[i];
}

bool Mouse::isButtonJustPressed(int i)
{
	return buttons[i] && !prevButtons[i];
}

bool Mouse::isButtonReleased(int i)
{
	return !buttons[i] && prevButtons[i];
}

void Mouse::posCallback(GLFWwindow* window, double xpos, double ypos)
{
	x = xpos;
	y = ypos;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;

		firstMouse = false;
	}

	dx = xpos - lastX;
	dy = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
}