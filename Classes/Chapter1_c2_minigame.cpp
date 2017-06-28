#include "Chapter1_c2_minigame.h"
#include "GameResult.h"

Chapter1_c2_minigame::Chapter1_c2_minigame()
{
}


Chapter1_c2_minigame::~Chapter1_c2_minigame()
{
}

bool Chapter1_c2_minigame::init()
{
	Sprite* background = Sprite::create("chapter1/scene2/mini/background.png");
	background->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(background);

	GAMETIME = 15.0f;

	timer_bar = Sprite::create("common/timer_bar.png");
	timer_bar->setPosition(Vec2(WIDTH / 2, HEIGHT - 60));
	this->addChild(timer_bar);

	original_Scale = timer_bar->getScaleX() / GAMETIME;

	Sprite* girlsFoot1 = Sprite::create("chapter1/scene2/mini/girls.png");
	girlsFoot1->setName("Foot");
	girlsFoot1->setPosition(Vec2(WIDTH / 2 + CUBE, HEIGHT / 2 + CUBE));
	this->addChild(girlsFoot1);

	Sprite* girlsFoot2 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot2->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 + CUBE));
	this->addChild(girlsFoot2);

	Sprite* girlsFoot3 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot3->setPosition(Vec2(WIDTH / 2 - CUBE, HEIGHT / 2 + CUBE));
	this->addChild(girlsFoot3);


	//-----------------------


	Sprite* girlsFoot4 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot4->setPosition(Vec2(WIDTH / 2 - CUBE, HEIGHT / 2));
	this->addChild(girlsFoot4);

	Sprite* girlsFoot5 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot5->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(girlsFoot5);

	Sprite* girlsFoot6 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot6->setPosition(Vec2(WIDTH / 2 + CUBE, HEIGHT / 2));
	this->addChild(girlsFoot6);


	//-------------------------


	Sprite* girlsFoot7 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot7->setPosition(Vec2(WIDTH / 2 - CUBE, HEIGHT / 2 - CUBE));
	this->addChild(girlsFoot7);

	Sprite* girlsFoot8 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot8->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 - CUBE));
	this->addChild(girlsFoot8);

	Sprite* girlsFoot9 = Sprite::create("chapter1/scene2/mini/animal.png");
	girlsFoot9->setPosition(Vec2(WIDTH / 2 + CUBE, HEIGHT / 2 - CUBE));
	this->addChild(girlsFoot9);


	vFootPrint.clear();
	vFootPrint.push_back(girlsFoot1);
	vFootPrint.push_back(girlsFoot2);
	vFootPrint.push_back(girlsFoot3);
	vFootPrint.push_back(girlsFoot4);
	vFootPrint.push_back(girlsFoot5);
	vFootPrint.push_back(girlsFoot6);
	vFootPrint.push_back(girlsFoot7);
	vFootPrint.push_back(girlsFoot8);

	score = 0;
	Timebar = 0.0f;
	ftime = 0.0f;

	srand(time(NULL));
	isClear = false;
	execute = true;

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);

	UserDefault::getInstance()->setIntegerForKey("GameState", 0);
	return true;
}
void Chapter1_c2_minigame::update(float dt)
{
	if (execute){
		Timebar += dt;
		ftime += dt;

		timer_bar_Time += dt;

		if (timer_bar_Time >= 1.0f){

			timer_bar_Time -= timer_bar_Time;
			timer_bar->setScaleX(timer_bar->getScaleX() - original_Scale);
			if (timer_bar->getScaleX() <= 0)
			{
				timer_bar->setScaleX(0);
				if (score >= 15){

					gameresult->CLEAR();
				}
				else
				{
					gameresult->FAIL();
				}
			}
		}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if (GetAsyncKeyState(VK_F7)) {
			if (!isClear) {
				isClear = true;
				gameresult->CLEAR();
				timer_bar->stopAllActions();
			}
		}
#endif
		//// timer_bar->setScaleX(timer_bar->getScaleX() - original_Time);
		//if (timer_bar->getScaleX() <= 0)
		//{
		//	timer_bar->setScaleX(0);
		//	// 게임을 클리어 했을때 -----------------------------
		//	if (score >= 20)
		//	{
		//		gameresult->CLEAR();
		//	}
		//	else
		//	{
		//		gameresult->FAIL();
		//	}
		//}
		//if (ftime >= 2.5f)
		//{
		//	ftime -= ftime;
		//	shake();
		//}
	}
}

bool Chapter1_c2_minigame::onTouchStart(Touch* touch)
{
	for (auto foot : vFootPrint)
	{
		if (foot->getBoundingBox().containsPoint(touch->getLocation()))
		{
			if (foot->getName() == "Foot")
			{
				shake();
				score++;
			}
		}
	}
	return true;
}

void Chapter1_c2_minigame::onTouchMove(Touch* touch)
{

}

void Chapter1_c2_minigame::onTouchEnd(Touch* touch)
{

}

int Chapter1_c2_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}

void Chapter1_c2_minigame::MiniGameStateReset()
{
	timer_bar->stopAllActions();
	gameresult->reset();
}

void Chapter1_c2_minigame::shake()
{
	static auto dist = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(0, 7);
		return dist1(rng);
	};
	int _array[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	long numMix1, numMix2;
	for (int i = 0; i <= 30; i++)
	{
		numMix1 = dist();
		numMix2 = dist();
		//----------------------


		long Temp;
		Temp = _array[numMix1];
		_array[numMix1] = _array[numMix2];
		_array[numMix2] = Temp;
	}

	for (int i = 0; i < 8; i++)
	{
		vFootPrint.at(i)->setTag(_array[i]);
	}

	//-----------------------------------------

	for (auto it : vFootPrint)
	{
		switch (it->getTag())
		{
		case 0:
			it->setPosition(Vec2(WIDTH / 2 + CUBE, HEIGHT / 2 + CUBE));
			break;
		case 1:
			it->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 + CUBE));
			break;
		case 2:
			it->setPosition(Vec2(WIDTH / 2 - CUBE, HEIGHT / 2 + CUBE));
			break;
		case 3:
			it->setPosition(Vec2(WIDTH / 2 - CUBE, HEIGHT / 2));
			break;
		case 4:
			it->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
			break;
		case 5:
			it->setPosition(Vec2(WIDTH / 2 + CUBE, HEIGHT / 2));
			break;
		case 6:
			it->setPosition(Vec2(WIDTH / 2 - CUBE, HEIGHT / 2 - CUBE));
			break;
		case 7:
			it->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 - CUBE));
			break;
		case 8:
			it->setPosition(Vec2(WIDTH / 2 + CUBE, HEIGHT / 2 - CUBE));
			break;
		}
	}
}