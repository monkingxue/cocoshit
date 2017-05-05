#ifndef _BASEAI_H_
#define _BASEAI_H_

#include<iostream>
#include"cocos2d.h"
#include"BaseRole.h"
#include"LogicMapLayer.h"
#include"AStar.h"
#include"BaseFSM.h"
#include"RoleController.h"

USING_NS_CC;

class BaseAI :public Ref
{
public:
	static BaseAI* createAI(BaseRole* role, LogicMapLayer* logicMap);
	bool init(BaseRole* role, LogicMapLayer* logicMap);
	void startRoleAI();
	void stopRoleAI();
	void updateFunc(float dt);
	void updateAttack(float dt);
	void findHero(Point heroPoint);
	void goToHero(list<MapPoint *> path);
	void attackHero();
	void purge();

	int simulateKeyBoard;
	BaseRole* baseRole;
	LogicMapLayer* logicMapLayer;
	AStar astar;
	Vector<FiniteTimeAction*> moveSeq;
	vector<string> move;
	list<MapPoint *> path;
};

#endif