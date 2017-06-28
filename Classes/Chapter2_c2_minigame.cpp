#include "Chapter2_c2_minigame.h"
#include "GameResult.h"

Chapter2_c2_minigame::Chapter2_c2_minigame()
{
	slideCnt = (0);
	touch = (false);
	touchPos = (Vec2::ZERO);
	matchboxSlide = (false);
}


Chapter2_c2_minigame::~Chapter2_c2_minigame()
{
}

bool Chapter2_c2_minigame::init()
{
	isClear = false;
	Sprite* background = Sprite::create("chapter2/scene2/mini/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	lantern = Sprite::create("chapter2/scene2/mini/r1.png");
	lantern->setPosition(Vec2(152, 395));
	this->addChild(lantern,2);

	match = Sprite::create("chapter2/scene2/mini/1.png");
	match->setPosition(Vec2(738, 303));
	this->addChild(match,3);

	matchbox = Sprite::create("chapter2/scene2/mini/match.png");
	matchbox->setPosition(Vec2(961, 498));
	this->addChild(matchbox,2);

	fire_match = false;
	fire = false;
	fire_time = 0.0f;

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);

	return true;
}
void Chapter2_c2_minigame::update(float dt)
{
	if (isClear)
	{
		if (match->getBoundingBox().intersectsRect(matchbox->getBoundingBox())){
			fire_time += dt;
			if (fire_time >= 2.5f)
			{
				if (!fire_match)
				{
					fire_match = true;
					isClear = false;
					Animation* ani = Animation::create();
					ani->setDelayPerUnit(0.1855f);
					for (int i = 1; i <= 4; i++) {
						ani->addSpriteFrameWithFileName(StringUtils::format("chapter2/scene2/mini/fire_match/%d.png", i));
					}
					matchbox->runAction(Sequence::create(Animate::create(ani), nullptr));

					SimpleAudioEngine::getInstance()->playEffect("BGM/fire.mp3", false);
				}
			}
		}
	}
}
bool Chapter2_c2_minigame::onTouchStart(Touch* touch)
{
	if (match->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->touch = true;
	}
	return true;
}
void Chapter2_c2_minigame::onTouchMove(Touch* touch)
{
	if (this->touch)
	{
		touchPos = touch->getLocation();
		match->setPosition(touchPos);
	}

	if (match->getBoundingBox().intersectsRect(matchbox->getBoundingBox()))
	{
		if (matchboxSlide)
		{
			if (!fire)
			{
				slideCnt += 1;
				if (slideCnt >= 5)
				{
					fire = true;
					Animation* ani = Animation::create();
					ani->addSpriteFrameWithFileName("chapter2/scene2/mini/2.png");
					ani->addSpriteFrameWithFileName("chapter2/scene2/mini/3.png");
					ani->addSpriteFrameWithFileName("chapter2/scene2/mini/4.png");
					ani->setDelayPerUnit(0.1555f);

					match->runAction(Animate::create(ani));
					match->setTag(1);
					isClear = true;
				}

			}
			matchboxSlide = false;
		}
	}
	else
	{
		if (!matchboxSlide)
			matchboxSlide = true;
	}

	if (match->getBoundingBox().intersectsRect(lantern->getBoundingBox()))
	{
		if (match->getTag() == 1)
		{
			lantern->setTexture("chapter2/scene2/mini/r2.png");
			gameresult->CLEAR();
		}
	}
}
void Chapter2_c2_minigame::onTouchEnd(Touch* touch)
{

}
int Chapter2_c2_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter2_c2_minigame::MiniGameStateReset()
{
	fire_match = false;
	slideCnt = 0;
	match->setTag(0);
	gameresult->reset();
	matchboxSlide = false;
	fire = false;
}