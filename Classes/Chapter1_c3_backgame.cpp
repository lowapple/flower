#include "Chapter1_c3_backgame.h"
#include "Item.h"

Chapter1_c3_backgame::Chapter1_c3_backgame()
{
	nEvent = 0;
	log("Chapter1_c3");
}


Chapter1_c3_backgame::~Chapter1_c3_backgame()
{

}

bool Chapter1_c3_backgame::init()
{
	Sprite* background = Sprite::create("chapter1/scene3/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	// move grass
	MenuItemImage* moveGrass_menu_button = MenuItemImage::create("chapter1/scene3/moveGrass.png", "chapter1/scene3/moveGrass.png",
	[&](Ref* sender)
	{
		nEvent = 1;
	});
	moveGrass_menu_button->setPosition(Vec2(1008, 365));
	moveGrass_menu_button->setRotation(30.f);
	moveGrass_menu_button->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(0.05, Vec2(3.0f, -3.0f)),
		MoveBy::create(0.05f, Vec2(-3.0f, 3.0f)),
		DelayTime::create(1.5f), nullptr)));

	button = Menu::create(moveGrass_menu_button, nullptr);
	button->setPosition(Vec2::ZERO);
	this->addChild(button, 2);

	flower = Item::createItem("chapter1/scene3/flower.png", Vec2(550, 500), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"어머 꽃이네?", -1, MyString, 60, nullptr, nullptr);
		flower->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		flower->setStory(string("어머 꽃이네?"));
	}
#endif
	this->addChild(flower, 2);

	scissor = Item::createItem("chapter1/scene3/scissor.png", Vec2(370, 90), this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"가위, 바위, 보 ...?", -1, MyString, 60, nullptr, nullptr);
		scissor->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		scissor->setStory(string("가위, 바위, 보 ...?"));
	}
#endif
	this->addChild(scissor, 2);


	_string = Item::createItem("chapter1/scene3/string.png", Vec2(954, 72), this);
	_string->setItemScale(0.5f);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"주변에 고양이가 있나보다..", -1, MyString, 60, nullptr, nullptr);
		_string->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		_string->setStory(string("주변에 고양이가 있나보다.."));
	}
#endif
	this->addChild(_string, 2);

	Sprite* man_sprite = Sprite::create("chapter1/scene3/man.png");
	man_sprite->setPosition(262, 340);
	this->addChild(man_sprite);
	man_sprite->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.6f), CallFuncN::create([&](Node* pSender)
	{
		static bool face;
		if (!face)
			face = true;
		else
			face = false;
		static_cast<Sprite*>(pSender)->setFlipX(face);
	}), nullptr)));

	return true;
}

void Chapter1_c3_backgame::update(float delta)
{

}

bool Chapter1_c3_backgame::onTouchStart(Touch* touch)
{
	if (scissor->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		scissor->enable();
	}
	else
	{
		scissor->disable();
	}

	if (flower->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		flower->enable();
	}
	else
	{
		flower->disable();
	}

	if (_string->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		_string->enable();
	}
	else
	{
		_string->disable();
	}
	return true;
}
void Chapter1_c3_backgame::onTouchMove(Touch* touch)
{

}
void Chapter1_c3_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter1_c3_backgame::getEvent()
{
	return nEvent;
}

void Chapter1_c3_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter1_c3_backgame::menuPause()
{
	button->setEnabled(false);
}

void Chapter1_c3_backgame::menuResume()
{
	button->setEnabled(true);
}