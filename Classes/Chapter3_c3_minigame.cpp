#include "Chapter3_c3_minigame.h"
#include "GameResult.h"

Chapter3_c3_minigame::Chapter3_c3_minigame()
{
}


Chapter3_c3_minigame::~Chapter3_c3_minigame()
{
}

bool Chapter3_c3_minigame::init()
{
	srand(time(NULL));
	Sprite* background = Sprite::create("chapter3/scene3/mini/background.png");
	background->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(background);

	dgree = ui::Slider::create();
	dgree->setPosition(Vec2(WIDTH / 2 + 450, HEIGHT / 2));
	dgree->setScale(1.6f);
	dgree->setRotation(270);
	dgree->loadBarTexture("chapter3/scene3/mini/Slider_Back.png"); // what the slider looks like
	dgree->loadSlidBallTextures("chapter3/scene3/mini/SliderNode_Normal.png", "chapter3/scene3/mini/SliderNode_Press.png", "chapter3/scene3/mini/SliderNode_Disable.png");
	dgree->loadProgressBarTexture("chapter3/scene3/mini/Slider_PressBar.png");
	dgree->setVisible(true);
	dgree->setZOrder(4);
	this->addChild(dgree,3);

	girls = Sprite::create("chapter3/scene3/mini/g1.png");
	girls->setPosition(Vec2(140, 245));
	this->addChild(girls,2);

	touch = false;
	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult,5);

	stamina = Sprite::create("chapter3/scene3/mini/stamina.png");
	stamina->setPosition(Vec2(girls->getPosition().x, girls->getPosition().y + girls->getContentSize().height / 2 + 20));
	this->addChild(stamina,3);

	useRock = false;
	GAME_TIME = 40.0f;

	timer_bar = Sprite::create("common/timer_bar.png");
	timer_bar->setPosition(Vec2(WIDTH / 2, HEIGHT - 60));
	this->addChild(timer_bar),4;

	original_Scale = timer_bar->getScaleX() / GAME_TIME;

	excute = true;
	heart_cnt = 3;
	makeHeart(heart_cnt);
	randTimer = 2.0f;
	return true;
}
void Chapter3_c3_minigame::update(float dt)
{
	if (excute){
		static float dtime = 0.0f;
		dtime += dt;

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

		// 유령 생성
		if (dtime >= randTimer){
			dtime -= dtime;

			/*Animation* ani = Animation::create();
			ani->addSpriteFrameWithFileName("chapter3/scene3/mini/c1.png");
			ani->addSpriteFrameWithFileName("chapter3/scene3/mini/c2.png");
			ani->setDelayPerUnit(0.2);
			*/

			int shadow_tag = randClass::rand(1, 4);
			Sprite* shadow = Sprite::create();
			switch (shadow_tag)
			{
			case 1:
				shadow->setTexture("chapter3/scene3/mini/c1.png");
				shadow->setPosition(Vec2(WIDTH + 50, 293));
				shadow->setTag(1);

				break;
			case 2:
				shadow->setTexture("chapter3/scene3/mini/cc1.png");
				shadow->setPosition(Vec2(WIDTH + 50, HEIGHT / 2 - randClass::rand(1, 200)));
				shadow->setTag(2);
				break;
			case 3:
				shadow->setTexture("chapter3/scene3/mini/c1.png");
				shadow->setPosition(Vec2(WIDTH + 50, HEIGHT / 2 + 200));
				shadow->setFlippedY(true);
				shadow->setTag(3);
				break;
			case 4:
				shadow->setTexture("chapter3/scene3/mini/c1.png");
				shadow->setPosition(Vec2(WIDTH / 2 + 250, -200));
				shadow->setTag(4);
				shadow->runAction(MoveBy::create(1.0f, Vec2(0, 400)));
				break;
			default:
				break;
			}
			this->addChild(shadow, 2);
			if (shadow_tag <= 4)
				vwolf.pushBack(shadow);

			randTimer = randClass::rand(1, 8);
		}

		// 유령의 움직임
		for (auto it : vwolf)
		{
			it->setPosition(Vec2(it->getPosition().x - 100 * dt, it->getPosition().y));
		}


		// 돌의 움직임
		for (auto it : vrock)
		{
			it->move(dt);
		}

		// 유령과 캐릭터가 충돌 했을때
		for (auto it : vwolf)
		{
			if (it->getBoundingBox().containsPoint(girls->getPosition()))
			{
				heart_cnt--;
				if (heart_cnt < 0)
				{
					gameresult->FAIL();
				}
				else
				{
					makeHeart(heart_cnt);
				}

				Sprite* effect1 = Sprite::create("chapter3/scene3/mini/e1.png");
				effect1->setPosition(girls->getPosition().x - 15, girls->getPosition().y + girls->getContentSize().height / 2 + 20);
				this->addChild(effect1);

				Sprite* effect2 = Sprite::create("chapter3/scene3/mini/e1.png");
				effect2->setPosition(girls->getPosition().x + 15, girls->getPosition().y + girls->getContentSize().height / 2 + 20);
				this->addChild(effect2);

				Animation* anime = Animation::create();
				anime->addSpriteFrameWithFileName("chapter3/scene3/mini/e1.png");
				anime->addSpriteFrameWithFileName("chapter3/scene3/mini/e2.png");
				anime->addSpriteFrameWithFileName("chapter3/scene3/mini/e3.png");
				anime->addSpriteFrameWithFileName("chapter3/scene3/mini/e2.png");
				anime->addSpriteFrameWithFileName("chapter3/scene3/mini/e3.png");
				anime->setDelayPerUnit(0.1f);

				effect1->runAction(Sequence::create(Animate::create(anime), RemoveSelf::create(), nullptr));
				effect2->runAction(Sequence::create(Animate::create(anime), RemoveSelf::create(), nullptr));
				it->runAction(Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), nullptr));
				vwolf.eraseObject(it, 2);
				break;
			}
		}

		// 유령이 돌에 맞았을때
		for (auto it : vrock)
		{
			for (auto ji : vwolf)
			{
				Rect rect;
				if (ji->getTag() != 3)
					rect = Rect(ji->getPosition().x - (ji->getContentSize().width / 2) - 10, ji->getPosition().y + (ji->getContentSize().height / 2) - 50, 50, 50);
				else
					rect = Rect(ji->getPosition().x - (ji->getContentSize().width / 2) + 10, ji->getPosition().y - (ji->getContentSize().height / 2), 50, 50);
				if (rect.intersectsRect(it->getBoundingBox()))
				{
					Sprite* effect = Sprite::create("chapter3/scene3/mini/e1.png");
					effect->setPosition(rect.getMidX(), rect.getMidY());
					this->addChild(effect, 2);

					Animation* effect2 = Animation::create();
					effect2->addSpriteFrameWithFileName("chapter3/scene3/mini/e1.png");
					effect2->addSpriteFrameWithFileName("chapter3/scene3/mini/e2.png");
					effect2->addSpriteFrameWithFileName("chapter3/scene3/mini/e3.png");
					effect2->addSpriteFrameWithFileName("chapter3/scene3/mini/e2.png");
					effect2->addSpriteFrameWithFileName("chapter3/scene3/mini/e3.png");
					effect2->setDelayPerUnit(0.1f);

					effect->runAction(Sequence::create(Animate::create(effect2), RemoveSelf::create(), nullptr));

					ji->runAction(Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), nullptr));
					vrock.eraseObject(it);
					vwolf.eraseObject(ji);
					this->removeChild(it);
					goto collide;
				}
			}
		}
	collide:;
	}
}
bool Chapter3_c3_minigame::onTouchStart(Touch* touch)
{
	if (!useRock)
	{
		useRock = true;
		stamina->setScaleX(0.0f);
		stamina->runAction(Sequence::create(ScaleTo::create(2.0f, 1.0f, 1.0f), CallFunc::create([&](){useRock = false; }), nullptr));;


		Animation* throwAnimation = Animation::create();
		throwAnimation->addSpriteFrameWithFileName("chapter3/scene3/mini/g2.png");
		throwAnimation->addSpriteFrameWithFileName("chapter3/scene3/mini/g3.png");
		throwAnimation->addSpriteFrameWithFileName("chapter3/scene3/mini/g1.png");
		throwAnimation->setDelayPerUnit(0.1f);

		girls->runAction(Animate::create(throwAnimation));

		float fdgree = dgree->getPercent();
		//--------------------
		if (fdgree >= 90)
			fdgree = 90;
		else if (fdgree <= 5)
			fdgree = 5;
		//---------------------

		rock* _rock = rock::createrock("chapter3/scene3/mini/rock.png");
		_rock->setDgree(fdgree);
		_rock->setPosition(Vec2(186, 363));
		this->addChild(_rock,3);
		vrock.pushBack(_rock);
	}
	return true;
}
void Chapter3_c3_minigame::onTouchMove(Touch* touch)
{

}
void Chapter3_c3_minigame::onTouchEnd(Touch* touch)
{

}
int Chapter3_c3_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter3_c3_minigame::MiniGameStateReset()
{
	timer_bar->stopAllActions();
	gameresult->reset();
}

float Chapter3_c3_minigame::angle(Vec2 you, Vec2 target)
{
	float result;
	float dx = target.x - you.x;
	float dy = target.y - you.x;
	result = (atan2(dx, dy)) * 180 / PI;
	result = result - 90;
	if (result < 0)
	{
		result = result + 360;
	}
	return 360 - result;
}

void Chapter3_c3_minigame::makeHeart(int num)
{
	if (hearts.size() != 0)
	{
		for (Sprite* heart : hearts)
		{
			this->removeChild(heart);
			heart->removeAllChildrenWithCleanup(true);
		}
		hearts.clear();
	}

	for (int i = 0; i < num; i++)
	{
		Sprite* heart = Sprite::create("chapter3/scene3/mini/heart.png");
		heart->setPosition(Vec2(girls->getPosition().x, girls->getPosition().y + 230 + heart->getContentSize().width * i));
		this->addChild(heart,3);
		hearts.pushBack(heart);
	}
}