#ifndef _ROLECONTROLLER_H_
#define _ROLECONTROLLER_H_

#include<iostream>
#include"cocos2d.h"
#include"BaseRole.h"
USING_NS_CC;

class RoleController : public Ref
{
public:
	static RoleController* getInstance();
	bool init();
	BaseRole* getHero();
	BaseRole* getMonster();
	void purge();

	std::vector<BaseRole *>heroVec;
	std::vector<BaseRole *>monsterVec;
};

#endif