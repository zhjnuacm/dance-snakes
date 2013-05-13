#ifndef MAP_H
#define MAP_H



#include "cocos2d.h"
using namespace cocos2d;
class Map
{

private:
	CCTMXTiledMap * tmxMap;

public:
	static Map * create(char *path);

	void setTmxMap(CCTMXTiledMap * tmxMap)			{ this->tmxMap = tmxMap ;	}
	CCTMXTiledMap * getTmxMap()						{ return this->tmxMap;		}

	
	int getTiedType(CCPoint p);
	bool isEmpty(CCPoint p);
	CCSprite * getTiledAt(CCPoint p);
	bool isPointInner(CCPoint p );

	bool isCanPutFood(CCPoint p);
	static CCPoint convertCoordGLToTile(CCPoint p);
	static CCPoint tiledPositionToCoordGL(CCPoint);

};


#endif