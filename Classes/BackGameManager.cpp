#include "BackGameManager.h"
#include "BackGame.h"

BackGameManager::BackGameManager()
{

}

BackGameManager::~BackGameManager()
{
	if (backgame)
		delete backgame;
}

void BackGameManager::changeBackGame(BackGame* target)
{
	//ownerLayer->runAction(
	//	Sequence::create
	//	(
	//	// 1
	//	CallFunc::create([=]()
	//{
	//	// FadeOut;
	//	if (backgame)
	//		FadeOutIn(backgame, 0.15f, true);
	//}),
	//	DelayTime::create(0.2f),
	//	// 2
	//	CallFunc::create([=]()
	//{
	//	if (backgame){
	//		backgame->removeAllChildren();
	//		backgame->removeAllChildrenWithCleanup(true);
	//		backgame = nullptr;
	//	}
	//	backgame = target;
	//	backgame->init();
	//	ownerLayer->addChild(backgame, 1);
	//	// 빠른 FadeOut
	//	FakeOut(backgame);
	//}),
	//	DelayTime::create(0.2f),
	//	// 3
	//	CallFunc::create([=]()
	//{
	//	// FadeIn
	//	FakeIn(backgame);
	//	if (backgame)
	//		FadeOutIn(backgame, 0.15f, false);
	//}), nullptr));
	
	int getZorder = backgame->getZOrder();
	FadeOutIn(backgame, 0.25f, true);
	backgame = target;
	ownerLayer->addChild(target, getZorder-1);

	//ownerLayer->runAction(
	//	Sequence::create
	//	(
	//	// 1
	//	CallFunc::create([=]()
	//{
	//	// FadeOut;
	//	if (backgame)
	//		FadeOutIn(backgame, 0.15f, true);
	//}),
	//	DelayTime::create(0.2f),
	//	// 2
	//	CallFunc::create([=]()
	//{

	//	// 빠른 FadeOut
	//	// FakeOut(backgame);
	//}),
	//	DelayTime::create(0.2f),
	//	// 3
	//	CallFunc::create([=]()
	//{
	//	// FadeIn
	//	//FakeIn(backgame);
	//	//if (backgame)
	//	//	FadeOutIn(backgame, 0.15f, false);
	//}), nullptr));
}

bool BackGameManager::init()
{

	return true;
}

void BackGameManager::initWithChapter(BackGame* target)
{
	if (backgame)
	{
		backgame->removeAllChildren();
		backgame->removeAllChildrenWithCleanup(true);
		backgame = nullptr;
	}
	backgame = target;
	ownerLayer->addChild(target, 1);
}

void BackGameManager::setLayer(Layer* layer)
{
	ownerLayer = layer;
}

BackGame* BackGameManager::getBackGame()
{
	return backgame;
}

void BackGameManager::pause()
{
	pauseRecursive(ownerLayer, true);
}

void BackGameManager::resume()
{
	pauseRecursive(ownerLayer, false);
}