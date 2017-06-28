#include "MainMenu.h"
#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"

#include "Chapter1_Story.h"

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;

	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/Background/main.mp3",true);
	_menuStart = false;

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	Sprite* background = Sprite::create("main_menu/main_background.png");
	background->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(background, 6);

	_sign = Sprite::create("main_menu/sign.png");
	_sign->setPosition(Vec2(1068, 335 + 150));
	this->addChild(_sign, 7);

	//-------------------------------------------------------------------------------------------------------------------

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_result/gameresult.plist", "game_result/gameresult.png");

	_resultLayer = Layer::create();
	_resultLayer->setTag(0x123);
	this->addChild(_resultLayer, 7);
	/*
	result = 633,511
	*/
	_gameresult = Sprite::createWithSpriteFrameName("top.png");
	_gameresult->setPosition(Vec2(WIDTH / 2, HEIGHT / 1.3f));
	_resultLayer->addChild(_gameresult, 2);
	v_Chapter.pushBack(_gameresult);


	_result = Sprite::create("main_menu/flower.png");
	_result->setPosition(Vec2(352, 388));
	_result->setRotation(-15);
	this->addChild(_result, 7);

	_sceneCnt = 7;
	float XPOS = 477;
	float YPOS = 298;

	for (int i = 0; i < 6; i++)
	{
		Sprite* chapter = Sprite::createWithSpriteFrameName("playback.png");
		chapter->setPosition(Vec2(XPOS, YPOS));
		_resultLayer->addChild(chapter, 3);

		char str[255];
		sprintf(str, "main_menu/button/chapter%d_button.png", i + 1);
		MenuItemSprite* item = MenuItemSprite::create(Sprite::create(str), Sprite::create(str)->divSprite(0.95f), [=](Ref* sender)
		{
			this->changeScene(i);
		});

		item->setPosition(Vec2(XPOS, YPOS - 25));
		item->setScale(1.5f);

		Menu* menu = Menu::create(item, nullptr);
		menu->setPosition(Vec2::ZERO);
		_resultLayer->addChild(menu, 4);
		v_Chapter_menu.pushBack(menu);

		XPOS += 150;

		if (i == 2)
		{
			XPOS = 477;
			YPOS -= 140;
		}
		v_Chapter.pushBack(chapter);
	}

	for (auto it : v_Chapter)
	{
		it->setPosition(Vec2(it->getPosition().x, it->getPosition().y + HEIGHT));
	}

	for (auto it : v_Chapter_menu)
	{
		it->setPosition(Vec2(it->getPosition().x, it->getPosition().y + HEIGHT));
	}

	credit = Sprite::create("common/credit.png");
	credit->setPosition(Vec2(WIDTH / 2, HEIGHT + credit->getContentSize().height / 2 + 20));
	this->addChild(credit,12);
	credit_enable = false;

	_story_label = Label::createWithTTF(" ", string("fonts/crayon.ttf"), 35, Size::ZERO, TextHAlignment::CENTER);
	_story_label->setColor(Color3B::BLACK);
	_story_label->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 + 120));
	this->addChild(_story_label, 7);

	this->schedule(schedule_selector(MainMenu::update));
	return true;
}

bool MainMenu::onTouchBegan(Touch *touch, Event *unused_event)
{
	start_position = touch->getLocation();
	end_position = touch->getLocation();

	if (_sign->getBoundingBox().containsPoint(touch->getLocation()))
	{
		SimpleAudioEngine::getInstance()->playEffect("BGM/popup.wav");
		if (!_menuStart)
		{
			_menuStart = true;
			_sign->runAction(Sequence::create(MoveBy::create(0.1f, Vec2(0, -40)), MoveBy::create(1.0f, Vec2(0, WIDTH)), nullptr));

			float dt = 0.4f;
			for (auto it : v_Chapter){
				it->runAction(Sequence::create(MoveBy::create(dt, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -30.0f)), nullptr));
				dt += 0.04;
			}
			for (auto it : v_Chapter_menu){
				it->runAction(Sequence::create(MoveBy::create(dt, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -30.0f)), nullptr));
			}

			_result->setPosition(Vec2(WIDTH / 2, 606));
			_result->setScale(0.5f);
			_result->setRotation(0);
			_result->setOpacity(0);

			_result->runAction(FadeIn::create(1.5f));
		}
	}
	return true;
}

void MainMenu::update(float delta)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (GetAsyncKeyState(VK_F7))
	{
		UserDefault::getInstance()->setBoolForKey   ("CH3C2_MINI", false);
		UserDefault::getInstance()->setIntegerForKey("CHAPTER1_STORY", 0);

		UserDefault::getInstance()->setBoolForKey("Chapter2", true);
		UserDefault::getInstance()->setBoolForKey("Chapter1", true);

		UserDefault::getInstance()->setBoolForKey("Ch1c1", true);
		UserDefault::getInstance()->setBoolForKey("Ch1c2", false);
		UserDefault::getInstance()->setBoolForKey("Ch1c3", true);

		UserDefault::getInstance()->setBoolForKey("Ch2c1", false);
		UserDefault::getInstance()->setBoolForKey("Ch2c2", true);
		UserDefault::getInstance()->setBoolForKey("Ch2c3", true);
		UserDefault::getInstance()->setBoolForKey("Ch2c4", true);

		UserDefault::getInstance()->setBoolForKey("Ch3c1", true);
		UserDefault::getInstance()->setBoolForKey("Ch3c2", true);
		UserDefault::getInstance()->setBoolForKey("Ch3c3", true);
		UserDefault::getInstance()->setBoolForKey("Ch3c4", true);
		UserDefault::getInstance()->setBoolForKey("Ch3c5", true);
		UserDefault::getInstance()->setBoolForKey("Ch3c6", true);
	}
#endif
}

void MainMenu::onTouchMoved(Touch *touch, Event *unused_event)
{
	end_position = touch->getLocation();
}

void MainMenu::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (end_position.y - 200 >= start_position.y)
	{
		if (!credit_enable)
		{
			credit_enable = true;
			credit->runAction(Sequence::create(MoveTo::create(0.2f, DEVICE_CENTER),MoveBy::create(0.16,Vec2(0,-18)),MoveBy::create(0.10,Vec2(0,18)),nullptr));
		}
	}
	else
	{
		if (credit_enable)
		{
			credit_enable = false;
			credit->runAction(Sequence::create(MoveBy::create(0.11,Vec2(0,-11)), MoveTo::create(0.35f, Vec2(WIDTH / 2, HEIGHT + credit->getContentSize().height / 2 + 20)),nullptr));
		}
	}
}

void MainMenu::changeScene(int c)
{
	switch (c)
	{
	case 0:
		if (_sceneCnt != 0) {

			SimpleAudioEngine::getInstance()->playEffect("BGM/popup.wav");
			// 한글로 바꾸기
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			char MyString[60];
			WideCharToMultiByte(CP_UTF8, 0,KR_L_STR("집에가고 싶어요"), -1, MyString, 60, nullptr, nullptr);
			_story_label->setString(MyString);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_story_label->setString(string("집에가고 싶어요"));
#endif
			_sceneCnt = 0;
		}
		else{
			//pageTurnBGM();
			int story = UserDefault::getInstance()->getIntegerForKey("CHAPTER1_STORY");
			if (story == 0)
			{
				BGM_PAGE;
				Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, Chapter1_Story::createScene(), false));
			}
			else
			{
				BGM_PAGE;
				Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, Chapter1::createScene(), false));
			}
		}
		break;
	case 1:
		if (_sceneCnt != 1) 
		{
			SimpleAudioEngine::getInstance()->playEffect("BGM/popup.wav");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			char MyString[60];
			WideCharToMultiByte(CP_UTF8, 0,KR_L_STR("잠시 쉴래요?"), -1, MyString, 60, nullptr, nullptr);
			_story_label->setString(MyString);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_story_label->setString(string("잠시 쉴래요"));
#endif
			_sceneCnt = 1;
		}
		else{
			if (UserDefault::getInstance()->getBoolForKey("Chapter1")) 
			{
				//pageTurnBGM();
				BGM_PAGE;
				Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, Chapter2::createScene(), false));
			}
		}
		break;
	case 2:
		if (_sceneCnt != 2) 
		{
			SimpleAudioEngine::getInstance()->playEffect("BGM/popup.wav");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			char MyString[60];
			WideCharToMultiByte(CP_UTF8, 0,KR_L_STR("어두운곳은 싫어"), -1, MyString, 60, nullptr, nullptr);
			_story_label->setString(MyString);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_story_label->setString(string("어두운곳은 싫어"));
#endif
			_sceneCnt = 2;
		}
		else{
			if (UserDefault::getInstance()->getBoolForKey("Chapter2")) {
				//pageTurnBGM();
				BGM_PAGE;
				Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, Chapter3::createScene(), false));
			}
		}
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}
}
