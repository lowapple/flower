#pragma once
#include "pch.h"
#include "MiniGame.h"

class GameResult;
class Chapter2_c2_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	Sprite* lantern;
	Sprite* match;
	Sprite* matchbox;

	bool matchboxSlide;
	bool touch;
	Vec2 touchPos;
	int  slideCnt;
	bool isClear;
	bool fire_match = false;
	bool fire;

	float fire_time;
public:
	Chapter2_c2_minigame();
	~Chapter2_c2_minigame();

	static Chapter2_c2_minigame* createMiniGame()
	{
		Chapter2_c2_minigame *ret = new Chapter2_c2_minigame();
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
};