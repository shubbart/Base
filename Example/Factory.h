#pragma once

#include "Entity.h"

class Factory
{	
	ObjectPool<Entity>	  entities;
	
	// The factory will store an object pool for each component type
	ObjectPool<Transform> transforms;
	ObjectPool<Rigidbody> rigidbodies;
	ObjectPool<Collider>  colliders;
	ObjectPool<Sprite>    sprites;
	ObjectPool<Lifetime>  lifetimes;
	ObjectPool<Camera>    cameras;
	ObjectPool<Text>	  texts;
	ObjectPool<PlayerController> controllers;
	ObjectPool<Enemy> enemies;

public:

	// iterators to access the entity pool
	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }

	// for now, they're all the same size
	Factory(size_t size = 512)
								: entities(size), transforms(size), rigidbodies(size),
								  colliders(size), sprites(size), lifetimes(size),
								  cameras(size), controllers(size), texts(size), enemies(size)
	{
	}

	// What follows are specialized spawning functions
	// just observe the steps taken and replicate for your own usages

	ObjectPool<Entity>::iterator spawnCamera(float w2, float h2, float zoom)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->camera = cameras.push();
		e->camera->offset = vec2{w2,h2};
		e->camera->scale = vec2{ zoom,zoom };
		return e;
	}

	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{w,h};
		e->transform->setLocalPosition(vec2{ x,y });	
		return e;
	}

	ObjectPool<Entity>::iterator spawnFireball(unsigned sprite, vec2 pos, vec2 dim, float ang, vec2 impulse, unsigned faction, bool isPlayer = true)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();
		e->collider = colliders.push();

		e->transform->setLocalPosition(pos);
		e->transform->setLocalScale(dim);
		e->transform->setLocalAngle(ang);

		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{1.2f, 1.2f};
		

		e->rigidbody->addImpulse(impulse);


		e->lifetime->lifespan = 1.6f;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}

		
		return e;
	}

	ObjectPool<Entity>::iterator spawnPlayer(unsigned sprite, unsigned font, bool isPlayer = true)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->controller = controllers.push();
		e->text = texts.push();

		e->text->sprite_id = font;
		e->text->offset = vec2{ -24,-24 };
		e->text->off_scale = vec2{.5f,.5f};
		e->text->setString("Player1");

		e->transform->setLocalScale(vec2{48,48});

		e->sprite->sprite_id = sprite;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}
		return e;
	}


	ObjectPool<Entity>::iterator spawnAsteroid(unsigned sprite)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();

		e->transform->setLocalScale(vec2{ 48,48 });

		e->transform->setGlobalPosition(vec2::fromAngle(randRange(0, 360)*DEG2RAD)*(rand01() * 200 + 64));

		e->rigidbody->addSpin(rand01()*12-6);

		e->sprite->sprite_id = sprite;

		return e;
	}

	ObjectPool<Entity>::iterator spawnMouse(unsigned sprite_id)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->tint = RED;
		e->controller = controllers.push();
		e->transform->setLocalScale( vec2{25,25});
		e->sprite->sprite_id = sprite_id;


		return e;

	}

	ObjectPool<Entity>::iterator spawnPortal(unsigned sprite_id)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->controller = controllers.push();
		e->transform->setLocalScale(vec2{ 25,25 });
		e->sprite->sprite_id = sprite_id;


		return e;

	}

	ObjectPool<Entity>::iterator spawnImp(unsigned sprite, float speed, float health, float range)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->enemy = enemies.push();
		e->transform->setLocalScale(vec2{ 30,40 });
		e->transform->setGlobalPosition(vec2::fromAngle(randRange(0, 360)*DEG2RAD)*(rand01() * 200 + 64));

		e->sprite->sprite_id = sprite;
		e->enemy->speed = speed;
		e->enemy->health = health;
		e->enemy->range = range;

		return e;
	}

	ObjectPool<Entity>::iterator spawnTransform(vec2 pos, vec2 dims = {10,10}, float rot = 0)
	{
		auto e = entities.push();

		e->transform = transforms.push();

		e->transform->setGlobalPosition(pos);
		e->transform->setGlobalScale(dims);
		e->transform->setGlobalAngle(rot);

		return e;
	}
};


