#pragma once

// glfw mouse button indexes
#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_RIGHT 1
#define MOUSE_BUTTON_MIDDLE 2

enum MouseButton
{
	Left,
	Right,
	Middle
};

enum MouseMode
{
	Captured, // captures cursor to the center
	Hidden,   // just unvisible
	Normal,   // normal mode
	Disabled  // use this for camera etc.
};


struct Mouse
{
public:
	double x, y;
	double lastX, lastY;
	double dx, dy;
	double scrollX, scrollY;

	Mouse(GLFWwindow* window);

	void update();

	void setMouseMode(MouseMode m);

	bool isButtonPressed(int i);
	bool isButtonJustPressed(int i);
	bool isButtonReleased(int i);

	void posCallback(GLFWwindow* window, double xpos, double ypos);
private:
	GLFWwindow *window;

	bool firstMouse = true;

	bool buttons[3];
	bool prevButtons[3];
};
