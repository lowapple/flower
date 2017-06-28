#pragma once
#include "pch.h"
#include "BackGame.h"

class Chapter3_c2_backgame : public BackGame
{
private:
	int   nEvent;
	Sprite* background;
	Menu* menu;
	bool  black_out;
public:
	Chapter3_c2_backgame();
	~Chapter3_c2_backgame();
	static Chapter3_c2_backgame* createBackGame()
	{
		Chapter3_c2_backgame *ret = new Chapter3_c2_backgame();
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
	bool init()				 override;
	void update(float delta) override;

	bool onTouchStart(Touch* touch) override;
	void onTouchMove(Touch* touch)  override;
	void onTouchEnd(Touch* touch)   override;

	int getEvent()			 override;
	void setEvent(int) override;

	void menuPause() override;
	void menuResume() override;
};