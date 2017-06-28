#include "PauseMenu.h"

PauseMenu::PauseMenu()
{

}

PauseMenu::~PauseMenu()
{

}
bool PauseMenu::init()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("menu/pause_menu.plist", "menu/pause_menu.png");

	layer = LayerColor::create(Color4B(0, 0, 0, 0));
	layer->setContentSize(Size(WIDTH, 150));
	layer->setPosition(Vec2(0, HEIGHT  - layer->getContentSize().height));
	layer->setVisible(false);
	layer->setScale(0.4f);

	this->addChild(layer);

	menu_bar = Sprite::create("menu/pause_menu_bar.png");
	menu_bar->setPosition(Vec2(layer->getContentSize().width / 2, layer->getContentSize().height / 2));
	layer->addChild(menu_bar);

	// back
	MenuItemSprite* pause_menu_Restart = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("back.png")),
		Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("back2.png")),
	[&](Ref* sender)
	{
		nEvent = 1;
	});
	pause_menu_Restart->setPosition(Vec2(WIDTH / 2 - 100, layer->getContentSize().height / 2));

	// exitKey
	MenuItemSprite* pause_menu_Exit = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("home.png")),
		Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("home2.png")),
		[&](Ref* sender)
	{
		BGM_PAGE2;
		nEvent = 2;
	});
	pause_menu_Exit->setPosition(Vec2(WIDTH / 2, layer->getContentSize().height / 2));

	// optionKey
	MenuItemSprite* pause_menu_Continue = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("option.png")),
		Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("option2.png")),
		[&](Ref* sender)
	{
		nEvent = 3;
	});
	pause_menu_Continue->setPosition(Vec2(WIDTH / 2 + 100, layer->getContentSize().height / 2));

	Menu* pause_button_menu = Menu::create(pause_menu_Restart, pause_menu_Continue, pause_menu_Exit, nullptr);
	pause_button_menu->setPosition(Vec2::ZERO);
	layer->addChild(pause_button_menu);

	nEvent = 0;
	return true;
}

void PauseMenu::enable()
{
	SimpleAudioEngine::getInstance()->playEffect("BGM/popup.wav");
	layer->setVisible(true);
	layer->runAction(Sequence::create(ScaleTo::create(0.3f, 1.2f), ScaleTo::create(0.1f, 1.0f), nullptr));
	//layer->runAction(MoveTo::create(0.2f, Vec2(0.0f, HEIGHT - layer->getContentSize().height)));
}
void  PauseMenu::disable()
{
	SimpleAudioEngine::getInstance()->playEffect("BGM/popup.wav");
	layer->runAction(Sequence::create(ScaleTo::create(0.09f,1.2f),ScaleTo::create(0.15f, 0.4f), CallFuncN::create(
	[&](Node* node)
	{
		node->setVisible(false);
	}), nullptr));

	//layer->runAction(MoveTo::create(0.2f, Vec2(0.0f, HEIGHT + layer->getContentSize().height)));
}

void  PauseMenu::minienable()
{
	enable();
}
void  PauseMenu::minidisable()
{
	disable();
}

int PauseMenu::getEvent()
{
	return nEvent;
}

void PauseMenu::setEvent(int n)
{
	nEvent = n;
}
