#include "Chapter1.h"

#include "Chapter1_c1_backgame.h"
#include "Chapter1_c2_backgame.h"
#include "Chapter1_c3_backgame.h"

#include "Chapter1_Story_mini1.h"
#include "Chapter1_Story_mini2.h"
#include "Chapter1_Story_mini3.h"

#include "Chapter1_c1_minigame.h"
#include "Chapter1_c2_minigame.h"
#include "Chapter1_c3_minigame.h"


#include "BackGameManager.h"
#include "MiniGameManager.h"


#include "PauseMenu.h"
#include "Chapter2.h"
#include "MainMenu.h"
#include "NoNext.h"

Scene* Chapter1::createScene()
{
	auto scene = Scene::create();
	auto layer = Chapter1::create();
	scene->addChild(layer);
	return scene;
}

bool Chapter1::init()
{
	if (!Layer::init())
		return false;

	// touch listener
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	// keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(Chapter1::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// back game
	backgameLayer = Layer::create();
	this->addChild(backgameLayer, 1);

	backgamemanager = new BackGameManager();
	backgamemanager->setLayer(backgameLayer);
	backgamemanager->initWithChapter(Chapter1_c1_backgame::createBackGame());

	isBackGame = true;

	// mini game
	minigameLayer = Layer::create();
	this->addChild(minigameLayer, 2);

	minigamemanager = new MiniGameManager();
	minigamemanager->setLayer(minigameLayer);
	minigamemanager->initWithMiniGame(Chapter1_c1_minigame::createMiniGame());
	minigamemanager->fadeout();
	minigamemanager->pause();
	minigamemanager->getMiniGame()->PauseMiniGame();

	isMiniGame = false;

	// game clear
	if (UserDefault::getInstance()->getBoolForKey("Ch1c1"))
		scene1 = true;
	else
		scene1 = false;

	if (UserDefault::getInstance()->getBoolForKey("Ch1c2"))
		scene2 = true;
	else
		scene2 = false;

	if (UserDefault::getInstance()->getBoolForKey("Ch1c3"))
		scene3 = true;
	else
		scene3 = false;

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

			if (isMiniGame){
				minigamemanager->pause();
				minigamemanager->getMiniGame()->PauseMiniGame();
			}
			if (isBackGame){
				backgamemanager->pause();
				backgamemanager->getBackGame()->menuPause();
			}
		}
		else
		{
			isPause = false;
			pause_menu->disable();
			if (isBackGame)
			{
				backgamemanager->resume();
				backgamemanager->getBackGame()->menuResume();
			}
			if (isMiniGame)
			{
				minigamemanager->resume();
			}

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
	this->addChild(nonext,5);

	this->schedule(schedule_selector(Chapter1::update));
	sceneCnt = 0;
	return true;
}

void Chapter1::update(float delta)
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
			switch (sceneCnt)
			{
			case 0:
				Director::getInstance()->pushScene(TransitionPageTurn::create(0.4f, Chapter1_Story_mini1::createScene(), false));
				break;
			case 1:
				Director::getInstance()->pushScene(TransitionPageTurn::create(0.4f, Chapter1_Story_mini2::createScene(), false));
				break;
			case 2:
				break;
			}

				this->runAction(Sequence::create(DelayTime::create(0.255f),
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
					minigamemanager->initWithMiniGame(Chapter1_c1_minigame::createMiniGame());
					break;
				case 1:
					minigamemanager->initWithMiniGame(Chapter1_c2_minigame::createMiniGame());
					break;
				case 2:
					minigamemanager->initWithMiniGame(Chapter1_c3_minigame::createMiniGame());
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
					minigamemanager->initWithMiniGame(Chapter1_c1_minigame::createMiniGame());
					break;
				case 1:
					minigamemanager->initWithMiniGame(Chapter1_c2_minigame::createMiniGame());
					break;
				case 2:
					minigamemanager->initWithMiniGame(Chapter1_c3_minigame::createMiniGame());
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
					UserDefault::getInstance()->setBoolForKey("Ch1c1", true);
					scene1 = true;
				}
				else if (sceneCnt == 1)
				{
					UserDefault::getInstance()->setBoolForKey("Ch1c2", true);
					scene2 = true;
				}
				else if (sceneCnt == 2)
				{
					Director::getInstance()->pushScene(TransitionPageTurn::create(0.4f, Chapter1_Story_mini3::createScene(), false));
					UserDefault::getInstance()->setBoolForKey("Ch1c3", true);
					scene3 = true;
				}
				backgamemanager->getBackGame()->menuResume();
				break;
			}
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
				{
					backgamemanager->resume();
					backgamemanager->getBackGame()->menuResume();
				}
				if (isMiniGame)
				{
					minigamemanager->resume();
				}
				//if (!isBackGame)
				//	isBackGame = true;
				//else if (!isMiniGame)
				//	isMiniGame = true;

				break;
				// HomeKey
			case 2:
				// pageTurnBGM();
				Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, MainMenu::createScene(), true));
				break;
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

bool Chapter1::onTouchBegan(Touch *touch, Event *unused_event)
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
void Chapter1::onTouchMoved(Touch *touch, Event *unused_event)
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
void Chapter1::onTouchEnded(Touch *touch, Event *unused_event)
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
				if (sceneCnt >= 3)
					sceneCnt = 3;
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

void Chapter1::minigameChange()
{
	minigamemanager->getMiniGame()->MiniGameStateReset();
	switch (sceneCnt)
	{
	case 0:
		minigamemanager->changeMiniGame(Chapter1_c1_minigame::createMiniGame());
		break;
	case 1:
		if (scene1){
			minigamemanager->changeMiniGame(Chapter1_c2_minigame::createMiniGame());
		}
		break;
	case 2:
		if (scene2){
			minigamemanager->changeMiniGame(Chapter1_c3_minigame::createMiniGame());
		}
		break;
	default:
		break;
	}
}
void Chapter1::backgameChange()
{
	switch (sceneCnt)
	{
	case 0:
		BGM_PAGE3;
		backgamemanager->changeBackGame(Chapter1_c1_backgame::createBackGame());
		break;
	case 1:
		if (scene1){
			BGM_PAGE3;
			backgamemanager->changeBackGame(Chapter1_c2_backgame::createBackGame());
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
			backgamemanager->changeBackGame(Chapter1_c3_backgame::createBackGame());
		}
		else
		{
			nonext->enable();
			sceneCnt--;
		}
		break;
	case 3:
		if (scene3) {
			//pageTurnBGM();
			UserDefault::getInstance()->setBoolForKey("Chapter1", true);
			Director::getInstance()->replaceScene(TransitionPageTurn::create(0.6f, Chapter2::createScene(), false));
		}
		break;
	}
}
void Chapter1::sceneChange()
{
	minigameChange();
	backgameChange();
}