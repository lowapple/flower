#include "Chapter3.h"

#include "Chapter3_c1_backgame.h"
#include "Chapter3_c2_backgame.h"
#include "Chapter3_c3_backgame.h"
#include "Chapter3_c4_backgame.h"
#include "Chapter3_c5_backgame.h"
#include "Chapter3_c6_backgame.h"

#include "Chapter3_Story_mini1.h"
#include "Chapter3_Story_mini2.h"
#include "Chapter3_Story_mini3.h"
#include "Chapter3_Story_mini4.h"
#include "Chapter3_Story_mini5.h"
#include "Chapter3_Story_mini6.h"

#include "Chapter3_c1_minigame.h"
#include "Chapter3_c2_minigame.h"
#include "Chapter3_c3_minigame.h"
#include "Chapter3_c4_minigame.h"
#include "Chapter3_c5_minigame.h"
#include "Chapter3_c6_minigame.h"

#include "BackGameManager.h"
#include "MiniGameManager.h"


#include "PauseMenu.h"
#include "MainMenu.h"
#include "NoNext.h"

Scene* Chapter3::createScene()
{
	auto scene = Scene::create();
	auto layer = Chapter3::create();
	scene->addChild(layer);
	return scene;
}

bool Chapter3::init()
{
	if (!Layer::init())
		return false;

	// touch listener
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	// keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(Chapter3::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// back game
	backgameLayer = Layer::create();
	this->addChild(backgameLayer, 1);

	backgamemanager = new BackGameManager();
	backgamemanager->setLayer(backgameLayer);
	backgamemanager->initWithChapter(Chapter3_c1_backgame::createBackGame());

	isBackGame = true;

	// mini game
	minigameLayer = Layer::create();
	this->addChild(minigameLayer, 2);

	minigamemanager = new MiniGameManager();
	minigamemanager->setLayer(minigameLayer);
	minigamemanager->initWithMiniGame(Chapter3_c1_minigame::createMiniGame());
	minigamemanager->fadeout();
	minigamemanager->pause();

	isMiniGame = false;

	// game clear
	if (UserDefault::getInstance()->getBoolForKey("Ch3c1"))
		scene1 = true;
	else
		scene1 = false;

	if (UserDefault::getInstance()->getBoolForKey("Ch3c2") && UserDefault::getInstance()->getBoolForKey("CH3C2_MINI"))
		scene2 = true;
	else
		scene2 = false;

	if (UserDefault::getInstance()->getBoolForKey("Ch3c3"))
		scene3 = true;
	else
		scene3 = false;

	if (UserDefault::getInstance()->getBoolForKey("Ch3c4"))
		scene4 = true;
	else
		scene4 = false;

	if (UserDefault::getInstance()->getBoolForKey("Ch3c5"))
		scene5 = true;
	else
		scene5 = false;

	if (UserDefault::getInstance()->getBoolForKey("Ch3c6"))
		scene6 = true;
	else
		scene6 = false;

	// pause_button
	pause_menu = PauseMenu::createPauseMenu();
	isPause = false;
	this->addChild(pause_menu, 3);

	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("menu/pause_menu.plist", "menu/pause_menu.png");
	// pause_button
	MenuItemSprite* pause_button = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("pause.png")),
		Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("pause2.png")),
		[&](Ref* sender)
	{
		if (!isPause)
		{
			isPause = true;
			if (isMiniGame)
				pause_menu->minienable();
			else
				pause_menu->enable();

			minigamemanager->pause();
			backgamemanager->pause();
			backgamemanager->getBackGame()->menuPause();
		}
		else
		{
			isPause = false;
			pause_menu->disable();
			backgamemanager->resume();
			minigamemanager->resume();
			backgamemanager->getBackGame()->menuResume();

		}
	});
	pause_button->setPosition(Vec2(WIDTH - pause_button->getContentSize().width / 1.25f, HEIGHT - pause_button->getContentSize().height / 1.25f));


	// registered on menu
	Menu* menuPause = Menu::create(pause_button, nullptr);
	menuPause->setPosition(Vec2::ZERO);
	this->addChild(menuPause, 4);

	nonext = new NoNext();
	nonext->init();
	nonext->autorelease();
	this->addChild(nonext, 5);


	this->schedule(schedule_selector(Chapter3::update));
	sceneCnt = 0;
	return true;
}

void Chapter3::update(float delta)
{
	// back & mini game update
	if (!isPause){
		if (isMiniGame)
			minigamemanager->getMiniGame()->update(delta);
		if (isBackGame)
			backgamemanager->getBackGame()->update(delta);
	}

	// selected mini game
	if (isBackGame)
	{
		if (backgamemanager->getBackGame()->getEvent() == 1)
		{
			isBackGame = false;
			isMiniGame = true;

			// mini game story
			/*switch (sceneCnt)
			{
			case 0:
			minigamemanager->initWithMiniGame(Chapter3_c1_minigame::createMiniGame());
			break;
			case 1:
			minigamemanager->initWithMiniGame(Chapter3_c2_minigame::createMiniGame());
			break;
			case 2:
			minigamemanager->initWithMiniGame(Chapter3_c3_minigame::createMiniGame());
			break;
			}*/

			this->runAction(Sequence::create(DelayTime::create(0.455f),
				CallFunc::create([&]()
			{
				minigamemanager->start();
			}), nullptr));
			// back game reset
			backgamemanager->getBackGame()->setEvent(0);
			backgamemanager->getBackGame()->menuPause();
		}
	}

	// game result
	if (isMiniGame)
	{

		if (minigamemanager->getMiniGame()->getMiniGameState() != 0)
		{
			// game result
			// 1. restart
			// 2. exit
			// 3. continue
			switch (minigamemanager->getMiniGame()->getMiniGameState())
			{
				//-------------
				// RESTART
			case 1:
				switch (sceneCnt)
				{
				case 0:
					minigamemanager->initWithMiniGame(Chapter3_c1_minigame::createMiniGame());
					break;
				case 1:
					minigamemanager->initWithMiniGame(Chapter3_c2_minigame::createMiniGame());
					break;
				case 2:
					minigamemanager->initWithMiniGame(Chapter3_c3_minigame::createMiniGame());
					break;
				case 3:
					minigamemanager->initWithMiniGame(Chapter3_c4_minigame::createMiniGame());
					break;
				case 4:
					minigamemanager->initWithMiniGame(Chapter3_c5_minigame::createMiniGame());
					break;
				case 5:
					minigamemanager->initWithMiniGame(Chapter3_c6_minigame::createMiniGame());
					break;
				}
				break;
				//--------------
				// EXIT
			case 2:
				isMiniGame = false;
				isBackGame = true;
				//sceneChange();
				//minigameChange();
				switch (sceneCnt)
				{
				case 0:
					minigamemanager->initWithMiniGame(Chapter3_c1_minigame::createMiniGame());
					break;
				case 1:
					minigamemanager->initWithMiniGame(Chapter3_c2_minigame::createMiniGame());
					break;
				case 2:
					minigamemanager->initWithMiniGame(Chapter3_c3_minigame::createMiniGame());
					break;
				case 3:
					minigamemanager->initWithMiniGame(Chapter3_c4_minigame::createMiniGame());
					break;
				case 4:
					minigamemanager->initWithMiniGame(Chapter3_c5_minigame::createMiniGame());
					break;
				case 5:
					minigamemanager->initWithMiniGame(Chapter3_c6_minigame::createMiniGame());
					break;
				}
				minigamemanager->fadeout();
				backgamemanager->getBackGame()->menuResume();

				break;
				//---------------
				// CONTINUE
			case 3:
				isMiniGame = false;
				isBackGame = true;

				FakeOut(minigamemanager->getMiniGame());
				pauseRecursive(minigamemanager->getMiniGame(), true);

				if (sceneCnt == 0)
				{
					UserDefault::getInstance()->setBoolForKey("Ch3c1", true);
					Director::getInstance()->pushScene(TransitionPageTurn::create(0.4f,Chapter3_Story_mini1::createScene(),false));
					scene1 = true;
				}
				else if (sceneCnt == 1)
				{
					UserDefault::getInstance()->setBoolForKey("Ch3c2", true);
					UserDefault::getInstance()->setBoolForKey("CH3C2_MINI", true);
					Director::getInstance()->pushScene(TransitionPageTurn::create(0.4f, Chapter3_Story_mini2::createScene(), false));
					scene2 = true;
				}
				else if (sceneCnt == 2)
				{
					UserDefault::getInstance()->setBoolForKey("Ch3c3", true);
					scene3 = true;
					Director::getInstance()->pushScene(TransitionPageTurn::create(0.4f, Chapter3_Story_mini3::createScene(), false));
				}
				else if (sceneCnt == 3)
				{
					UserDefault::getInstance()->setBoolForKey("Ch3c4", true);
					scene4 = true;
				}
				else if (sceneCnt == 4)
				{
					UserDefault::getInstance()->setBoolForKey("Ch3c5", true);
					scene5 = true;
				}
				else if (sceneCnt == 5)
				{
					UserDefault::getInstance()->setBoolForKey("Ch3c6", true);
					scene6 = true;
				}
				backgamemanager->getBackGame()->menuResume();
				break;
			}
			minigamemanager->getMiniGame()->MiniGameStateReset();
		}
	}

	// Pause Button is running -> touch
	{
		if (pause_menu->getEvent() != 0)
		{
			switch (pause_menu->getEvent())
			{
				// BackKey
			case 1:
				isPause = false;
				pause_menu->disable();
				if (isBackGame)
					backgamemanager->resume();
				if (isMiniGame)
					minigamemanager->resume();

				//if (!isMiniGame)
				//	isMiniGame = true;

				//else if (!isBackGame)
				//	isBackGame = true;
				backgamemanager->getBackGame()->menuResume();
				break;
				// HomeKey
			case 2:
				// pageTurnBGM();
				Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, MainMenu::createScene(), true));
				break;
				// OptionKey
			case 3:
				// OptionKey
				if (isMiniGame)
				{
					isPause = false;
					isMiniGame = false;
					isBackGame = true;

					pause_menu->minidisable();

					minigamemanager->pause();
					FakeOut(minigamemanager->getMiniGame());
					backgamemanager->resume();
				}
				break;
			}

			// reset Pause Button
			pause_menu->setEvent(0);
		}
	}
}

bool Chapter3::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!isPause){
		log("Touch X : %.f Y : %.f", touch->getLocation().x, touch->getLocation().y);
		// touch_slide
		touch_start_vec = touch->getLocation();
		touch_end_vec = touch->getLocation();

		// backgame running -> touch delivery
		if (isBackGame)
			backgamemanager->getBackGame()->onTouchStart(touch);
		// minigame runnint -> touch delivery
		if (isMiniGame)
			minigamemanager->getMiniGame()->onTouchStart(touch);

		return true;
	}
}
void Chapter3::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (!isPause){
		// touch_slide
		touch_end_vec = touch->getLocation();

		// backgame running -> touch delivery
		if (isBackGame)
			backgamemanager->getBackGame()->onTouchMove(touch);
		// minigame runnint -> touch delivery
		if (isMiniGame)
			minigamemanager->getMiniGame()->onTouchMove(touch);
	}
}
void Chapter3::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (!isPause){
		// backgame running -> touch delivery
		if (isBackGame)
			backgamemanager->getBackGame()->onTouchEnd(touch);
		// minigame runnint -> touch delivery
		if (isMiniGame)
			minigamemanager->getMiniGame()->onTouchEnd(touch);
		// scene change
		if (isBackGame)
		{
			if (touch_start_vec.x - 200 >= touch_end_vec.x)
			{
				sceneCnt++;
				if (sceneCnt >= 6)
					sceneCnt = 6;
				sceneChange();
			}
			else if (touch_start_vec.x + 200 <= touch_end_vec.x)
			{
				sceneCnt--;
				if (sceneCnt <= 0)
					sceneCnt = 0;
				sceneChange();
			}
		}
	}
}

void Chapter3::minigameChange()
{
	switch (sceneCnt)
	{
	case 0:{
		minigamemanager->getMiniGame()->MiniGameStateReset();
		minigamemanager->changeMiniGame(Chapter3_c1_minigame::createMiniGame());
	}
		   break;
	case 1:
		if (scene1){
			minigamemanager->getMiniGame()->MiniGameStateReset();
			minigamemanager->changeMiniGame(Chapter3_c2_minigame::createMiniGame());
	}
		break;
	case 2:
		if (scene2){
			minigamemanager->getMiniGame()->MiniGameStateReset();
			minigamemanager->changeMiniGame(Chapter3_c3_minigame::createMiniGame());
		}
		break;
	case 3:
		if (scene3) {
			minigamemanager->getMiniGame()->MiniGameStateReset();
			minigamemanager->changeMiniGame(Chapter3_c4_minigame::createMiniGame());
		}
		break;
	case 4:
		if (scene4){
			minigamemanager->getMiniGame()->MiniGameStateReset();
			minigamemanager->changeMiniGame(Chapter3_c5_minigame::createMiniGame());
		}
		break;
	case 5:
		if (scene5){
			minigamemanager->getMiniGame()->MiniGameStateReset();
			minigamemanager->changeMiniGame(Chapter3_c6_minigame::createMiniGame());
		}
		break;
	default:
		break;
	}
}
void Chapter3::backgameChange()
{
	switch (sceneCnt)
	{
	case 0:
		backgamemanager->changeBackGame(Chapter3_c1_backgame::createBackGame());
		break;
	case 1:
		if (scene1){
			BGM_PAGE3;
			backgamemanager->changeBackGame(Chapter3_c2_backgame::createBackGame());
		}
		else
		{
			nonext->enable();
			sceneCnt--;
		}
		break;
	case 2:
		if (scene2){
			BGM_PAGE3;
			backgamemanager->changeBackGame(Chapter3_c3_backgame::createBackGame());
		}
		else
		{
			nonext->enable();
			sceneCnt--;
		}
		break;
	case 3:
		if (scene3){
			BGM_PAGE3;
			backgamemanager->changeBackGame(Chapter3_c4_backgame::createBackGame());
		}
		else
		{
			nonext->enable();
			sceneCnt--;
		}
		break;
	case 4:
		if (scene4){
			BGM_PAGE3;
			backgamemanager->changeBackGame(Chapter3_c5_backgame::createBackGame());
		}
		else
		{
			nonext->enable();
			sceneCnt--;
		}
		break;
	case 5:
		if (scene5){
			BGM_PAGE3;
			backgamemanager->changeBackGame(Chapter3_c6_backgame::createBackGame());
		}
		else
		{
			nonext->enable();
			sceneCnt--;
		}
		break;
	case 6:
		if (scene4) {
			//pageTurnBGM();
			UserDefault::getInstance()->setBoolForKey("Chapter3", true);
			//Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, Chapter3::createScene(), false));
		}
		break;
	}
}
void Chapter3::sceneChange()
{
	minigameChange();
	backgameChange();
}