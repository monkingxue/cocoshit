#include "WinLayer.h"

bool Winlayer::init()
{
	Node* node = CSLoader::createNode("Winlayer.csb");

	//Button* menuButton = static_cast<Button*>(node->getChildByTag(31));

	Button* exitButton = static_cast<Button*>(node->getChildByTag(31));
	//menuButton->addTouchEventListener(CC_CALLBACK_2(Winlayer::clickCallBackMenu, this));
	exitButton->addClickEventListener(CC_CALLBACK_1(Winlayer::clickCallBackExit, this));
	this->addChild(node);
	return true;
}

/*void Winlayer::clickCallBackMenu(Ref* sender, Widget::TouchEventType controlEvent)
{
	if (controlEvent == Widget::TouchEventType::ENDED)
		tsm->toStartScene();
}*/

void Winlayer::clickCallBackExit(Ref* sender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}