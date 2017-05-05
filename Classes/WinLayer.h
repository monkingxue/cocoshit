#ifndef _WINLAYER_H_
#define _WINLAYER_H_

#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include"cocostudio\CocoStudio.h"
#include"MenuLayer.h"
#include"SceneManager.h"
#include"SimpleAudioEngine.h"
#include<iostream>

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio;
using namespace ui;
class Winlayer :public Layer
{
public:
	SceneManager * tsm;
	CREATE_FUNC(Winlayer);
	virtual bool init();
	//void clickCallBackMenu(Ref* sender, Widget::TouchEventType controlEvent);
	void clickCallBackExit(Ref* sender);
};

#endif