#include"BaseRole.h"
#include"BaseFSM.h"
#include"BaseAI.h"

BaseRole* BaseRole::createWithProperty(PropertyManager* manager)
{
	BaseRole* baseRole = new BaseRole();
	if (baseRole && baseRole->init(manager))
		baseRole->autorelease();
	else
	{
		CC_SAFE_DELETE(baseRole);
		return nullptr;
	}
	return baseRole;

}


bool BaseRole::init(PropertyManager* manager)
{
	propertyManager = manager;

	ArmatureDataManager::getInstance()->addArmatureFileInfo(propertyManager->getDataname());
	armature = Armature::create(propertyManager->getArmatureName());
	/*armature->getAnimation()->play("default");*/
	this->addChild(armature);
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BaseRole::animationEvent, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	return true;
}

void BaseRole::animationEvent(Armature * pArmature, MovementEventType movementType, const std::string& movementIDstr)
{
	const char* movementTag = movementIDstr.c_str();
	if (strcmp(movementTag, "dead") == 0)
		if (movementType == COMPLETE)
		{
			armature->runAction(Sequence::create(FadeOut::create(0.5f), NULL));
			this->state = ROLE_FREE;
		}
}

void BaseRole::purge()
{
	this->getBaseFSM()->purge();
	this->getBaseAI()->purge();
	this->removeFromParent();
}
