#ifndef SNAKENODE_H
#define SNAKENODE_H

#include "Point.h"
#include "cocos2d.h"
using namespace cocos2d;

class SnakeNode 
{

private:
	CCSprite * sprite;
public:
	static SnakeNode * create(bool);
	static SnakeNode * marsCreate(bool);

	// tiled зјБъ
	static SnakeNode * create( CCPoint , bool) ; 
	static SnakeNode * marsCreate(CCPoint, bool);

	void setSprite(CCSprite * sprite) {this->sprite = sprite;};
	CCSprite * getSprite() {return this->sprite;};

	bool init();

	CCPoint getLocation();
	void move(CCPoint);
};

#endif
