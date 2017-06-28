#pragma once
#include "pch.h"

class Chapter1_Story_mini2 : public Layer
{
private:
	Sprite* story;
	int		story_cnt;
public:
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Chapter1_Story_mini2::create();
		scene->addChild(layer);
		return scene;
	}
	bool init() override
	{
		this->setTouchEnabled(true);
		this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

		story_cnt = 1;

		story = Sprite::create("chapter1/scene2/fin/1.png");
		story->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(story);
		return true;
	}
	bool onTouchBegan(Touch *touch, Event *unused_event) override
	{
		story_cnt++;
		if (story_cnt != 6){
			BGM_PAGE3;
			story->setTexture(StringUtils::format("chapter1/scene2/fin/%d.png", story_cnt));
		}
		else
			Director::getInstance()->popScene();

		return true;
	}
	CREATE_FUNC(Chapter1_Story_mini2);
};