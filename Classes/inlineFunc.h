#ifndef _INLINE_FUNC
#define _INLINE_FUNC
#pragma once
#include "pch.h"
/*

UserDefault::getInstance()
"GameState"
0 ���� Vertical
1 ���� Horizontal

*/

inline void FadeOutIn(Node* node, float sec, bool inout)
{
	Ref* child = nullptr;
	auto children = node->getChildren();

	if (inout)
	{
		node->runAction(Sequence::create(FadeOut::create(sec),RemoveSelf::create(),nullptr));
	}

	//if (inout)
	//{
	//	// Item�̸� �Ѿ
	//	if (node->getTag() == 0x123)
	//		return;
	//	if (node != nullptr)
	//		node->runAction(FadeOut::create(sec));
	//}
	//else
	//{
	//	// Item�̸� �Ѿ
	//	if (node->getTag() == 0x123)
	//		return;
	//	if (node != nullptr)
	//		node->runAction(FadeIn::create(sec));
	//}

	for (size_t i = 0; i < children.size(); i++)
	{
		FadeOutIn(children.at(i), sec, inout);
	}
}

inline void FakeOut(Node* node)
{
	Ref* child = nullptr;
	auto children = node->getChildren();

	node->setVisible(false);
	// Item�̸� �Ѿ
	if (node->getTag() == 0x123)
		return;

	node->runAction(FadeOut::create(0.00001f));

	for (size_t i = 0; i < children.size(); i++)
	{
		FakeOut(children.at(i));
	}
}

inline void FakeIn(Node* node)
{
	Ref* child = nullptr;
	auto children = node->getChildren();

	// Item�̸� �Ѿ
	if (node->getTag() == 0x123)
		return;
	node->setVisible(true);

	for (size_t i = 0; i < children.size(); i++)
	{
		FakeIn(children.at(i));
	}
}

inline void pauseRecursive(Node* node, bool pause)
{
	Ref* child = nullptr;
	auto children = node->getChildren();

	if (pause)
	{
		//node->pause();
		node->pauseSchedulerAndActions();
	}
	else
	{
		//node->resume();
		node->resumeSchedulerAndActions();
	}

	for (size_t i = 0; i<children.size(); i++)
	{
		pauseRecursive(children.at(i), pause);
	}
}

inline void ManagerOutIn(Node* node, bool is)
{
	Ref* child = nullptr;
	auto children = node->getChildren();

	if (is)
	{
		node->setVisible(is);
		node->runAction(FadeOut::create(0.000001f));
	}
	else
	{
		node->setVisible(is);
		node->runAction(FadeIn::create(0.000001f));
	}

	for (size_t i = 0; i<children.size(); i++)
	{
		pauseRecursive(children.at(i), is);
	}
}

inline float Lerp(float value1, float value2, float amount)
{
	return float(value1 + ((float)(value2 - value1) * amount));
}

#endif

inline void pageTurnBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BGM/pageTurn.wav", false);
}

//-----------------------------------------

inline void INITupload(Node* node)
{
	Ref* child = nullptr;
	auto children = node->getChildren();

	if (node->getTag() == 0x123)
		return;

	node->setPosition(Vec2(0, HEIGHT));

	for (size_t i = 0; i < children.size(); i++)
	{
		INITupload(children.at(i));
	}

};
inline void uploadNode(Node* node)
{
	Ref* child = nullptr;
	auto children = node->getChildren();

	if (node->getTag() == 0x123)
		return;

	node->runAction(MoveBy::create(0.5f, Vec2(0, HEIGHT)));

	for (size_t i = 0; i < children.size(); i++)
	{
		uploadNode(children.at(i));
	}

};

//-------------------------------------------------
// �迭�� �����ǥ�� ������
inline Vec2 ArrayPositionReturn(Vec2 basePos)
{
	Vec2 Temp;
	Temp.x = floor(basePos.x / 60);
	Temp.y = floor(basePos.y / 60);

	return Temp;
}
//-------------------------------------------------
// ���� �����ǥ�� �����Ѵ�
inline Vec2 MapPositionReturn(Vec2 basePos)
{
	Vec2 Temp;
	Temp.x = basePos.x * 60 + 50;
	Temp.y = basePos.y * 60 + 30;
	return Temp;
}

class randClass
{
public:
	static int rand(int n, int m)
	{
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(n, m);
		return dist1(rng);
	}
};

#define KR_L_STR(str) L#str