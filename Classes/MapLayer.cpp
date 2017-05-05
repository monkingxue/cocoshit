#include"MapLayer.h"

void MapLayer::setBackground(const char* filename)
{
	TMXTiledMap* map = TMXTiledMap::create(filename);
	map->setAnchorPoint(Point::ZERO);
	map->setPosition(Point::ZERO);
	this->addChild(map);
}
void MapLayer::setMenu(const char* filename)
{
	menutext = Sprite::create(filename);
	menutext->setPosition(80,430);
	addChild(menutext, 2);
}
void MapLayer::hideMenu(bool menuVisible)
{
	if (menuVisible)
		menutext->setVisible(false);
	else
		menutext->setVisible(true);
}
bool MapLayer::init()
{

	return true;
}