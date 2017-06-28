#pragma once
#include "pch.h"
#include "inlineFunc.h"

class MiniGame;
class MiniGameManager
{
private:
	Layer* ownerLayer;
	MiniGame* minigame = nullptr;

public:
	MiniGameManager();
	~MiniGameManager();

	void init();
	void changeMiniGame(MiniGame*);
	void initWithMiniGame(MiniGame*);
	void setLayer(Layer*);
	void start();
	void pause();
	void resume();
	void fadeout();

	MiniGame* getMiniGame();
};