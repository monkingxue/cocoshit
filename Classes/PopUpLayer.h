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
	bool operateMode;//用于储存setting中改变的操作方式，1表示键盘，0表示摇杆
	SceneManager* tsm;
	CREATE_FUNC(PopUpLayer);
	virtual bool init();
	void clickCallBackReturn(Ref* sender, Widget::TouchEventType controlEvent);
	void sliderEvent(Ref* sender, Slider::EventType type);
	void changeState(Ref* sender, Widget::TouchEventType controlEvent);
	void changeButtonState();//改变按钮样式：启用/禁用

private:
	Button* keyboardButton;
	Button* rockerButton;

};
#endif