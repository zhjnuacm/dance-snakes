#ifndef SNAKE_H_
#define SNAKE_H_

#include "SnakeBase.h"

class Snake : public SnakeBase {
private:
	CCParticleSystemQuad *effect;

	
public:
	
	CCParticleSystemQuad *getEffect(){return this->effect;}
	void setEffect(CCParticleSystemQuad * e){this->effect = e;}
	static Snake * create();
	bool init();
	void move();
};

#endif