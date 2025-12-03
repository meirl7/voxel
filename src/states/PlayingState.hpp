#pragma once

#include "gameState.hpp"

class PlayingState : public GameState
{
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual void render() override;
	virtual void update() override;
	virtual void input() override;
};