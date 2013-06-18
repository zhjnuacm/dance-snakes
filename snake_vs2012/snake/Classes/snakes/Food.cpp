#include "Food.h"
#include "config.h"
#include "Map.h"


Food * Food::create(CCPoint p)
{
	Food * ret = new Food();
	ret->setSprite(CCSprite::create("img/food.png"));
	ret->getSprite()->setPosition(Map::tiledPositionToCoordGL(p));

	ret->getSprite()->retain();
	

	if(ret && ret->getSprite() && ret->init())
		return ret;

	return NULL;
}

int Food::getType() {
	return this->type;
}

void Food::setType(int type) {
	this->type = type;
}

int Food::getValue() {
	return this->value;
}

void Food::setValue(int value) {
	this->value = value;
}

CCPoint Food::getLocation() {
	return Map::convertCoordGLToTile(this->getSprite()->getPosition());
}

void Food::setLocation(CCPoint location) {
	this->getSprite()->setPosition(Map::tiledPositionToCoordGL(location));
}

bool Food::init() {
	
	setType(1);
	setValue(this->type * FOODUNITVALUE);

	return true;
}


Food::~Food()
{
	
	delete this->sprite;
	
}