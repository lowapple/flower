#include "Chapter2_c2_backgame.h"
#include "Item.h"

Chapter2_c2_backgame::Chapter2_c2_backgame()
{
	nEvent = 0;
}


Chapter2_c2_backgame::~Chapter2_c2_backgame()
{
	
}

bool Chapter2_c2_backgame::init()
{
	door = false;
	Sprite* background = Sprite::create("chapter2/scene2/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	Sprite* girls_sprite = Sprite::create("chapter2/scene2/girls.png");
	MenuItemSprite* girls = MenuItemSprite::create(girls_sprite, girls_sprite->divSprite(0.98),
	[&](Ref* sender)
	{

	});
	girls->setPosition(Vec2(240, 402));

	Sprite* match_lantern = Sprite::create("chapter2/scene2/match.png");
	MenuItemSprite* match = MenuItemSprite::create(match_lantern, match_lantern->divSprite(0.9755),
	[&](Ref* sender)
	{
		nEvent = 1;
	});
	match->setPosition(Vec2(1129, 195));

	shovel = Item::createItem("chapter2/scene2/shovel.png", Vec2(400, 600), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"¾ÆÀú¾¾ÀÇ ³°Àº »ğÀÌ´Ù.", -1, MyString, 60, nullptr, nullptr);
		shovel->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		shovel->setStory(string("¾ÆÀú¾¾ÀÇ ³°Àº »ğÀÌ´Ù."));
	}
#endif
	shovel->setItemScale(0.5f);
	shovel->getItem()->setRotation(90);
	this->addChild(shovel, 3);

	web = Item::createItem("chapter2/scene2/web.png", Vec2(100, 680), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"¿À·¡µÈ ÁıÀÎ°Í °°´Ù.", -1, MyString, 60, nullptr, nullptr);
		web->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		web->setStory(string("¿À·¡µÈ ÁıÀÎ°Í °°´Ù."));
	}
#endif
	this->addChild(web, 3);


	calender = Item::createItem("chapter2/scene2/calender.png", Vec2(1205, 300), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"5/20ÀÏ?\n¹«½¼ ³¯ÀÌÁö?", -1, MyString, 60, nullptr, nullptr);
		calender->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		calender->setStory(string("5/20ÀÏ?\n¹«½¼ ³¯ÀÌÁö?"));
	}
#endif
	this->addChild(calender, 3);

	menu = Menu::create(girls, match, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,2);
	return true;
}

void Chapter2_c2_backgame::update(float delta)
{

}

bool Chapter2_c2_backgame::onTouchStart(Touch* touch)
{
	Rect door_rect = Rect(675, 530, 853 - 675, 718 - 530);
	if (door_rect.containsPoint(touch->getLocation()))
	{
		door = true;
	}
	else
	{
		door = false;
	}

	if (web->getItem()->getBoundingBox().containsPoint(touch->getLocation()) == true)
	{
		web->enable();
	}
	else
	{
		web->disable();
	}

	if (shovel->getItem()->getBoundingBox().containsPoint(touch->getLocation()) == true)
	{
		shovel->enable();
	}
	else
	{
		shovel->disable();
	}

	if (calender->getItem()->getBoundingBox().containsPoint(touch->getLocation()) == true)
	{
		calender->enable();
	}
	else
	{
		calender->disable();
	}
	return true;
}
void Chapter2_c2_backgame::onTouchMove(Touch* touch)
{

}
void Chapter2_c2_backgame::onTouchEnd(Touch* touch)
{
	Rect door_rect = Rect(675, 530, 853 - 675, 718 - 530);
	if (door_rect.containsPoint(touch->getLocation()))
	{
		if (door)
		{
			SimpleAudioEngine::getInstance()->playEffect("BGM/scale_door.mp3");
			SimpleAudioEngine::getInstance()->setEffectsVolume(0.3f);
		}
	}
	else
	{
		door = false;
	}
}

int Chapter2_c2_backgame::getEvent()
{
	return nEvent;
}
void Chapter2_c2_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter2_c2_backgame::menuPause()
{
	menu->setEnabled(false);
}

void Chapter2_c2_backgame::menuResume()
{
	menu->setEnabled(true);
}