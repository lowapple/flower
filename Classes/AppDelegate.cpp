#include "AppDelegate.h"

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect(D_GAME_NAME, cocos2d::Rect(0, 0, WIDTH, HEIGHT), D_WINDOWS_SHOW);
		// glview = GLView::createWithRect(D_GAME_NAME , cocos2d::Rect(0,0,WIDTH,HEIGHT) , D_WINDOWS_SHOW);
		director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(WIDTH , HEIGHT , kResolutionShowAll);
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);
	auto scene = Intro::createScene();
    director->runWithScene(scene);
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
