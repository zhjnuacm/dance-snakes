#include "FoodFactory.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"
#include "cocos2d.h"

using cocos2d::CCPoint;

unsigned int FoodFactory::genNum = 0;

Food *FoodFactory::genFood() {
	
	FoodFactory::genNum++;

	srand((int)time(NULL));

	int fx, fy;
	
	fx = (rand() * FoodFactory::genNum) % (mapX - 1) + 1;
	fy = (rand() *FoodFactory::genNum) % mapY + 1;
		
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
