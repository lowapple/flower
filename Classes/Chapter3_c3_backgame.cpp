#include "Chapter3_c3_backgame.h"
#include "Item.h"

Chapter3_c3_backgame::Chapter3_c3_backgame()
{
	nEvent = 0;
}


Chapter3_c3_backgame::~Chapter3_c3_backgame()
{

}

bool Chapter3_c3_backgame::init()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Background/stage3_3.mp3");
	Sprite* background = Sprite::create("chapter3/scene3/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	pickaxe= Item::createItem("chapter3/scene3/pickaxe.png", Vec2(1236, 460), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"단단히 박혀서\n빠지지 않는다.", -1, MyString, 60, nullptr, nullptr);
		pickaxe->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		pickaxe->setStory(string("단단히 박혀서 빠지지 않는다."));
	}
#endif
	this->addChild(pickaxe, 3);
	
	return true;
}

void Chapter3_c3_backgame::update(float delta)
{

}

bool Chapter3_c3_backgame::onTouchStart(Touch* touch)
{
	Rect bounding = Rect(464, 152, 200, 300);
	if (bounding.containsPoint(touch->getLocation()))
	{
		nEvent = 1;
	}
	if (pickaxe->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		pickaxe->setItemScale(0.7f);
		pickaxe->enable();
	}
	else
	{
		pickaxe->disable();
	}

	return true;
}
void Chapter3_c3_backgame::onTouchMove(Touch* touch)
{

}
void Chapter3_c3_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter3_c3_backgame::getEvent()
{
	return nEvent;
}
void Chapter3_c3_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter3_c3_backgame::menuPause()
{
	//menu->setEnabled(false);
}

void Chapter3_c3_backgame::menuResume()
{
	//menu->setEnabled(true);
}