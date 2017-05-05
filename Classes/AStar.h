#ifndef _ASTAR_H_
#define _ASTAR_H_
/*
//A*算法对象类
*/
#include<vector>  
#include<list>  

const int kCost1 = 20; //直移一格消耗  
const int kCost2 = 28; //斜移一格消耗  

struct MapPoint
{
	int x, y; //点坐标，这里为了方便按照C++的数组来计算，x代表横排，y代表竖列  
	int F, G, H; //F=G+H  
	MapPoint *parent; //parent的坐标
	MapPoint(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)  //变量初始化  
	{}
};

class AStar
{
public:
	void InitAstar(std::vector<std::vector<int>> &_maze);
	std::list<MapPoint *> GetPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner);

private:
	MapPoint *findPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner);
	std::vector<MapPoint *> getSurroundPoints(const MapPoint *point, bool isIgnoreCorner) const;
	bool isCanreach(const MapPoint *point, const MapPoint *target, bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断  
	MapPoint *isInList(const std::list<MapPoint *> &list, const MapPoint *point) const; //判断开启/关闭列表中是否包含某点  
	MapPoint *getLeastFpoint(); //从开启列表中返回F值最小的节点  
	//计算FGH值  
	int calcG(MapPoint *tempStart, MapPoint *point);
	int calcH(MapPoint *point, MapPoint *end);
	int calcF(MapPoint *point);

	std::vector<std::vector<int>> maze;
	std::list<MapPoint *> openList;  //开启列表  
	std::list<MapPoint *> closeList; //关闭列表  
};

#endif