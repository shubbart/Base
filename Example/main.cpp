
#include "sfwdraw.h"
#include "GameState.h"
#include "MenuState.h"
#include "Intro.h"
#include "Lvl1Splash.h"
#include "Lvl2Splash.h"
#include "Lvl3Splash.h"
#include "Lvl4Splash.h"
#include "Lvl5Splash.h"
#include <cassert>
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Gameover.h"
#include "Victory.h"


/*
	The main function should be used for application state management.
	Currently, only one state is implemented here, you'll need to add additional
	and get them to behave properly.
*/
void main()
{
	sfw::initContext(800,600, "The Warlock");
	sfw::setBackgroundColor(BLACK);
	STATES curState = MENU_ENTER;

	GameState gs;
	IntroState is;
	MenuState ms;
	Level1Splash lvls1;
	Level2Splash lvls2;
	Level3Splash lvls3;
	Level4Splash lvls4;
	Level5Splash lvls5;
	Level2 lvl2;
	Level3 lvl3;
	Level4 lvl4;
	Level5 lvl5;
	Gameover go;
	Victory vs;
	
	bool term = false;

	 // called once
	go.init();
	ms.init();
	is.init();
	lvls1.init();
	lvls2.init();
	lvls3.init();
	lvls4.init();
	lvls5.init();
	lvl2.init();
	lvl3.init();
	lvl4.init();
	lvl5.init();

	//gs.play(); // Should be called each time the state is transitioned into

	while (sfw::stepContext() && term == false)
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
			gs.init();
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
		case LVL3SPLASH_ENTER:
			lvls3.play();
		case LVL3SPLASH:
			lvls3.step();
			lvls3.draw();
			curState = (STATES)lvls3.next();
			break;
		case LEVEL_3:
			lvl3.play();
		case LVL_3:
			lvl3.step();
			lvl3.draw();
			curState = LVL_3;
			break;
		case LVL4SPLASH_ENTER:
			lvls4.play();
		case LVL4SPLASH:
			lvls4.step();
			lvls4.draw();
			curState = (STATES)lvls4.next();
			break;
		case LEVEL_4:
			lvl4.play();
		case LVL_4:
			lvl4.step();
			lvl4.draw();
			curState = LVL_4;
			break;
		case LVL5SPLASH_ENTER:
			lvls5.play();
		case LVL5SPLASH:
			lvls5.step();
			lvls5.draw();
			curState = (STATES)lvls5.next();
			break;
		case LEVEL_5:
			lvl5.play();
		case LVL_5:
			lvl5.step();
			lvl5.draw();
			curState = LVL_5;
			break;
		case GAMEOVER_ENTER:
			go.play();
		case GAMEOVER:
			go.step();
			go.draw();
			go.next();
			curState = (STATES)go.next();
			break;
		case VICTORY_ENTER:
			vs.play();
		case VICTORY:
			vs.step();
			vs.draw();
			vs.next();
			curState = (STATES)vs.next();
		case EXIT:
			term = true;
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