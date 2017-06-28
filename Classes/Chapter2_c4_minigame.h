#pragma once
#include "pch.h"
#include "MiniGame.h"

enum class gradient
{
	GREEN_LEFT,
	GREEN_RIGHT,
	YELLOW_LEFT,
	YELLOW_RIGHT,
	RED,
};

#define MAX_GRADIENT 50.0f

class GameResult;
class Chapter2_c4_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	Vec2 playerVelocity;
	Sprite* arrow;
	gradient curArrow;

	Sprite* sensorbar;
	Sprite* character;
	bool  execute;
	//-----------------
	// VEL
	float DEFAULT_DECELERATION = 0.4f;
	float DEFAULT_SENSITIVITY = 89.8f;
	float MAX_VELOCITY = 100.0f;

	float GAME_TIME = 25.0f;
	/*
	SENSITIVITY = 59.8f = /4;
	*/
	Label* gradientLabel;
	Sprite* exclamation_mark;
	Sprite* timer_bar;

	float Time;
public:
	Chapter2_c4_minigame();
	~Chapter2_c4_minigame();

	static Chapter2_c4_minigame* createMiniGame()
	{
		Chapter2_c4_minigame *ret = new Chapter2_c4_minigame();
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
	void changeMotion();
};