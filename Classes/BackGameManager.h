#pragma once
#include "pch.h"
#include "inlineFunc.h"

class BackGame;
class BackGameManager
{
private:
	Layer* ownerLayer;
	BackGame* backgame = nullptr;

public:
	BackGameManager();
	~BackGameManager();

	bool init();
	void pause();
	void resume();

	BackGame* getBackGame();
	
	void setLayer(Layer* layer);
	void initWithChapter(BackGame* target);
	void changeBackGame(BackGame* target);
};
