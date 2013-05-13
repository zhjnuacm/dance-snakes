#ifndef FOODFACTORY_H
#define FOODFACTORY_H

#include "Food.h"

class FoodFactory {


public:
	//�S�C�a��ʳ���λ��
	static FoodFactory * create();
	Food* genFood();
	bool init();
};

#endif