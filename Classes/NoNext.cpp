#include "NoNext.h"

bool NoNext::init()
{
	_noNext_sprite = Sprite::create("common/no_next.png");
	_noNext_sprite->setPosition(DEVICE_CENTER);
	_noNext_sprite->setScale(0.5f);
	_noNext_sprite->setVisible(false);
	this->addChild(_noNext_sprite);


	auto _yes_button = MenuItemImage::create("common/success.png", "common/success2.png", [&](Ref*sender)
	{
		if (_isEnable)
		{
			SimpleAudioEngine::getInstance()->playEffect("BGM/button.wav");
			_yes_menu->setVisible(false);
			_yes_menu->setEnabled(false);
			_noNext_sprite->runAction(Sequence::create(ScaleTo::create(0.2f, 1.2f), ScaleTo::create(0.07f, 0.4f),FadeOut::create(0.03f), nullptr));
		}
	});
	_yes_button->setPosition(Vec2(WIDTH / 2,180));
	
	_yes_menu = Menu::create(_yes_button, nullptr);
	_yes_menu->setPosition(Vec2::ZERO);
	_yes_menu->setVisible(false);
	_yes_menu->setEnabled(false);
	this->addChild(_yes_menu);
	return true;
}

void NoNext::enable()
{
	_isEnable = true;
	_noNext_sprite->setVisible(true);
	_noNext_sprite->runAction(Sequence::create(FadeIn::create(0.03f),ScaleTo::create(0.2f, 1.2f), ScaleTo::create(0.05f, 1.0f), nullptr));
	_yes_menu->setVisible(true);
	_yes_menu->setEnabled(true);
}