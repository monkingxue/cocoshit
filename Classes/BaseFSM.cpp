#include"BaseFSM.h"
#include<math.h>

extern vector<vector<int>> gLogicMap;

BaseFSM* BaseFSM::createFSM(BaseRole* baseRole, Bubble* baseBubble)
{
	BaseFSM* baseFSM = new BaseFSM();
	if (baseFSM && baseFSM->init(baseRole, baseBubble))
	{
		baseFSM->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(baseFSM);
		return nullptr;
	}

	return baseFSM;
}

bool BaseFSM::init(BaseRole* baseRole, Bubble* baseBubble)
{
	role = baseRole;
	bubble = baseBubble;
	logicmap = LogicMapLayer::create();
	return true;
}

void BaseFSM::switchMoveState(int dir)
{
		switch (dir){
		case 0:
			this->changeToDeFault(); break;
		case 1:
			this->changeToRight(); break;
		case 2:
			this->changeToUp(); break;
		case 3:
			this->changeToLeft(); break;
		case 4:
			this->changeToDown(); break;
		case 5:
			this->changeToAttack(); break;
		default:
			break;
		}
}

void BaseFSM::changeToDeFault()
{
	if (role->state != ROLE_DEAD && role->state != ROLE_ATTACK)
	{
		role->state = ROLE_DEFAULT;
		role->getArmature()->getAnimation()->stop();
	}
}



void BaseFSM::changeToLeft()
{
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	std::string movent = role->getArmature()->getAnimation()->getCurrentMovementID();
	char* nowMovent = const_cast<char*>(movent.c_str());
	if (strcmp(nowMovent, "run_left") != 0)
	{
		role->getArmature()->getAnimation()->play("run_left");
	}
	role->setPosition(Point(role->getPositionX() - role->propertyManager->getSpeed(), role->getPositionY()));

}

void BaseFSM::changeToRight()
{
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	std::string movent = role->getArmature()->getAnimation()->getCurrentMovementID();
	char* nowMovent = const_cast<char*>(movent.c_str());
	if (strcmp(nowMovent, "run_right") != 0)
	{
		role->getArmature()->getAnimation()->play("run_right");
	}
	role->setPosition(Point(role->getPositionX() + role->propertyManager->getSpeed(), role->getPositionY()));

}

void BaseFSM::changeToUp()
{
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	std::string movent = role->getArmature()->getAnimation()->getCurrentMovementID();
	char* nowMovent = const_cast<char*>(movent.c_str());
	if (strcmp(nowMovent, "run_back") != 0)
	{
		role->getArmature()->getAnimation()->play("run_back");
	}
	role->setPosition(Point(role->getPositionX(), role->getPositionY() + role->propertyManager->getSpeed()));

}

void BaseFSM::changeToDown()
{
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	std::string movent = role->getArmature()->getAnimation()->getCurrentMovementID();
	char* nowMovent = const_cast<char*>(movent.c_str());
	if (strcmp(nowMovent, "run_front") != 0)
	{
		role->getArmature()->getAnimation()->play("run_front");
	}
	role->setPosition(Point(role->getPositionX(), role->getPositionY() - role->propertyManager->getSpeed()));
}

void BaseFSM::changeToDead()
{
	if (role->state != ROLE_DEAD)
	{
		role->state = ROLE_DEAD;
		std::string movent = role->getArmature()->getAnimation()->getCurrentMovementID();
		char* nowMovent = const_cast<char*>(movent.c_str());
		if (strcmp(nowMovent, "dead") != 0)
		{
			role->getArmature()->getAnimation()->play("dead", -1, 0);
		}
	}
}

void BaseFSM::changeToAttack()
{
	vector<string> bubbleAnimation;
	bubbleAnimation.push_back("BubbleDefaultAnimation");
	bubbleAnimation.push_back("BubbleExplodeAnimation");
	Point bubblePosition;
	pair<int, int> bubbleLogicPosition;
	if (role->state != ROLE_DEAD)
	{
		role->state = ROLE_ATTACK;
		
		std::string movent = bubble->getArmature()->getAnimation()->getCurrentMovementID();
		char* nowMovent = const_cast<char*>(movent.c_str());
		if (strcmp(nowMovent, "BubbleDefaultAnimation") != 0 && strcmp(nowMovent, "BubbleExplodeAnimation") != 0)
		{
			bubblePosition = logicmap->setBubble(role->getPosition(), role->type);
			bubbleLogicPosition = logicmap->getLogicPosicion(bubblePosition.x, bubblePosition.y);
			bubble->setPosition(bubblePosition);

			bubble->startBubble();

			bubble->mapPreState = gLogicMap[bubbleLogicPosition.first][bubbleLogicPosition.second];
			bubble->changeLogicPoint = bubbleLogicPosition;
			if (gLogicMap[bubbleLogicPosition.first][bubbleLogicPosition.second] == 1)
			{
				gLogicMap[bubbleLogicPosition.first][bubbleLogicPosition.second] = 0;

				bubble->getArmature()->getAnimation()->playWithNames(bubbleAnimation, -1, false);
			}
		}
	}
}

void BaseFSM::purge()
{
	role = nullptr;
	CC_SAFE_RELEASE(this);
}