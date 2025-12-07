#pragma once

class State
{
public:
	bool isPaused = false;

	virtual ~State() = default;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void onPaused() = 0;
	virtual void onResume() = 0;

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void input() = 0;
private:
	
};