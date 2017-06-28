#include "Chapter3_c6_backgame.h"
#include "Item.h"

Chapter3_c6_backgame::Chapter3_c6_backgame()
{
	nEvent = 0;
}


Chapter3_c6_backgame::~Chapter3_c6_backgame()
{

}

bool Chapter3_c6_backgame::init()
{
	Sprite* background = Sprite::create("chapter3/scene6/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	return true;
}

void Chapter3_c6_backgame::update(float delta)
{

}

bool Chapter3_c6_backgame::onTouchStart(Touch* touch)
{
	Rect rect = Rect(422, 4, 100, 300);
	if (rect.containsPoint(touch->getLocation()))
	{
		//nEvent = 1;
		isPressed = true;
	}
	return true;
}
void Chapter3_c6_backgame::onTouchMove(Touch* touch)
{

}
void Chapter3_c6_backgame::onTouchEnd(Touch* touch)
{
	if (isPressed)
	{
		isPressed = false;
		nEvent = 1;
	}
}

int Chapter3_c6_backgame::getEvent()
{
	return nEvent;
}
void Chapter3_c6_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter3_c6_backgame::menuPause()
{

}

void Chapter3_c6_backgame::menuResume()
{

}