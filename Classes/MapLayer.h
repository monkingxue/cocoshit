#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include"cocos2d.h"
#include"ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;

class MapLayer : public Layer
{
public:
	CREATE_FUNC(MapLayer);
	virtual bool init();
	void setBackground(const char* filename);
	void setMenu(const char* filename);
	void MapLayer::hideMenu(bool menuVisible);

private:
	ImageView* bgImageView;
	Sprite* menutext;

};

#endif