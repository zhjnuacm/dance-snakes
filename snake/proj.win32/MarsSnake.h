#ifndef MARSSNAKE_H_
#define MARSSNAKE_H_

#include "DIR.h"
#include "SnakeNode.h"
#include "config.h"
#include "cocos2d.h"

using namespace cocos2d;

class Snake {

private:

	SnakeNode *snakeNodeList[MAXLENGTH];
	int score;
	DIR direction;
	int len;

public:

	static Snake * create();
	//整條snake 移動
	void move();

	DIR getDirection();

	void setDirection(DIR);

	int getScore();

	void setScore(int score);

	int getLen();

	//判斷是否自連
	bool isSelfCOllision(CCPoint);
	
	SnakeNode** getSnakeNodeList();
	
	bool init();

	//吃到食物，在尾部添加節點
	SnakeNode * addTail();
	
	SnakeNode *getHead();
	bool isPointInSnake(CCPoint p );
};

#endif