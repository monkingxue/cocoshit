#ifndef _OPERATELAYER_H_
#define _OPERATELAYER_H_

#include"cocos2d.h"
#include"ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;

class OperateLayer : public Layer
{
public:
	CREATE_FUNC(OperateLayer);
	virtual bool init();
	void touchCallBack(Ref* sender, Widget::TouchEventType controlEvent);
};

#endif