#pragma once
#include "pch.h"
#include "MiniGame.h"

#define JUMP_HEIGHT_MAX 300
#define JUMP_HEIGHT_MIN 70

class Huddle : public Sprite
{
private:
public:
	static Huddle* spriteWithFile(const char* FileName, Layer* ownerLayer)
	{
		Huddle* sprite = new Huddle();
		if (sprite && sprite->initWithFile(FileName)){
			sprite->autorelease();
			sprite->rockCreate();
			if (sprite->getTag() != 4){
				ownerLayer->addChild(sprite, 4);
			}
			else
				ownerLayer->addChild(sprite, 6);
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return NULL;
	}

	void rockCreate()
	{
		static auto Tag = [=](){
			random_device rd;
			mt19937_64 rng(rd());
			uniform_int_distribution<int> dist1(1, 4);
			return dist1(rng);
		};
		int tag = 0;
		// 태그를 3번 섞음 = 정확성
		for (int i = 0; i < 3; i++)
		{
			tag = Tag();
		}

		this->setAnchorPoint(Vec2(0.5f, 0.0f));
		this->setTag(tag);
		//------------------------
		switch (tag)
		{
		case 1:
			this->setPosition(Vec2(WIDTH + 10, 180 - 30));
			break;
		case 2:
			this->setPosition(Vec2(WIDTH + 10, 90 - 30));
			break;
		case 3:
			this->setPosition(Vec2(WIDTH + 10, 0 - 30));
			break;
		case 4:
			this->setTexture("chapter3/scene5/mini/1-1.png");
			this->setPosition(Vec2(WIDTH + 10, HEIGHT));
			this->setAnchorPoint(Vec2(0.5f, 1.0f));
			this->setScaleY(1.395f);
			break;
		default:
			break;
		}
		//------------------------
		this->runAction(MoveTo::create(4.0f, Vec2(-100, this->getPosition().y)));
	}
};

class GameResult;
class Chapter3_c5_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	Layer* groundLayer;
	Sprite* background1;
	Sprite* background2;
	float timer_bar_Time = 0.0f;
	Sprite* timer_bar;
	float	original_Scale;
	Vector<Huddle*> vHuddle;

	Sprite* girls;
	bool	jump;
	float	jumpHeight;

	bool	slide;

	int	 moveCnt;
	Vec2 begine;
	Vec2 end;
	bool execute;
public:
	Chapter3_c5_minigame();
	~Chapter3_c5_minigame();

	static Chapter3_c5_minigame* createMiniGame()
	{
		Chapter3_c5_minigame *ret = new Chapter3_c5_minigame();
		if (ret && ret->init())
		{
			ret->autorelease();
			return ret;
		}
		else
		{
			CC_SAFE_DELETE(ret);
			return nullptr;
		}
	}
public:
	bool init() override;
	void update(float dt) override;
	bool onTouchStart(Touch* touch);
	void onTouchMove(Touch* touch);
	void onTouchEnd(Touch* touch);
	int  getMiniGameState();
	void MiniGameStateReset();

	void createHuddle();
	void moveGirls();
};