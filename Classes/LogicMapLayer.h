#ifndef _LOGICMAPLAYER_H_
#define _LOGICMAPLAYER_H_
#include<iostream>
#include<utility>
#include"cocos2d.h"

using namespace std;
USING_NS_CC;



class LogicMapLayer :public cocos2d::Layer
{
public:
	CREATE_FUNC(LogicMapLayer);
	virtual bool init();
	bool isCanReach(Point rawPosition, int direction);
	vector<pair<int, int>> getLogicPosicion(float x, float y, int direction);
	pair<int, int> getLogicPosicion(float x, float y);
	Point  setBubble(Point rawPosition, int roleType);

private:
	pair<int, int> logicPosition;
	vector<pair<int, int>> logicPositionVec;
};
#endif