#pragma once

#include "pch.h"

class Logo : public Layer
{
private:
public:
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(Logo);
};