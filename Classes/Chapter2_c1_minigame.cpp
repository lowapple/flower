#include "Chapter2_c1_minigame.h"
#include "GameResult.h"

Chapter2_c1_minigame::Chapter2_c1_minigame()
{
	isClear = (false);
	MOTHNUM = (6);
	mothCnt = (0);
}


Chapter2_c1_minigame::~Chapter2_c1_minigame()
{
}

bool Chapter2_c1_minigame::init()
{
	Sprite* background = Sprite::create("chapter2/scene1/mini/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background);

	UserDefault::getInstance()->setIntegerForKey("GameState", 0);
	srand(time(NULL));
	//-------------------------------------------------
	vMoth.clear();
	int tempXpos = 980;
	int tempYpos = 360;

	for (int i = 0; i < MOTHNUM; i++)
	{
		Moth* moth = Moth::spriteWithFile("chapter2/scene1/mini/moth.png");

		tempYpos += randClass::rand(-40, 40);
		tempXpos += randClass::rand(-40, 40);

		moth->setAnchorPoint(Vec2(0.5f, 1.0f));
		moth->setPosition(Vec2(tempXpos, tempYpos));
		moth->setTag(0);
		this->addChild(moth);
		vMoth.pushBack(moth);

		tempXpos = 980;
		tempYpos = 360;

		ccBezierConfig bezierConfig;
		bezierConfig.controlPoint_1 = Point(moth->getPosition().x, moth->getPosition().y + randClass::rand(-400,400));
		bezierConfig.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-400, 400), moth->getPosition().y + randClass::rand(-400, 400));
		bezierConfig.endPosition = Point(moth->getPosition().x + randClass::rand(-400, 400), moth->getPosition().y);

		ccBezierConfig bezierConfig2;
		bezierConfig2.controlPoint_1 = Point(moth->getPosition().x + randClass::rand(-400,400), moth->getPosition().y + randClass::rand(-400,400));
		bezierConfig2.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-400,400), moth->getPosition().y + randClass::rand(-400,400));
		bezierConfig2.endPosition = Point(moth->getPosition().x, moth->getPosition().y);

		ccBezierConfig bezierConfig4;
		bezierConfig4.controlPoint_1 = Point(moth->getPosition().x + randClass::rand(-400,400), moth->getPosition().y + randClass::rand(-400,400));
		bezierConfig4.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-400,400), moth->getPosition().y + randClass::rand(-400,400));
		bezierConfig4.endPosition = Point(moth->getPosition().x, moth->getPosition().y);

		ccBezierConfig bezierConfig3;
		bezierConfig3.controlPoint_1 = Point(moth->getPosition().x + randClass::rand(-400,400), moth->getPosition().y + randClass::rand(-400,400));
		bezierConfig3.controlPoint_2 = Point(moth->getPosition().x + randClass::rand(-400,400), moth->getPosition().y + randClass::rand(-400,400));
		bezierConfig3.endPosition = Point(moth->getPosition().x, moth->getPosition().y);

		moth->runAction(
			RepeatForever::create(Sequence::create(
			BezierTo::create(16.0f, bezierConfig),
			BezierTo::create(16.0f, bezierConfig3),
			BezierTo::create(16.0f, bezierConfig2),
			BezierTo::create(16.0f, bezierConfig),
			BezierTo::create(16.0f, bezierConfig4),
			BezierTo::create(16.0f, bezierConfig2),
			nullptr)));
	}

	mothCase = Sprite::create("chapter2/scene1/mini/mothCase.png");
	mothCase->setRotation(90);
	mothCase->setPosition(Vec2(WIDTH / 2 - 400, HEIGHT / 2));
	this->addChild(mothCase);

	mothCnt = 0;
	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);
	return true;
}
void Chapter2_c1_minigame::update(float dt)
{
	for (auto it : vMoth)
	{
			if (it->touch)
				it->setPosition(touchPos);
		
	}

	if (mothCnt >= MOTHNUM)
	{
		isClear = true;
		gameresult->CLEAR();
	}

	//--------------------
	// 반딧불이의 회전
	static float mothTime = 0.0f;
	mothTime += dt;
	if (mothTime >= 0.05f)
	{
		mothTime -= mothTime;
		for (auto it : vMoth)
		{
			if (it->getTag() == 0){
				if (it->old_pos == Vec2::ZERO)
				{
					it->old_pos = it->getPosition();
				}
				else
				{
					float diffX = it->getPosition().x - it->old_pos.x;
					float diffY = it->getPosition().y - it->old_pos.y;
					float angleRadian = atan2f(diffY, diffX);
					float angleOffset = CC_RADIANS_TO_DEGREES(angleRadian) * (-1) + 90;
					it->setRotation(angleOffset);
				}
			}
		}
	}
}
bool Chapter2_c1_minigame::onTouchStart(Touch* touch)
{
	for (auto it : vMoth)
	{
		touchPos = touch->getLocation();
		if (it->enable){
			if (it->getBoundingBox().containsPoint(touch->getLocation()))
			{
				if (it->touch)
					return 0;

				it->pauseSchedulerAndActions();
				it->touch = true;
				return 0;
			}
		}
	}
	return true;
}
void Chapter2_c1_minigame::onTouchMove(Touch* touch)
{
	touchPos = touch->getLocation();
	for (auto it : vMoth)
	{
		if (it->enable)
		{
			if (mothCase->getBoundingBox().intersectsRect(it->getBoundingBox()))
			{
				it->setTag(1);
			}
		}
	}
}
void Chapter2_c1_minigame::onTouchEnd(Touch* touch)
{
	touchPos = touch->getLocation();
	for (auto it : vMoth)
	{
		if (it->enable){

			if (mothCase->getBoundingBox().intersectsRect(it->getBoundingBox()))
			{
				// 반딧불이가 케이스 안으로 들어감
				if (it->getTag() == 1)
				{
					it->enable = false;
					it->stopAllActions();
					it->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-10, 0)), RotateBy::create(0.1f, 5),MoveBy::create(0.3f, Vec2(10, 0)), RotateBy::create(0.1f, 5), nullptr)));
					//it->runAction(RepeatForever::create(RotateBy::create(0.1f, 10)));
					//it->setRotation(it->getRotation() + 90);
					mothCnt++;
				}
			}
			else
			{
				it->enable = true;
				it->resumeSchedulerAndActions();
			}

			it->touch = false;
			it->setTag(0);
		}
	}
}
int Chapter2_c1_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter2_c1_minigame::MiniGameStateReset()
{
	gameresult->reset();
}