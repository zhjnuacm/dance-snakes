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
	static SnakeNode * create();
	
	// tiled зјБъ
	static SnakeNode * create( CCPoint ) ; 

	void setSprite(CCSprite * sprite) {this->sprite = sprite;};
	CCSprite * getSprite() {return this->sprite;};

	bool init();

	CCPoint getLocation();
	void move(CCPoint);
};

#endif
