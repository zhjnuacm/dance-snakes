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
	//���lsnake �Ƅ�
	void move();

	DIR getDirection();

	void setDirection(DIR);

	int getScore();

	void setScore(int score);

	int getLen();

	//�Д��Ƿ����B
	bool isSelfCOllision(CCPoint);
	
	SnakeNode** getSnakeNodeList();
	
	bool init();

	//�Ե�ʳ���β����ӹ��c
	SnakeNode * addTail();
	
	SnakeNode *getHead();
	bool isPointInSnake(CCPoint p );
};

#endif