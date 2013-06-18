#include "MarsSnake.h"
#include "Snake.h"
#include "Map.h"
#include "config.h"
#include <vector>

using std::vector;

MarsSnake * MarsSnake::create()
{
	MarsSnake * ret = new MarsSnake();
	if(ret && ret->init())
		return ret;
	return NULL;
}

bool MarsSnake::canGoToNext(DIR dir,  Snake * ptrSnake,  Map* ptrMap) {
	DIR reverseDir = static_cast<DIR>((dir+2)%4);
	if(getDirection() != reverseDir && !(ptrSnake->isCollision(getNextLocation(dir)))
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

void MarsSnake::aimAtFood( CCPoint& p, vector<DIR> &canGo,  Snake * ptrSnake,  Map* ptrMap) {
	DIR preDir = getDirection();
	CCPoint marsPoint = getHead()->getLocation();
	bool flag = false;

	if(p.x < marsPoint.x && canGoToNext(LEFT, ptrSnake, ptrMap)){
		canGo.push_back(LEFT), flag = true;}
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
CCPoint MarsSnake::toolTogetAnthorPoint(CCPoint point, DIR dir) {
	int fx = point.x, fy = point.y;
	
	if(UP == dir)			--fy;
	else if(DOWN == dir)	++fy;
	else if(LEFT == dir)	--fx;
	else if(RIGHT == dir)	++fx;
	return CCPoint(fx, fy);
}

int MarsSnake::getTheSnakeIndex(CCPoint pp) {
	for(int i = 0; i < len - 1; ++i)
		if((pp.x == snakeNodeList[i]->getLocation().x) && (pp.y == snakeNodeList[i]->getLocation().y))
			return i;
	return -1;
}

DIR MarsSnake::isWouldDied (DIR firstSelete) {
	CCPoint nxtPoint = this->getNextLocation(this->direction), nxt1, nxt2;
	DIR preDir = this->direction;

	if(isCollision(nxtPoint)) {
		DIR dir1 = static_cast<DIR>((preDir+1)%4);
		DIR dir2 = static_cast<DIR>((preDir+3)%4);
		nxt1 = toolTogetAnthorPoint(nxtPoint, dir1);
		nxt2 = toolTogetAnthorPoint(nxtPoint, dir2);
		
		if(isCollision(nxt1) && !isCollision(nxt2)) {
			return dir2;
		} 
		else if(!isCollision(nxt1) && isCollision(nxt2)) {
			return dir1;
		}
		else if(isCollision(nxt1) && isCollision(nxt2)) {
			int ind1 = getTheSnakeIndex(nxt1);
			int ind2 = getTheSnakeIndex(nxt2);
			if(ind1 > ind2) return dir1;
			else return dir2;
		}
		else {
			printf("两个都不行，，这个完全不可能会出现!!!");
		}
	}
	return firstSelete;
}

//transfrom the food point
DIR MarsSnake::findWay( CCPoint p,  Snake* ptrSnake,  Map* ptrMap) {
	vector<DIR> canGo;
	aimAtFood(p, canGo, ptrSnake, ptrMap);
	DIR firstSelete = canGo.size() ? *canGo.begin() : LEFT;
	//DIR zhangaiwuSelete =  isWouldDied(firstSelete);

	return isWouldDied(firstSelete);
}

 CCPoint MarsSnake::getNextLocation(DIR dir) {
	int x = getHead()->getLocation().x;
	int y = getHead()->getLocation().y;
	int fx = x, fy = y;
	
	if(UP == dir)			--fy;
	else if(DOWN == dir)	++fy;
	else if(LEFT == dir)	--fx;
	else if(RIGHT == dir)	++fx;
	return CCPoint(fx, fy);
}

 CCPoint MarsSnake::getNextLocation() {
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
