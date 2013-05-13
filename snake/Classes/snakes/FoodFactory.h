#ifndef FOODFACTORY_H
#define FOODFACTORY_H

#include "Food.h"

class FoodFactory {


public:
	//隨機產生食物打位置
	static FoodFactory * create();
	Food* genFood();
	bool init();
};

#endif