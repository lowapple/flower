#include "Chapter1_c1_backgame.h"
#include "Item.h"

Chapter1_c1_backgame::Chapter1_c1_backgame()
{
	nEvent = 0;
	log("Chapter1_c1");
}


Chapter1_c1_backgame::~Chapter1_c1_backgame()
{

}

bool Chapter1_c1_backgame::init()
{
	// background
	Sprite* background = Sprite::create("chapter1/scene1/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);


	Sprite* man_sprite = Sprite::create("chapter1/scene1/man.png");
	// man button
	MenuItemSprite* man_menu_button = MenuItemSprite::create(man_sprite, man_sprite->divSprite(0.988f),
		[&](Ref* sender)
	{
		log("man button");
	});
	man_menu_button->setPosition(Vec2(500, 0));
	man_menu_button->setAnchorPoint(Vec2(0.5f, 0.0f));



	Sprite* girls_sprite = Sprite::create("chapter1/scene1/girls.png");
	// girls_button
	MenuItemSprite* girls_menu_button = MenuItemSprite::create(girls_sprite, girls_sprite->divSprite(0.988f),
		[&](Ref* sender)
	{
		log("girls button");
		nEvent = 1;
	});
	girls_menu_button->setPosition(Vec2(560, -25));
	girls_menu_button->setAnchorPoint(Vec2::ZERO);

	// object
	news = Item::createItem("chapter1/scene1/news.png", Vec2(871, 408), this);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		char MyString[60];
		WideCharToMultiByte(CP_UTF8, 0, L"긴장감 고조, 전쟁!?\n4일전 신문이다.", -1, MyString, 60, nullptr, nullptr);
		news->setStory(MyString);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		news->setStory(string("긴장감 고조, 전쟁!?\n4일전 신문이다."));
	}
#endif
	this->addChild(news, 4);

	Sprite* butterfly_sprite = Sprite::create("common/buf_1.png");
	butterfly_sprite->setPosition(Vec2(878, 217));
	this->addChild(butterfly_sprite,3);

	Animation* buf_animate = Animation::create();
	buf_animate->setDelayPerUnit(0.2f);
	buf_animate->addSpriteFrameWithFileName("common/buf_1.png");
	buf_animate->addSpriteFrameWithFileName("common/buf_2.png");
	buf_animate->addSpriteFrameWithFileName("common/buf_3.png");
	buf_animate->addSpriteFrameWithFileName("common/buf_4.png");
	buf_animate->addSpriteFrameWithFileName("common/buf_3.png");
	buf_animate->addSpriteFrameWithFileName("common/buf_2.png");

	butterfly_sprite->runAction(RepeatForever::create(Animate::create(buf_animate)));
	butterfly_sprite->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.8f, Vec2(0, 10.0f)), MoveBy::create(0.8f, Vec2(0, -10.0f)), nullptr)));
	human = Menu::create(man_menu_button, girls_menu_button, nullptr);
	human->setPosition(Vec2::ZERO);
	this->addChild(human);
	return true;
}

void Chapter1_c1_backgame::update(float delta)
{

}

bool Chapter1_c1_backgame::onTouchStart(Touch* touch)
{
	if (news->getItem()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		UserDefault::getInstance()->setBoolForKey("News", true);
		news->enable();
	}
	else{
		news->disable();
	}
	return true;
}
void Chapter1_c1_backgame::onTouchMove(Touch* touch)
{

}
void Chapter1_c1_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter1_c1_backgame::getEvent()
{
	return nEvent;
}
void Chapter1_c1_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter1_c1_backgame::menuPause()
{
	human->setEnabled(false);
}

void Chapter1_c1_backgame::menuResume()
{
	human->setEnabled(true);
}
