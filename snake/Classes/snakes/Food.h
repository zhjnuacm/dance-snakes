#ifndef FOOD_H
#define FOOD_H


#include "cocos2d.h"
using namespace cocos2d;
class Food {

private:
	int type;
	int value;
	CCSprite * sprite;
	CCParticleSystemQuad *effect;
public:
	CCParticleSystemQuad *getEffect(){return this->effect;}
	void setEffect(CCParticleSystemQuad * e){this->effect = e;}
	static Food * create(CCPoint );

	int getType();

	void setType(int type);

	int getValue();

	void setValue(int value);

	CCPoint getLocation();

	void setLocation(CCPoint location);

	bool init();

	void setSprite(CCSprite * sprite)		{this->sprite = sprite;}
	CCSprite * getSprite()					{return this->sprite;}
	~Food();
};

#endif
