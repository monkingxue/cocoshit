#include"HRocker.h"

#define PI 3.14159265

HRocker* HRocker::createHRocker(const char* rockerImageName, const char* rockerBGImageName, Point position)
{
	HRocker* layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

void HRocker::rockerInit(const char* rockerBGImageName, const char* rockerImageName, Point position)
{
	auto spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);
	this->addChild(spRockerBG, 0, tag_rockerBG);

	auto spRocker = Sprite::create(rockerImageName);
	spRocker->setPosition(position);
	spRocker->setVisible(false);
	this->addChild(spRocker, 0, tag_rocker);

	rockerBGPosition = position;
	rockerBGR = spRockerBG->getContentSize().width / 2;
	rockerDirection = -1;
	isCanMove = false;
}

void HRocker::startRocker(bool _isStopOther)
{
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool HRocker::onTouchBegan(Touch* touch, Event* unused_event)
{
	Point point = touch->getLocation();
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);

	if (rocker->getBoundingBox().containsPoint(point))
	{
		isCanMove = true;
	}

	return true;
}

float HRocker::getRad(Point pos1, Point pos2)
{
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;

	float x = px2 - px1;
	float y = py2 - py1;

	float hypo = sqrt(pow(x, 2) + pow(y, 2));
	float cosAngle = x / hypo;
	float rad = acos(cosAngle);

	if (py2 < py1)
		rad = -rad;
	
	return rad;
}

Point getAnglePosition(float r, float angle, Point point)
{
	return ccpAdd(Point(r * cos(angle), r * sin(angle)), point);
}

void HRocker::onTouchMoved(Touch* touch, Event* unused_event)
{
	if (!isCanMove)
		return;
	Point point = touch->getLocation();
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);

	float angle = getRad(rockerBGPosition, point);
	if (sqrt(pow(rockerBGPosition.x - point.x, 2) + pow(rockerBGPosition.y - point.y, 2)) >= rockerBGR)
		rocker->setPosition(getAnglePosition(rockerBGR, angle, rockerBGPosition));
	else
		rocker->setPosition(point);

	if (angle >= -PI / 4 && angle < PI / 4)
	{
		rockerDirection = rocker_right;
		faceDir = face_right;
	}

	else if (angle >= PI / 4 && angle < 3 * PI / 4)
	{
		rockerDirection = rocker_up;
	}

	else if ((angle >= 3 * PI / 4 && angle <= PI) || (angle >= -PI && angle < -3 * PI / 4))
	{
		rockerDirection = rocker_left;
		faceDir = face_left;
	}

	else if (angle >= - 3 * PI / 4 && angle < - PI / 4)
	{
		rockerDirection = rocker_down;
	}

		
}

void HRocker::onTouchEnded(Touch* touch, Event* unused_event)
{
	if (!isCanMove)
		return;

	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);

	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08f, rockerBG->getPosition()));
	isCanMove = false;
	rockerDirection = rocker_stay;
}

void HRocker::stopRocker()
{
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	_eventDispatcher->removeEventListenersForTarget(this);
}