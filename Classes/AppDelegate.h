#pragma once

#include "pch.h"
//#include "Chapter1.h"
#include "MainMenu.h"
#include "Intro.h"

class AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};
