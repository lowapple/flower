#include "Chapter3_c4_minigame.h"
#include "GameResult.h"

Chapter3_c4_minigame::Chapter3_c4_minigame()
{
}


Chapter3_c4_minigame::~Chapter3_c4_minigame()
{
}

bool Chapter3_c4_minigame::init()
{
	Sprite* background = Sprite::create("chapter3/scene4/mini/background.png");
	background->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(background);

	exit_sprite = Sprite::create("chapter3/scene4/mini/exit.png");
	exit_sprite->setPosition(Vec2(292, 593));
	this->addChild(exit_sprite);

	nEvent = 0;

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 10);
	return true;
}
void Chapter3_c4_minigame::update(float dt)
{

}
bool Chapter3_c4_minigame::onTouchStart(Touch* touch)
{
	Sprite* point = Sprite::create("chapter3/scene4/mini/point.png");
	point->setPosition(touch->getLocation());
	this->addChild(point);

	points.pushBack(point);
	return true;
}
void Chapter3_c4_minigame::onTouchMove(Touch* touch)
{
	Sprite* point = Sprite::create("chapter3/scene4/mini/point.png");
	point->setPosition(touch->getLocation());
	this->addChild(point);

	points.pushBack(point);
}
void Chapter3_c4_minigame::onTouchEnd(Touch* touch)
{
	if (point_to_clear())
	{
		if (nEvent == 1)
			gameresult->CLEAR();
	}
	else
	{
		if (nEvent == 2)
			gameresult->FAIL();
	}
}
int Chapter3_c4_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter3_c4_minigame::MiniGameStateReset()
{
	points.clear();
	nEvent = 0;
	gameresult->reset();
}

bool Chapter3_c4_minigame::point_to_clear()
{
	//log("%d", points.size());
	if (points.size() <= 5)
		return false;

	for (int i = 0; i < points.size(); i++)
	{
		if (points.size() <= 150)
		{
			if (exit_sprite->getBoundingBox().intersectsRect(points.at(1)->getBoundingBox()) && exit_sprite->getBoundingBox().intersectsRect(points.back()->getBoundingBox()))
			{
				nEvent = 1;
				return true;
			}
			else
			{
				this->removeChild(points.at(i));
			}
		}
		else
		{
			this->removeChild(points.at(i));
		}
	}
	points.clear();
	nEvent = 3;
}