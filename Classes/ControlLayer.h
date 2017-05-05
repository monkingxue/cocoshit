#ifndef _CONTROLLAYER_H_
#define _CONTROLLAYER_H_

#include"cocos2d.h"
#include"SceneManager.h"
#include"BaseRole.h"
#include"HRocker.h"
#include"KeyBoard.h"
#include"MapLayer.h"
#include"PopUpLayer.h"
USING_NS_CC;


class ControlLayer : public Layer
{
public:
	SceneManager* tsm;

	static ControlLayer* createControl(bool mode);
	virtual bool init(bool mode);
	virtual void update(float dt);
	void purge();

private:
	HRocker* rocker;
	KeyBoard* keyBoard;
	MapLayer* maplayer;
	LogicMapLayer* logicMapLayer;
	bool operateMode;
};

#endif