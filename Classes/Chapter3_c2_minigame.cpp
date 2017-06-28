#include "Chapter3_c2_minigame.h"
#include "GameResult.h"

Chapter3_c2_minigame::Chapter3_c2_minigame()
{
	playerVelocity =  Vec2::ZERO ;
	light_cnt = 0;
}


Chapter3_c2_minigame::~Chapter3_c2_minigame()
{
}

bool Chapter3_c2_minigame::init()
{
	this->setAccelerometerEnabled(true);
	background = Sprite::create("chapter3/scene2/mini/background.png");
	background->setPosition(DEVICE_CENTER);
	this->addChild(background, 0, "background");

	Vec2 posArr[] = { Vec2(3372, 578), Vec2(3001, 422), Vec2(2657, 298), Vec2(2352, 195) };

	float scale = 1.0f;

	_vlight.clear();

	for (int i = 0; i < 4; i++)
	{
		Sprite* light = Sprite::create("chapter3/scene2/mini/light_off.png");
		light->setPosition(posArr[i]);
		light->setScale(scale);
		background->addChild(light,2);

		light->setTag(1);
		scale -= 0.19f;

		_vlight.pushBack(light);
	}


	scale = 1.0f;
	Vec2 posArr2[] = { Vec2(419, 610), Vec2(778, 455), Vec2(1131, 317), Vec2(1434, 212) };

	for (int i = 0; i < 4; i++)
	{
		Sprite* light = Sprite::create("chapter3/scene2/mini/light_off.png");
		light->setFlippedX(true);
		light->setPosition(posArr2[i]);
		light->setScale(scale);
		background->addChild(light, 2);
		light->setTag(1);

		scale -= 0.15f;

		_vlight.pushBack(light);
	}

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);
	return true;
}
void Chapter3_c2_minigame::update(float dt)
{
Vec2 temp = this->getPosition();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (GetAsyncKeyState(VK_LEFT))
	{
		temp += Vec2(4.0f, 0.0f);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		temp += Vec2(-4.0f, 0.0f);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//-------------------------------

	temp.x += playerVelocity.x;
#endif

	if (temp.x < -(WIDTH * 2) / 2)
		temp.x = -(WIDTH * 2) / 2;
	if (temp.x >(WIDTH * 2) / 2)
		temp.x = (WIDTH * 2) / 2;

	this->setPosition(temp);
	//----------------------------
}
bool Chapter3_c2_minigame::onTouchStart(Touch* touch)
{
	//Vec2 temp = static_cast<Sprite*>(this->getChildByName("background"))->convertTouchToNodeSpace(touch);
	//log("X : %.f  Y : %.f", temp.x, temp.y);

	for (auto it : _vlight)
	{
		if (it->getBoundingBox().containsPoint(background->convertToNodeSpace(touch->getLocation())))
		{
			if (it->getTag() == 1)
			{
				it->setTag(2);;
				it->setTexture("chapter3/scene2/mini/light_on.png");
				light_cnt++;

				if (light_cnt >= _vlight.size())
				{
					this->runAction(MoveTo::create(0.5f, Vec2::ZERO));
					gameresult->CLEAR();
				}
			}
		}
	}

	return true;
}
void Chapter3_c2_minigame::onTouchMove(Touch* touch)
{

}
void Chapter3_c2_minigame::onTouchEnd(Touch* touch)
{

}
int Chapter3_c2_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter3_c2_minigame::MiniGameStateReset()
{
	gameresult->reset();
}
void Chapter3_c2_minigame::onAcceleration(Acceleration* acc, Event* unused_event)
{
	playerVelocity.x = playerVelocity.x * DEFAULT_DECELERATION
		+ acc->x * (DEFAULT_SENSITIVITY / 1.0f);
	playerVelocity.y = playerVelocity.y * DEFAULT_DECELERATION
		+ acc->y * (DEFAULT_SENSITIVITY / 1.0f);

	if (playerVelocity.x > MAX_VELOCITY) {
		playerVelocity.x = MAX_VELOCITY;
	}
	else if (playerVelocity.x < -MAX_VELOCITY) {
		playerVelocity.x = -MAX_VELOCITY;
	}
}
