#include"ControlLayer.h"
#include"LogicMapLayer.h"
#include"OperateLayer.h"
#include"BaseFSM.h"
#include"RoleController.h"
#include"BaseAI.h"
#include"DataManager.h"
#include"json\rapidjson.h"
#include"json\document.h"

using namespace rapidjson;

extern vector<vector<int>> gLogicMap;

ControlLayer* ControlLayer::createControl(bool mode)
{
	ControlLayer* controlLayer = new ControlLayer();
	if (controlLayer && controlLayer->init(mode))
		controlLayer->autorelease();
	else
		CC_SAFE_DELETE(controlLayer);
	return controlLayer;
}

bool ControlLayer::init(bool mode)
{
	operateMode = mode;

	OperateLayer* operateLayer = OperateLayer::create();
	this->addChild(operateLayer);

	rocker = HRocker::createHRocker("rocker_out.png", "rocker_in.png", Point(100, 100));
	this->addChild(rocker,99);

	keyBoard = KeyBoard::create();
	keyBoard->startKB();
 	this->addChild(keyBoard); 

	logicMapLayer = LogicMapLayer::create();
	this->addChild(logicMapLayer);


	Bubble* bubble[2];
	for (int i = 0; i < 2; i++)
	{
		bubble[i] = Bubble::create();
		this->addChild(bubble[i], 1);
	}

	auto dataManagerInstance = DataManager::getInstance();

	for (int i = 0; i < dataManagerInstance->getLevelDataArrayByIndex(dataManagerInstance->getLevelIndex()).size(); i++)
	{
		PropertyManager* pManager = PropertyManager::create();
		std::string heroData = FileUtils::getInstance()->getStringFromFile(dataManagerInstance->levelDataArray[i]);
		Document configDoc;
		configDoc.Parse<kParseDefaultFlags>(heroData.c_str());
		pManager->setArmatureName(configDoc["ArmatureName"].GetString());
		pManager->setDataname(configDoc["Dataname"].GetString());
		pManager->setID(configDoc["ID"].GetInt());
		pManager->setSpeed(configDoc["Speed"].GetInt());
		pManager->setPlayerName(configDoc["PlayerName"].GetString());
		pManager->retain();

		BaseRole* role = BaseRole::createWithProperty(pManager);
		role->state = ROLE_DEFAULT;
		Point rolePos;
		rolePos.x = configDoc["Position"][0].GetInt();
		rolePos.y = configDoc["Position"][1].GetInt();
		role->setPosition(rolePos); 
		role->type = static_cast<ROLE_TYPE>(configDoc["RoleType"].GetInt());
		this->addChild(role, 1);

		if (role->type == 1)
			RoleController::getInstance()->heroVec.push_back(role);
		else if (role->type == 2)
			RoleController::getInstance()->monsterVec.push_back(role);

		BaseFSM* baseRoleFSM = BaseFSM::createFSM(role, bubble[i]);
		baseRoleFSM->retain();
		role->setBaseFSM(baseRoleFSM);

		if (role->type == 2)
		{
			BaseAI* ai = BaseAI::createAI(role, logicMapLayer);
			ai->retain();
			role->setBaseAI(ai);
			ai->startRoleAI();
		}
		
	}

	for (int i = 0; i < 2; i++)
	{
		bubble[i]->heroVec = RoleController::getInstance()->heroVec;
		bubble[i]->monsterVec = RoleController::getInstance()->monsterVec;
	}

	maplayer = MapLayer::create();
	maplayer->setBackground(dataManagerInstance->getMapTexture().c_str());
	maplayer->setMenu("menutext.png");//Menu text
	this->addChild(maplayer, 0);

	Director::getInstance()->getScheduler()->schedule(schedule_selector(ControlLayer::update), this, (float)1/60, false);

	return true;
}

void ControlLayer::purge()
{
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(ControlLayer::update), this);
	RoleController::getInstance()->purge();
}

void ControlLayer::update(float dt)
{
	int direction = operateMode ? keyBoard->keyBoardDirection : rocker->rockerDirection;
	if (!operateMode)
		rocker->startRocker(true);
	else
		rocker->stopRocker();
	auto hero = RoleController::getInstance()->getHero();
	auto monster = RoleController::getInstance()->getMonster();
	if (hero->state != ROLE_FREE && monster->state != ROLE_FREE)
	{
		if (hero != nullptr && monster != nullptr)
		{
			if (logicMapLayer->isCanReach(hero->getPosition(), direction))
				hero->getBaseFSM()->switchMoveState(direction);
			else
				hero->getBaseFSM()->switchMoveState(0);
			if (logicMapLayer->isCanReach(monster->getPosition(), monster->getBaseAI()->simulateKeyBoard))
				monster->getBaseFSM()->switchMoveState(monster->getBaseAI()->simulateKeyBoard);
			else
				monster->getBaseFSM()->switchMoveState(0);
		}
	}

	std::vector<BaseRole*>::iterator itr = RoleController::getInstance()->monsterVec.begin();
	while (itr != RoleController::getInstance()->monsterVec.end())
	{
		if ((*itr)->state == ROLE_FREE)
		{
			(*itr)->purge();
			RoleController::getInstance()->monsterVec.erase(itr);
			break;
		}
		++itr;
	}

	itr = RoleController::getInstance()->heroVec.begin();
	while (itr != RoleController::getInstance()->heroVec.end())
	{
		if ((*itr)->state == ROLE_FREE)
		{
			(*itr)->purge();
			RoleController::getInstance()->heroVec.erase(itr);
			break;
		}
		++itr;
	}

	if (RoleController::getInstance()->monsterVec.size() == 0)
	{
		this->purge();
		if (DataManager::getInstance()->getLevelIndex() == 2)
		{
			tsm->toWinScene();
			this->purge();
			return;
		}

		gLogicMap.clear();

		DataManager::getInstance()->setLevelIndex(DataManager::getInstance()->getLevelIndex() + 1);

		tsm->toGameScene();
	}

	if (RoleController::getInstance()->heroVec.size() == 0)
	{
		tsm->toLoseScene();
		this->purge();
	}		
	maplayer->hideMenu(keyBoard->menucase);
}