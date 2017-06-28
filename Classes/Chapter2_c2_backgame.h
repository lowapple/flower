#pragma once
#include "pch.h"
#include "BackGame.h"

class Item;
class Chapter2_c2_backgame : public BackGame
{
private:
	int nEvent;
	Menu* menu;

	bool door;

	Item* web;
	Item* shovel;
	Item* calender;
public:
	Chapter2_c2_backgame();
	~Chapter2_c2_backgame();
	static Chapter2_c2_backgame* createBackGame()
	{
		Chapter2_c2_backgame *ret = new Chapter2_c2_backgame();
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