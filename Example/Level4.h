#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"

/*
The gamestate represents a discrete container of all that is
necessary to drive the game experience.

A factory object is used to manage the creation and deletion of
objects in the simulation.

The game state updates the entities within the factory using
a series of 'systems.'
*/

class Level4 : public BaseState
{
	Factory factory;
	unsigned spr_background, spr_player, spr_shield, spr_iceblast, spr_flamerune, spr_demonbolt, spr_explosion, spr_death, spr_fireball, spr_font, spr_mouse,
		spr_portal, spr_imp, spr_impA, spr_impD, spr_imp2, spr_imp2D, spr_fire, spr_mage, spr_mageA, spr_mageD;
	ObjectPool<Entity>::iterator currentCamera;

public:
	int count = 0;
	float frameTimer;
	float pTimer;
	float pSpawner;
	int spawnTimer;
	float duration = 8;
	float burnRate = 1;
	bool PlayerAlive = true;

	// Entity stats
	float impSpd = 25;
	float impMSpd = 50;
	float impHP = 10;
	float impRange = 5;
	float impDmg = 2;
	float impX = 0;
	float impY = 250;

	float imp2Spd = 15;
	float imp2MSpd = 30;
	float imp2HP = 30;
	float imp2Range = 5;
	float imp2Dmg = 8;
	float imp2X = 0;
	float imp2Y = 250;

	float mageSpd = 15;
	float mageMSpd = 30;
	float mageHP = 20;
	float mageRange = 12;
	float mageDmg = 12;
	float mageX = 0;
	float mageY = 250;

	virtual void init()
	{
		spr_fireball = sfw::loadTextureMap("../res/fireball.png", 8, 8);
		spr_background = sfw::loadTextureMap("../res/background.jpg");
		spr_player = sfw::loadTextureMap("../res/player.png", 3, 4);
		spr_shield = sfw::loadTextureMap("../res/shield.png");
		spr_iceblast = sfw::loadTextureMap("../res/iceblast.png");
		spr_flamerune = sfw::loadTextureMap("../res/flamerune.png", 4, 4);
		spr_demonbolt = sfw::loadTextureMap("../res/demonbolt.png");
		spr_explosion = sfw::loadTextureMap("../res/explosion.png", 12);
		spr_fire = sfw::loadTextureMap("../res/fire.png", 7);
		spr_death = sfw::loadTextureMap("../res/death.png", 11);
		spr_font = sfw::loadTextureMap("../res/font.png", 32, 4);
		spr_mouse = sfw::loadTextureMap("../res/target.png");
		spr_portal = sfw::loadTextureMap("../res/portal.png");
		spr_imp = sfw::loadTextureMap("../res/imp.png", 4, 4);
		spr_impA = sfw::loadTextureMap("../res/imp_attack.png", 4, 4);
		spr_impD = sfw::loadTextureMap("../res/imp_death.png", 7, 1);
		spr_imp2 = sfw::loadTextureMap("../res/imp2.png", 4, 4);
		spr_imp2D = sfw::loadTextureMap("../res/imp2_death.png", 7, 1);
		spr_mage = sfw::loadTextureMap("../res/mage.png", 4, 4);
		spr_mageA = sfw::loadTextureMap("../res/mage_attack.png", 4, 4);
		spr_mageD = sfw::loadTextureMap("../res/mage_death.png", 7, 1);
	}

	virtual void play()
	{
		PlayerAlive = true;

		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });

		// call some spawning functions!
		factory.spawnStaticImage(spr_background, 0, 0, 400, 300);

		factory.spawnPlayer(spr_player, spr_font, true, 100);


		/*factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);*/

		count = 22;
		factory.spawnTransform({ 0,0 });

		factory.spawnPortal(spr_portal, 0, 250, 60, 60);

		factory.spawnPortal(spr_portal, 0, 250, 60, 60);
		factory.spawnFire(spr_fire, 200, 175, 40, 40);
		factory.spawnFire(spr_fire, -200, 175, 40, 40);
		factory.spawnFire(spr_fire, 200, -175, 40, 40);
		factory.spawnFire(spr_fire, -200, -175, 40, 40);


	}

	virtual void stop()
	{

	}

	// should return what state we're going to.
	// REMEMBER TO HAVE ENTRY AND STAY states for each application state!
	virtual size_t next() const { return 0; }


	// update loop, where 'systems' exist
	virtual void step()
	{
		float dt = sfw::getDeltaTime();
		float frameRate = 1;
		unsigned dirN = 1; // 0,1,2,3 : South, North, East, West
		unsigned dirS = 0;
		unsigned dirE = 2;
		unsigned dirW = 3;
		unsigned dir = 0;
		unsigned frameID;

		spawnTimer += 1;
		if (spawnTimer == 100 || spawnTimer == 200)
		{
			factory.spawnImp(spr_imp, impSpd, impMSpd, impHP, impRange, impDmg, impX, impY, 30, 40);
		}

		pSpawner += 1;
		if (pSpawner == 500)
		{
			factory.spawnPortal(spr_portal, 0, -250, 60, 60);
		}

		if (spawnTimer == 600 || spawnTimer == 700)
		{
			factory.spawnImp(spr_imp, impSpd, impMSpd, impHP, impRange, impDmg, 0, -250, 30, 40);
		}

		if (pSpawner == 1000)
		{
			factory.spawnPortal(spr_portal, -250, -250, 60, 60);
		}

		if (spawnTimer == 1100 || spawnTimer == 1150 || spawnTimer == 1200)
		{
			factory.spawnImp(spr_imp2, imp2Spd, imp2MSpd, imp2HP, imp2Range, imp2Dmg, -250, -250, 50, 60);
		}

		if (pSpawner == 1500)
		{
			factory.spawnPortal(spr_portal, 250, 250, 60, 60);
		}

		if (spawnTimer == 1600 || spawnTimer == 1650 || spawnTimer == 1700)
		{
			factory.spawnImp(spr_imp2, imp2Spd, imp2MSpd, imp2HP, imp2Range, imp2Dmg, 250, 250, 50, 60);
		}

		if (pSpawner == 2500)
		{
			factory.spawnPortal(spr_portal, 250, 0, 60, 60);
		}

		if (spawnTimer == 2600 || spawnTimer == 2700)
		{
			factory.spawnMage(spr_mage, mageSpd, mageMSpd, mageHP, mageRange, mageDmg, 250, 0, 50, 60);
		}

		if (pSpawner == 3000)
		{
			factory.spawnPortal(spr_portal, -250, 0, 60, 60);
		}

		if (spawnTimer == 3200 || spawnTimer == 3300)
		{
			factory.spawnMage(spr_mage, mageSpd, mageMSpd, mageHP, mageRange, mageDmg, -250, 0, 50, 60);
		}

		if (pSpawner == 3300)
		{
			factory.spawnPortal(spr_portal, -250, 250, 60, 60);
		}

		if (spawnTimer == 3350 || spawnTimer == 3400 || spawnTimer == 3450 || spawnTimer == 3500)
		{
			factory.spawnMage(spr_mage, mageSpd, mageMSpd, mageHP, mageRange, mageDmg, -250, 250, 50, 60);
		}

		if (pSpawner == 3400)
		{
			factory.spawnPortal(spr_portal, 250, -250, 60, 60);
		}

		if (spawnTimer == 3450 || spawnTimer == 3500 || spawnTimer == 3550 || spawnTimer == 3600)
		{
			factory.spawnMage(spr_mage, mageSpd, mageMSpd, mageHP, mageRange, mageDmg, 250, -250, 50, 60);
		}



		for (auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

							  // rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			// Animate fire
			if (it->transform->isFire == true)
			{
				frameTimer += frameRate * dt;
				frameID = frameTimer;
				it->sprite->frame_id = frameID % 7 + dir * 0;
			}

			// AI
			for (auto bit = factory.begin(); bit != factory.end(); bit++)
			{
				// Tracking
				if (it != bit && bit->enemy && bit->transform->isEnemy && e.transform && e.transform->isPlayer && !e.transform->isSpell)
				{
					bit->enemy->poll(&bit->transform, &bit->rigidbody, &e.transform, dt);

				}
				// Facing and sprite animation
				if (it != bit && bit->enemy && bit->transform->isEnemy && e.transform && e.transform->isPlayer && !e.transform->isSpell)
				{
					float facing = bit->enemy->getDirection(&bit->transform->getGlobalPosition(), &e.transform->getGlobalPosition());

					/*if (facing > 45 && facing < 135) dir = 0; // Up
					if (facing > 135 && facing < 225) dir = 1; // Left
					if (facing > 225 && facing < 315) dir = 2; // Down
					if (facing > 315 && facing < 45) dir = 3; // Right*/

					frameTimer += frameRate * dt;
					frameID = frameTimer;
					bit->sprite->frame_id = frameID % 3 + dir * 2;
				}

			}

			//if (it->enemy->enemyAttack == true)
			//{
			//	if (it->sprite->sprite_id == spr_mage)
			//		it->sprite->sprite_id = spr_mageA;
			//	frameTimer += frameRate * dt;
			//	frameID = frameTimer;
			//	it->sprite->frame_id = frameID % 3 + dir * 2;
			//}


			// controller update
			if (e.transform && e.rigidbody && e.controller)
			{
				e.controller->mouse = e.controller->getMouse(); // update mouse

				e.controller->poll(&e.transform, &e.rigidbody, dt);
				if (e.controller->shotRequest) // controller requested a bullet fire
				{
					vec2 screenMouse = { sfw::getMouseX(), sfw::getMouseY() };
					vec2 worldMouse = currentCamera->camera->getScreenPointToWorldPoint(&currentCamera->transform, screenMouse);

					vec2 firingVel = (worldMouse - e.transform->getGlobalPosition()).normal() * 200;

					factory.spawnFireball(spr_fireball, e.transform->getGlobalPosition(),
						vec2{ 32,32 }, firingVel.angle(), firingVel, 10, 1, true);
				}
				if (e.controller->shieldRequest) // Magic Barrier
				{
					factory.spawnShield(spr_shield, e.transform->getGlobalPosition(),
						vec2{ 125,125 }, 10, 1, true);
				}
				if (e.controller->ibRequest) // Iceblast
				{
					vec2 screenMouse = { sfw::getMouseX(), sfw::getMouseY() };
					vec2 worldMouse = currentCamera->camera->getScreenPointToWorldPoint(&currentCamera->transform, screenMouse);

					vec2 firingVel = (worldMouse - e.transform->getGlobalPosition()).normal() * 75;

					factory.spawnIceblast(spr_iceblast, e.transform->getGlobalPosition(),
						vec2{ 45,32 }, firingVel.angle(), firingVel, 15, 1, true);
				}

				if (e.controller->frRequest) // Flamerune
				{
					vec2 screenMouse = { sfw::getMouseX(), sfw::getMouseY() };
					vec2 worldMouse = currentCamera->camera->getScreenPointToWorldPoint(&currentCamera->transform, screenMouse);

					factory.spawnFR(spr_flamerune, worldMouse, vec2{ 40,40 }, 1, true);
				}

				if (e.controller->dbRequest) // Demonic Bolt
				{
					vec2 screenMouse = { sfw::getMouseX(), sfw::getMouseY() };
					vec2 worldMouse = currentCamera->camera->getScreenPointToWorldPoint(&currentCamera->transform, screenMouse);

					vec2 firingVel = (worldMouse - e.transform->getGlobalPosition()).normal() * 200;

					factory.spawnDB(spr_demonbolt, e.transform->getGlobalPosition(),
						vec2{ 75,75 }, firingVel.angle(), firingVel, 35, 1, true);
				}
			}

			if (it->transform->isPortal == true)
			{
				pTimer += frameRate * dt;
				it->rigidbody->addSpin(.025);
				if (pTimer > 5)
				{
					del = true;
					pTimer = 0;
				}
			}

			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			if (it->transform->isBurning)
			{
				duration -= frameRate * dt;
				burnRate -= frameRate * dt;
				if (burnRate <= 0)
				{
					it->rigidbody->HP -= 5;
					burnRate = 1;
				}
				if (duration <= 0)
					!it->transform->isBurning;
				std::cout << it->rigidbody->HP << std::endl;
			}

			// Death
			if (it->rigidbody && it->rigidbody->HP <= 0)
			{
				frameTimer += frameRate * dt;
				frameID = frameTimer;

				if (it->enemy)
				{
					if (it->sprite->sprite_id == spr_imp2)
						it->sprite->sprite_id = spr_imp2D;
					if (it->sprite->sprite_id == spr_mage)
						it->sprite->sprite_id = spr_mageD;
					if (it->sprite->sprite_id == spr_imp)
						it->sprite->sprite_id = spr_impD;
					it->sprite->frame_id = frameID % 7 + dir * 0;

					if (frameID > 6)
					{
						del = true;
						--count;
						frameTimer = 0;
					}
				}
				else
				{
					if (it->transform->isDB == true)
					{
						it->rigidbody->damage = 15;
						it->rigidbody->mass = 500;
						it->rigidbody->drag = 4;
						it->sprite->sprite_id = spr_explosion;
						it->sprite->angle = PI;

						frameTimer += (frameRate * dt) / 2;
						frameID = frameTimer;

						it->sprite->frame_id = frameID % 10;
					}
					else if (it->transform->isRune == false)
					{
						it->sprite->sprite_id = spr_death;
						if (it->transform->isIceblast == true)
						{
							it->sprite->tint = CYAN;
						}
						it->sprite->frame_id = frameID % 11 + dir * 0;
						if (it->transform->PlayerIsAlive == true && frameID > 7)
						{
							it->transform->PlayerIsAlive = false;
							PlayerAlive = false;
						}
					}
					if (frameID > 10)
					{
						del = true;
						frameTimer = 0;
					}
				}
			}


			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}

		}



		// Physics system!
		// You'll want to extend this with custom collision responses


		for (auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for (auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
					// if they aren't the same and they both have collidable bits...
				{
					if (it->transform->isPlayer == true && bit->transform->isPlayer == true)
						continue; // if the objects are both either the player and/or player created objects, ignore collision

					if (it->transform->isEnemy == true && bit->transform->isEnemy == true)
						continue;// if the objects are both either the enemy and/or enemy created objects, ignore collision

					if (it->transform->isFrozen == true && bit->transform->isIceblast == true)
						continue;

					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);

						// if there was a collision,
						if (cd.result())
						{
							// Iceblast collision
							if (it->transform->isEnemy == true && bit->transform->isIceblast == true && it->transform->isFrozen == false)
							{
								it->rigidbody->HP -= bit->rigidbody->damage;

								it->rigidbody->velocity = it->rigidbody->velocity * .25;
								it->enemy->speed = it->enemy->speed * .25;
								it->transform->isFrozen = true;
								continue;
							}

							if (bit->transform->isEnemy == true && it->transform->isIceblast == true && bit->transform->isFrozen == false)
							{
								bit->rigidbody->HP -= it->rigidbody->damage;

								bit->rigidbody->velocity = bit->rigidbody->velocity * .25;
								bit->enemy->speed = bit->enemy->speed * .25;
								bit->transform->isFrozen = true;
								continue;
							}


							// Flame Rune collision
							if (it->transform->isEnemy == true && bit->transform->isRune == true)
							{
								it->transform->isBurning = true;
								bit->rigidbody->HP -= it->rigidbody->damage;
								continue;
							}
							if (bit->transform->isEnemy == true && it->transform->isRune == true)
							{
								bit->transform->isBurning = true;
								it->rigidbody->HP -= bit->rigidbody->damage;
								continue;
							}

							// condition for dynamic resolution
							if (it->rigidbody && bit->rigidbody)
							{
								it->rigidbody->HP -= bit->rigidbody->damage;
								bit->rigidbody->HP -= it->rigidbody->damage;
								base::DynamicResolution(cd, &it->transform, &it->rigidbody, &bit->transform, &bit->rigidbody);
							}
							// condition for static resolution
							else if (it->rigidbody && !bit->rigidbody)
								base::StaticResolution(cd, &it->transform, &it->rigidbody);
						}
					}
				}



		for each(auto &e in factory)
		{
			if (e.transform && e.sprite && e.transform->isPlayer)
			{
				if (sfw::getKey('W')) dir = dirN;
				if (sfw::getKey('S')) dir = dirS;
				if (sfw::getKey('A')) dir = dirW;
				if (sfw::getKey('D')) dir = dirE;

				frameTimer += frameRate * dt;
				frameID = frameTimer;
				e.sprite->frame_id = frameID % 3 + dir * 3;
			}
		}


		// DEBUGGING
		/*	vec2 screenMouse = { sfw::getMouseX(), sfw::getMouseY() };
		vec2 worldMouse  = currentCamera->camera->getScreenPointToWorldPoint(&currentCamera->transform, screenMouse);

		std::cout << "mouse scrrn pos: " << screenMouse.x << "," << screenMouse.y << "\n";
		std::cout << "mouse world pos: " << worldMouse.x << "," << worldMouse.y << "\n";*/
	}


	virtual void draw()
	{
		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, cam);

		// draw text
		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);
		sfw::drawTexture(spr_mouse, sfw::getMouseX(), sfw::getMouseY(), 25, 25, 0.f, true, 0U, RED);

#ifdef _DEBUG
		for each(auto &e in factory)
			if (e.transform)
				e.transform->draw(cam);

		for each(auto &e in factory)
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.rigidbody)
				e.rigidbody->draw(&e.transform, cam);


#endif
	}
	STATES Level4::next()
	{
		if (PlayerAlive == false)
		{
			for (auto it = factory.begin(); it != factory.end();)
			{
				it->onFree();
				it.free();
			}
			return GAMEOVER_ENTER;
		}
		if (count <= 0)
		{
			for (auto it = factory.begin(); it != factory.end();)
			{
				it->onFree();
				it.free();
			}
			return LVL5SPLASH_ENTER;
		}
		else
			return LVL_4;
	}
};
