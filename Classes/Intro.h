#pragma once
#include "pch.h"
#include "MainMenu.h"

class Intro : public Layer
{
public:
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Intro::create();

		scene->addChild(layer);
		return scene;
	}
	bool init() override
	{
		Sprite* background = Sprite::create("common/Intro.png");
		background->setPosition(DEVICE_CENTER);
		this->addChild(background);

		this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([&](){Director::getInstance()->replaceScene(TransitionFade::create(1.5f, MainMenu::createScene())); }),nullptr));
		return true;
	}
	CREATE_FUNC(Intro);
};
