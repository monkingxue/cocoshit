#include"PopUpLayer.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

bool PopUpLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Node* node = CSLoader::createNode("Poplayer.csb");

	keyboardButton = static_cast<Button*>(node->getChildByTag(21));//���̰�ť
	keyboardButton->setBright(true);          //����Ĭ�ϰ�ť����
	keyboardButton->setEnabled(true);       //����Ĭ������
	keyboardButton->setTouchEnabled(true);
	keyboardButton->addTouchEventListener(CC_CALLBACK_2(PopUpLayer::changeState,this));

	rockerButton = static_cast<Button*>(node->getChildByTag(22));//ҡ�˰�ť
	rockerButton->setBright(false);
	rockerButton->setEnabled(false);
	rockerButton->setTouchEnabled(false);
	rockerButton->addTouchEventListener(CC_CALLBACK_2(PopUpLayer::changeState, this));

	Slider* volumeSlider = static_cast<Slider*>(node->getChildByTag(23));//������
	volumeSlider->addEventListener(CC_CALLBACK_2(PopUpLayer::sliderEvent, this));

	Button* returnButton = static_cast<Button*>(node->getChildByTag(24));//�رհ�ť
	returnButton->addTouchEventListener(CC_CALLBACK_2(PopUpLayer::clickCallBackReturn, this));

	this->addChild(node);

	return true;	
}

void PopUpLayer::changeState(Ref* sender, Widget::TouchEventType controlEvent)//�ص�����
{
	operateMode = !operateMode;
	changeButtonState();
}


void PopUpLayer::clickCallBackReturn(Ref* sender, Widget::TouchEventType controlEvent)
{
	if (controlEvent == Widget::TouchEventType::ENDED)
	{
		tsm->mode = operateMode;
		tsm->toStartScene();
	}	
}

void PopUpLayer::sliderEvent(Ref* sender, Slider::EventType type)
{
	Slider* volumeSlider = dynamic_cast<Slider*>(sender);
	int volumePercent = volumeSlider->getPercent();

}

void PopUpLayer::changeButtonState()
{
	keyboardButton->setBright(operateMode);
	keyboardButton->setEnabled(operateMode);
	keyboardButton->setTouchEnabled(operateMode);
	rockerButton->setBright(!operateMode);
	rockerButton->setEnabled(!operateMode);
	rockerButton->setTouchEnabled(!operateMode);
}