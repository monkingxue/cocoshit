#ifndef _PROPERTYMANAGER_H_
#define _PROPERTYMANAGER_H_

#include"cocos2d.h"
#include<iostream>
USING_NS_CC;

class PropertyManager : public Ref
{
public:
	CREATE_FUNC(PropertyManager);
	virtual bool init();

	CC_SYNTHESIZE(int, ID, ID); 
	CC_SYNTHESIZE(int, Speed, Speed);
	CC_SYNTHESIZE(std::string, ArmatureName, ArmatureName);
	CC_SYNTHESIZE(std::string, DataName, Dataname);
	CC_SYNTHESIZE(std::string, PlayerName, PlayerName);
};

#endif