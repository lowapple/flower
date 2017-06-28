#pragma once
#include "pch.h"
#include "MiniGame.h"

class GameResult;
class Chapter3_c2_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	Sprite* background;
	Vec2 playerVelocity;
	//---------------------------
	// VEL
	float DEFAULT_DECELERATION = 0.4f;
	float DEFAULT_SENSITIVITY = 9.8f;
	float MAX_VELOCITY = 100.0f;

	Vector<Sprite*> _vlight;
	int				light_cnt;
public:
	Chapter3_c2_minigame();
	~Chapter3_c2_minigame();

	static Chapter3_c2_minigame* createMiniGame()
	{
		Chapter3_c2_minigame *ret = new Chapter3_c2_minigame();
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

	void onAcceleration(Acceleration* acc, Event* unused_event);
};