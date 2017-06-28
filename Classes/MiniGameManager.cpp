#include "MiniGameManager.h"
#include "MiniGame.h"

MiniGameManager::MiniGameManager()
{

}

MiniGameManager::~MiniGameManager()
{
	if (minigame)
		delete minigame;
}

// Fadeout -> ����ü -> FadeIn
void MiniGameManager::changeMiniGame(MiniGame* target)
{
	//ownerLayer->runAction(
	//	Sequence::create
	//	(
	//	// 1
	//	CallFunc::create([=]()
	//{
	//	// FadeOut;
	//	if (minigame)
	//		FadeOutIn(minigame, 0.00001f, true);
	//}),
	//	DelayTime::create(0.1f),
	//	// 2
	//	CallFunc::create([=]()
	//{
	//	if (minigame){
	//		minigame->removeAllChildren();
	//		minigame->removeAllChildrenWithCleanup(true);
	//		minigame = nullptr;
	//	}
	//	minigame = target;
	//	minigame->init();
	//	ownerLayer->addChild(minigame, 1);
	//	// ���� FadeOut
	//	FakeOut(minigame);
	//	pauseRecursive(minigame, true);
	//}),
	//	DelayTime::create(0.1f),
	//	// 3
	//	CallFunc::create([=]()
	//{
	//}), NULL));

	FakeOut(target);
	minigame = target;
	ownerLayer->addChild(target, 2);
}

void MiniGameManager::init()
{
	ManagerOutIn(ownerLayer, true);
}

void MiniGameManager::initWithMiniGame(MiniGame* target)
{
	if (minigame)
	{
		minigame->removeAllChildren();
		minigame->removeAllChildrenWithCleanup(true);
		minigame = nullptr;
	}
	minigame = target;
	ownerLayer->addChild(target, 2);
}

//�θ� ���̾ �ʱ�ȭ �Ѵ�
void MiniGameManager::setLayer(Layer* layer)
{
	ownerLayer = layer;
}

//�̴ϰ����� �޾ƿ´�.
MiniGame* MiniGameManager::getMiniGame()
{
	if (minigame)
		return minigame;
}

// �̴ϰ��� ����
void MiniGameManager::start()
{
	if (minigame)
	{
		minigame->init();
		resume();
		FakeIn(minigame);
	}
}

void MiniGameManager::pause()
{
	if (minigame)
	{
		pauseRecursive(minigame, true);
	}
}
void MiniGameManager::resume()
{
	if (minigame){
		pauseRecursive(minigame, false);
	}
}

void MiniGameManager::fadeout()
{
	FakeOut(minigame);
}