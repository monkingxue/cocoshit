#include"BaseAI.h"
#include<math.h>
#include<ctime>

extern vector<vector<int>> gLogicMap;

BaseAI* BaseAI::createAI(BaseRole* role, LogicMapLayer* logicMapController)
{
	BaseAI* ai = new BaseAI();
	if (ai && ai->init(role, logicMapController))
		ai->autorelease();
	else
		CC_SAFE_DELETE(ai);
	return ai;
}

bool BaseAI::init(BaseRole* role, LogicMapLayer* logicMapController)
{
	baseRole = role;
	logicMapLayer = logicMapController;
	vector<vector<int>> AIMap(gLogicMap);
	simulateKeyBoard = 0;
	for (auto &col : AIMap)
		for (auto &item : col)
			item = item == 1 ? 0 : 1;
	astar.InitAstar(AIMap);

	return true;
}

void BaseAI::startRoleAI()
{	
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(BaseAI::updateFunc), this, (float)0.3f, false);
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(BaseAI::updateAttack), this, (float)0.5f, false);
}

void BaseAI::stopRoleAI()
{
	Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(BaseAI::updateFunc), this);
	Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(BaseAI::updateAttack), this);
}

void BaseAI::updateFunc(float dt)
{
	this->simulateKeyBoard = 0;
	std::vector<BaseRole*>roleVec;
	roleVec = RoleController::getInstance()->heroVec;
	int roleID = 0;
	findHero(roleVec[roleID]->getPosition());
}

void BaseAI::updateAttack(float dt)
{
	attackHero();
}

void BaseAI::findHero(Point heroPoint)
{
	Point monsterPoint = baseRole->getPosition();
	pair<int, int> heroLogicPoint = logicMapLayer->getLogicPosicion(heroPoint.x, heroPoint.y);
	pair<int, int> monsterLogicPoint = logicMapLayer->getLogicPosicion(monsterPoint.x, monsterPoint.y);

	srand((unsigned)time(0));
	int ranNum = rand() % 8;
	int deta = 1;
	switch (ranNum)
	{
	case 0:
		if (heroLogicPoint.first + deta != 1)
			heroLogicPoint.first += deta; break;
	case 1:
		if (heroLogicPoint.first - deta != 1)
			heroLogicPoint.first -= deta; break;
	case 2:
		if (heroLogicPoint.second + deta != 1)
			heroLogicPoint.second += deta; break;
	case 3:
		if (heroLogicPoint.second - deta != 1)
			heroLogicPoint.second -= deta; break;
	default:
		break;
	}

	MapPoint start(monsterLogicPoint.first, monsterLogicPoint.second);
	MapPoint end(heroLogicPoint.first, heroLogicPoint.second);
	path = astar.GetPath(start, end, false);
	while (path.size() > 2)
		path.pop_back();
	if (path.size() != 0)
		goToHero(path);
	path.clear();
}

void BaseAI::goToHero(list<MapPoint *> path)
{

	int distanceX = 0;
	int distanceY = 0;
	auto nowPoint = path.front();
	path.pop_front();
	auto nextPoint = path.front();
	distanceX = nextPoint->x - nowPoint->x;
	distanceY = nextPoint->y - nowPoint->y;
	if (distanceX == 1)
		this->simulateKeyBoard = 4;
	else if (distanceX == -1)
		this->simulateKeyBoard = 2;
	else if (distanceY == 1)
		this->simulateKeyBoard = 1;
	else if (distanceY == -1)
		this->simulateKeyBoard = 3;
	else
		this->simulateKeyBoard = 0;
}

void BaseAI::attackHero()
{
	std::vector<BaseRole*>roleVec;
	roleVec = RoleController::getInstance()->heroVec;
	int roleID = 0;
	if (baseRole->getPosition().distance(roleVec[roleID]->getPosition()) <= 50)
		this->simulateKeyBoard = 5;
}

void BaseAI::purge()
{
	stopRoleAI();
	//CC_SAFE_RELEASE(this);
}