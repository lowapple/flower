#include "Logo.h"

Scene* Logo::createScene()
{
	auto scene = Scene::create();
	auto layer = Logo::create();
	scene->addChild(layer);
	return scene;
}
bool Logo::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();


	return true;
}