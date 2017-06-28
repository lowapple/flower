#pragma once
#include "pch.h"

class MiniGame : public Layer
{
private:
protected:
public:
	MiniGame(){ };
	virtual ~MiniGame(){};

	virtual bool init(){ return true; };
	virtual void update(float dt) = 0;

	virtual bool onTouchStart(Touch* touch) = 0;
	virtual void onTouchMove(Touch* touch) = 0;
	virtual void onTouchEnd(Touch* touch) = 0;

	virtual bool clear(){ return false; }
	virtual int  getMiniGameState(){ return 4; }
	virtual void MiniGameStateReset(){}

	virtual void PauseMiniGame(){};
};