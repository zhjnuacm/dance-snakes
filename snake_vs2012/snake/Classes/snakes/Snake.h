#ifndef SNAKE_H_
#define SNAKE_H_

#include "SnakeBase.h"
#include "DIR.h"

const unsigned int TIME_GAP = 400;
const int SEQKEYDOWN_LIMIT = 3;
const unsigned __int64 TIME_UP = 2600000000000000000;
class Snake : public SnakeBase {
private:
	CCParticleSystemQuad *effect;
    struct SeqKeyDown
	{
		unsigned __int64 downTime;
		DIR direction;
		SeqKeyDown(){
			downTime = TIME_UP;
		}
	}seqKeyDown[SEQKEYDOWN_LIMIT];
	
public:
	
	CCParticleSystemQuad *getEffect(){return this->effect;}
	void setEffect(CCParticleSystemQuad * e){this->effect = e;}
	static Snake * create();
	bool init();
	void move();
	
	void addKeyDown(DIR);

	DIR getNextDIR(DIR);
};

#endif