#pragma once
#include "pch.h"
#include "inlineFunc.h"

class Chapter1;
class Chapter2;
class Chapter3;

class Chapter1_Story;
class MainMenu : public LayerColor
{
public:
	MainMenu();
	~MainMenu();

	static Scene* createScene();
	bool init() override;
	void update(float delta);
	CREATE_FUNC(MainMenu);
public:
	bool onTouchBegan(Touch *touch, Event *unused_event) override;
	void onTouchMoved(Touch *touch, Event *unused_event) override;
	void onTouchEnded(Touch *touch, Event *unused_event) override;

private:
	MenuItemSprite* film;
	MenuItemSprite* flower;

	//-------------------------

	Layer*			_resultLayer;
	Sprite*			_result;
	Sprite*			_gameresult;
	Sprite*			_sign;
	Vector<Sprite*> v_Chapter;
	Vector<Menu*>	v_Chapter_menu;
	int				_sceneCnt;

	bool			_menuStart;
	void changeScene(int);

	// CHAPTER_STORY
	Label*		_story_label;

	Sprite* credit;
	Vec2 start_position;
	Vec2 end_position;
	bool credit_enable;
};
