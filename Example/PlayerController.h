#pragma once

#include "Base.h"

using base::vec2;

class PlayerController
{
	
public:
	
	float speed = 50, turnSpeed = 3, currentHP = 100;
	
	vec2 mouse;
	vec2 getMouse()
	{
		return base::vec2{ sfw::getMouseX(), sfw::getMouseY() };
	}

	float timer = 2;

	float shotTimer = 0.0f;
	float shieldCD = 0;
	float iceblastCD = 0;
	float flameruneCD = 0;
	float demonboltCD = 0;
	bool shotRequest = false;
	bool shieldRequest = false;
	bool ibRequest = false;
	bool frRequest = false;
	bool dbRequest = false;

	void poll(base::Transform *T, base::Rigidbody *rb, float dt)
	{
		

		if (sfw::getKey('W'))
		{
			rb->addForce(T->getGlobalUp().up() * speed);	
		}

		if (sfw::getKey('S'))
		{
			rb->addForce(T->getGlobalUp().down() * speed);
		}

		if (sfw::getKey('A'))
		{
			rb->addForce(T->getGlobalUp().left() * speed );
		}


		if (sfw::getKey('D'))
		{
			rb->addForce(T->getGlobalUp().right() * speed );
		}


		shotTimer -= dt;
		if (sfw::getMouseButton(MOUSE_BUTTON_LEFT) && shotTimer < 0)
		{
			shotRequest = true;
			shotTimer = 0.85f;		
		}
		else shotRequest = false;


		shieldCD -= dt;
		if (sfw::getMouseButton(MOUSE_BUTTON_RIGHT) && shieldCD <= 0)
		{
			shieldRequest = true;
			shieldCD = 8;
		}
		else shieldRequest = false;

		iceblastCD -= dt;
		if (sfw::getKey('Q') && iceblastCD <= 0)
		{
			ibRequest = true;
			iceblastCD = 5;
		}
		else ibRequest = false;

		flameruneCD -= dt;
		if (sfw::getKey('E') && flameruneCD <= 0)
		{
			frRequest = true;
			flameruneCD = 6;
		}
		else frRequest = false;

		demonboltCD -= dt;
		if (sfw::getKey('F') && demonboltCD <= 0)
		{
			dbRequest = true;
			demonboltCD = 10;
		}
		else dbRequest = false;

	}



};