#include "stateManager.hpp"

#include <utility>

void StateManager::changeState(std::unique_ptr<State> state)
{
	states.clear();
	states.push_back(std::move(state));
}

void StateManager::pushState(std::unique_ptr<State> state)
{
	if (!states.empty())
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
