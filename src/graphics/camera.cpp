#include "camera.hpp"

Camera::Camera()
{
    position = glm::vec3(0.0f, 50.0f, 0.0f);
    pitch = 0.0f;
    yaw = 0.0f;
    mouseSensitivity = 0.1f;
    fov = 45.0f;
    movementSpeed = 25.f;
    front = glm::vec3(0.0f, 0.f, -1.0f);
    worldup = glm::vec3(0.0f, 1.0f, 0.0f);
    update();
}

Camera::Camera(glm::vec3 pos)
{
	position = pos;
	update();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);

    //fr.x = cos(glm::radians(yaw));
    //fr.z = sin(glm::radians(yaw));
    
    right = glm::normalize(glm::cross(front, worldup));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::processInput(Input& input)
{
	velocity = Time::deltaTime * movementSpeed;
	if (input.isKeyPressed(GLFW_KEY_W))
	{
		position += front * velocity;
	}
	if (input.isKeyPressed(GLFW_KEY_S))
	{
		position -= front * velocity;
	}
	if (input.isKeyPressed(GLFW_KEY_A))
	{
		position -= right * velocity;
	}
	if (input.isKeyPressed(GLFW_KEY_D))
	{
		position += right * velocity;
	}

	if (input.isMouseMoving)
	{
		yaw += float(input.mouseOffsetX) * mouseSensitivity;
		pitch += float(input.mouseOffsetY) * mouseSensitivity;

		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
		update();
	}
}
