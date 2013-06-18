#include "SnakeNode.h"
#include "Map.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace cocos2d;

SnakeNode * SnakeNode::create(bool isHead)
{
	SnakeNode * ret = new SnakeNode();
	if(isHead){
		ret->sprite = CCSprite::create("img/shead.png",CCRectMake(0,0,32,32));
	}
	else{
		ret->sprite = CCSprite::create("img/sbody.png",CCRectMake(0,0,32,32));
	}
	if(ret && ret->init())
		return ret;
	return NULL;
}

/*
*create the node of marsSnake
*/
SnakeNode * SnakeNode::marsCreate(bool isHead)
{
	SnakeNode * ret = new SnakeNode();
	if(isHead){
		ret->sprite = CCSprite::create("img/shead2.png",CCRectMake(0,0,32,32));
	}
	else
		ret->sprite = CCSprite::create("img/sbody2.png",CCRectMake(0,0,32,32));
	//ret->getSprite()->setColor(ccc3(12,12,12));
	if(ret && ret->init())
		return ret;
	return NULL;
}

SnakeNode * SnakeNode::create(CCPoint p, bool isHead)
{
	SnakeNode * ret = SnakeNode::create(isHead);
	if(ret)
	{
		ret->getSprite()->setPosition(Map::tiledPositionToCoordGL(p));
		return ret;
	}
	return NULL;
}

/*
*create the node of marsSnake
*/
SnakeNode * SnakeNode::marsCreate(CCPoint p, bool isHead)
{
	SnakeNode * ret = SnakeNode::marsCreate(isHead);
	if(ret){
		ret->getSprite()->setPosition(Map::tiledPositionToCoordGL(p));
		return ret;
	}
	return NULL;
}

void SnakeNode::move(CCPoint pp) {
	this->getSprite()->setPosition(Map::tiledPositionToCoordGL(pp));

}

CCPoint SnakeNode::getLocation() {
	return Map::convertCoordGLToTile(this->getSprite()->getPosition());
}


bool SnakeNode::init()
{
	bool bRet = false;
	bRet = true;
	return bRet;
}