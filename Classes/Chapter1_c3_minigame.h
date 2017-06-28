#pragma once
#include "pch.h"
#include "MiniGame.h"

enum class TouchState
{
	NORMAL,
	UP_SLIDE,
	DOWN_SLIDE,
};

class GameResult;
class Chapter1_c3_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	Sprite* background;
	std::queue<Sprite*> vHurdle;

	TouchState touchState;
	Vec2 touchBegine;
	Vec2 touchEnd;
	bool isClear;

	float timebarMinus;
	Sprite* timer_bar;

	bool excute;
	float GAME_TIME = 15.0f;
	int slideTreeCnt;

	float obstacle;
	float timebar;

	int tagNum;
public:
	Chapter1_c3_minigame();
	~Chapter1_c3_minigame();

	static Chapter1_c3_minigame* createMiniGame()
	{
		Chapter1_c3_minigame *ret = new Chapter1_c3_minigame();
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

	// TreeCreator
	void TreeCreator();
};