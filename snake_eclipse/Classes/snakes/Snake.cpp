#include "Snake.h"
#include "DIR.h"
#include <stdio.h>
long millisecondNow()  
{ 
	struct cocos2d::cc_timeval now; 
	cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL); 
	return (now.tv_sec * 1000 + now.tv_usec / 1000); 
}

Snake * Snake::create()
{
	Snake * ret = new Snake();
	if(ret && ret->init())
		return ret;
	return NULL;
}

bool Snake::init() {
	this->len = INITLENGTH;
	for(int i = 1; i < INITLENGTH; ++i)
		snakeNodeList[this->len-i] = SnakeNode::create(ccp(1, i), false);
	snakeNodeList[0] = SnakeNode::create(ccp(1, INITLENGTH), true);
	setScore(0);
	//this->effect = CCParticleGalaxy::create();
	//CCTexture2D * myTexture =  CCTextureCache::sharedTextureCache()->addImage("img/fire.png"); 
	//this->getEffect()->setTexture(myTexture);
	//this->getEffect()->setPosition(snakeNodeList[0]->getSprite()->getPosition());
	//this->getEffect()->setScale(0.7f);
	setDirection(RIGHT);
	return true;
}

void Snake::move()
{
	DIR nexDir = getNextDIR(this->getDirection());
	if(nexDir != this->getDirection())
		this->setDirection(nexDir);
	SnakeBase::move();
	//this->getEffect()->runAction(CCMoveTo::create(0.048f,snakeNodeList[0]->getSprite()->getPosition()));
}

void Snake::addKeyDown(DIR dir){

	//
	long mTime =  millisecondNow();
	//printf("ClickTime %I64u\n", mTime);
	int id = 0;
	for(int i = 1; i < SEQKEYDOWN_LIMIT; ++i)
	{
		if(seqKeyDown[i].downTime < seqKeyDown[id].downTime)
		{
			id = i;
		}
	}
	seqKeyDown[id].direction = dir;
	seqKeyDown[id].downTime = mTime;
}

DIR Snake::getNextDIR(DIR dir)
{
	//
	long mTime =  millisecondNow();
	int id = -1;
	unsigned long long compTime = TIME_UP;
	for(int i = 0; i < SEQKEYDOWN_LIMIT; ++i)
	{
		int gap = abs(seqKeyDown[i].direction - dir);
		if(gap & 1){ 
			if(seqKeyDown[i].downTime != TIME_UP && (mTime - seqKeyDown[i].downTime) <= TIME_GAP && seqKeyDown[i].downTime < compTime )
			{
				id = i;
				compTime = seqKeyDown[i].downTime;
			}
		}
	}
	if(id != -1) return seqKeyDown[id].direction;
	return getDirection();
}
