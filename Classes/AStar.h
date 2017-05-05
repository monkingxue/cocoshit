#ifndef _ASTAR_H_
#define _ASTAR_H_
/*
//A*�㷨������
*/
#include<vector>  
#include<list>  

const int kCost1 = 20; //ֱ��һ������  
const int kCost2 = 28; //б��һ������  

struct MapPoint
{
	int x, y; //�����꣬����Ϊ�˷��㰴��C++�����������㣬x������ţ�y��������  
	int F, G, H; //F=G+H  
	MapPoint *parent; //parent������
	MapPoint(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)  //������ʼ��  
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
	bool isCanreach(const MapPoint *point, const MapPoint *target, bool isIgnoreCorner) const; //�ж�ĳ���Ƿ����������һ���ж�  
	MapPoint *isInList(const std::list<MapPoint *> &list, const MapPoint *point) const; //�жϿ���/�ر��б����Ƿ����ĳ��  
	MapPoint *getLeastFpoint(); //�ӿ����б��з���Fֵ��С�Ľڵ�  
	//����FGHֵ  
	int calcG(MapPoint *tempStart, MapPoint *point);
	int calcH(MapPoint *point, MapPoint *end);
	int calcF(MapPoint *point);

	std::vector<std::vector<int>> maze;
	std::list<MapPoint *> openList;  //�����б�  
	std::list<MapPoint *> closeList; //�ر��б�  
};

#endif