#include "Chapter3_c5_minigame.h"
#include "GameResult.h"

Chapter3_c5_minigame::Chapter3_c5_minigame()
{
	jump = false;
	slide = false;
	moveCnt = 2;
	execute = true;
}


Chapter3_c5_minigame::~Chapter3_c5_minigame()
{

}

bool Chapter3_c5_minigame::init()
{
	jumpHeight = 10.0f;

	groundLayer = Layer::create();
	this->addChild(groundLayer);

	vHuddle.clear();
	background1 = Sprite::create("chapter3/scene5/mini/background.png");
	background1->setAnchorPoint(Vec2::ZERO);
	background1->setPosition(Vec2(0.0f, 0.0f));
	groundLayer->addChild(background1, 3);

	background2 = Sprite::create("chapter3/scene5/mini/background.png");
	background2->setAnchorPoint(Vec2::ZERO);
	background2->setPosition(Vec2(background1->getBoundingBox().size.width, 0.0f));
	groundLayer->addChild(background2, 3);

	groundLayer->runAction(RepeatForever::create(Sequence::create(MoveTo::create(7.0f, Vec2(-WIDTH * 2, 0)), Place::create(Vec2::ZERO), NULL)));

	girls = Sprite::create("chapter3/scene5/mini/cha_1.png");
	girls->setAnchorPoint(Vec2(0.5f, 0.0f));
	girls->setPosition(Vec2(100, 60));
	girls->setTag(2);
	this->addChild(girls, 5);

	timer_bar = Sprite::create("common/timer_bar.png");
	timer_bar->setPosition(Vec2(WIDTH / 2, HEIGHT - 100));
	this->addChild(timer_bar, 5);

	original_Scale = timer_bar->getScaleX() / 30.0f;

	Animation* ani = Animation::create();
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_1.png");
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_2.png");
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_3.png");
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_4.png");
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_5.png");
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_4.png");
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_3.png");
	ani->addSpriteFrameWithFileName("chapter3/scene5/mini/cha_2.png");
	ani->setDelayPerUnit(0.15f);

	girls->runAction(RepeatForever::create(Animate::create(ani)));

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 8);
	return true;
}
void Chapter3_c5_minigame::update(float dt)
{
	if (execute){
		static float time = 0.0f;
		time += dt;

		timer_bar_Time += dt;

		if (timer_bar_Time >= 1.0f){

			timer_bar_Time -= timer_bar_Time;
			timer_bar->setScaleX(timer_bar->getScaleX() - original_Scale);
			if (timer_bar->getScaleX() <= 0)
			{
				timer_bar->setScaleX(0);
				gameresult->CLEAR();
			}
		}

		// 허들을 생성한다.
		if (time >= 1.0f)
		{
			time -= time;
			createHuddle();
		}

		// 슬라이드 할때
		if (slide)
		{
			girls->pause();
			girls->setTexture("chapter3/scene5/mini/cha_6.png");
		}
		else
		{
			girls->resume();
		}

		// 충돌 처리
		if (vHuddle.size())
		{
			for (auto it : vHuddle)
			{
				if (it->getTag() != 4)
				{
					Rect boundingBox = Rect(it->getPosition().x - 10, it->getPosition().y, 20, 20);
					if (girls->getBoundingBox().intersectsRect(boundingBox))
					{
						if (girls->getTag() == it->getTag())
						{
							for (auto ji : vHuddle)
							{
								ji->pause();
							}
							execute = false;
							girls->pause();
							groundLayer->pause();
							gameresult->FAIL();
							return;
						}
					}
				}
				else
				{
					Rect bounding = Rect(it->getPosition().x - 50, 50, 50, HEIGHT);
					if (bounding.intersectsRect(girls->getBoundingBox()))
					{
						if (!slide)
						{
							for (auto ji : vHuddle)
							{
								ji->pause();
							}
							execute = false;
							girls->pause();
							groundLayer->pause();
							gameresult->FAIL();
						}
						return;
					}
				}
			}
		}
	}
}

bool Chapter3_c5_minigame::onTouchStart(Touch* touch)
{
	begine = touch->getLocation();
	end = touch->getLocation();

	if (touch->getLocation().x >= WIDTH / 2)
	{
		// 슬라이드
		slide = true;
	}

	return true;
}
void Chapter3_c5_minigame::onTouchMove(Touch* touch)
{
	end = touch->getLocation();
}
void Chapter3_c5_minigame::onTouchEnd(Touch* touch)
{
	// 위로 슬라이드
	if (end.y - 100 >= begine.y)
	{
		log("Up");
		if (girls->getTag() != 4){
			moveCnt--;
			if (moveCnt <= 1)
			{
				moveCnt = 1;
			}
		}
	}
	// 아래로 슬라이드
	else if (end.y + 100 <= begine.y)
	{
		log("Down");
		if (girls->getTag() != 4){
			moveCnt++;
			if (moveCnt >= 3)
			{
				moveCnt = 3;
			}
		}
	}

	moveGirls();
	slide = false;
}
int Chapter3_c5_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter3_c5_minigame::MiniGameStateReset()
{
	timer_bar->stopAllActions();
	gameresult->reset();
}
void Chapter3_c5_minigame::createHuddle()
{
	Huddle* _rock = Huddle::spriteWithFile("chapter3/scene5/mini/2-1.png", this);
	vHuddle.pushBack(_rock);
}

void Chapter3_c5_minigame::moveGirls()
{
	girls->setTag(moveCnt);
	switch (moveCnt)
	{
	case 1:
		girls->runAction(MoveTo::create(0.2f, Vec2(girls->getPosition().x, 150)));
		break;
	case 2:
		girls->runAction(MoveTo::create(0.2f, Vec2(girls->getPosition().x, 60)));
		break;
	case 3:
		girls->runAction(MoveTo::create(0.2f, Vec2(girls->getPosition().x, -30)));
		break;
	default:
		break;
	}
}