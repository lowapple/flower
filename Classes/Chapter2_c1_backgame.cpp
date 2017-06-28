#include "Chapter2_c1_backgame.h"
#include "Item.h"

Chapter2_c1_backgame::Chapter2_c1_backgame()
{
	nEvent = 0;
	log("Chapter1_c1");
}


Chapter2_c1_backgame::~Chapter2_c1_backgame()
{

}

bool Chapter2_c1_backgame::init()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Background/forest.mp3");
	Sprite* background = Sprite::create("chapter2/scene1/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	{
		int tempXpos = 150;
		int tempYpos = 370;

		for (int i = 0; i < 8; i++)
		{
			Sprite* moth = Sprite::create("chapter2/scene1/moth.png");
			moth->setPosition(tempXpos, tempYpos);
			moth->setTag(0);
			this->addChild(moth,2);

			ccBezierConfig bezierConfig;
			bezierConfig.controlPoint_1 = Point(moth->getPosition().x, moth->getPosition().y + randClass::rand(-50,50));
			bezierConfig.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-50, 50), moth->getPosition().y + randClass::rand(-50, 50));
			bezierConfig.endPosition = Point(moth->getPosition().x + randClass::rand(-50, 50), moth->getPosition().y);

			ccBezierConfig bezierConfig2;
			bezierConfig2.controlPoint_1 = Point(moth->getPosition().x + randClass::rand(-50,50), moth->getPosition().y + randClass::rand(-50,50));
			bezierConfig2.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-50,50), moth->getPosition().y + randClass::rand(-50,50));
			bezierConfig2.endPosition = Point(moth->getPosition().x, moth->getPosition().y);

			ccBezierConfig bezierConfig4;
			bezierConfig4.controlPoint_1 = Point(moth->getPosition().x + randClass::rand(-50,50), moth->getPosition().y +randClass::rand(-50,50));
			bezierConfig4.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-50,50), moth->getPosition().y +randClass::rand(-50,50));
			bezierConfig4.endPosition = Point(moth->getPosition().x, moth->getPosition().y);

			ccBezierConfig bezierConfig3;
			bezierConfig3.controlPoint_1 = Point(moth->getPosition().x + randClass::rand(-50,50), moth->getPosition().y + randClass::rand(-50,50));
			bezierConfig3.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-50,50), moth->getPosition().y + randClass::rand(-50,50));
			bezierConfig3.endPosition = Point(moth->getPosition().x, moth->getPosition().y);

			auto action = BezierTo::create(8.0, bezierConfig);
			moth->runAction(
				RepeatForever::create(Sequence::create(
				BezierTo::create(4.0f, bezierConfig),
				BezierTo::create(4.0f, bezierConfig3),
				BezierTo::create(4.0f, bezierConfig2),
				BezierTo::create(4.0f, bezierConfig),
				BezierTo::create(4.0f, bezierConfig4),
				BezierTo::create(4.0f, bezierConfig2),
				nullptr)));
		}
	}

	Sprite* girls_sprite = Sprite::create("chapter2/scene1/girls.png");
	// girls
	MenuItemSprite* girls = MenuItemSprite::create(girls_sprite, girls_sprite->divSprite(0.98),
		[=](Ref* sender)
	{
		nEvent = 1;
	});
	girls->setPosition(Vec2(190, 335));

	Sprite* man_sprite = Sprite::create("chapter2/scene1/man.png");
	// man
	MenuItemSprite* man = MenuItemSprite::create(man_sprite, man_sprite->divSprite(0.98),
		[](Ref* sender)
	{

	});
	man->setPosition(Vec2(492, 335));

	candy = Item::createItem("chapter2/scene1/candy.png", Vec2(365, 135), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"거대한 달팽이", -1, MyString, 60, nullptr, nullptr);
		candy->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		candy->setStory(string("거대한 달팽이"));
	}
#endif
	candy->setItemScale(1.3f);
	this->addChild(candy, 3);

	duck = Item::createItem("chapter2/scene1/duck.png", Vec2(705, 114), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"주인이 찾고 있겠지?", -1, MyString, 60, nullptr, nullptr);
		duck->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		duck->setStory(string("주인이 찾고 있겠지?"));
	}
#endif
	duck->setItemScale(1.3f);
	this->addChild(duck, 3);

	menu = Menu::create(girls, man,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}

void Chapter2_c1_backgame::update(float delta)
{

}

bool Chapter2_c1_backgame::onTouchStart(Touch* touch)
{
	if (candy->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		candy->enable();
	}
	else
	{
		candy->disable();
	}

	if (duck->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		duck->enable();
	}
	else
	{
		duck->disable();
	}

	return true;
}
void Chapter2_c1_backgame::onTouchMove(Touch* touch)
{

}
void Chapter2_c1_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter2_c1_backgame::getEvent()
{
	return nEvent;
}
void Chapter2_c1_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter2_c1_backgame::menuPause()
{
	menu->setEnabled(false);
}

void Chapter2_c1_backgame::menuResume()
{
	menu->setEnabled(true);
}