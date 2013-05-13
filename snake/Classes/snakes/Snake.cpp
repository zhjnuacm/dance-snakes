#include "Snake.h"
#include "Point.h"
#include "Map.h"
#include<iostream>
using namespace std;


Snake * Snake::create()
{
	Snake * ret = new Snake();
	if(ret && ret->init())
		return ret;
	return NULL;
}



void Snake::move() {
	
	for(int i = len - 1; i > 0; --i)
	{
		snakeNodeList[i]->move(snakeNodeList[i - 1]->getLocation());
	}
	CCPoint pp =  snakeNodeList[0]->getLocation();
	DIR dir = this->getDirection();
	switch(dir)
	{
		case UP: snakeNodeList[0]->move(ccp(pp.x, pp.y - 1)); break;
		case DOWN: snakeNodeList[0]->move(ccp(pp.x, pp.y + 1)); break;
		case LEFT: snakeNodeList[0]->move(ccp(pp.x - 1, pp.y)); break;
		case RIGHT: snakeNodeList[0]->move(ccp(pp.x + 1, pp.y)); break;
	}
}

DIR Snake::getDirection() {
	return this->direction;
}

void Snake::setDirection(DIR dir) {
	this->direction = dir;
}

int Snake::getScore() {
	return this->score;
}

void Snake::setScore(int score) {
	this->score = score;
}

int Snake::getLen() {
	return this->len;
}

bool Snake::init() {
	this->len = INITLENGTH;
	for(int i = 1; i <= INITLENGTH; ++i)
		snakeNodeList[this->len-i] = SnakeNode::create(ccp(1, i));
	setScore(0);
	setDirection(RIGHT);
	
	return true;
}

bool Snake::isSelfCOllision(CCPoint pp)
{
	for(int i = 0; i < len - 1; ++i)
		if((pp.x == snakeNodeList[i]->getLocation().x) && (pp.y == snakeNodeList[i]->getLocation().y))
			return true;
	return false;
}


SnakeNode* Snake::addTail()
{
	if(this->len > MAXLENGTH) return NULL;
	snakeNodeList[this->len++] = SnakeNode::create(ccp(-1, -1));
	return snakeNodeList[this->len-1];
}

SnakeNode* Snake::getHead() {
	return this->snakeNodeList[0];
}


SnakeNode** Snake::getSnakeNodeList() {
	
	return this->snakeNodeList;
}