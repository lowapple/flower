#pragma once

#include "stdafx.h"

class Logo : public Layer
{
private:
public:
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(Logo);
};