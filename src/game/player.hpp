#pragma once
#include <glm/ext/vector_float3.hpp>

class Input;
class World;
class Camera;

class Player
{
public:
	glm::vec3 position;
	glm::vec3 velocity;

	bool onGround;

	Player(Input& input, World& world);

	~Player();

	void update();
	

private:
	Input& input;
	World& world;
};