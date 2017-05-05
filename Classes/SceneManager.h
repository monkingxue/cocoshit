#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include"cocos2d.h"
USING_NS_CC;

class SceneManager
{
public:
	Scene * startScene;
	Scene * gameScene;
	Scene * settingsScene;
	Scene* winScene;
	Scene* loseScene;

	bool mode;

	void createScene();
	void toGameScene();
	void toSettingsScene();
	void toStartScene();
	void toWinScene();
	void toLoseScene();
};

#endif