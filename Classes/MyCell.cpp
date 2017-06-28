#include "MyCell.h"

MyCell:: MyCell() {
	this->sprite = nullptr;
}

MyCell::~MyCell() {
	this->sprite = nullptr;
}

void MyCell::init(string fileName, Layer *layer) {
	this->sprite = Sprite::create(fileName);

	layer->addChild(this->sprite);
}

void MyCell::setRowIdx(int rowIdx) {
	this->rowIdx = rowIdx;
}

void MyCell::setPosition(Vec2 pos) {
	this->sprite->setPosition(pos);
}

Sprite *MyCell::getSprite() {
	return this->sprite;
}

int MyCell::getRowIdx() {
	return this->rowIdx;
}