#include "GameResult.h"

bool GameResult::init()
{
	nEvent = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_result/gameresult.plist", "game_result/gameresult.png");

	soundEnable = false;
	soundDisable = false;

	_resultLayer = Layer::create();
	_resultLayer->setTag(0x123);
	this->addChild(_resultLayer);

	_result = Sprite::create();
	_result->setPosition(Vec2(633, 511));
	//_result->setTag(0x123);
	_resultLayer->addChild(_result, 2);

	_gameresult = Sprite::createWithSpriteFrameName("top.png");
	_gameresult->setPosition(Vec2(WIDTH / 2, HEIGHT / 1.3f));
	_resultLayer->addChild(_gameresult, 1);

	_middle = Sprite::createWithSpriteFrameName("middle.png");
	_middle->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 - 60));
	_resultLayer->addChild(_middle);

	_middle2 = Sprite::createWithSpriteFrameName("middle.png");
	_middle2->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 - 200));
	_resultLayer->addChild(_middle2);

	_playback = Sprite::createWithSpriteFrameName("playback.png");
	_playback->setPosition(Vec2(WIDTH / 2 + 210, HEIGHT / 2 - 65));
	_resultLayer->addChild(_playback);

	// restart
	_restart = MenuItemSprite::create(Sprite::createWithSpriteFrameName("restart.png"), Sprite::createWithSpriteFrameName("restart.png"),
		[=](Ref* sender)
	{
		log("RESTART");
		nEvent = 1;
	});
	_restart->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 - 80));


	// exit
	_exit = MenuItemSprite::create(Sprite::createWithSpriteFrameName("exit.png"), Sprite::createWithSpriteFrameName("exit.png"),
		[=](Ref* sender)
	{
		nEvent = 2;
	});
	_exit->setPosition(Vec2(WIDTH / 2, HEIGHT / 2 - 220));

	// continue
	_continue = MenuItemSprite::create(Sprite::createWithSpriteFrameName("play.png"), Sprite::createWithSpriteFrameName("play.png"),
		[=](Ref* sender)
	{
		nEvent = 3;

	});
	_continue->setPosition(Vec2(855, 275));

	Menu* downMenu = Menu::create(_restart, _exit, nullptr);
	downMenu->setPosition(Vec2::ZERO);
	_resultLayer->addChild(downMenu);

	Menu* playMenu = Menu::create(_continue, nullptr);
	playMenu->setPosition(Vec2::ZERO);
	_resultLayer->addChild(playMenu);

	//_resultLayer->runAction(Sequence::create(MoveTo::create(1.0f, Vec2::ZERO),MoveTo::create(0.15f,Vec2(0,30)),MoveTo::create(0.1f,Vec2::ZERO),nullptr));
	this->Exit();
	return true;
}

void GameResult:: CLEAR()
{
	if (!enable)
	{
		enable = true;
		if (!soundEnable)
		{
			soundEnable = false;
			SimpleAudioEngine::getInstance()->playEffect("BGM/true.wav");
		}
		_result->setTexture("game_result/clear.png");
		_result->runAction(MoveBy::create(0.8f, Vec2(0, -HEIGHT)));

		_gameresult->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -40.0f)), nullptr));

		_restart->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -30.0f)), nullptr));
		_middle->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -30.0f)), nullptr));

		_middle2->runAction(Sequence::create(MoveBy::create(0.8f, Vec2(0, -HEIGHT / 1)), MoveBy::create(0.07f, Vec2(0, 60.0f)), MoveBy::create(0.07f, Vec2(0, -60.0f)), nullptr));
		_exit->runAction(Sequence::create(MoveBy::create(0.6f, Vec2(0, -HEIGHT / 1)), MoveBy::create(0.07f, Vec2(0, 60.0f)), MoveBy::create(0.07f, Vec2(0, -60.0f)), nullptr));

		_playback->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 60.0f)), MoveBy::create(0.04f, Vec2(0, -60.0f)), nullptr));
		_continue->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 60.0f)), MoveBy::create(0.04f, Vec2(0, -60.0f)), nullptr));

		if (UserDefault::getInstance()->getIntegerForKey("GameState") == 1)
		{
			_resultLayer->setPosition(Vec2(-WIDTH / 1.255f, -HEIGHT));
			_resultLayer->setRotation(-90);
		}
	}
	//test(this);
}

void GameResult::FAIL()
{
	if (!enable)
	{
		enable = true;
		if (!soundDisable)
		{
			soundDisable = true;
			SimpleAudioEngine::getInstance()->playEffect("BGM/false.wav");
		}
		_result->setTexture("game_result/fail.png");
		_result->runAction(MoveBy::create(0.8f, Vec2(0, -HEIGHT)));

		_gameresult->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -40.0f)), nullptr));

		_restart->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -30.0f)), nullptr));
		_middle->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 40.0f)), MoveBy::create(0.04f, Vec2(0, -30.0f)), nullptr));

		_middle2->runAction(Sequence::create(MoveBy::create(0.8f, Vec2(0, -HEIGHT / 1)), MoveBy::create(0.07f, Vec2(0, 60.0f)), MoveBy::create(0.07f, Vec2(0, -60.0f)), nullptr));
		_exit->runAction(Sequence::create(MoveBy::create(0.6f, Vec2(0, -HEIGHT / 1)), MoveBy::create(0.07f, Vec2(0, 60.0f)), MoveBy::create(0.07f, Vec2(0, -60.0f)), nullptr));

		//_playback->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 60.0f)), MoveBy::create(0.04f, Vec2(0, -60.0f)), nullptr));
		//_continue->runAction(Sequence::create(MoveBy::create(0.4f, Vec2(0, -HEIGHT / 1.0f)), MoveBy::create(0.05f, Vec2(0, 60.0f)), MoveBy::create(0.04f, Vec2(0, -60.0f)), nullptr));

		if (UserDefault::getInstance()->getIntegerForKey("GameState") == 1)
		{
			_resultLayer->setPosition(Vec2(-WIDTH / 1.255f, -HEIGHT));
			_resultLayer->setRotation(-90);
		}
	}
}

void GameResult::Exit()
{
	INITupload(this);
}

int GameResult::getEvent()
{
	if (nEvent)
	{
		return nEvent;
	}
	else
		return 0;
}

void GameResult::reset()
{
	nEvent = 0;
}