#pragma once

class GameState
{
public:
	// here destructor must be exsist
	virtual ~GameState() = default;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void input() = 0;
private:

};