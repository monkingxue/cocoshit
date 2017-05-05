#ifndef _HROCKER_H_
#define _HROCKER_H_

#include"cocos2d.h"
USING_NS_CC;

typedef enum
{
	tag_rocker,
	tag_rockerBG
}tagForHRocker;

typedef enum
{
	rocker_stay,//0
	rocker_right,
	rocker_up,
	rocker_left,
	rocker_down
}tagDirection;

typedef enum
{
	face_right,
	face_left,
	face_up,
	face_down
}faceDirection;

class HRocker : public Layer
{
public:
	static HRocker * createHRocker(const char* rockerImageName, const char* rockerBGImageName, Point position);
	void startRocker(bool _isStopOther);
	void stopRocker();
	CREATE_FUNC(HRocker);
	int rockerDirection;
	faceDirection faceDir;

private:
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, Point position);
	bool isCanMove;
	float getRad(Point pos1, Point pos2);
	Point rockerBGPosition;
	bool onTouchBegan(Touch* touch, Event* unused_event);
	void onTouchMoved(Touch* touch, Event* unused_event);
	void onTouchEnded(Touch* touch, Event* unused_event);
	float rockerBGR;
};

#endif