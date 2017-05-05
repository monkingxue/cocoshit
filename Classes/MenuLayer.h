#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include"cocos2d.h"
#include"SceneManager.h"
#include"ui\CocosGUI.h"
#include"cocostudio\CocoStudio.h"
#include"ControlLayer.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class MenuLayer : public Layer
{
public:
	SceneManager * tsm;

	CREATE_FUNC(MenuLayer);
	virtual bool init();
	void clickCallBackStart(Ref* sender, Widget::TouchEventType controlEvent);
	void clickCallBackExit(Ref* sender);
	void clickCallBackSettings(Ref* sender, Widget::TouchEventType controlEvent);
};

#endif