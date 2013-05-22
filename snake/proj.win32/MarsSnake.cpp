#include "MarsSnake.h"
#include "Point.h"
#include "Map.h"
#include<iostream>
using namespace std;


MarsSnake * MarsSnake::create()
{
	MarsSnake * ret = new MarsSnake();
	if(ret && ret->init())
		return ret;
	return NULL;
}

void MarsSnake::move() {
	
	for(int i = len - 1; i > 0; --i)
	{
		MarsSnakeNodeList[i]->move(MarsSnakeNodeList[i - 1]->getLocation());
	}
	CCPoint pp =  MarsSnakeNodeList[0]->getLocation();
	DIR dir = this->getDirection();
	switch(dir)
	{
		case UP: MarsSnakeNodeList[0]->move(ccp(pp.x, pp.y - 1)); break;
		case DOWN: MarsSnakeNodeList[0]->move(ccp(pp.x, pp.y + 1)); break;
		case LEFT: MarsSnakeNodeList[0]->move(ccp(pp.x - 1, pp.y)); break;
		case RIGHT: MarsSnakeNodeList[0]->move(ccp(pp.x + 1, pp.y)); break;
	}
}

DIR MarsSnake::getDirection() {
	return this->direction;
}

void MarsSnake::setDirection(DIR dir) {

	this->direction = dir;
}

int MarsSnake::getScore() {
	return this->score;
}

void MarsSnake::setScore(int score) {
	this->score = score;
}

int MarsSnake::getLen() {
	return this->len;
}

bool MarsSnake::init() {
	this->len = INITLENGTH;
	for(int i = 1; i <= INITLENGTH; ++i)
		MarsSnakeNodeList[this->len-i] = MarsSnakeNode::create(ccp(1, i));
	setScore(0);
	setDirection(RIGHT);
	return true;
}

bool MarsSnake::isSelfCOllision(CCPoint pp)
{
	for(int i = 0; i < len - 1; ++i)
		if((pp.x == MarsSnakeNodeList[i]->getLocation().x) && (pp.y == MarsSnakeNodeList[i]->getLocation().y))
			return true;
	return false;
}


MarsSnakeNode* MarsSnake::addTail()
{
	if(this->len > MAXLENGTH) return NULL;
	MarsSnakeNodeList[this->len++] = MarsSnakeNode::create(ccp(-1, -1));
	return MarsSnakeNodeList[this->len-1];
}

MarsSnakeNode* MarsSnake::getHead() {
	return this-MarsMarsSnakeNodeList[0];
}


MarsSnakeNode** MarsSnake::getMarsSnakeNodeList() {
	
	return this-MarsMarsSnakeNodeList;
}