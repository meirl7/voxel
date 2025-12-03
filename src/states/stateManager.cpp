#include "stateManager.hpp"

#include <utility>

// if there are 2 or more states, then all previous states will be paused

void StateManager::changeState(std::unique_ptr<GameState> state)
{
	// clear all states
	while (!states.empty())
	{
		states.pop_back();
	}
	states.push_back(std::move(state));
}

void StateManager::pushState(std::unique_ptr<GameState> state)
{
	if (!states.empty()) // freezing all previous states
	{
		states.back()->onPaused();
		states.push_back(std::move(state));
	}
	states.back()->onEnter();
}


void StateManager::popState()
{
	if (!states.empty())
	{
		states.back()->onExit();
		states.pop_back();
		if (!states.empty())
		{
			states.back()->onResume();
		}
	}
}

void StateManager::update()
{
	if (!states.empty() && !states.back()->isPaused)
	{
		states.back()->update();
	}
}

void StateManager::input()
{
	if (!states.empty() && !states.back()->isPaused)
	{
		states.back()->input();
	}
}

void StateManager::render()
{
	if (!states.empty() && !states.back()->isPaused)
	{
		states.back()->render();
	}
}
