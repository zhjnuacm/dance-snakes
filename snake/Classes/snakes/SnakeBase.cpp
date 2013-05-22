#include "SnakeBase.h"
#include "Point.h"
#include "Map.h"
#include <iostream>
#include <sstream>

using namespace std;

SnakeBase * SnakeBase::create()
{
	SnakeBase * ret = new SnakeBase();
	if(ret && ret->init())
		return ret;
	return NULL;
}

void SnakeBase::move() {
	
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

DIR SnakeBase::getDirection() {
	return this->direction;
}

void SnakeBase::setDirection(DIR dir) {

	this->direction = dir;
}

int SnakeBase::getScore() {
	return this->score;
}

std::string SnakeBase::getScoreString() {
	std::stringstream newstr;
	newstr << getScore();
	return newstr.str();
}

void SnakeBase::setScore(int score) {
	this->score = score;
}

int SnakeBase::getLen() {
	return this->len;
}

bool SnakeBase::init() {
	this->len = INITLENGTH;
	for(int i = 1; i < INITLENGTH; ++i)
		snakeNodeList[this->len-i] = SnakeNode::create(ccp(1, i), false);
	snakeNodeList[0] = SnakeNode::create(ccp(1, INITLENGTH), true);
	setScore(0);
	setDirection(RIGHT);
	return true;
}

bool SnakeBase::isSelfCollision(const CCPoint pp) const
{
	for(int i = 1; i < len - 1; ++i)
		if((pp.x == snakeNodeList[i]->getLocation().x) && (pp.y == snakeNodeList[i]->getLocation().y))
			return true;
	return false;
}

bool SnakeBase::isCollision(const CCPoint pp) const
{
	for(int i = 0; i < len - 1; ++i)
		if((pp.x == snakeNodeList[i]->getLocation().x) && (pp.y == snakeNodeList[i]->getLocation().y))
			return true;
	return false;
}

SnakeNode* SnakeBase::addTail()
{
	if(this->len > MAXLENGTH) return NULL;
	snakeNodeList[this->len++] = SnakeNode::create(ccp(-1, -1), false);
	return snakeNodeList[this->len-1];
}

SnakeNode* SnakeBase::getHead() {
	return this->snakeNodeList[0];
}

SnakeNode** SnakeBase::getSnakeNodeList() {
	
	return this->snakeNodeList;
}

const CCPoint SnakeBase::getNextLocation() {
	int x = getHead()->getLocation().x;
	int y = getHead()->getLocation().y;
	int fx = x, fy = y;
	
	if(UP == this->direction)			--fy;
	else if(DOWN == this->direction)	++fy;
	else if(LEFT == this->direction)	--fx;
	else if(RIGHT == this->direction)	++fx;
	return CCPoint(fx, fy);
}