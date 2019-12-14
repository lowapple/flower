#pragma once

#include "pch.h"

class MyCell
{
private:
	int		rowIdx;
	Sprite *sprite;

public:
	MyCell();
	~MyCell();

	void init(string fileName, Layer *layer);

	void setRowIdx(int rowIdx);
	void setPosition(Vec2 pos);

	Sprite *getSprite();
	int	    getRowIdx();
};