#include "Chapter3_c4_backgame.h"
#include "Item.h"

Chapter3_c4_backgame::Chapter3_c4_backgame()
{
	nEvent = 0;
}


Chapter3_c4_backgame::~Chapter3_c4_backgame()
{

}

bool Chapter3_c4_backgame::init()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Background/cave.mp3");
	Sprite* background = Sprite::create("chapter3/scene4/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	EventBlock = false;

	rope = Item::createItem("chapter3/scene4/rope.png", Vec2(467, 335), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[100];
		WideCharToMultiByte(CP_UTF8, 0, L"¿Ö ÀÌ·±°Ô\nµ¿±¼¾È¿¡ ÀÖÀ»±î?\n¹º°¡ ¼¶¶àÇØ..", -1, MyString, 100, nullptr, nullptr);
		rope->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		rope->setStory(string("¿Ö ÀÌ·±°Ô\nµ¿±¼¾È¿¡ ÀÖÀ»±î?\n¹º°¡ ¼¶¶àÇØ.."));
	}
#endif
	this->addChild(rope, 3);
	return true;
}

void Chapter3_c4_backgame::update(float delta)
{

}

bool Chapter3_c4_backgame::onTouchStart(Touch* touch)
{
	Rect rect = Rect(257, 363, 330, 200);
	if (rect.containsPoint(touch->getLocation()))
	{
		if (!EventBlock){
			nEvent = 1;
		}
	}

	if (rope->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		EventBlock = true;
		rope->enable();
	}
	else
	{
		EventBlock = false;
		rope->disable();
	}
	return true;
}
void Chapter3_c4_backgame::onTouchMove(Touch* touch)
{

}
void Chapter3_c4_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter3_c4_backgame::getEvent()
{
	return nEvent;
}
void Chapter3_c4_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter3_c4_backgame::menuPause()
{
	//menu->setEnabled(false);
}

void Chapter3_c4_backgame::menuResume()
{
	//menu->setEnabled(true);
}