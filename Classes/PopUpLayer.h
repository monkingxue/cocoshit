#ifndef _POPUPLAYER_H_
#define _POPUPLAYER_H_

#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include"cocostudio\CocoStudio.h"
#include"MenuLayer.h"
#include"SceneManager.h"
#include"SimpleAudioEngine.h"
#include"SimpleAudioEngine.h"
#include"ControlLayer.h"
#include<iostream>

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio;
using namespace ui;

class PopUpLayer :public Layer
{
public:
	bool operateMode;//���ڴ���setting�иı�Ĳ�����ʽ��1��ʾ���̣�0��ʾҡ��
	SceneManager* tsm;
	CREATE_FUNC(PopUpLayer);
	virtual bool init();
	void clickCallBackReturn(Ref* sender, Widget::TouchEventType controlEvent);
	void sliderEvent(Ref* sender, Slider::EventType type);
	void changeState(Ref* sender, Widget::TouchEventType controlEvent);
	void changeButtonState();//�ı䰴ť��ʽ������/����

private:
	Button* keyboardButton;
	Button* rockerButton;

};
#endif