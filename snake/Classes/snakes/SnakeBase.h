#ifndef SNAKEBASE_H
#define SNAKEBASE_H

#include "DIR.h"
#include "SnakeNode.h"
#include "config.h"
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

class SnakeBase {

protected:

	SnakeNode *snakeNodeList[MAXLENGTH];
	int score;
	DIR direction;
	int len;

public:

	SnakeBase(): score(0) {}
	static SnakeBase * create();
	//���lsnake �Ƅ�
	void move();

	DIR getDirection();

	void setDirection(DIR);

	int getScore();

	std::string getScoreString();

	void setScore(int score);
	
	int getLen();

	//�Д��Ƿ����B
	bool isSelfCollision(const CCPoint) const;

	bool isCollision(const CCPoint) const;
	
	SnakeNode** getSnakeNodeList();
	
	bool init();

	//�Ե�ʳ���β����ӹ��c
	SnakeNode * addTail();
	
	SnakeNode *getHead();

	const CCPoint getNextLocation();
};

#endif