#ifndef MARSMarsSnake_H_
#define MARSMarsSnake_H_

#include "SnakeBase.h"
#include "Map.h"
#include "Snake.h"
#include <vector>

class MarsSnake : public SnakeBase {

private:
	CCParticleSystemQuad *effect;
public:

	CCParticleSystemQuad *getEffect(){return this->effect;}
	void setEffect(CCParticleSystemQuad * e){this->effect = e;}
	static MarsSnake* create();

	bool init();

	DIR findWay(const CCPoint p, const Snake*, const Map*);

	void aimAtFood(const CCPoint&, std::vector<DIR>&, const Snake*, const Map*);

	void aimAtAvoidSnake(const Snake*, std::vector<DIR>&);
	
	const CCPoint getNextLocation(DIR dir);
	
	const CCPoint getNextLocation();

	SnakeNode* addTail();

	void move();

private:
	bool canGoToNext(DIR, const Snake*, const Map*);

};

#endif