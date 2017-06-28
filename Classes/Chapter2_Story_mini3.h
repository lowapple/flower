#pragma once
#include "pch.h"

class Chapter2_Story_mini3 : public Layer
{
private:
	Sprite* story;
	int		story_cnt;
public:
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Chapter2_Story_mini3::create();
		scene->addChild(layer);
		return scene;
	}
	bool init() override
	{
		this->setTouchEnabled(true);
		this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

		story_cnt = 3;

		story = Sprite::create("chapter2/scene3/fin/3.png");
		story->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(story);
		return true;
	}
	bool onTouchBegan(Touch *touch, Event *unused_event) override
	{
		story_cnt++;
		if (story_cnt != 7)
			story->setTexture(StringUtils::format("chapter2/scene3/fin/%d.png", story_cnt));
		else
			Director::getInstance()->popScene();

		return true;
	}
	CREATE_FUNC(Chapter2_Story_mini3);
};