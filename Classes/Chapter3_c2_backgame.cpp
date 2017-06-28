#include "Chapter3_c2_backgame.h"
#include "Item.h"

Chapter3_c2_backgame::Chapter3_c2_backgame()
{
	nEvent = 0;
}


Chapter3_c2_backgame::~Chapter3_c2_backgame()
{

}

bool Chapter3_c2_backgame::init()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Background/cave.mp3");
	if (!UserDefault::getInstance()->getBoolForKey("CH3C2_MINI"))
	{
		background = Sprite::create("chapter3/scene2/background.png");
		background->setPosition(DEVICE_CENTER);
		this->addChild(background);
	}
	else
	{
		background = Sprite::create("chapter3/scene2/background2.png");
		background->setPosition(DEVICE_CENTER);
		this->addChild(background);
		black_out = false;
	}

	Sprite* man_sprite = Sprite::create("chapter3/scene2/man.png");
	MenuItemSprite* man = MenuItemSprite::create(man_sprite, man_sprite->divSprite(0.98),
		[&](Ref* sender)
	{
		nEvent = 1;
	});
	man->setPosition(Vec2(811, 481));

	menu = Menu::create(man, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	if (!UserDefault::getInstance()->getBoolForKey("CH3C2_MINI"))
	{
		LayerColor* colorlayer = LayerColor::create(Color4B(0, 0, 0, 150));
		colorlayer->setPosition(Vec2::ZERO);
		colorlayer->setName("black_out");
		this->addChild(colorlayer);
		black_out = true;
	}

	return true;
}

void Chapter3_c2_backgame::update(float delta)
{
	if (black_out)
	{
		if (UserDefault::getInstance()->getBoolForKey("CH3C2_MINI"))
		{
			background->setTexture("chapter3/scene2/background2.png");
			this->removeChildByName("black_out");
			black_out = false;
		}
	}
}

bool Chapter3_c2_backgame::onTouchStart(Touch* touch)
{
	return true;
}
void Chapter3_c2_backgame::onTouchMove(Touch* touch)
{

}
void Chapter3_c2_backgame::onTouchEnd(Touch* touch)
{

}

int Chapter3_c2_backgame::getEvent()
{
	return nEvent;
}
void Chapter3_c2_backgame::setEvent(int nevent)
{
	nEvent = nevent;
}

void Chapter3_c2_backgame::menuPause()
{

}

void Chapter3_c2_backgame::menuResume()
{

}