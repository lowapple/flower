#include "Chapter2_c4_backgame.h"
#include "Item.h"

Chapter2_c4_backgame::Chapter2_c4_backgame()
{
	nEvent = 0;
	log("Chapter1_c1");
}


Chapter2_c4_backgame::~Chapter2_c4_backgame()
{

}

bool Chapter2_c4_backgame::init()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Background/main.mp3");
	Sprite* background = Sprite::create("chapter2/scene4/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	Sprite* girls_man_sprite = Sprite::create("chapter2/scene4/girls_man.png");
	MenuItemSprite* girls_man = MenuItemSprite::create(girls_man_sprite, girls_man_sprite->divSprite(0.98),
		[&](Ref* sender)
	{
		nEvent = 1;
	});
	girls_man->setPosition(Vec2(755, 478));
	girls_man->setAnchorPoint(Vec2(1.0f, 0.0f));

	broken_frame = Item::createItem("chapter2/scene4/broken_frame.png", Vec2(365, 490), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"¾×ÀÚ¸¦ ±ú¶ß·Á ¹ö·È´Ù.", -1, MyString, 60, nullptr, nullptr);
		broken_frame->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		broken_frame->setStory(string("¾×ÀÚ¸¦ ±ú¶ß·Á ¹ö·È´Ù."));
	}
#endif
	broken_frame->getItem()->setFlipY(false);
	broken_frame->setItemScale(0.5f);
	this->addChild(broken_frame, 2);

	menu = Menu::create(girls_man, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}

void Chapter2_c4_backgame::update(float delta)
{

}

bool Chapter2_c4_backgame::onTouchStart(Touch* touch)
{
	if (broken_frame->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		broken_frame->enable();
	}
	else
	{
		broken_frame->disable();
	}
	return true;
}
void Chapter2_c4_backgame::onTouchMove(Touch* touch)
{

}
void Chapter2_c4_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter2_c4_backgame::getEvent()
{
	return nEvent;
}
void Chapter2_c4_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter2_c4_backgame::menuPause()
{

}

void Chapter2_c4_backgame::menuResume()
{

}