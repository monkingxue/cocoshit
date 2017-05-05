#ifndef _BASEFSM_H_
#define _BASEFSM_H_

#include<iostream>
#include"cocos2d.h"
#include"LogicMapLayer.h"
#include"BaseRole.h"
#include"Bubble.h"

USING_NS_CC;

class BaseRole;
class Bubble;

class BaseFSM : public Ref
{
public:
	static BaseFSM* createFSM(BaseRole* baseRole, Bubble* baseBubble);
	bool init(BaseRole* baseRole, Bubble*baseBubble);

	void switchMoveState(int dir);
	void changeToDeFault();
	void changeToLeft();
	void changeToRight();
	void changeToUp();
	void changeToDown();
	void changeToDead();
	void changeToAttack();
	void purge();

	BaseRole* role;
	Bubble* bubble;
	LogicMapLayer* logicmap;
};

#endif