#pragma once
#include "pch.h"
#include "MiniGame.h"

class GameResult;
class Chapter3_c4_minigame : public MiniGame
{
private:
	Sprite* exit_sprite;
	Vector<Sprite*> points;
	GameResult* gameresult;

	int nEvent;
public:
	Chapter3_c4_minigame();
	~Chapter3_c4_minigame();

	static Chapter3_c4_minigame* createMiniGame()
	{
		Chapter3_c4_minigame *ret = new Chapter3_c4_minigame();
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

	bool point_to_clear();
};