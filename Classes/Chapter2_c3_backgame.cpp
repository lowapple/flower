#include "Chapter2_c3_backgame.h"
#include "Item.h"

Chapter2_c3_backgame::Chapter2_c3_backgame()
{
	nEvent = 0;
	log("Chapter1_c1");
}


Chapter2_c3_backgame::~Chapter2_c3_backgame()
{

}

bool Chapter2_c3_backgame::init()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Background/scary.mp3");
	Sprite* background = Sprite::create("chapter2/scene3/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	Sprite* girls_sprite = Sprite::create("chapter2/scene3/girls.png");
	MenuItemSprite* girls = MenuItemSprite::create(girls_sprite, girls_sprite->divSprite(0.98),
	[&](Ref* sender)
	{

	});
	girls->setAnchorPoint(Vec2(1.0f, 0.0f));
	girls->setPosition(Vec2(WIDTH-100, 0.0f));

	bat = Item::createItem("chapter2/scene3/batman.png", Vec2(1169, 680), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"왜 그렇게 심각하나요?", -1, MyString, 60, nullptr, nullptr);
		bat->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		bat->setStory(string("왜 그렇게 심각하나요?"));
	}
#endif
	bat->getItem()->setFlipY(true);
	this->addChild(bat, 3);


	LayerColor* colorlayer = LayerColor::create(Color4B(0, 0, 0, 150));
	colorlayer->setPosition(Vec2::ZERO);
	colorlayer->setName("black_out");
	this->addChild(colorlayer,7);

	menu = Menu::create(girls, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}

void Chapter2_c3_backgame::update(float delta)
{

}

bool Chapter2_c3_backgame::onTouchStart(Touch* touch)
{
	Rect eye_rect = Rect(327, 327,680 - 327,716-32);
	if (eye_rect.containsPoint(touch->getLocation()))
	{
		isEye = true;
	}
	else
	{
		isEye = false;
	}

	if (bat->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		bat->getItem()->setFlipY(false);
		bat->enable();
	}
	else
	{
		bat->disable();
	}
	return true;
}
void Chapter2_c3_backgame::onTouchMove(Touch* touch)
{

}
void Chapter2_c3_backgame::onTouchEnd(Touch* touch)
{
	Rect eye_rect = Rect(327, 327, 680 - 327, 716 - 32);
	if (eye_rect.containsPoint(touch->getLocation()))
	{
		if (isEye)
		{
			nEvent = 1;
		}
		else
		{
			nEvent = 0;
		}
	}
}

int Chapter2_c3_backgame::getEvent()
{
	return nEvent;
}
void Chapter2_c3_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter2_c3_backgame::menuPause()
{
	menu->setEnabled(false);
}

void Chapter2_c3_backgame::menuResume()
{
	menu->setEnabled(true);
}