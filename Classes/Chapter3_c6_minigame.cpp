#include "Chapter3_c6_minigame.h"
#include "GameResult.h"

Chapter3_c6_minigame::Chapter3_c6_minigame()
{
	_touch_enable = false;
}


Chapter3_c6_minigame::~Chapter3_c6_minigame()
{
}

bool Chapter3_c6_minigame::init()
{
	Sprite* background = Sprite::create("chapter3/scene6/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background,1);

	_girls = Sprite::create("chapter3/scene6/mini/girls.png");
	_girls->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 - 50));
	this->addChild(_girls,2);

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 6);

	return true;
}
void Chapter3_c6_minigame::update(float dt)
{
	if (_touch_enable)
	{
		Vec2 imgPos = _girls->getPosition();
		Vec2 interval = Vec2(_touch_position.x - imgPos.x, _touch_position.y - imgPos.y);

		if (interval.x > -5.f && interval.x < 5.f &&
			interval.y > -5.f && interval.y < 5.f)
			return;

		float radian = atan2(interval.y, interval.x);
		Vec2 move = Vec2(cos(radian) * 600 * dt,sin(radian)* 600 * dt);
		_girls->setPosition(imgPos + move);

		//-------------------------------
		float gs = Lerp(_girls->getScale(), _touch_scale, dt);
		_girls->setScale(gs);
	}
}
bool Chapter3_c6_minigame::onTouchStart(Touch* touch)
{
	_touch_position = touch->getLocation();
	_touch_enable = true;

	float tm = ((HEIGHT - touch->getLocation().y)+ 500) / 1000;
	log("size : %.3f", tm);
	_touch_scale = tm;
	//_girls->setScale(tm);
	return true;
}
void Chapter3_c6_minigame::onTouchMove(Touch* touch)
{

}
void Chapter3_c6_minigame::onTouchEnd(Touch* touch)
{

}
int Chapter3_c6_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter3_c6_minigame::MiniGameStateReset()
{
	gameresult->reset();
}