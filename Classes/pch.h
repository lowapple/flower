#ifndef _PCH
#define _PCH
#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "audio/include/SimpleAudioEngine.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace ui;

#define WIDTH 1280
#define HEIGHT 720
#define DEVICE_CENTER Vec2(WIDTH/2,HEIGHT/2)
#define D_WINDOWS_SHOW 0.7
#define D_GAME_NAME "Flower"
#define FONT FileUtils::getInstance()->fullPathForFilename("fonts/crayon.ttf")

#define BGM_PAGE  SimpleAudioEngine::getInstance()->playEffect("BGM/page_turn.wav");
#define BGM_PAGE2 SimpleAudioEngine::getInstance()->playEffect("BGM/page_turn2.wav");
#define BGM_PAGE3 SimpleAudioEngine::getInstance()->playEffect("BGM/page_turn3.wav");
#endif