#pragma once
#include "pch.h"
#include "MiniGame.h"

#define RadToDeg 57.29577951f
#define DegToRad 0.017453293f
#define PI 3.1415926f

class rock : public Sprite
{
public:
	float _time;
	float _angle;
public:
	rock()
		: _angle(0.0f)
		, _time(0.0f){};
	virtual ~rock(){};
	static rock* createrock(const char* str)
	{
		rock *sprite = new (std::nothrow) rock();
		if (sprite && sprite->initWithFile(str))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	void setDgree(float angle)
	{
		_angle = angle;
	}
	void move(float dt)
	{
		this->_time += 2.0f * dt;

		float x = 13 * cos(double(this->_angle * DegToRad)) * this->_time;
		float y = 13 * sin(double(this->_angle * DegToRad)) * this->_time - ((9.8f * this->_time * this->_time) / 2);
		this->setPosition(Vec2(this->getPosition().x + x, this->getPosition().y + y));
	}
};

class GameResult;
class Chapter3_c3_minigame : public MiniGame
{
private:
	GameResult* gameresult;

	bool touch;

	bool excute;
	float fAngle;
	float x;
	float y;

	Slider* dgree; // 각도 조절
	//-----------------------
	bool	useRock;
	Sprite* stamina;

	float GAME_TIME = 40.0f;

	Vector<rock*> vrock;
	Vector<Sprite*> vwolf;
	Vector<Sprite*> hearts;
	int				heart_cnt;
	Sprite* girls;
	float	randTimer;

	float timer_bar_Time = 0.0f;
	Sprite* timer_bar;
	float	original_Scale;
public:
	Chapter3_c3_minigame();
	~Chapter3_c3_minigame();

	static Chapter3_c3_minigame* createMiniGame()
	{
		Chapter3_c3_minigame *ret = new Chapter3_c3_minigame();
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

	float angle(Vec2, Vec2);

	void makeHeart(int num);
};