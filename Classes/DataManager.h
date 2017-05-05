#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include<iostream>
#include"cocos2d.h"
#include"json\rapidjson.h"
#include"json\document.h"
using namespace std;
using namespace rapidjson;
USING_NS_CC;

class DataManager
{
public:
	static DataManager * getInstance();
	void initWIthJsonFile(const char* filename);
	std::vector<std::string> getLevelDataArrayByIndex(int index);

	std::string tollgateData;
	std::vector<std::string> levelDataArray;
	CC_SYNTHESIZE(int, levelIndex, LevelIndex);
	CC_SYNTHESIZE(std::string, mapTexture, MapTexture);
	CC_SYNTHESIZE(std::string, logicMapData, LogicMapData);
};


#endif