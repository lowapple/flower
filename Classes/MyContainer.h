#pragma once

#include "pch.h"

class MyCell;
class MyContainer
{
private:
	Layer *layer;
	int	   cellWidth;
	int	   cellHeight;

	float  currOffX;

	MyCell *cells;
	int		rowNum;

public:
	MyContainer();
	~MyContainer();
	
	void init(int rowNum, int cellWidth, int cellHeight, Layer *layer);
	void generateCell(string fileName, int rowIdx);
	void update(Vec2 delta);
};