#include "Chapter3_c5_backgame.h"
#include "Item.h"

Chapter3_c5_backgame::Chapter3_c5_backgame()
{
	nEvent = 0;
}


Chapter3_c5_backgame::~Chapter3_c5_backgame()
{

}

bool Chapter3_c5_backgame::init()
{
	Sprite* background = Sprite::create("chapter3/scene5/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	axe = Item::createItem("chapter3/scene5/axe.png", Vec2(161, 172), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"그대가 나의 마스터인가?", -1, MyString, 60, nullptr, nullptr);
		axe->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		axe->setStory(string("그대가 나의 마스터인가?"));
	}
#endif
	axe->setItemScale(0.45f);
	axe->getItem()->setRotation(-45);
	this->addChild(axe, 3);
	return true;
}

void Chapter3_c5_backgame::update(float delta)
{

}

bool Chapter3_c5_backgame::onTouchStart(Touch* touch)
{
	Rect rect = Rect(911, 125, 60, 370);
	if (rect.containsPoint(touch->getLocation()))
	{
		isPressed = true;
		//nEvent = 1;
	}

	if (axe->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		axe->enable();
	}
	else
	{
		axe->disable();
	}
	return true;
}
void Chapter3_c5_backgame::onTouchMove(Touch* touch)
{

}
void Chapter3_c5_backgame::onTouchEnd(Touch* touch)
{
	Rect rect = Rect(911, 125, 60, 370);
	if (rect.containsPoint(touch->getLocation()))
	{
		if (isPressed)
		{
			isPressed = false;
			nEvent = 1;
		}
	}
}

int Chapter3_c5_backgame::getEvent()
{
	return nEvent;
}
void Chapter3_c5_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter3_c5_backgame::menuPause()
{

}

void Chapter3_c5_backgame::menuResume()
{

}