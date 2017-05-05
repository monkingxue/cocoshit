#include"SceneManager.h"
#include"MenuLayer.h"
#include"ControlLayer.h"
#include"PopUpLayer.h"
#include"WinLayer.h"
#include"Loselayer.h"

void SceneManager::createScene()
{
	startScene = Scene::create();
	this->mode = true;
	auto  menuLayer = MenuLayer::create();
	menuLayer->tsm = this;
	startScene->addChild(menuLayer);
}

void SceneManager::toGameScene()
{
	gameScene = Scene::create();
	auto controlLayer = ControlLayer::createControl(mode);
	controlLayer->tsm = this;
	gameScene->addChild(controlLayer);
	Director::getInstance()->replaceScene(gameScene);
}

void SceneManager::toSettingsScene()
{
	    settingsScene = Scene::create();
		auto settingsLayer = PopUpLayer::create();
		settingsLayer->tsm = this;
		settingsScene->addChild(settingsLayer);
		Director::getInstance()->replaceScene(settingsScene);
}

void SceneManager::toStartScene()
{
	startScene = Scene::create();
	auto  menuLayer = MenuLayer::create();
	menuLayer->tsm = this;
	startScene->addChild(menuLayer);
	Director::getInstance()->replaceScene(startScene);
}

void SceneManager::toWinScene()
{
	winScene = Scene::create();
	auto winLayer = Winlayer::create();
	winLayer->tsm = this;
	winScene->addChild(winLayer);
	Director::getInstance()->replaceScene(winScene);
}

void SceneManager::toLoseScene()
{
	loseScene = Scene::create();
	auto loseLayer = Loselayer::create();
	loseLayer->tsm = this;
	loseScene->addChild(loseLayer);
	Director::getInstance()->replaceScene(loseScene);
}