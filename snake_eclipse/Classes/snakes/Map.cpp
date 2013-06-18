#include "Map.h"
#include "config.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

Map * Map::create(char * path)
{
	Map * ret = new Map();
	
	if(path != NULL)
	{
		ret->setTmxMap(CCTMXTiledMap::create(path));
		
		return ret;
	}
	return NULL;
}

CCPoint Map::convertCoordGLToTile(CCPoint p)
{
	int x = (int)p.x / TILED_WIDTH;
	
	int y = (int)(((mapY) * TILED_HEIGHT) - p.y) / TILED_HEIGHT;

	return CCPointMake((float)x,(float)y);
}


CCPoint Map::tiledPositionToCoordGL(CCPoint p)
{
	return ccp(p.x*TILED_WIDTH + TILED_WIDTH/2.0 ,WINDOW_HEIGHT - p.y*TILED_HEIGHT - TILED_HEIGHT/2.0);
}

int Map::getTiedType(CCPoint p) const
{
	int value = this->getTmxMap()->layerNamed("block")->tileGIDAt(p);
	return value;
}

bool Map::isPointInner(CCPoint p)  const
{
	if(p.x >= mapX || p.x < 0 || p.y >= mapY || p.y < 0)
		return false;
	int v = getTiedType(p);
	if(v >= 136)
		return false;
	return true;
}

bool Map::isCanPutFood(CCPoint p)
{
	return isPointInner(p);
}
