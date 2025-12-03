#pragma once

#include <vector>
#include <memory>

#include "gameState.hpp"

class StateManager
{
public:
	void changeState();

	void update();
	void input();
	void render();
	void onEnter();
	void onExit();
private:
	std::vector<std::unique_ptr<GameState>> states;
};