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

class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_player, spr_cast, spr_death, spr_fireball, spr_roid, spr_font, spr_mouse,
			 spr_portal, spr_imp, spr_impA, spr_impD;
	ObjectPool<Entity>::iterator currentCamera;
	size_t player_wUp = 3;


public:
	int count = 0;
	float frameTimer;
	virtual void init()
	{
		spr_fireball = sfw::loadTextureMap("../res/fireball.png",8,8);
		spr_space = sfw::loadTextureMap("../res/space.jpg");
		spr_player = sfw::loadTextureMap("../res/player.png", 3, 4);
		spr_cast = sfw::loadTextureMap("../res/cast.png", 9, 4);
		spr_death = sfw::loadTextureMap("../res/death.png", 5,5);
		spr_roid = sfw::loadTextureMap("../res/rock.png");
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
		spr_mouse = sfw::loadTextureMap("../res/target.png");
		spr_portal = sfw::loadTextureMap("../res/portal.png", 4, 1);
		spr_imp = sfw::loadTextureMap("../res/imp.png",4,4);
		spr_impA = sfw::loadTextureMap("../res/imp_attack.png", 4,4);
		spr_impD = sfw::loadTextureMap("../res/imp_death.png", 4, 1);

		


	}

	virtual void play()
	{
		// Entity stats
		float impSpd = 25;
		float impMSpd = 50;
		float impHP = 10;
		float impRange = 5;
		float impDmg = 2;

		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });

		// call some spawning functions!
		factory.spawnStaticImage(spr_space, 0, 0, 800, 600);
		
		factory.spawnPlayer(spr_player, spr_font, true, 100);
		
	
		/*factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);*/
		factory.spawnImp(spr_imp, impSpd, impMSpd, impHP, impRange, impDmg);
		factory.spawnImp(spr_imp, impSpd, impMSpd, impHP, impRange, impDmg);
		count = 2;

		factory.spawnTransform({ 0,0 });
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

		for(auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference
			
			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			// AI
			for (auto bit = factory.begin(); bit != factory.end(); bit++)
			{
				// Tracking
				if (it != bit && bit->enemy && bit->transform->isEnemy && e.transform && e.transform->isPlayer && !e.transform->isPSpell)
				{
					bit->enemy->poll(&bit->transform, &bit->rigidbody, &e.transform, dt);

				}
				// Facing and sprite animation
				if (it != bit && bit->enemy && bit->transform->isEnemy && e.transform && e.transform->isPlayer && !e.transform->isPSpell)
				{
					float down = dot(bit->transform->getDir(&bit->transform, &e.transform), vec2{ -1,0 });
					float up = dot(bit->transform->getDir(&bit->transform, &e.transform), vec2{ 1,0 });
					float left = dot(bit->transform->getDir(&bit->transform, &e.transform), vec2{ 0,-1 });
					float right = dot(bit->transform->getDir(&bit->transform, &e.transform), vec2{ 0,1 });

					float face = fmaxf(fmaxf(down, up), fmaxf(left, right));
					if (face = up) dir = 0;
					if (face = down) dir = 2;
					if (face = left) dir = 1;
					if (face = right) dir = 3;

					frameTimer += frameRate * dt;
					frameID = frameTimer;
					bit->sprite->frame_id = frameID % 4 + dir * 4;
				}
			}
			

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
			}

			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			if (it->rigidbody && it->rigidbody->HP <= 0)
			{
				if (it->enemy)
					--count;
				del = true;
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

		
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for(auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				// if they aren't the same and they both have collidable bits...
				{
					if (it->transform->isPlayer == true && bit->transform->isPlayer == true)
						continue; // if the objects are both either the player and/or player created objects, ignore collision

					if (it->transform->isEnemy == true && bit->transform->isEnemy == true)
						continue;// if the objects are both either the enemy and/or enemy created objects, ignore collision
				
					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
						// if there was a collision,
						if (cd.result())
						{
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
};