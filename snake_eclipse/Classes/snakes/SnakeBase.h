#ifndef SNAKEBASE_H
#define SNAKEBASE_H
#include "DIR.h"
#include "SnakeNode.h"
#include "cocos2d.h"
#include "config.h"
#include <string>

using namespace cocos2d;

class SnakeBase {

protected:

	SnakeNode *snakeNodeList[100];
	int score;
	DIR direction;
	int len;
	
	int moveSteps;
public:
	int getMoveSteps() {return this->moveSteps;}
	void setMoveSteps(int step){this->moveSteps = step;}

	SnakeBase(): score(0) {}
	static SnakeBase * create();
	
	void move();

	DIR getDirection();

	void setDirection(DIR);

	int getScore();

	std::string getScoreString();

	void setScore(int score);

	int getLen();

	
	bool isSelfCollision(const CCPoint) const;

	bool isCollision(const CCPoint) const;

	SnakeNode** getSnakeNodeList();

	bool init();

	
	SnakeNode * addTail();

	SnakeNode *getHead();

	const CCPoint getNextLocation();
};

#endif
