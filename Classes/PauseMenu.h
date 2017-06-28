#pragma once
#include "pch.h"
#include "inlineFunc.h"

class PauseMenu : public Layer
{
private:
	LayerColor* layer;
	Sprite*		menu_bar;
	int			nEvent;
public:
	PauseMenu();
	virtual ~PauseMenu();
	static PauseMenu* createPauseMenu()
	{
		PauseMenu *ret = new PauseMenu();
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
	bool init() override;
	void enable();
	void disable();
	void minienable();
	void minidisable();

	int getEvent();
	void setEvent(int);
};
