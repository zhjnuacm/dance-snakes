#include "FoodFactory.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"
#include "cocos2d.h"

using cocos2d::CCPoint;
Food *FoodFactory::genFood() {
	
	srand((int)time(NULL));
	int fx, fy;
	
	fx = rand() % (mapX - 1) + 1;
	fy = rand() % mapY + 1;
		
	return Food::create(CCPoint(fx, fy));
}


FoodFactory * FoodFactory::create()
{
	FoodFactory * ret = new FoodFactory();
	if(ret && ret->init())
		return ret;
	return NULL;
}

bool FoodFactory::init()
{
	return true;
}