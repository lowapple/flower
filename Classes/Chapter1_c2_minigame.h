#pragma once
#include "pch.h"
#include "MiniGame.h"

class GameResult;
class Chapter1_c2_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	int score;

	float timer_bar_Time = 0.0f;
	Sprite* timer_bar;
	float	original_Scale;
	std::vector<Sprite*> vFootPrint;

	bool execute;
	bool isClear;

	int CUBE = 200;
	float GAMETIME = 15.0f;

	// etc
	float Timebar;
	float ftime;
public:
	Chapter1_c2_minigame();
	~Chapter1_c2_minigame();

	static Chapter1_c2_minigame* createMiniGame()
	{
		Chapter1_c2_minigame *ret = new Chapter1_c2_minigame();
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
	int getMiniGameState();
	void MiniGameStateReset();

	//chapter1_c2 func

	void shake();
};

