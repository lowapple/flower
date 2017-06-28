#pragma once
#include "pch.h"

class Chapter3_Story_mini6 : public Layer
{
private:
	Sprite* story;
	int		story_cnt;
public:
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Chapter3_Story_mini6::create();
		scene->addChild(layer);
		return scene;
	}
	bool init() override
	{
		this->setTouchEnabled(true);
		this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

		story_cnt = 2;

		story = Sprite::create("chapter3/scene1/fin/2.png");
		story->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(story);
		return true;
	}
	bool onTouchBegan(Touch *touch, Event *unused_event) override
	{
		story_cnt++;
		if (story_cnt != 5)
			story->setTexture(StringUtils::format("chapter3/scene1/fin/%d.png", story_cnt));
		else
			Director::getInstance()->popScene();

		return true;
	}
	CREATE_FUNC(Chapter3_Story_mini6);
};