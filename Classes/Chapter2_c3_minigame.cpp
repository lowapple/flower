#include "Chapter2_c3_minigame.h"
#include "GameResult.h"

Chapter2_c3_minigame::Chapter2_c3_minigame()
{

}


Chapter2_c3_minigame::~Chapter2_c3_minigame()
{

}

bool Chapter2_c3_minigame::init()
{
	UserDefault::getInstance()->setIntegerForKey("GameState", 0);

	Sprite* background = Sprite::create("chapter2/scene3/mini/background2.png");
	background->setColor(Color3B::BLACK);
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	Thresh_Lantern = Sprite::create("chapter2/scene3/mini/lantern.png");
	Thresh_Lantern->setPosition(Vec2(500, 500));
	this->addChild(Thresh_Lantern, 1);

	this->G_Creepy();

	fUpdate_Time = 3.0f;
	nScore = 0;

	timer_bar = Sprite::create("common/timer_bar.png");
	timer_bar->setPosition(Vec2(WIDTH / 2, HEIGHT - 60));
	this->addChild(timer_bar);

	original_Scale = timer_bar->getScaleX() / 30.0f;

	leftscore = Label::createWithTTF("15", string("fonts/crayon.ttf"), 35, Size::ZERO, TextHAlignment::CENTER);
	leftscore->setPosition(Vec2(WIDTH - 130, 130));
	leftscore->setColor(Color3B::RED);
	this->addChild(leftscore);


	lantern_change = false;
	rest = 0.0f;

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);
	return true;
}
void Chapter2_c3_minigame::update(float dt)
{
	rest += dt;

	timer_bar_Time += dt;

	if (timer_bar_Time >= 1.0f){

		timer_bar_Time -= timer_bar_Time;
		timer_bar->setScaleX(timer_bar->getScaleX() - original_Scale);
		if (timer_bar->getScaleX() <= 0)
		{

			timer_bar->setScaleX(0);
			if (nScore <= 15)
			{
				gameresult->FAIL();
			}
		}
	}

	if (rest >= fUpdate_Time)
	{
		rest -= rest;
		Eyes_reset();
	}

	// 충돌 했을때
	if (!lantern_change)
	{
		if (Thresh_Lantern->getBoundingBox().intersectsRect(Creepy_Eyes->getBoundingBox()))
		{
			lantern_change = true;
			Creepy_Eyes->runAction(Sequence::create(FadeOut::create(0.7f), CallFunc::create([&]()
			{
				nScore += 1;
				if (nScore >= 15)
					nScore = 15;
				leftscore->setString(StringUtils::format("%d", OVER_COUNT - nScore));
				if (nScore >= OVER_COUNT)
				{
					gameresult->CLEAR();
				}
				Eyes_reset();
			}
			), CallFunc::create([&](){lantern_change = false; }), nullptr));
		}
	}
	//ScoreUpdate(dt);
}

bool Chapter2_c3_minigame::onTouchStart(Touch* touch)
{
	L_bound = Thresh_Lantern->boundingBox();
	E_bound = Creepy_Eyes->getBoundingBox();

	auto TouchLoc = touch->getLocation();

	if (L_bound.containsPoint(TouchLoc) == true)
	{
		TouchCheck = true;
		Light();
	}
	return true;
}
void Chapter2_c3_minigame::onTouchMove(Touch* touch)
{
	if (TouchCheck == true)
	{
		Thresh_Lantern->setPosition(touch->getLocation());
		Light();
	}
}
void Chapter2_c3_minigame::onTouchEnd(Touch* touch)
{
	TouchCheck = false;
}
int Chapter2_c3_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter2_c3_minigame::MiniGameStateReset()
{
	rest = 0;
	nScore = 0;
	//timerbar->stopAllActions();
	gameresult->reset();
}
void Chapter2_c3_minigame::G_Creepy()
{
	float fX = rand() % 1150;
	float fY = rand() % 680;

	Creepy_Eyes = Sprite::create("chapter2/scene3/mini/creepy.png");
	Creepy_Eyes->setPosition(Vec2(fX, fY));
	this->addChild(Creepy_Eyes, 1);

	Sprite* eyes = Sprite::create("chapter2/scene3/mini/creepy.png");
	eyes->setScale(0.73);
	eyes->setColor(Color3B::RED);
	eyes->setPosition(Vec2(Creepy_Eyes->getContentSize().width * 2 - 50, Creepy_Eyes->getContentSize().height / 2));
	Creepy_Eyes->addChild(eyes);
}
void Chapter2_c3_minigame::TlqkfMask()
{
	drawNode = DrawNode::create();
	clip = ClippingNode::create(drawNode);
	clip->setPosition(Vec2(0, 0));
	this->addChild(clip);

	BackG = Sprite::create("chapter2/scene3/mini/background.png");
	BackG->setColor(Color3B::WHITE);
	BackG->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	clip->addChild(BackG, 1);
}
void Chapter2_c3_minigame::Light()
{
	TlqkfMask();
	drawNode->setPosition(Vec2(Thresh_Lantern->getPosition().x, Thresh_Lantern->getPosition().y));
	clip->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(), nullptr));

	const int MAX = 40;
	const float RAD_MAX = 3.141592f * 2;

	Point centerPoint = Point(0, 0);

	Point pointArr[MAX];

	for (int i = 0; i < MAX; i++)
	{
		float rad = (RAD_MAX / MAX) * i;

		float x = cos(rad) * 100 + centerPoint.x;
		float y = sin(rad) * 100 + centerPoint.y;

		pointArr[i] = Point(x, y);
	}

	drawNode->drawPolygon(pointArr, MAX, Color4F::WHITE, 0, Color4F::WHITE);
	clip->setStencil(drawNode);

	clip->setInverted(false);

}

void Chapter2_c3_minigame::Eyes_reset()
{
	static bool change = false;
	float fX = rand() % 1150;
	float fY = rand() % 680;

	if (!change)
	{
		change = true;
		Creepy_Eyes->setPosition(Vec2(fX, fY));
		Creepy_Eyes->runAction(Sequence::create(FadeIn::create(0.6f), CallFunc::create([&](){change = false; }), nullptr));
	}
}

void Chapter2_c3_minigame::ScoreUpdate(float dt)
{
	//static float fG_Time = 0.f;
	//fG_Time += dt;

	//if (fG_Time >= 1.0f)
	//{
	//	fG_Time -= fG_Time;
	//	timerbar->setScaleX((timerbar->getScaleX() - original_time));

	//	if (timerbar->getScaleX() <= 0.0f)
	//	{
	//		timerbar->setScaleX(0.0f);
	//		gameresult->CLEAR();
	//	}
	//}
}