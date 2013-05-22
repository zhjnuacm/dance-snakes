#ifndef SNAKE_H_
#define SNAKE_H_

#include "SnakeBase.h"

class Snake : public SnakeBase {

public:
	static Snake * create();
	bool init();
};

#endif