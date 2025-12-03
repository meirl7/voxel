#pragma once

#include <vector>
#include <memory>

#include "gameState.hpp"

// using principle LIFO

class StateManager
{
public:
	void changeState(std::unique_ptr<GameState> state);

	void pushState(std::unique_ptr<GameState> state);
	void popState();

	void update();
	void input();
	void render();
private:
	std::vector<std::unique_ptr<GameState>> states;
};