#include "Chapter1_c2_backgame.h"
#include "Item.h"

Chapter1_c2_backgame::Chapter1_c2_backgame()
{
	nEvent = 0;
	log("Chapter1_c2");
}


Chapter1_c2_backgame::~Chapter1_c2_backgame()
{

}

bool Chapter1_c2_backgame::init()
{
	Sprite* background = Sprite::create("chapter1/scene2/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	Sprite* foot_print = Sprite::create("chapter1/scene2/footprint.png");
	MenuItemSprite* footprint_menu_button= MenuItemSprite::create(foot_print, foot_print->divSprite(0.988f),
	[&](Ref* sender)
	{
		nEvent = 1;
	});
	
	footprint_menu_button->setRotation(-8);
	footprint_menu_button->setPosition(Vec2(340, -15));
	footprint_menu_button->setAnchorPoint(Vec2(0.5f, 0.0f));
	
	Sprite* girls_sprite = Sprite::create("chapter1/scene2/girls.png");
	MenuItemSprite* girls_menu_button = MenuItemSprite::create(girls_sprite, girls_sprite->divSprite(0.98f),
	[&](Ref* sender)
	{

	});
	girls_menu_button->setPosition(Vec2(565, 240));

	menu = Menu::create(footprint_menu_button, girls_menu_button, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	choker = Item::createItem("chapter1/scene2/choker.png", Vec2(78,428), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"비싸보이는 목걸이다.", -1, MyString, 60, nullptr, nullptr);
		choker->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		choker->setStory(string("비싸보이는 목걸이다."));
	}
#endif
	this->addChild(choker);

	fruit = Item::createItem("chapter1/scene2/fruit.png", Vec2(1064, 207), this);
	fruit->setItemScale(0.6f);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"맛있어 보이진 않는다.", -1, MyString, 60, nullptr, nullptr);
		fruit->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		fruit->setStory(string("맛있어 보이진 않는다."));
	}
#endif
	this->addChild(fruit);
	return true;
}

void Chapter1_c2_backgame::update(float delta)
{

}

bool Chapter1_c2_backgame::onTouchStart(Touch* touch)
{
	if (choker->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		choker->enable();
	}
	else
	{
		choker->disable();
	}

	if (fruit->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		fruit->enable();
	}
	else
	{
		fruit->disable();
	}
	return true;
}
void Chapter1_c2_backgame::onTouchMove(Touch* touch)
{

}
void Chapter1_c2_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter1_c2_backgame::getEvent()
{
	return nEvent;
}
void Chapter1_c2_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter1_c2_backgame::menuPause()
{
	menu->setEnabled(false);
}

void Chapter1_c2_backgame::menuResume()
{
	menu->setEnabled(true);
}
