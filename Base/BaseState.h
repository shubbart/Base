#pragma once


class BaseState
{

public:
	virtual void init() {} // called once, on application startup.
	virtual void term() {} // called once, on shutdown.

	virtual void play() {} // called on enter transition
	virtual void stop() {} // called on exit transition

	virtual size_t next() const = 0; // called every frame
	
	virtual void step() {} // called every frame
	virtual void draw() {} // called every frame
};

enum STATES
{
	MENU_ENTER,
	MENU,
	INTRO_ENTER,
	INTRO,
	GAMEOVER_ENTER,
	GAMEOVER,
	EXIT,
	LVL1SPLASH_ENTER,
	LVL1SPLASH,
	GAME_ENTER,
	GAME,
	LVL2SPLASH_ENTER,
	LVL2SPLASH,
	LEVEL_2,
	LVL_2,
	LVL3SPLASH_ENTER,
	LVL3SPLASH,
	LEVEL_3,
	LVL_3,
	LVL4SPLASH_ENTER,
	LVL4SPLASH,
	LEVEL_4,
	LVL_4,
	LVL5SPLASH_ENTER,
	LVL5SPLASH,
	LEVEL_5,
	LVL_5,
	VICTORY_ENTER,
	VICTORY
};