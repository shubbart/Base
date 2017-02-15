#pragma once
#include "Base.h"
using base::vec2;
using namespace base;

class Enemy
{

public:
	float speed = 50.f, turnSpeed = 3.f, health = 10.f, range = 5.f;
	
	bool isAlive = true;

	float hInput, vInput = 0.f;

	float deg2rad(float deg) { return deg * PI / 180; }
	float rad2deg(float rad) { return rad * 180 / PI; }
	
	void poll(ObjectPool<Transform>::iterator enemyT, ObjectPool<Rigidbody>::iterator enemyRB, ObjectPool<Transform>::iterator playerT, float dt)
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
		if (enemyT->getGlobalPosition().y > playerT->getGlobalPosition().y)
			enemyRB->acceleration.y -= speed;
		if (enemyT->getGlobalPosition().y < playerT->getGlobalPosition().y)
			enemyRB->acceleration.y += speed;
		if (enemyT->getGlobalPosition().x > playerT->getGlobalPosition().x)
			enemyRB->acceleration.x -= speed;
		if (enemyT->getGlobalPosition().x < playerT->getGlobalPosition().x)
			enemyRB->acceleration.x += speed;
	}
};
