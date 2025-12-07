#pragma once

#include <vector>
#include <memory>

#include "state.hpp"

// using principle LIFO

class StateManager
{
public:
	void changeState(std::unique_ptr<State> state);

	void pushState(std::unique_ptr<State> state);
	void popState();

	void update();
	void input();
	void render();
private:
	std::vector<std::unique_ptr<State>> states;
};