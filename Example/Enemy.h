#pragma once
#include "Base.h"
using base::vec2;
using namespace base;

class Enemy
{

public:
	float maxSpeed, speed = 50.f, range = 0.f;

	float hInput, vInput = 0.f;

	float deg2rad(float deg) { return deg * PI / 180; }
	float rad2deg(float rad) { return rad * 180 / PI; }
	
	void poll(base::Transform *enemyT, base::Rigidbody *enemyRB, base::Transform *playerT, float dt)
	{
	
		vec2 facing = enemyT->getGlobalUp().normal();
		vec2 dist = enemyT->getGlobalPosition() - playerT->getGlobalPosition();
		float view = acos(dot(facing, dist));
		view = rad2deg(view);

		vec2 findVec{ playerT->getGlobalPosition().x - enemyT->getGlobalPosition().x,
			playerT->getGlobalPosition().y - enemyT->getGlobalPosition().y };
		float angleBetween = acos(dot(enemyT->getGlobalPosition().normal(), playerT->getGlobalPosition().normal()));
		angleBetween = rad2deg(angleBetween);
		// Track the player
		if (enemyT->getGlobalPosition().y > playerT->getGlobalPosition().y )
			enemyRB->acceleration.y -= speed;
		if (enemyT->getGlobalPosition().y < playerT->getGlobalPosition().y)
			enemyRB->acceleration.y += speed;
		if (enemyT->getGlobalPosition().x > playerT->getGlobalPosition().x )
			enemyRB->acceleration.x -= speed;
		if (enemyT->getGlobalPosition().x < playerT->getGlobalPosition().x)
			enemyRB->acceleration.x += speed;
	}

	float getDirection(vec2 *enemyV, vec2 *playerV)
	{
		return acos(enemyV->x * playerV->x + enemyV->y * playerV->y) * 180/PI;
		//float down = dot((enemyV - playerV), vec2{ 0,-1 });
		//float up = dot((enemyV - playerV), vec2{ 0,1 });
		//float left = dot((enemyV - playerV), vec2{ -1,0 });
		//float right = dot((enemyV - playerV), vec2{ 1,0 });

		//float face = fmaxf(fmaxf(down, up), fmaxf(left, right));

		//if (face = up) return 0;
		//if (face = down) return 2;
		//if (face = left) return 1;
		//if (face = right) return 3;
	}


};
