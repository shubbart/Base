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

	ObjectPool<Entity>::iterator spawnFire(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{ w,h };
		e->transform->setLocalPosition(vec2{ x,y });
		e->transform->isFire = true;
		return e;
	}

	ObjectPool<Entity>::iterator spawnFireball(unsigned sprite, vec2 pos, vec2 dim, float ang, vec2 impulse, float damage, unsigned faction, bool isPlayer = true)
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
		e->sprite->angle = PI;
		e->sprite->dimensions = vec2{1.2f, 1.2f};
		
		e->rigidbody->HP = 1;
		e->rigidbody->addImpulse(impulse);


		e->lifetime->lifespan = 1.6f;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}
		e->transform->isSpell = true;
		e->transform->isEnemy = false;
		e->rigidbody->damage = damage;

		return e;
	}

	ObjectPool<Entity>::iterator spawnShield(unsigned sprite, vec2 pos, vec2 dim, float damage, unsigned faction, bool isPlayer = true)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();
		e->collider = colliders.push();

		e->transform->setLocalPosition(pos);
		e->transform->setLocalScale(dim);

		e->sprite->sprite_id = sprite;

		e->rigidbody->HP = 20;
		e->rigidbody->mass = 500;

		e->lifetime->lifespan = 4.f;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}
		e->transform->isSpell = true;
		e->rigidbody->damage = damage;

		return e;
	}

	ObjectPool<Entity>::iterator spawnIceblast(unsigned sprite, vec2 pos, vec2 dim, float ang, vec2 impulse, float damage, unsigned faction, bool isPlayer = true)
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
		e->sprite->dimensions = vec2{ 1.2f, 1.2f };

		e->rigidbody->HP = 1;
		e->rigidbody->addImpulse(impulse);


		e->lifetime->lifespan = 3.5f;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}
		e->transform->isSpell = true;
		e->transform->isEnemy = false;
		e->rigidbody->damage = damage;

		e->transform->isIceblast = true;
		return e;
	}

	ObjectPool<Entity>::iterator spawnFR(unsigned sprite, vec2 pos, vec2 dim, unsigned faction, bool isPlayer = true)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();
		e->collider = colliders.push();

		e->transform->setLocalPosition(pos);
		e->transform->setLocalScale(dim);
		e->sprite->dimensions = vec2{ 1.2f, 1.2f };
		e->sprite->tint = RED;

		e->sprite->sprite_id = sprite;

		e->rigidbody->HP = 1;

		e->lifetime->lifespan = 5.f;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}
		e->transform->isSpell = true;
		e->transform->isRune = true;
		return e;
	}

	ObjectPool<Entity>::iterator spawnDB(unsigned sprite, vec2 pos, vec2 dim, float ang, vec2 impulse, float damage, unsigned faction, bool isPlayer = true)
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
		e->sprite->tint = GREEN;
		e->sprite->dimensions = vec2{ 3.0f, 3.0f };

		e->rigidbody->HP = 1;
		e->rigidbody->addImpulse(impulse);


		e->lifetime->lifespan = 2.0f;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}
		e->transform->isSpell = true;
		e->transform->isEnemy = false;
		e->rigidbody->damage = damage;
		e->transform->isDB = true;
		return e;
	}

	ObjectPool<Entity>::iterator spawnPlayer(unsigned sprite, unsigned font, bool isPlayer, float health)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->controller = controllers.push();

		e->transform->setLocalScale(vec2{48,48});
		e->rigidbody->HP = health;
		e->rigidbody->damage = 10;

		e->sprite->sprite_id = sprite;
		if (isPlayer == true)
		{
			e->transform->setPlayer();
		}

		e->transform->PlayerIsAlive = true;
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

	ObjectPool<Entity>::iterator spawnPortal(unsigned sprite_id, float posX, float posY, float scaleX, float scaleY)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->transform->setLocalPosition(vec2{ posX,posY });
		e->sprite = sprites.push();
		e->transform->setLocalScale(vec2{ scaleX,scaleY });
		e->sprite->sprite_id = sprite_id;
		e->transform->isPortal = true;
		e->rigidbody = rigidbodies.push();
		e->rigidbody->HP = 100;

		return e;
	}

	ObjectPool<Entity>::iterator spawnImp(unsigned sprite, float speed, float maxSpeed, float health, float range, float damage, float posX, float posY, float dimX, float dimY)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->enemy = enemies.push();
		e->transform->setLocalScale(vec2{ dimX, dimY });
		e->transform->setLocalPosition(vec2{ posX,posY });

		e->sprite->sprite_id = sprite;
		e->enemy->speed = speed;
		e->enemy->maxSpeed = maxSpeed;
		e->rigidbody->HP = health;
		e->enemy->range = range;
		e->transform->isEnemy = true;
		e->transform->isPlayer = false;
		e->rigidbody->damage = damage;
		return e;
	}

	ObjectPool<Entity>::iterator spawnMage(unsigned sprite, float speed, float maxSpeed, float health, float range, float damage, float posX, float posY, float dimX, float dimY)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->enemy = enemies.push();
		e->transform->setLocalScale(vec2{ dimX, dimY });
		e->transform->setLocalPosition(vec2{ posX,posY });

		e->sprite->sprite_id = sprite;
		e->enemy->speed = speed;
		e->enemy->maxSpeed = maxSpeed;
		e->rigidbody->HP = health;
		e->enemy->range = range;
		e->transform->isEnemy = true;
		e->transform->isPlayer = false;
		e->rigidbody->damage = damage;
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


