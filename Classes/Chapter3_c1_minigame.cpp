#include "Chapter3_c1_minigame.h"
#include "GameResult.h"

Chapter3_c1_minigame::Chapter3_c1_minigame()
{
	dragCnt = { 0.0f };
}


Chapter3_c1_minigame::~Chapter3_c1_minigame()
{
}

bool Chapter3_c1_minigame::init()
{
	// 보여질 그림 배경 그림
	Sprite* background = Sprite::create("chapter3/scene1/mini/background.png");
	background->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(background);

	//  holesClipper 재단 노드
	holesClipper = ClippingNode::create();
	holesClipper->setPosition(Vec2::ZERO);
	this->addChild(holesClipper);

	holesClipper->setInverted(true);
	holesClipper->setAlphaThreshold(0.5f);

	// 템플릿 생성 holesStencil
	holesStencil = Node::create();
	holesClipper->setStencil(holesStencil);

	// 바탕 holes 만들기
	//holes = Node::create();
	//holesClipper->addChild(holes); //설정 바닥

	//먼지 추가
	Sprite* dust = Sprite::create("chapter3/scene1/mini/signs.png");
	dust->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	holesClipper->addChild(dust, 1, "dust");

	UserDefault::getInstance()->setIntegerForKey("GameState", 0);

	gameresult = GameResult::createLayer();
	gameresult->init();
	gameresult->Exit();
	this->addChild(gameresult, 5);
	return true;
}
void Chapter3_c1_minigame::update(float dt)
{

}
bool Chapter3_c1_minigame::onTouchStart(Touch* touch)
{
	Vec2 point = touch->getLocation();
	Rect rect = Rect(382, 189, 856, 566);
	if (rect.containsPoint(point))
	{
		auto holeStencil = Sprite::create("common/clean.png");
		holeStencil->setPosition(point);
		holesStencil->addChild(holeStencil);
	}
	return true;
}
void Chapter3_c1_minigame::onTouchMove(Touch* touch)
{
	dragCnt += 0.003f;
	Vec2 point = touch->getLocation();
	Rect rect = Rect(382, 189, 856, 566);
	if (rect.containsPoint(point))
	{
		auto holeStencil = Sprite::create("common/clean.png");
		holeStencil->setPosition(point);
		holesStencil->addChild(holeStencil);
	}

	log("%.3f", dragCnt);

	if (dragCnt >= 1.55f)
	{
		gameresult->CLEAR();
	}
}
void Chapter3_c1_minigame::onTouchEnd(Touch* touch)
{

}
int Chapter3_c1_minigame::getMiniGameState()
{
	return gameresult->getEvent();
}
void Chapter3_c1_minigame::MiniGameStateReset()
{
	gameresult->reset();
}