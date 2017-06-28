#pragma once
#include "pch.h"
#include "MiniGame.h"

class GameResult;
class Chapter3_c6_minigame : public MiniGame
{
private:
	Sprite*		_girls;
	Vec2		_touch_position;
	float		_touch_scale;
	bool		_touch_enable;
	GameResult* gameresult;
public:
	Chapter3_c6_minigame();
	~Chapter3_c6_minigame();

	static Chapter3_c6_minigame* createMiniGame()
	{
		Chapter3_c6_minigame *ret = new Chapter3_c6_minigame();
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