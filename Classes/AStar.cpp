#include<math.h>  
#include"AStar.h"  

void AStar::InitAstar(std::vector<std::vector<int>> &_maze)
{
	maze = _maze;
}

int AStar::calcG(MapPoint *temStart, MapPoint *point)
{
	int extraG = (abs(point->x - temStart->x) + abs(point->y - temStart->y)) == 1 ? kCost1 : kCost2;
	int parentG = point->parent == NULL ? 0 : point->parent->G; //����ǳ�ʼ�ڵ㣬���丸�ڵ��ǿ�  
	return parentG + extraG;
}

int AStar::calcH(MapPoint *point, MapPoint *end)
{
	//�ü򵥵�ŷ����þ������H�����H�ļ����ǹؼ������кܶ��㷨��û�����о�^_^  
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
	openList.push_back(new MapPoint(startPoint.x, startPoint.y)); //�������,��������һ���ڵ㣬�������  
	while (!openList.empty())
	{
		auto curPoint = getLeastFpoint(); //�ҵ�Fֵ��С�ĵ�  
		openList.remove(curPoint); //�ӿ����б���ɾ��  
		closeList.push_back(curPoint); //�ŵ��ر��б�  
		//1,�ҵ���ǰ��Χ�˸����п���ͨ���ĸ���  
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints)
		{
			//2,��ĳһ�����ӣ���������ڿ����б��У����뵽�����б����õ�ǰ��Ϊ�丸�ڵ㣬����F G H  
			if (!isInList(openList, target))
			{
				target->parent = curPoint;

				target->G = calcG(curPoint, target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}
			//3����ĳһ�����ӣ����ڿ����б��У�����Gֵ, �����ԭ���Ĵ�, ��ʲô������, �����������ĸ��ڵ�Ϊ��ǰ��,������G��F  
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
				return resPoint; //�����б���Ľڵ�ָ�룬��Ҫ��ԭ�������endpointָ�룬��Ϊ���������  
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
	//����·�������û�ҵ�·�������ؿ�����  
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

MapPoint *AStar::isInList(const std::list<MapPoint *> &list, const MapPoint *point) const
{
	//�ж�ĳ���ڵ��Ƿ����б��У����ﲻ�ܱȽ�ָ�룬��Ϊÿ�μ����б����¿��ٵĽڵ㣬ֻ�ܱȽ�����  
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
		|| isInList(closeList, target)) //������뵱ǰ�ڵ��غϡ�������ͼ�����ϰ�������ڹر��б��У�����false  
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //��б�ǿ���  
			return true;
		else
		{
			//б�Խ�Ҫ�ж��Ƿ��ס  
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