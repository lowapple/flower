#pragma once
#include "stdafx.h"

class ChatWindow : public Node
{
private:
	bool	isWrite;
	LayerColor* chatWindow;
	// 현재 글자를 표시할 Label
	LabelTTF* chatLabel;
	// 챗팅창 사진
	Sprite* Schatwindow;
	// 현재 표시 할 글자
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

			// 문장을 출력할 대상
			string word = chatStr;

			int startpos = getNthChar_UTF8(word.c_str(), cnt);
			int endpos = getNthChar_UTF8(word.c_str(), cnt + 1);

			// 글자를 쪼개기(시작,얼마나)
			string temp = word.substr(startpos, endpos - startpos);
			// _temp에 쪼갠조각인 temp를 추가
			_temp.append(temp);
			// 글자를 적용(Label)
			chatLabel->setString(_temp.c_str());
			// 글자 카운트를 늘려서 다음글자로 넘어간다.
			cnt = cnt + 1;
			// 글자가 같으면
			if (word == _temp)
			{
				isWrite = false;
				// 스케줄 정지
				unschedule(schedule_selector(ChatWindow::write));
				// 변수 초기화
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
				idx+=2; //한글인지 확인
				HANGUL = true;
				/*CCLog("***********byte 2************");*/  }

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if((ch & 0x80 ) == 0x80 ){
				idx+=3; //한글인지 확인
				HANGUL = true;
				/*CCLog("***********byte 3************");*/  }

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

			if ((ch & 0x80) == 0x80){
				idx += 3; //한글인지 확인 2였음
				HANGUL = true;
				/*CCLog("***********byte 2************"); */
			}

#endif 

			//1바이트 일 경우 
			if (!HANGUL){
				idx += 1;
			}
			utfidx++;
			HANGUL = false;
		}
		return idx;
	}
};