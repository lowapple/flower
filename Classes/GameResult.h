#ifndef CLEAR_FAIL
#define CLEAR_FAIL
#pragma once
#include "pch.h"
#include "inlineFunc.h"

class GameResult : public Layer
{
private:
	// Event
	int nEvent;

	// Enable
	bool enable;
	bool soundEnable;
	bool soundDisable;
	// GAME_STATE

	Sprite*			_result;

	Layer*			_resultLayer;
	Sprite*			_gameresult;
	Sprite*			_middle;
	Sprite*			_middle2;
	Sprite*			_playback;

	MenuItemSprite*  _restart;
	MenuItemSprite*  _exit;
	MenuItemSprite*  _continue;

public:
	GameResult()
		: enable(false),
		nEvent(0){};
	~GameResult(){};
	static GameResult* createLayer()
	{
		GameResult* sprite = new GameResult();
		if (sprite && sprite->init())
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return NULL;
	}

	bool init() override;

	void CLEAR();

	void FAIL();

	void Exit();

	int getEvent();

	void reset();
};

#endif
