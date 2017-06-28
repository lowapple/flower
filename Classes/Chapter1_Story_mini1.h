#pragma once
#include "pch.h"

class Chapter1_Story_mini1 : public Layer
{
private:
	Sprite* story;
	int		story_cnt;
public:
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Chapter1_Story_mini1::create();
		scene->addChild(layer);
		return scene;
	}
	bool init() override
	{
		this->setTouchEnabled(true);
		this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

		story_cnt = 1;

		story = Sprite::create("chapter1/scene1/fin/1.png");
		story->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(story);
		return true;
	}
	bool onTouchBegan(Touch *touch, Event *unused_event) override
	{
		story_cnt += 1;
		switch (story_cnt)
		{
		case 2:
			story->setTexture("chapter1/scene1/fin/2.png");
			break;
		case 3:
			story->setTexture("chapter1/scene1/fin/3.png");
			break;
		case 4:
			story->setTexture("chapter1/scene1/fin/4.png");
			break;
		case 5:
			story->setTexture("chapter1/scene1/fin/5.png");
			break;
		case 6:
			story->setTexture("chapter1/scene1/fin/6.png");
			break;
		case 7:
			Director::getInstance()->popScene();
			break;
		default:
			break;
		}
		return true;
	}

	CREATE_FUNC(Chapter1_Story_mini1);
};