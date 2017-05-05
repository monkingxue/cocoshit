#include"DataManager.h"

vector<vector<int>> gLogicMap;

static DataManager* dataManager = nullptr;
DataManager * DataManager::getInstance()
{
	if (dataManager == nullptr)
	{
		dataManager = new DataManager();
	}
	return dataManager;
}

void DataManager::initWIthJsonFile(const char* filename)
{
	tollgateData = FileUtils::getInstance()->getStringFromFile(filename);
}

std::vector<std::string> DataManager::getLevelDataArrayByIndex(int index)
{
	Document doc;
	doc.Parse<kParseDefaultFlags>(tollgateData.c_str());
	//CCLOG("%s", tollgateData.c_str());
	levelDataArray.clear();
	rapidjson::Value & array = doc["Tollgate"];
	if (array.IsArray())
	{
		int i = index;
		int j = 0;
		for (; j < array[i]["RoleData"].Size(); j++)
		{
			rapidjson::Value & str = array[i]["RoleData"][j];
			levelDataArray.push_back(str.GetString());
		}
	}
	rapidjson::Value & logicMap = array[index]["LogicMap"];
	CCLOG("%s", logicMap.GetString());
	this->setLogicMapData(logicMap.GetString());
	rapidjson::Value & map = array[index]["Map"];
	this->setMapTexture(map.GetString());

	CCLOG("%s", this->logicMapData);

	std::string LogicMapData = FileUtils::getInstance()->getStringFromFile(this->logicMapData);
	Document mapDoc;
	mapDoc.Parse<kParseDefaultFlags>(LogicMapData.c_str());
	CCLOG("%s", LogicMapData.c_str());
	vector<int> temp;
	for (int l = 0; l < mapDoc["Map"].Size(); l++)
	{
		for (int n = 0; n < mapDoc["Map"][l].Size(); n++)
		{
			temp.push_back(mapDoc["Map"][l][n].GetInt());
		}
		gLogicMap.push_back(temp);
		temp.clear();
	}
	
	return levelDataArray;
}