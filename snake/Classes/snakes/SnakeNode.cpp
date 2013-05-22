#include "SnakeNode.h"
#include "Map.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace cocos2d;

SnakeNode * SnakeNode::create(bool isHead)
{
	SnakeNode * ret = new SnakeNode();
	if(isHead)
		ret->sprite = CCSprite::create("maps/tmw_desert_spacing.png",CCRectMake(32*7+8,32*4+6,30,30));
	else
		ret->sprite = CCSprite::create("maps/tmw_desert_spacing.png",CCRectMake(32*7+8,32*3+4,31,31));
	
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
	if(isHead)
		ret->sprite = CCSprite::create("maps/tmw_desert_spacing.png",CCRectMake(32*7+8,32*4+6,30,30));
	else
		ret->sprite = CCSprite::create("maps/tmw_desert_spacing.png",CCRectMake(32*7+8,32*5+6,30,30));
	
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
	if(ret)
	{
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