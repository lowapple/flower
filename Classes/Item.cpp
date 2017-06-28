#include "Item.h"

Item::Item(const char* SpritePath, Vec2 vec, Layer* ownerLayer)
{
	activity = { false };
	scale = {1.0f};
	backupPos = vec;
	activity = false;

	// 아이템 스프라이트를 생성한다.
	item = Sprite::create(SpritePath);
	item->setPosition(vec);
	this->addChild(item, 5);

	// 아이템 윈도우를 생성하고 visible을 false로 
	item_window = Sprite::create("common/item_window.png");
	item_window->setPosition(DEVICE_CENTER);
	item_window->setVisible(false);
	this->addChild(item_window,4);
	
	// 아이템을 설명하는 Label을 생성합니다. setString으로 내용을 입력해야 합니다.
	story = Label::createWithTTF(" ",string("fonts/crayon.ttf"),30);
	story->setVisible(false);
	story->setColor(Color3B::BLACK);
	story->setPosition(Vec2(WIDTH / 2 + 165, HEIGHT / 2));
	story->setTag(0x123);
	this->addChild(story, 5);

	itemSound = false;
	scale = 1.0f;
}

Item::~Item()
{

}

void Item::enable()
{
	if (!activity)
	{
		SimpleAudioEngine::getInstance()->playEffect("BGM/pickup.wav");
		item_window->setVisible(true);
		story->setVisible(true);
		item->setPosition(Vec2(WIDTH / 2 - 130, HEIGHT / 2));

		item_window->setScale(0.5f);
		item_window->runAction(Sequence::create(ScaleTo::create(0.1f, 1.0f), ScaleTo::create(0.05f, 1.2f), ScaleTo::create(0.03f, 1.0f), nullptr));
		item->runAction(Sequence::create(ScaleBy::create(0.3f, 2.0f), nullptr));

		activity = true;
	}
}

void Item::disable()
{
	// 활성화가 되었을때, 아이템을 사라지게 한다.
	if (activity)
	{
		if (!itemSound)
		{
			itemSound = true;
			SimpleAudioEngine::getInstance()->playEffect("BGM/pickup.wav");
		}
		item_window->runAction(Sequence::create(ScaleTo::create(0.04f, 1.2f), ScaleTo::create(0.3f, 0.0f), CallFuncN::create(
			[=](Node* pSender)
		{
			pSender->setVisible(false);
			pSender->setScale(1.0f);
		}), nullptr));

		item->setScale(scale);
		item->setPosition(backupPos);
		item->runAction(Spawn::create(FadeOut::create(0.8f), MoveBy::create(0.8f, Vec2(0, -20)), nullptr));
		story->setVisible(false);

	}
}

Sprite* Item::getItem()
{
	return item;
}

void Item::setStory(const string& str)
{
	//story->setSystemFontName(FONT);
	story->setString(str);
}

bool Item::init()
{
	cleanup();
	item->setScale(scale);
	item_window->setTag(0x123);
	return true;
}

void Item::setItemScale(float sc)
{
	scale = sc;
	item->setScale(scale);
}
