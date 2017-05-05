#include<math.h>  
#include"AStar.h"  

void AStar::InitAstar(std::vector<std::vector<int>> &_maze)
{
	maze = _maze;
}

int AStar::calcG(MapPoint *temStart, MapPoint *point)
{
	int extraG = (abs(point->x - temStart->x) + abs(point->y - temStart->y)) == 1 ? kCost1 : kCost2;
	int parentG = point->parent == NULL ? 0 : point->parent->G; //如果是初始节点，则其父节点是空  
	return parentG + extraG;
}

int AStar::calcH(MapPoint *point, MapPoint *end)
{
	//用简单的欧几里得距离计算H，这个H的计算是关键，还有很多算法，没深入研究^_^  
	return sqrt((double)(end->x - point->x)*(double)(end->x - point->x) + (double)(end->y - point->y)*(double)(end->y - point->y))*kCost1;
}

int AStar::calcF(MapPoint *point)
{
	return point->G + point->H;
}

MapPoint *AStar::getLeastFpoint()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto &point : openList)
		if (point->F<resPoint->F)
			resPoint = point;
		return resPoint;
	}
	return NULL;
}

MapPoint *AStar::findPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner)
{
	openList.clear();
	closeList.clear();
	openList.push_back(new MapPoint(startPoint.x, startPoint.y)); //置入起点,拷贝开辟一个节点，内外隔离  
	while (!openList.empty())
	{
		auto curPoint = getLeastFpoint(); //找到F值最小的点  
		openList.remove(curPoint); //从开启列表中删除  
		closeList.push_back(curPoint); //放到关闭列表  
		//1,找到当前周围八个格中可以通过的格子  
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints)
		{
			//2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H  
			if (!isInList(openList, target))
			{
				target->parent = curPoint;

				target->G = calcG(curPoint, target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}
			//3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F  
			else
			{
				int tempG = calcG(curPoint, target);
				if (tempG<target->G)
				{
					target->parent = curPoint;

					target->G = tempG;
					target->F = calcF(target);
				}
			}
			MapPoint *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝  
		}
	}

	return NULL;
}

std::list<MapPoint *> AStar::GetPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner)
{
	std::list<MapPoint *> path;
	if (startPoint.x == endPoint.x && startPoint.y == endPoint.y)
	{
		return path;
	}
	MapPoint *result = findPath(startPoint, endPoint, isIgnoreCorner);
	//返回路径，如果没找到路径，返回空链表  
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

MapPoint *AStar::isInList(const std::list<MapPoint *> &list, const MapPoint *point) const
{
	//判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标  
	for (auto p : list)
	if (p->x == point->x&&p->y == point->y)
		return p;
	return NULL;
}

bool AStar::isCanreach(const MapPoint *point, const MapPoint *target, bool isIgnoreCorner) const
{
	if (target->x<0 || target->x>maze.size() - 1
		|| target->y<0 && target->y>maze[0].size() - 1
		|| maze[target->x][target->y] == 1
		|| target->x == point->x&&target->y == point->y
		|| isInList(closeList, target)) //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false  
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //非斜角可以  
			return true;
		else
		{
			//斜对角要判断是否绊住  
			if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)
				return true;
			else
				return isIgnoreCorner;
		}
	}
}

std::vector<MapPoint *> AStar::getSurroundPoints(const MapPoint *point, bool isIgnoreCorner) const
{
	std::vector<MapPoint *> surroundPoints;

	for (int x = point->x - 1; x <= point->x + 1; x++)
		for (int y = point->y - 1; y <= point->y + 1; y++)
		{
			if (isCanreach(point, new MapPoint(x, y), isIgnoreCorner))
			{
				auto tempPoint = new MapPoint(x, y);
				surroundPoints.push_back(tempPoint);
			}
				
		}
	return surroundPoints;
}