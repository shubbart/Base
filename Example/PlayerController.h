#pragma once

#include "Base.h"

class PlayerController
{

public:

	float speed = 50, turnSpeed = 3;

	float shotTimer = 0.0f;
	bool shotRequest = false;

	void poll(base::Transform *T, base::Rigidbody *rb, float dt)
	{
		rb->drag = 5;
		rb->angularDrag = 5;
		if (sfw::getKey('W'))
		{
			rb->addForce(T->getGlobalUp().up() * speed);
			rb->drag = 0;
		}

		if (sfw::getKey('S'))
		{
			rb->addForce(T->getGlobalUp().down() * speed);
			rb->drag = 0;
		}

		if (sfw::getKey('A'))
		{
			rb->addForce(T->getGlobalUp().left() * speed );
			rb->drag = 0;
		}

		if (sfw::getKey('D'))
		{
			rb->addForce(T->getGlobalUp().right() * speed );
			rb->drag = 0;
		}

		shotTimer -= dt;
		if (sfw::getKey(' ') && shotTimer < 0)
		{
			shotRequest = true;
			shotTimer = 0.86f;
		}
		else shotRequest = false;
	}

};