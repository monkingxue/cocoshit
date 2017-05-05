#include "LoseLayer.h"

bool Loselayer::init()
{

	Node* node = CSLoader::createNode("Loselayer.csb");
	//Button* menuButton = static_cast<Button*>(node->getChildByTag(41));
	Button* exitButton = static_cast<Button*>(node->getChildByTag(41));
	//menuButton->addTouchEventListener(CC_CALLBACK_2(Loselayer::clickCallBackMenu, this));
	exitButton->addClickEventListener(CC_CALLBACK_1(Loselayer::clickCallBackExit, this));
	this->addChild(node);
	return true;
}

/*void Loselayer::clickCallBackMenu(Ref* sender, Widget::TouchEventType controlEvent)
{
	if (controlEvent == Widget::TouchEventType::ENDED)
		tsm->toStartScene();
}*/

void Loselayer::clickCallBackExit(Ref* sender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}