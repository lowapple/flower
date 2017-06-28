#pragma once
#include "pch.h"
#include "MiniGame.h"

class GameResult;
class Chapter1_c1_minigame : public MiniGame
{
private:
	GameResult* gameresult;
	Sprite* girls;
	Sprite* background;

	float timer_bar_Time = 0.0f;
	Sprite* timer_bar;
	float	original_Scale;

	// Object
	float object_Time;
	float object_Speed;
	int	  object_Num;
	Vector<Sprite*> vObject;

	// vel
	Vec2  playerVelocity;
	float DEFAULT_DECELERATION = 0.4f;
	float DEFAULT_SENSITIVITY = 9.8f;
	float MAX_VELOCITY = 100.0f;

	float GAME_TIME = 30.0f;
	float DOWNGRADE = 3.0f;

	// ETC
	int miniState;
	bool excute;
	float bar_Time;
	float create_Time;
	float downgradeTime;
public:
	Chapter1_c1_minigame();
	~Chapter1_c1_minigame();

	static Chapter1_c1_minigame* createMiniGame()
	{
		Chapter1_c1_minigame *ret = new Chapter1_c1_minigame();
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

	//-----------------
	void onAcceleration(Acceleration* acc, Event* unused_event);
	void createObject();
	void moveObject();
	void collide();

	void PauseMiniGame();
};

