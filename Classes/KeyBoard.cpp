#include"KeyBoard.h"

bool KeyBoard::init()
{
	keyBoardDirection = -1;
	mulPressed = 0;
	return true;
}

void KeyBoard::startKB()
{
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(KeyBoard::onKeyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(KeyBoard::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}

void KeyBoard::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	++mulPressed;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		keyBoardDirection = keyBoard_up;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		keyBoardDirection = keyBoard_left;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		keyBoardDirection = keyBoard_down;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		keyBoardDirection = keyBoard_right;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		keyBoardDirection = keyBoard_space;
		break;
	case EventKeyboard::KeyCode::KEY_F1:
		menucase = !menucase;
		break;
	case EventKeyboard::KeyCode::KEY_F2:
		Director::getInstance()->end();
		break;
	case EventKeyboard::KeyCode::KEY_F3:
		break;
	default:
		keyBoardDirection = keyBoard_stay;
		break;
	}
}

void KeyBoard::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	--mulPressed;
	if (!mulPressed)
	{
		keyBoardDirection = keyBoard_stay;
	}	
}

void KeyBoard::stopKB()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}