#include "Food.h"
#include "config.h"
#include "Map.h"


Food * Food::create(CCPoint p)
{
	Food * ret = new Food();
	ret->setSprite(CCSprite::create("maps/tmw_desert_spacing.png",CCRectMake(32*6+8,32*3+4,31,31)));
	ret->getSprite()->setPosition(Map::tiledPositionToCoordGL(p));
	//ret->getSprite()->retain();

	//ret->setEffect(CCParticleSun::create());
	
	//CCTexture2D * myTexture =  CCTextureCache::sharedTextureCache()->addImage("img/fire.png"); 
	//ret->getEffect()->setTexture(myTexture);
	//ret->getEffect()->setPosition(Map::tiledPositionToCoordGL(p));
	//ret->getEffect()->setScale(0.3);
	

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
	delete this->effect;
	delete this->sprite;
	
}