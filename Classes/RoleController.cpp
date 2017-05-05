#include"RoleController.h"

static RoleController* roleController = nullptr;

RoleController* RoleController::getInstance()
{
	if (roleController == nullptr)
	{
		roleController = new(std::nothrow) RoleController();
		roleController->init();
	}
	return roleController;
}

bool RoleController::init()
{
	return true;
}

BaseRole* RoleController::getHero()
{
	return heroVec[0];
}

BaseRole* RoleController::getMonster()
{
	return monsterVec[0];
}

void RoleController::purge()
{
	if (heroVec.size() != 0)
	{
		for (auto hero : heroVec)
			hero->purge();
	}
	if (monsterVec.size() != 0)
	{
		for (auto monster : monsterVec)
			monster->purge();
	}

	heroVec.clear();
	heroVec.shrink_to_fit();
	monsterVec.clear();
	monsterVec.shrink_to_fit();
}