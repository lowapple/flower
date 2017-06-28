#pragma once
#include "stdafx.h"

class ChatWindow : public Node
{
private:
	bool	isWrite;
	LayerColor* chatWindow;
	// ���� ���ڸ� ǥ���� Label
	LabelTTF* chatLabel;
	// ê��â ����
	Sprite* Schatwindow;
	// ���� ǥ�� �� ����
	string chatStr;
protected:
public:
	void createChatWindow()
	{
		chatWindow = LayerColor::create(Color4B(0.0f,0.0f,0.0f,0.0f));
		chatWindow->setContentSize(Size(320, 200));
		this->addChild(chatWindow);

		Schatwindow = Sprite::create("chatwindow.jpg");
		Schatwindow->setPosition(Vec2(chatWindow->getContentSize().width / 2, chatWindow->getContentSize().height/2));
		chatWindow->addChild(Schatwindow);

		chatLabel = LabelTTF::create(" ","fonts/Marker Felt.ttf",30,Size(250,250),TextHAlignment::CENTER,TextVAlignment::TOP);
		//chatLabel->setAnchorPoint(Vec2::ZERO);
		chatLabel->setPosition(Vec2(chatWindow->getContentSize().width * 0.5f, chatWindow->getContentSize().height * 0.4f));
		chatLabel->setColor(Color3B::BLACK);

		chatWindow->addChild(chatLabel);

		isWrite = false;
	}

	Sprite* getChatWindow()
	{
		return Schatwindow;
	}

	void setChatWindowPosition(Vec2 position)
	{
		chatWindow->setPosition(position);
	}

	void setChatString(const char* chat)
	{
		string temp = chat;
		chatStr.swap(temp);
	}

	void update(float dt)
	{

	}

	void enable()
	{
		isWrite = true;
		//chatWindow->setOpacity(255);
		Schatwindow->setOpacity(255);
		chatLabel->setOpacity(255);
		schedule(schedule_selector(ChatWindow::write),0.05);
	}

	void disable()
	{
		chatWindow->setOpacity(0);
		Schatwindow->setOpacity(0);
		chatLabel->setOpacity(0);
		unschedule(schedule_selector(ChatWindow::write));
	}
	void write(float f)
	{
		if (isWrite)
		{
			static int cnt = 0;
			static string _temp;

			// ������ ����� ���
			string word = chatStr;

			int startpos = getNthChar_UTF8(word.c_str(), cnt);
			int endpos = getNthChar_UTF8(word.c_str(), cnt + 1);

			// ���ڸ� �ɰ���(����,�󸶳�)
			string temp = word.substr(startpos, endpos - startpos);
			// _temp�� �ɰ������� temp�� �߰�
			_temp.append(temp);
			// ���ڸ� ����(Label)
			chatLabel->setString(_temp.c_str());
			// ���� ī��Ʈ�� �÷��� �������ڷ� �Ѿ��.
			cnt = cnt + 1;
			// ���ڰ� ������
			if (word == _temp)
			{
				isWrite = false;
				// ������ ����
				unschedule(schedule_selector(ChatWindow::write));
				// ���� �ʱ�ȭ
				cnt = 0;
				chatStr.clear();
				_temp.clear();
			}
		}
	}

	int getNthChar_UTF8(const char * str, int nChar)
	{
		int idx = 0, utfidx = 0;
		bool HANGUL = false;
		unsigned char ch;
		while ((ch = str[idx]))
		{
			if (utfidx >= nChar) {

				break;
			}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

			if((ch & 0x80 ) == 0x80 ){
				idx+=2; //�ѱ����� Ȯ��
				HANGUL = true;
				/*CCLog("***********byte 2************");*/  }

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if((ch & 0x80 ) == 0x80 ){
				idx+=3; //�ѱ����� Ȯ��
				HANGUL = true;
				/*CCLog("***********byte 3************");*/  }

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

			if ((ch & 0x80) == 0x80){
				idx += 3; //�ѱ����� Ȯ�� 2����
				HANGUL = true;
				/*CCLog("***********byte 2************"); */
			}

#endif 

			//1����Ʈ �� ��� 
			if (!HANGUL){
				idx += 1;
			}
			utfidx++;
			HANGUL = false;
		}
		return idx;
	}
};