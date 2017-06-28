#pragma once
#include "pch.h"

class NoNext : public Layer
{
private:
	bool    _isEnable;
	Sprite* _noNext_sprite;
	Menu  * _yes_menu;
	bool isExecute;
public:
	NoNext() : _isEnable(false){};
	~NoNext(){};

	bool init() override;
	void enable();
};