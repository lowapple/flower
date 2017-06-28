#pragma once
#include "pch.h"

class BackGame : public Layer
{
private:
public:
	BackGame(){}
	virtual ~BackGame(){}

	virtual bool init() { return true; }
	virtual void update(float delta){}
	
	virtual int getEvent() = 0;
	virtual void setEvent(int) = 0;

	virtual bool onTouchStart(Touch* touch) = 0;
	virtual void onTouchMove(Touch* touch) = 0;
	virtual void onTouchEnd(Touch* touch) = 0;

	virtual void menuPause(void) = 0;
	virtual void menuResume(void) = 0;
};