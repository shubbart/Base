#pragma once
#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"

class Level5Splash : public BaseState
{
	Factory factory;
	unsigned spr_logo;
	ObjectPool<Entity>::iterator currentCamera;
	unsigned spr_mouse = sfw::loadTextureMap("../res/target.png");
	float timer;
	float timeRate;
public:
	virtual void init() { spr_logo = sfw::loadTextureMap("../res/lvl5splash.png"); };
	virtual void term() {};
	virtual void play()
	{
		timer = 0;
		timeRate = 1;
		factory.spawnStaticImage(spr_logo, 0, 0, 800, 600);
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 400,300 });
	};
	virtual void stop() {};

	virtual size_t next() const
	{

		if (timer >= 3)
			return LEVEL_5;
		return LVL5SPLASH;
	};

	virtual void step()
	{
		float dt = sfw::getDeltaTime();
		timer += timeRate * dt;
	};

	virtual void draw()
	{
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);
		sfw::drawTexture(spr_mouse, sfw::getMouseX(), sfw::getMouseY(), 25, 25, 0.f, true, 0U, RED);
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, cam);
	};
};


