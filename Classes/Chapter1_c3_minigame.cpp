#include "Chapter1_c3_minigame.h"
#include "GameResult.h"

Chapter1_c3_minigame::Chapter1_c3_minigame()
{
}


Chapter1_c3_minigame::~Chapter1_c3_minigame()
{
}

bool Chapter1_c3_minigame::init()
{
	background = Sprite::create("chapter1/scene3/mini/background.png");
	background->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(background);

	touchBegine = Vec2::ZERO;
	touchEnd = Vec2::ZERO;
	touchState = TouchState::NORMAL;

	isClear = false;

	timer_bar = Sprite::create("common/timer_bar.png");
	timer_bar->setPosition(Vec2(WIDTH / 2, HEIGHT - 60));
	this->addChild(timer_bar, 5);

	timebarMinus = timer_bar->getScaleX() / GAME_TIME;

	UserDefault::getInstance()->setIntegerForKey("GameState", 0);
	slideTreeCnt = 3;

	excute = true;
	obstacle = 0.0f;
	timebar = 0.0f;
	tagNum = 50;

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 60);
	return true;
}
void Chapter1_c3_minigame::update(float dt)
{
	if (excute)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if (GetAsyncKeyState(VK_F7))
		{
			excute = false;
			gameresult->CLEAR();

			return;
		}
#endif
		obstacle += dt;
		timebar += dt;

		if (!isClear)
		{
			if (obstacle >= 1.7f)
			{
				obstacle -= obstacle;
				TreeCreator();
			}
			if (vHurdle.size())
			{
				if (vHurdle.front()->getScale() >= 1.0f)
				{
					vHurdle.front()->setColor(Color3B::RED);
				}
				if (vHurdle.front()->getScale() >= 1.3f)
				{
					vHurdle.front()->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create([&]()
					{
						this->timer_bar->setScaleX(this->timer_bar->getScaleX() + timebarMinus * 2);

						Sprite* damage = Sprite::create("common/damage.png");
						damage->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
						damage->setScaleY(damage->getScaleY() * 1.6f);
						damage->setScaleX(damage->getScaleX() * 1.5f);
						damage->setRotation(90);
						this->addChild(damage, 6);
						slideTreeCnt--;
						damage->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), nullptr));
					}), RemoveSelf::create(), nullptr));
					vHurdle.pop();
				}
				if (touchState == TouchState::UP_SLIDE)
				{
					if (vHurdle.front()->getColor() == Color3B::RED)
					{
						this->removeChild(vHurdle.front());
						vHurdle.pop();
						touchState = TouchState::NORMAL;
					}
					else
					{
						this->timer_bar->setScaleX(this->timer_bar->getScaleX() + timebarMinus * 2);

						Sprite* damage = Sprite::create("common/damage.png");
						damage->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
						damage->setScaleY(damage->getScaleY() * 1.6f);
						damage->setScaleX(damage->getScaleX() * 1.5f);
						damage->setRotation(90);
						this->addChild(damage, 6);
						slideTreeCnt--;
						this->removeChild(vHurdle.front());
						vHurdle.pop();
						touchState = TouchState::NORMAL;

						damage->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), nullptr));
					}
				}
			}
		}

		//---------------------
		if (timebar >= 1.0f)
		{
			timebar -= timebar;
			this->timer_bar->setScaleX(this->timer_bar->getScaleX() - timebarMinus);
			if (this->timer_bar->getScaleX() <= 0.0f)
			{
				this->timer_bar->setScaleX(0);
				gameresult->CLEAR();
				excute = false;
			}
		}
		if (slideTreeCnt <= 0)
		{
			slideTreeCnt = 0;
			gameresult->FAIL();
			excute = false;
		}

	}
}
bool Chapter1_c3_minigame::onTouchStart(Touch* touch)
{
	log("scale : %.f", vHurdle.front()->getScale());

	touchBegine = touch->getLocation();
	touchEnd = touch->getLocation();
	touchState = TouchState::NORMAL;
	return true;
}
void Chapter1_c3_minigame::onTouchMove(Touch* touch)
{
	touchEnd = touch->getLocation();
}
void Chapter1_c3_minigame::onTouchEnd(Touch* touch)
{
	if (touchState == TouchState::NORMAL)
	{
		if (touchEnd.y - touchBegine.y > 50)
		{
			touchState = TouchState::UP_SLIDE;
		}
	}
}
int Chapter1_c3_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter1_c3_minigame::MiniGameStateReset()
{
	gameresult->reset();
}

void Chapter1_c3_minigame::TreeCreator()
{
	static auto dist = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(1, 8);
		return dist1(rng);
	};

	Sprite* Hurdle = Sprite::create();
	switch (dist())
	{
	case 1:
		Hurdle->setTexture("chapter1/scene3/mini/1.png");
		Hurdle->setTag(0);
		break;
	case 2:
		Hurdle->setTexture("chapter1/scene3/mini/2.png");
		Hurdle->setFlippedX(true);
		Hurdle->setTag(1);
		break;
	case 3:
		Hurdle->setTexture("chapter1/scene3/mini/3.png");
		Hurdle->setTag(2);
		break;
	case 4:
		Hurdle->setTexture("chapter1/scene3/mini/4.png");
		Hurdle->setFlippedX(true);
		Hurdle->setTag(3);
		break;
	case 5:
		Hurdle->setTexture("chapter1/scene3/mini/1.png");
		Hurdle->setFlippedX(true);
		Hurdle->setTag(4);
		break;
	case 6:
		Hurdle->setTexture("chapter1/scene3/mini/2.png");
		Hurdle->setTag(5);
		break;
	case 7:
		Hurdle->setTexture("chapter1/scene3/mini/3.png");
		Hurdle->setFlippedX(true);
		Hurdle->setTag(6);
		break;
	case 8:
		Hurdle->setTexture("chapter1/scene3/mini/4.png");
		Hurdle->setTag(6);
		break;
	default:
		break;
	}
	Hurdle->setOpacity(0);
	Hurdle->setScale(0.6f);
	if (Hurdle->getTag() <= 3){
		Hurdle->setAnchorPoint(Vec2(0.0f, 0.5f));
		Hurdle->setPosition(Vec2(477, 500));
		Hurdle->runAction(MoveTo::create(5.0f, Vec2(61, 277)));
	}
	else
	{
		Hurdle->setAnchorPoint(Vec2(1.0f, 0.5f));
		Hurdle->setPosition(Vec2(848, 500));
		Hurdle->runAction(MoveTo::create(5.0f, Vec2(1262, 300)));
	}
	Hurdle->setColor(Color3B::BLACK);
	this->addChild(Hurdle, tagNum);
	tagNum -= 1;
	//--------------------
	// Animation
	Hurdle->runAction(Sequence::create(FadeIn::create(1.0f), nullptr));
	Hurdle->runAction(ScaleTo::create(4, 1.5));
	vHurdle.push(Hurdle);
}
