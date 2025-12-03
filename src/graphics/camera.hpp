#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../window/time.hpp"
#include "../utils/raycast.hpp"
#include "../window/input.hpp"


class Camera
{
public:
	glm::vec3 position, front, up, right, worldup;

	float yaw, pitch, movementSpeed, mouseSensitivity, fov;
	float velocity;

	Camera();
	Camera(glm::vec3 pos);
	glm::mat4 getViewMatrix();
	void update();
	void processInput(Input& input);
};