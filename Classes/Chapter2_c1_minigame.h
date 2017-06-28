#pragma once
#include "pch.h"
#include "MiniGame.h"

class Moth : public Sprite
{
public:
	bool touch;
	bool enable;
public:
	Vec2 old_pos;
	Moth()
		: touch(false)
		, enable(true)
		, old_pos(Vec2::ZERO){}
	~Moth(){};

	static Moth* spriteWithFile(const char* FileName)
	{
		Moth* sprite = new Moth();
		if (sprite && sprite->initWithFile(FileName)){
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return NULL;
	}
};

class GameResult;
class Chapter2_c1_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	// ��ġ�� ��ǥ�� �Է¹��� ------------------------------
	Vec2 touchPos;

	// �ݵ������� �������� �����ϰ� ��ġ�� ������ �Ǵ� -------
	Vector<Moth*> vMoth;

	// �ݵ����̸� ������ ���̽�
	Sprite* mothCase;

	int mothCnt;
	bool isClear;


	int MOTHNUM;
public:
	Chapter2_c1_minigame();
	~Chapter2_c1_minigame();

	static Chapter2_c1_minigame* createMiniGame()
	{
		Chapter2_c1_minigame *ret = new Chapter2_c1_minigame();
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