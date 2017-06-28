#pragma once
#include "pch.h"

class Chapter2_c1_backgame;
class Chapter2_c2_backgame;
class Chapter2_c3_backgame;
class Chapter2_c4_backgame;

class Chapter2_Story_mini1;
class Chapter2_Story_mini2;
class Chapter2_Story_mini3;
class Chapter2_Story_mini4;

class Chapter2_c1_minigame;
class Chapter2_c2_minigame;
class Chapter2_c3_minigame;
class Chapter2_c4_minigame;

class MiniGameManager;
class BackGameManager;

class PauseMenu;

class Chapter3;
class MainMenu;
class NoNext;
class Chapter2 : public Layer
{
private:
	// back game
	Layer*			 backgameLayer;		// layer
	BackGameManager* backgamemanager;   // manager
	bool			 isBackGame;		// running


	// mini game
	Layer*			 minigameLayer;
	MiniGameManager* minigamemanager;
	bool			 isMiniGame;

	// scene clear Existence and nonexistence
	bool scene1;
	bool scene2;
	bool scene3;
	bool scene4;

	int	 sceneCnt;

	// touch_slide_use
	Vec2 touch_start_vec;
	Vec2 touch_end_vec;

	// pasue & option menu
	PauseMenu* pause_menu;
	bool isPause;

	NoNext* nonext;
public:
	static Scene* createScene();
	bool init() override;
	void update(float delta);
	CREATE_FUNC(Chapter2);

	// touch func
	bool onTouchBegan(Touch *touch, Event *unused_event) override;
	void onTouchMoved(Touch *touch, Event *unused_event) override;
	void onTouchEnded(Touch *touch, Event *unused_event) override;

public:
	// back&mini changeFunc
	void minigameChange();
	void backgameChange();
	void sceneChange();
};