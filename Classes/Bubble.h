#ifndef _BUBBLE_H_
#define _BUBBLE_H_

#include"cocos2d.h"
#include"PropertyManager.h"
#include"cocostudio\CocoStudio.h"
#include"BaseFSM.h"
#include"LogicMapLayer.h"
#include"BaseRole.h"

class BaseRole;
USING_NS_CC;
using namespace cocostudio;

class Bubble :public Node
{
public:
	CREATE_FUNC(Bubble);
	virtual bool init();
	CC_SYNTHESIZE(Armature*, armature, Armature);
	void startBubble();
	void animationEvent(Armature * pArmature, MovementEventType movementType, const std::string& movementIDstr);

	int mapPreState;
	pair<int, int>changeLogicPoint;
	vector<BaseRole*> heroVec;
	vector<BaseRole*> monsterVec;
};

#endif