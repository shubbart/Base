
#include "sfwdraw.h"
#include "GameState.h"
#include "MenuState.h"
#include "Intro.h"
#include "Lvl1Splash.h"
#include "Lvl2Splash.h"
#include <cassert>
#include "Level2.h"


/*
	The main function should be used for application state management.
	Currently, only one state is implemented here, you'll need to add additional
	and get them to behave properly.
*/
void main()
{
	sfw::initContext(800,600, "The Warlock");
	STATES curState = MENU_ENTER;

	GameState gs;
	IntroState is;
	MenuState ms;
	Level1Splash lvls1;
	Level2Splash lvls2;
	Level2 lvl2;
	

	gs.init(); // called once
	ms.init();
	is.init();
	lvls1.init();
	lvls2.init();
	lvl2.init();

	gs.play(); // Should be called each time the state is transitioned into

	while (sfw::stepContext())
	{
		switch (curState)
		{
		case MENU_ENTER:
			ms.play();
		case MENU:
			ms.step();
			ms.draw();
			curState = (STATES)ms.next();
			break;
		case INTRO_ENTER:
			is.play();
		case INTRO:
			is.step();
			is.draw();
			curState = (STATES)is.next();
			break;
		case LVL1SPLASH_ENTER:
			lvls1.play();
		case LVL1SPLASH:
			lvls1.step();
			lvls1.draw();
			curState = (STATES)lvls1.next();
			break;
		case GAME_ENTER:
			gs.play();
		case GAME:
			gs.step();
			gs.draw();
			gs.next();
			curState = (STATES)gs.next();
			break;
		case LVL2SPLASH_ENTER:
			lvls2.play();
		case LVL2SPLASH:
			lvls2.step();
			lvls2.draw();
			curState = (STATES)lvls2.next();
			break;
		case LEVEL_2:
			lvl2.play();
		case LVL_2:
			lvl2.step();
			lvl2.draw();
			curState = LVL_2;
			break;
		default:
			assert(false && "Invalid state reached!");
		}
		//gs.next(); Determine the ID of the next state to transition to.
	}

	gs.stop(); // should be called each time the state is transitioned out of

	gs.term(); // called once


	sfw::termContext();

}