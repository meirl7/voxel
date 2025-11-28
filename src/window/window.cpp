#include "window.hpp"

Window::Window()
{
	width = 1600;
	height = 900;
	title = "Window";
	vSynvEnabled = true;

	mode = WindowMode::WINDOWED;

	init();
}

Window::~Window()
{
	glfwDestroyWindow(glwindow);
	glfwTerminate();
}

void Window::init()
{
	glfwInit();
	if (glfwInit() == GLFW_FALSE)
	{
		throw std::runtime_error("GLFW INIT FAILED");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glwindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!glwindow)
	{
		glfwTerminate();
		throw std::runtime_error("FAILED TO CREATE WINDOW");
	}

	glfwMakeContextCurrent(glwindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(glwindow);
		glfwTerminate();
		throw std::runtime_error("FAILED TO INIT GLAD");
	}
	
	
	glfwSwapInterval(1);


	glfwSetInputMode(glwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

bool Window::isShouldClose() const
{
	return glfwWindowShouldClose(glwindow);
}

void Window::setShouldClose() const
{
	glfwSetWindowShouldClose(glwindow, true);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(glwindow);
}
