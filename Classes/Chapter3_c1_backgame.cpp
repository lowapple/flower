#include "Chapter3_c1_backgame.h"
#include "Item.h"

Chapter3_c1_backgame::Chapter3_c1_backgame()
{
	nEvent = 0;
}


Chapter3_c1_backgame::~Chapter3_c1_backgame()
{

}

bool Chapter3_c1_backgame::init()
{
	Sprite* background = Sprite::create("chapter3/scene1/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	Sprite* binding_sprite = Sprite::create("chapter3/scene1/binding.png");
	MenuItemSprite* binding = MenuItemSprite::create(binding_sprite, binding_sprite->divSprite(0.98),
	[&](Ref* sender)
	{
		nEvent = 1;
	});

	binding->setPosition(Vec2(698, 390));
	menu = Menu::create(binding, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	doll = Item::createItem("chapter3/scene1/doll.png", Vec2(450, 154), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"ÁÁÀº Ä£±¸¿´À»ÅÙµ¥..", -1, MyString, 60, nullptr, nullptr);
		doll->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		doll->setStory(string("ÁÁÀº Ä£±¸¿´À»ÅÙµ¥.."));
	}
#endif
	this->addChild(doll, 3);

	snail = Item::createItem("chapter3/scene1/snail.png", Vec2(1236, 460), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"´«À» ÄÛÄÛ", -1, MyString, 60, nullptr, nullptr);
		snail->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		snail->setStory(string("´«À» ÄÛÄÛ"));
	}
#endif
	this->addChild(snail, 3);

	Sprite* girls = Sprite::create("chapter3/scene1/girls.png");
	girls->setPosition(Vec2(677, 135));
	this->addChild(girls);
	return true;
}

void Chapter3_c1_backgame::update(float delta)
{

}

bool Chapter3_c1_backgame::onTouchStart(Touch* touch)
{
	if (snail->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		snail->enable();
	}
	else
	{
		snail->disable();
	}

	if (doll->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		doll->enable();
	}
	else
	{
		doll->disable();
	}

	return true;
}
void Chapter3_c1_backgame::onTouchMove(Touch* touch)
{

}
void Chapter3_c1_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter3_c1_backgame::getEvent()
{
	return nEvent;
}
void Chapter3_c1_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter3_c1_backgame::menuPause()
{
	menu->setEnabled(false);
}

void Chapter3_c1_backgame::menuResume()
{
	menu->setEnabled(true);
}