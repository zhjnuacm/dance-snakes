#include "MarsSnake.h"
#include "Snake.h"
#include "Map.h"
#include <vector>

using std::vector;

MarsSnake * MarsSnake::create()
{
	MarsSnake * ret = new MarsSnake();
	if(ret && ret->init())
		return ret;
	return NULL;
}

bool MarsSnake::canGoToNext(DIR dir, const Snake* ptrSnake, const Map* ptrMap) {
	DIR reverseDir = static_cast<DIR>((dir+2)%4);
	if(getDirection() != reverseDir && !ptrSnake->isCollision(getNextLocation(dir))
		&& !isCollision(getNextLocation(dir))
		&& ptrMap->isPointInner(getNextLocation(dir)))
		return true;
	return false;
}

bool MarsSnake::init() {
	this->len = INITLENGTH;
	for(int i = 1; i < INITLENGTH; ++i)
		snakeNodeList[this->len-i] = SnakeNode::marsCreate(ccp(23, 15-i), false);
	snakeNodeList[0] = SnakeNode::marsCreate(ccp(23, 15-INITLENGTH), true);
	
	//this->setEffect( CCParticleSun::create());
	//CCTexture2D * myTexture =  CCTextureCache::sharedTextureCache()->addImage("img/fire.png"); 
	//this->getEffect()->setTexture(myTexture);
	//this->getEffect()->setPosition(snakeNodeList[0]->getSprite()->getPosition());
	//this->getEffect()->setScale(0.7f);
	setDirection(LEFT);
	return true;
}

SnakeNode* MarsSnake::addTail()
{
	if(this->len > MAXLENGTH) return NULL;
	snakeNodeList[this->len++] = SnakeNode::marsCreate(ccp(-1, -1), false);
	return snakeNodeList[this->len-1];
}

void MarsSnake::aimAtFood(const CCPoint& p, vector<DIR> &canGo, const Snake * ptrSnake, const Map* ptrMap) {
	DIR preDir = getDirection();
	CCPoint marsPoint = getHead()->getLocation();
	bool flag = false;

	if(p.x < marsPoint.x && canGoToNext(LEFT, ptrSnake, ptrMap))
		canGo.push_back(LEFT), flag = true;
	else if(p.x > marsPoint.x && canGoToNext(RIGHT, ptrSnake, ptrMap)) {
		canGo.push_back(RIGHT), flag = true;
	}

	if(p.y < marsPoint.y && canGoToNext(UP, ptrSnake, ptrMap)) {
		canGo.push_back(UP), flag = true;
	}
	else if(p.y > marsPoint.y && canGoToNext(DOWN, ptrSnake, ptrMap)) {
		canGo.push_back(DOWN), flag = true;
	}

	if(flag && canGoToNext(preDir, ptrSnake, ptrMap))
		canGo.push_back(preDir);
	else {
		DIR dir1 = static_cast<DIR>((preDir+1)%4);
		DIR dir2 = static_cast<DIR>((preDir+3)%4);
		if(canGoToNext(dir1, ptrSnake, ptrMap))
			canGo.push_back(dir1);
		if(canGoToNext(dir2, ptrSnake, ptrMap))
			canGo.push_back(dir2);
	}
}

//transfrom the food point
DIR MarsSnake::findWay(const CCPoint p, const Snake* ptrSnake, const Map* ptrMap) {
	vector<DIR> canGo;
	aimAtFood(p, canGo, ptrSnake, ptrMap);
	return canGo.size() ? *canGo.begin() : LEFT;
}

const CCPoint MarsSnake::getNextLocation(DIR dir) {
	int x = getHead()->getLocation().x;
	int y = getHead()->getLocation().y;
	int fx = x, fy = y;
	
	if(UP == dir)			--fy;
	else if(DOWN == dir)	++fy;
	else if(LEFT == dir)	--fx;
	else if(RIGHT == dir)	++fx;
	return CCPoint(fx, fy);
}

const CCPoint MarsSnake::getNextLocation() {
	int x = getHead()->getLocation().x;
	int y = getHead()->getLocation().y;
	int fx = x, fy = y;
	
	if(UP == this->direction)			--fy;
	else if(DOWN == this->direction)	++fy;
	else if(LEFT == this->direction)	--fx;
	else if(RIGHT == this->direction)	++fx;
	return CCPoint(fx, fy);
}

void MarsSnake::move()
{
	SnakeBase::move();
	//this->getEffect()->runAction(CCMoveTo::create(0.048f,snakeNodeList[0]->getSprite()->getPosition()));
}