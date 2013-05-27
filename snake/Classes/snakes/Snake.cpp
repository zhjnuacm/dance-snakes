#include "Snake.h"

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
	SnakeBase::move();
	//this->getEffect()->runAction(CCMoveTo::create(0.048f,snakeNodeList[0]->getSprite()->getPosition()));
}