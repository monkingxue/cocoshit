#ifndef _BASEROLE_H_
#define _BASEROLE_H_

#include"cocos2d.h"
#include"PropertyManager.h"
#include"cocostudio\CocoStudio.h"
#include"BaseFSM.h"
#include"LogicMapLayer.h"
USING_NS_CC;
using namespace cocostudio;

class BaseFSM;
class BaseAI;

typedef enum
{
	TYPE_HERO = 1,
	TYPE_MONSTER
}ROLE_TYPE;

typedef enum{
	ROLE_DEFAULT = 1,
	ROLE_MOVE,
	ROLE_DEAD,
	ROLE_FREE,
	ROLE_ATTACK
}ROLE_STATE;

class BaseRole : public Node
{
public:
	static BaseRole* createWithProperty(PropertyManager* manager);
	bool init(PropertyManager* manager);
	void purge();

	void animationEvent(Armature * pArmature, MovementEventType movementType, const std::string& movementIDstr);

	PropertyManager* propertyManager;
	ROLE_TYPE type;
	ROLE_STATE state;
	CC_SYNTHESIZE(Armature*, armature, Armature);
	CC_SYNTHESIZE(BaseFSM*, baseFSM, BaseFSM);
	CC_SYNTHESIZE(BaseAI*, baseAI, BaseAI);
};

#endif