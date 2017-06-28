#pragma once
#include "cocos2d.h"
#include "pch.h"
USING_NS_CC;

/*
// TESET
// 1. = new Item(...);
// 2. ->setItemScale()
// 3. ->init();
// 4. ->setStory();
// 5. ->addChild();
*/

class Item : public Layer
{
private:
	Sprite*		item;
	Sprite* item_window;
	Label*	story;

	float		scale;
	bool		activity;

	Vec2 backupPos;
	bool itemSound;
public:
	Item(const char* SpritePath, Vec2 vec, Layer* ownerLayer);
	~Item();

	static Item* createItem(const char* SpritePath, Vec2 vec, Layer* ownerLayer)
	{
		Item *ret = new Item(SpritePath,vec,ownerLayer);
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

	Sprite* getItem();
	bool init();
	void enable();
	void disable();
	void setItemScale(float);
	void setStory(const string&);
};