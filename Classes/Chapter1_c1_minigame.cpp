#include "Chapter1_c1_minigame.h"
#include "GameResult.h"

Chapter1_c1_minigame::Chapter1_c1_minigame()
{
	log("Chapter1_c1_minigame");
}


Chapter1_c1_minigame::~Chapter1_c1_minigame()
{
}

bool Chapter1_c1_minigame::init()
{
	this->setAccelerometerEnabled(true);

	Layer* groundLayer = Layer::create();
	groundLayer->setName("Ground");
	this->addChild(groundLayer);

	background = Sprite::create("chapter1/scene1/mini/background.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2(0.0f, 0.0f));
	groundLayer->addChild(background, 3);

	auto background2 = Sprite::create("chapter1/scene1/mini/background.png");
	background2->setAnchorPoint(Vec2::ZERO);
	background2->setPosition(Vec2(-background->getBoundingBox().size.width, 0.0f));
	groundLayer->addChild(background2, 3);

	groundLayer->runAction(RepeatForever::create(Sequence::create(MoveTo::create(18.0f, Vec2(WIDTH * 2, 0)), Place::create(Vec2::ZERO), NULL)));

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);

	girls = Sprite::create("chapter1/scene1/mini/1.png");
	girls->setPosition(Vec2(WIDTH - 200, HEIGHT - HEIGHT / 2));
	girls->setScale(0.74f);
	this->addChild(girls);

	Animation * ani = Animation::create();
	ani->addSpriteFrameWithFileName("chapter1/scene1/mini/1.png");
	ani->addSpriteFrameWithFileName("chapter1/scene1/mini/2.png");
	ani->addSpriteFrameWithFileName("chapter1/scene1/mini/3.png");
	ani->addSpriteFrameWithFileName("chapter1/scene1/mini/4.png");
	ani->addSpriteFrameWithFileName("chapter1/scene1/mini/5.png");

	ani->setDelayPerUnit(0.15f);
	girls->runAction(RepeatForever::create(Animate::create(ani)));

	// Ÿ�� ��
	timer_bar = Sprite::create("common/timer_bar.png");
	timer_bar->setPosition(Vec2(60, HEIGHT / 2));
	timer_bar->setRotation(90);
	this->addChild(timer_bar, 3);

	original_Scale = timer_bar->getScaleX() / GAME_TIME;
	srand(time(NULL));

	excute = true;

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);

	// �ʱ�ȭ
	miniState = { 0 };
	object_Time = { 1.5f };
	object_Speed = { 2.0f };
	object_Num = { 2 };
	excute = { true };
	create_Time = 0.0f;
	bar_Time = 0.0f;
	downgradeTime = 0.0f;
	UserDefault::getInstance()->setIntegerForKey("GameState", 1);
	return true;
}

void Chapter1_c1_minigame::PauseMiniGame()
{
	//excute = false;
}

void Chapter1_c1_minigame::update(float dt)
{
	if (excute)
	{
		//background->setPositionX(background->getPosition().x + 40.0f* dt);
		create_Time += dt;
		bar_Time += dt;
		downgradeTime += dt;
		timer_bar_Time += dt;

		if (timer_bar_Time >= 1.0f){

			timer_bar_Time -= timer_bar_Time;
			timer_bar->setScaleX(timer_bar->getScaleX() - original_Scale);
			if (timer_bar->getScaleX() <= 0)
			{
				timer_bar->setScaleX(0);
				background->pause();
				girls->pause();
				gameresult->CLEAR();
				excute = false;
				this->getChildByName("Ground")->stopAllActions();
			}
		}

		// ������ �϶�
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			playerVelocity.y += 50.0f * dt;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			playerVelocity.y -= 50.0f * dt;
		}
#endif
		//-------------------------------
		Vec2 temp = girls->getPosition();

		temp.x += playerVelocity.x;
		temp.y += playerVelocity.y;

		if (temp.x < 50)
			temp.x = 50;
		if (temp.x > WIDTH - 80)
			temp.x = WIDTH - 80;
		if (temp.y < 190)
			temp.y = 190;
		if (temp.y > 550)
			temp.y = 550;

		girls->setPosition(temp);

		//================================
		// ������Ʈ ��
		if (create_Time >= object_Time)
		{
			create_Time -= create_Time;
			createObject();
		}
		moveObject();
		collide();

		//===============================
		// DownGrade
		if (downgradeTime >= DOWNGRADE)
		{
			downgradeTime -= downgradeTime;
			object_Time -= 0.18f;
			if (object_Time <= 0.25f)
				object_Time = 0.25f;

			log("ObjectTime : %.2f", object_Time);
			object_Speed += 2.6f;
			if (object_Speed >= 17.0f)
				object_Speed = 17.0f;

			log("ObjectSpeed : %.2f", object_Speed);
		}

	}
}
bool Chapter1_c1_minigame::onTouchStart(Touch* touch)
{
	return true;
}
void Chapter1_c1_minigame::onTouchMove(Touch* touch)
{

}
void Chapter1_c1_minigame::onTouchEnd(Touch* touch)
{

}
int Chapter1_c1_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter1_c1_minigame::MiniGameStateReset()
{
	excute = false;
	this->getChildByName("Ground")->stopAllActions();
	timer_bar->stopAllActions();
	gameresult->reset();
}

void Chapter1_c1_minigame::onAcceleration(Acceleration* acc, Event* unused_event)
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
void Chapter1_c1_minigame::createObject()
{
	static auto dist = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(1, 8);
		return dist1(rng);
	};
	static auto onetwo = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(1, 2);
		return dist1(rng);
	};
	static auto roation = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(1, 360);
		return dist1(rng);
	};

	int cnt = dist();
	if (cnt == object_Num)
	{
		cnt = dist();
		object_Num = cnt;
	}


	char str[255];
	int kind = onetwo();
	sprintf(str, "chapter1/scene1/mini/Object%d.png", kind);

	Sprite* obj = Sprite::create(str);
	if (kind == 2)
		obj->setRotation(180);
	else if (kind == 1)
	{
		obj->setRotation(roation());
	}
	switch (cnt)
	{
	case 1:
		obj->setPosition(Vec2(-3, HEIGHT * 0.2f));
		break;
	case 2:
		obj->setPosition(Vec2(-3, HEIGHT * 0.4f));
		break;
	case 3:
		obj->setPosition(Vec2(-3, HEIGHT * 0.6f));
		break;
	case 4:
		obj->setPosition(Vec2(-3, HEIGHT * 0.8f));
		break;
	default:
		obj->setPosition(Vec2(-3, girls->getPosition().y));
		break;
	}
	this->addChild(obj);
	vObject.pushBack(obj);
}

void Chapter1_c1_minigame::moveObject()
{
	for (auto it : vObject)
	{
		Vec2 pos(object_Speed, 0);
		it->setPosition(it->getPosition() + pos);
	}
}

void Chapter1_c1_minigame::collide()
{
	for (auto it : vObject)
	{
		if (it->getBoundingBox().containsPoint(girls->getPosition()))
		{
			if (it->getBoundingBox().intersectsRect(girls->getBoundingBox()))
			{
				//jni_vibrate();
				this->removeChild(it);
				background->pause();
				girls->pause();
				gameresult->FAIL();
				excute = false;

				this->getChildByName("Ground")->stopAllActions();
			}
		}
	}
}
