#include "Mediator.h"
#include "snakes\SnakeNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Mediator::Mediator() {
}

Mediator* Mediator::mdInstance = new Mediator();

Mediator* Mediator::getInstance() {
		
	return mdInstance;
}

void Mediator::addGameScene(CCLayer * layer)
{
	this->gameScene = layer;
}

void Mediator::addGameMap(char *path)
{
	this->map = Map::create(path);
	this->gameScene->addChild(this->map->getTmxMap(),0);
}



bool Mediator::init() {

	this->isGameOver = false;

	this->snake = Snake::create();
	SnakeNode ** snakeNodes = this->snake->getSnakeNodeList();			//init snake
	for(int i = 0 ; i < this->snake->getLen() ; i++)
	{
		this->map->getTmxMap()->addChild(snakeNodes[i]->getSprite(),1);
	}

	this->foodFactory = FoodFactory::create();
	this->putNewFood();
	return true;
	
}


void Mediator::snakeMove(float dt) {
	
	DIR dir = this->snake->getDirection();
	this->snake->move();
}


bool Mediator::dectectCollision() {
	
	DIR dir = this->snake->getDirection();
	int x = this->snake->getHead()->getLocation().x;
	int y = this->snake->getHead()->getLocation().y;
	int fx = x, fy = y;
	
	if(UP == dir)			--fy;
	else if(DOWN == dir)	++fy;
	else if(LEFT == dir)	--fx;
	else if(RIGHT == dir)	++fx;

	this->isGameOver =  (!this->map->isPointInner(ccp(x, y)) || this->snake->isSelfCOllision(ccp(fx, fy)));
	return true;
}


bool Mediator::dectectFood() {
	CCPoint snakeHead = this->snake->getHead()->getLocation();
	CCPoint foodLocation = this->food->getLocation();
	if(snakeHead.x == foodLocation.x && snakeHead.y == foodLocation.y)
	{
		this->food->getSprite()->setVisible(false);  //need clean!!!
		
		this->putNewFood();
		SnakeNode * last = this->snake->addTail();
		//cout << this->snake->getLen() << endl;
		
		if(last){
			this->map->getTmxMap()->addChild(last->getSprite(),1);
		}
		else{
			this->isGameOver = true;
		}
		return true;
	}
	return false;
}



bool Mediator::end() {
	return this->isGameOver;
	
}


void Mediator::putNewFood() {
	
	while(true)
	{
		this->food = this->foodFactory->genFood();
		if(this->map->isCanPutFood(this->food->getLocation()) && !this->snake->isSelfCOllision(this->food->getLocation()))
		{
			this->map->getTmxMap()->addChild(this->food->getSprite(),1);
			break;
		}
		delete this->food->getSprite();
		delete this->food;
	}
}


bool Mediator::loadConfig(){
	return true;
}


Mediator::~Mediator(){
	delete mdInstance;
}



void Mediator::keyEvent()
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if(KEY_DOWN(VK_UP))
	{
		this->snake->setDirection(UP);
		return;
	}
	if(KEY_DOWN(VK_DOWN))
	{
		this->snake->setDirection(DOWN);
		return;
	}
	if(KEY_DOWN(VK_LEFT))
	{
		this->snake->setDirection(LEFT);
		return;
	}
	if(KEY_DOWN(VK_RIGHT))
	{
		this->snake->setDirection(RIGHT);
		return;
	}
	
#endif
}