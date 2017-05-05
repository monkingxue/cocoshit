#include"MenuLayer.h"

bool MenuLayer::init()
{
	Node* node = CSLoader::createNode("MainScene.csb");
	
	Layout* layout = static_cast<Layout*>(node->getChildByTag(1));
	
	Button* startButton = static_cast<Button*>(layout->getChildByTag(11));
	Button* exitButton = static_cast<Button*>(layout->getChildByTag(12));
	Button* settingsButton = static_cast<Button*>(layout->getChildByTag(13));
	startButton->addTouchEventListener(CC_CALLBACK_2(MenuLayer::clickCallBackStart, this));
	exitButton->addClickEventListener(CC_CALLBACK_1(MenuLayer::clickCallBackExit, this));
	settingsButton->addTouchEventListener(CC_CALLBACK_2(MenuLayer::clickCallBackSettings, this));
	this->addChild(node);
	return true;
}

void MenuLayer::clickCallBackStart(Ref* sender, Widget::TouchEventType controlEvent)
{
	if (controlEvent == Widget::TouchEventType::ENDED)
	{
		tsm->toGameScene();
	}
}

void MenuLayer::clickCallBackExit(Ref* sender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MenuLayer::clickCallBackSettings(Ref* sender, Widget::TouchEventType controlEvent)
{
	if (controlEvent == Widget::TouchEventType::ENDED)
		tsm->toSettingsScene();
}