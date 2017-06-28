#pragma once
#include "pch.h"
#include "BackGame.h"

class Item;
class Chapter3_c4_backgame : public BackGame
{
private:
	int nEvent;
	Menu* menu;

	Item* rope;
	bool EventBlock;
public:
	Chapter3_c4_backgame();
	~Chapter3_c4_backgame();
	static Chapter3_c4_backgame* createBackGame()
	{
		Chapter3_c4_backgame *ret = new Chapter3_c4_backgame();
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