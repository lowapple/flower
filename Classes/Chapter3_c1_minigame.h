#pragma once
#include "pch.h"
#include "MiniGame.h"

class GameResult;
class Chapter3_c1_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	// ClippingNode
	ClippingNode* holesClipper; // ��� ���
	Node* holesStencil; // ���ø� ���
	Node* holes; // �ٴ� ���

	float dragCnt;
public:
	Chapter3_c1_minigame();
	~Chapter3_c1_minigame();

	static Chapter3_c1_minigame* createMiniGame()
	{
		Chapter3_c1_minigame *ret = new Chapter3_c1_minigame();
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
public:
	bool init() override;
	void update(float dt) override;
	bool onTouchStart(Touch* touch);
	void onTouchMove(Touch* touch);
	void onTouchEnd(Touch* touch);
	int  getMiniGameState();
	void MiniGameStateReset();
};