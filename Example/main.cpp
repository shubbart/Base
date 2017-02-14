
#include "sfwdraw.h"
#include "GameState.h"
#include "MenuState.h"
#include <cassert>


/*
	The main function should be used for application state management.
	Currently, only one state is implemented here, you'll need to add additional
	and get them to behave properly.
*/
void main()
{
	sfw::initContext();
	STATES curState = MENU_ENTER;

	GameState gs;
	MenuState ms;

	gs.init(); // called once
	ms.init();

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
			if (sfw::getKey(KEY_ENTER))
				curState = GAME_ENTER;
			break;
		case GAME_ENTER:
			gs.play();
		case GAME:
			gs.step();
			gs.draw();
			curState = GAME;
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