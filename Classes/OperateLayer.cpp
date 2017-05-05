#include"OperateLayer.h"

bool OperateLayer::init()
{
	Button* button = Button::create();
	button->loadTextures("pressbutton.png", "releasebutton.png");
	button->setPosition(Point(700, 150));
	button->addTouchEventListener(CC_CALLBACK_2(OperateLayer::touchCallBack,this));
	this->addChild(button, 99);
	return true;
}

void OperateLayer::touchCallBack(Ref* sender, Widget::TouchEventType controlEvent)
{

}