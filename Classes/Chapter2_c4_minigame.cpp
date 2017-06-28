#include "Chapter2_c4_minigame.h"
#include "GameResult.h"


Chapter2_c4_minigame::Chapter2_c4_minigame()
{
	playerVelocity = (Vec2::ZERO);
	curArrow = (gradient::RED);
}


Chapter2_c4_minigame::~Chapter2_c4_minigame()
{
}

bool Chapter2_c4_minigame::init()
{
	execute = true;
	UserDefault::getInstance()->setIntegerForKey("GameState", 1);

	this->setAccelerometerEnabled(true);

	Sprite* background = Sprite::create("chapter2/scene4/mini/background.png");
	background->setAnchorPoint(Vec2(1.0f, 0.0f));
	background->setPosition(Vec2(WIDTH,0.0f));
	background->runAction(MoveBy::create(30.0f, Vec2(1280, 0.0f)));
	this->addChild(background);

	sensorbar = Sprite::create("chapter2/scene4/mini/sensorbar.png");
	sensorbar->setPosition(Vec2(WIDTH - 100, HEIGHT / 2));
	this->addChild(sensorbar);

	arrow = Sprite::create("chapter2/scene4/mini/arrow.png");
	arrow->setPosition(Vec2(WIDTH - 100, HEIGHT / 2));
	this->addChild(arrow);

	character = Sprite::create("chapter2/scene4/mini/1.png");
	character->setPosition(Vec2(WIDTH / 2 + 180, HEIGHT / 2));
	//character->setRotation(-90);
	character->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->addChild(character, 2);

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);

	exclamation_mark = Sprite::create("chapter2/scene4/mini/exclamation_mark.png");
	exclamation_mark->setPosition(Vec2(95, HEIGHT / 2));
	exclamation_mark->setRotation(-90.0f);
	this->addChild(exclamation_mark);

	// 타임 바
	timer_bar = Sprite::create("common/timer_bar.png");
	timer_bar->setPosition(Vec2(170, HEIGHT / 2));
	timer_bar->setRotation(90);
	this->addChild(timer_bar);

	Time = 0.0f;
	return true;
}
void Chapter2_c4_minigame::update(float dt)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (GetAsyncKeyState(VK_F7))
	{
		gameresult->CLEAR();
	}
#endif

	Time += dt;

	// SensorArrow -----------------
	Vec2 temp = arrow->getPosition();
	temp.y += playerVelocity.y*1.5f;
	if (temp.x < 50)
		temp.x = 50;
	if (temp.x > WIDTH - 80)
		temp.x = WIDTH - 80;
	if (temp.y < 100)
		temp.y = 100;
	if (temp.y > HEIGHT - 100)
		temp.y = HEIGHT - 100;

	arrow->setPosition(temp);

	//character->setRotation(bodyup->getRotation() + playerVelocity.y / 4.3f);
	// Label ----------------------
	/*char str[255];
	sprintf(str, "%.2f", bodyup->getRotation());
	gradientLabel->setString(str);*/
	//if (bodyup->getRotation() >= -90 + MAX_GRADIENT)
	//{
	//	bodyup->setRotation(-90 + MAX_GRADIENT);
	//}
	//else if (bodyup->getRotation() <= -90 - MAX_GRADIENT)
	//{
	//	bodyup->setRotation(-90 - MAX_GRADIENT);
	//}

	// Sensor ----------------------
	// RED
	if (arrow->getPosition().y >= 318 && arrow->getPosition().y <= 412){
		log("RED");
		curArrow = gradient::RED;
		//gradientLabel->setString(StringUtils::format("RED"));
	}
	// YELLOW
	else if (arrow->getPosition().y >= 412 && arrow->getPosition().y <= 490 || arrow->getPosition().y >= 237 && arrow->getPosition().y <= 317){
		log("YELLOW");

		if (arrow->getPosition().y >= 412 && arrow->getPosition().y <= 490)
		{
			curArrow = gradient::YELLOW_RIGHT;
			//gradientLabel->setString(StringUtils::format("YELLOW RIGHT"));
		}
		else if (arrow->getPosition().y >= 237 && arrow->getPosition().y <= 317)
		{
			curArrow = gradient::YELLOW_LEFT;
			//gradientLabel->setString(StringUtils::format("YELLOW LEFT"));
		}
	}
	// GREEN
	else if (arrow->getPosition().y >= 490 && arrow->getPosition().y <= 660 || arrow->getPosition().y >= 60 & arrow->getPosition().y <= 235){
		log("GREEN");

		if (arrow->getPosition().y >= 60 & arrow->getPosition().y <= 235)
		{
			curArrow = gradient::GREEN_LEFT;
			//gradientLabel->setString(StringUtils::format("GREEN LEFT"));
		}
		else if (arrow->getPosition().y >= 490 && arrow->getPosition().y <= 660)
		{
			curArrow = gradient::GREEN_RIGHT;
			//gradientLabel->setString(StringUtils::format("GREEN RIGHT"));
		}
	}
	this->changeMotion();


	//------------------------------------
	// 게임이 끝남
	if (timer_bar->getScaleX() <= 0)
	{
		timer_bar->setScaleX(0.0f);
		gameresult->FAIL();
		UserDefault::getInstance()->setIntegerForKey("GameState", 0);
	}

	if (Time >= GAME_TIME)
	{
		gameresult->CLEAR();
		execute = false;
		UserDefault::getInstance()->setIntegerForKey("GameState", 0);
	}

}
bool Chapter2_c4_minigame::onTouchStart(Touch* touch)
{
	return true;
}
void Chapter2_c4_minigame::onTouchMove(Touch* touch)
{

}
void Chapter2_c4_minigame::onTouchEnd(Touch* touch)
{

}
int Chapter2_c4_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter2_c4_minigame::MiniGameStateReset()
{
	gameresult->reset();
}

void Chapter2_c4_minigame::onAcceleration(Acceleration* acc, Event* unused_event)
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

void Chapter2_c4_minigame::changeMotion()
{
	if (execute){
		switch (curArrow)
		{
		case gradient::RED:
			character->setTexture("chapter2/scene4/mini/1.png");
			exclamation_mark->setColor(Color3B::GREEN);
			break;
		case gradient::YELLOW_LEFT:
			character->setTexture("chapter2/scene4/mini/4.png");
			exclamation_mark->setColor(Color3B::YELLOW);
			timer_bar->setScaleX(timer_bar->getScaleX() - 0.003f);
			break;
		case gradient::YELLOW_RIGHT:
			character->setTexture("chapter2/scene4/mini/2.png");
			exclamation_mark->setColor(Color3B::YELLOW);
			timer_bar->setScaleX(timer_bar->getScaleX() - 0.003f);
			break;
		case gradient::GREEN_LEFT:
			character->setTexture("chapter2/scene4/mini/4.png");
			exclamation_mark->setColor(Color3B::RED);
			timer_bar->setScaleX(timer_bar->getScaleX() - 0.006f);
			exclamation_mark->setColor(Color3B::YELLOW);
			break;
		case gradient::GREEN_RIGHT:
			character->setTexture("chapter2/scene4/mini/2.png");
			exclamation_mark->setColor(Color3B::RED);
			timer_bar->setScaleX(timer_bar->getScaleX() - 0.006f);
			break;
		}
	}
}
