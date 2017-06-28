#include "MyContainer.h"
#include "MyCell.h"

MyContainer::MyContainer() {
	this->layer = nullptr;
	this->cells = nullptr;
}

MyContainer::~MyContainer() {
	this->layer = nullptr;
	CC_SAFE_DELETE_ARRAY(this->cells);
}

void MyContainer::init(int rowNum, int cellWidth, int cellHeight, Layer *layer) {
	this->rowNum = rowNum;
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;

	this->layer = Layer::create();
	layer->addChild(this->layer);

	this->cells = new MyCell[rowNum];
	for (int i = 0; i < rowNum; i++) {
		this->cells[i].setRowIdx(i);
	}

	this->currOffX = 0.f;
}

void MyContainer::generateCell(string fileName, int rowIdx) {
	this->cells[rowIdx].init(fileName, this->layer);
	this->cells[rowIdx].setPosition(
		Vec2(rowIdx * this->cellWidth + this->cellWidth / 2, 
			 this->cellHeight / 2));
}

void MyContainer::update(Vec2 delta) {
	if (this->rowNum == 1)
		return;

	this->currOffX -= delta.x;

	if (this->currOffX < 0.f) {
		this->currOffX += this->cellWidth;

		// ++

		for (int i = 0; i < this->rowNum; i++) {
			this->cells[i].setRowIdx((this->cells[i].getRowIdx() + 1) % this->rowNum);
		}
	}
	else if (this->currOffX >= this->cellWidth) {
		this->currOffX -= this->cellWidth;

		// --

		for (int i = 0; i < this->rowNum; i++) {
			this->cells[i].setRowIdx(
				((this->cells[i].getRowIdx() - 1) + this->rowNum) % this->rowNum);
		}
	}

	for (int i = 0; i < this->rowNum; i++) {
		int idx = this->cells[i].getRowIdx();

		this->cells[i].setPosition(
			Vec2(idx * this->cellWidth + this->cellWidth / 2,
				 this->cellHeight / 2));
	}

	this->layer->setPosition(Vec2(-this->currOffX, 0));
}