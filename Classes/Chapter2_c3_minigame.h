#pragma once
#include "pch.h"
#include "MiniGame.h"

#define OVER_COUNT 15

class GameResult;
class Chapter2_c3_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	float Lantern_x;
	float Lantern_y;
	float fUpdate_Time;
	bool TouchCheck;

	float timer_bar_Time = 0.0f;
	Sprite* timer_bar;
	float	original_Scale;

	Sprite*Thresh_Lantern;
	Sprite*timerbar;
	Sprite*BackG;
	Sprite*Creepy_Eyes;

	Label* leftscore;

	ClippingNode* clip;

	DrawNode*drawNode;
	Rect L_bound;
	Rect E_bound;

	int nScore;
	float original_time;
	float rest;
	bool lantern_change;
public:
	Chapter2_c3_minigame();
	~Chapter2_c3_minigame();

	static Chapter2_c3_minigame* createMiniGame()
	{
		Chapter2_c3_minigame *ret = new Chapter2_c3_minigame();
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

	void G_Creepy();
	void TlqkfMask();
	void Light();
	void Eyes_reset();
	void ScoreUpdate(float dt);
};