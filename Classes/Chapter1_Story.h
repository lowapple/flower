#pragma once
#include "pch.h"
#include "Chapter1.h"

class Chapter1_Story : public Layer
{
private:
	Sprite* story;
	int		story_cnt;
public:
	static Scene* createScene()
	{
		Scene* scene = Scene::create();
		Layer* layer = Chapter1_Story::create();
		scene->addChild(layer);
		return scene;
	}
	bool init()
	{
		this->setTouchEnabled(true);
		this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

		story_cnt = UserDefault::getInstance()->getIntegerForKey("CHAPTER1_STORY");

		story = Sprite::create(StringUtils::format("chapter1/fin/%d.png", story_cnt));
		story->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(story);

		return true;
	}
	bool onTouchBegan(Touch *touch, Event *unused_event)
	{
		story_cnt += 1;

		if (story_cnt >= 14)
			story_cnt = 14;

		if (story_cnt == 14)
		{
			BGM_PAGE;
			Director::getInstance()->replaceScene(TransitionPageTurn::create(0.4, Chapter1::createScene(), false));
		}
		else
		{
			BGM_PAGE2;
			UserDefault::getInstance()->setIntegerForKey("CHAPTER1_STORY", story_cnt);
			Director::getInstance()->replaceScene(TransitionPageTurn::create(0.4f, Chapter1_Story::createScene(), false));
		}
		return true;
	}

	CREATE_FUNC(Chapter1_Story);
};