#include"LogicMapLayer.h"

extern vector<vector<int>> gLogicMap;
//{
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//1st line
//	{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0 },//2nd line
//	{ 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0 },//3rd line
//	{ 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },//4th line
//	{ 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0 },//5th line
//	{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },//6th line
//	{ 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0 },//7th line
//	{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0 },//8th line
//	{ 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0 },//9th line
//	{ 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0 },//10th line
//	{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 },//11th line
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //12th line
//};//use to mark whether the cell can be passed

bool LogicMapLayer::init()
{
	return true;
}

bool LogicMapLayer::isCanReach(Point rawPosition, int direction)
{
	logicPositionVec = getLogicPosicion(rawPosition.x, rawPosition.y, direction);
	int mapPointX_1 = logicPositionVec[0].first;
	int mapPointY_1 = logicPositionVec[0].second;
	int mapPointX_2 = logicPositionVec[1].first;
	int mapPointY_2 = logicPositionVec[1].second;
	logicPositionVec.clear();
	switch (direction)
	{
	case 1:
		return (gLogicMap[mapPointX_1][mapPointY_1 + 1] == 1 && gLogicMap[mapPointX_2][mapPointY_2 + 1] == 1);
	case 2:
		return (gLogicMap[mapPointX_1 - 1][mapPointY_1] == 1 && gLogicMap[mapPointX_2 - 1][mapPointY_2] == 1);
	case 3:
		return (gLogicMap[mapPointX_1][mapPointY_1 - 1] == 1 && gLogicMap[mapPointX_2][mapPointY_2 - 1] == 1);
	case 4:
		return (gLogicMap[mapPointX_1 + 1][mapPointY_1] == 1 && gLogicMap[mapPointX_2 + 1][mapPointY_2] == 1);
	default:
		break;
	}
	return true;
}

Point LogicMapLayer::setBubble(Point rawPosition, int roleType)
{
	logicPosition = getLogicPosicion(rawPosition.x, rawPosition.y);

	Point bubblePosition;
	bubblePosition.x = roleType == 1 ? logicPosition.second * 40 + 20 : (logicPosition.second + 1) * 40 + 20;
	bubblePosition.y = (11 - logicPosition.first) * 40 + 20;

	return bubblePosition;
}

vector<pair<int, int>> LogicMapLayer::getLogicPosicion(float x, float y, int direction)
{
	pair<int, int> finalTransform_1;
	pair<int, int> finalTransform_2;
	vector<pair<int, int>> finalPosition;
	const int space = 16;
	switch (direction)
	{
	case 1:
		finalTransform_1.first = 11 - ((int)y - 2) / 40;
		finalTransform_2.first = 11 - ((int)y - 25) / 40;
		finalTransform_1.second = finalTransform_2.second = ((int)x - 18) / 40;
		break;
	case 2:
		finalTransform_1.second = ((int)x + space) / 40;
		finalTransform_2.second = ((int)x - space) / 40;
		finalTransform_1.first = finalTransform_2.first = 11 - ((int)y - 30) / 40;
		break;
	case 3:
		finalTransform_1.first = 11 - ((int)y - 2) / 40;
		finalTransform_2.first = 11 - ((int)y - 25) / 40;
		finalTransform_1.second = finalTransform_2.second = ((int)x + 18) / 40;
		break;
	case 4:
		finalTransform_1.second = ((int)x + space) / 40;
		finalTransform_2.second = ((int)x - space) / 40;
		finalTransform_1.first = finalTransform_2.first = 11 - ((int)y + 10) / 40;
		break;
	default:
		finalTransform_1.first = finalTransform_2.first = 11 - ((int)y - 16) / 40;
		finalTransform_1.second = finalTransform_2.second = ((int)x - 12) / 40;
		break;
	}
	finalPosition.push_back(finalTransform_1);
	finalPosition.push_back(finalTransform_2);

	return finalPosition;
}

pair<int, int> LogicMapLayer::getLogicPosicion(float x, float y)
{
	pair<int, int> finalTransform;

	finalTransform.first = 11 - ((int)y - 16) / 40;
	finalTransform.second = ((int)x - 12) / 40;

	return finalTransform;
}
