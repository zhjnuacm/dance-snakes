#include "Mediator.h"
#include "snakes/SnakeNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SimpleAudioEngine.h"
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
	this->isNextLvl = false;
	this->snake = Snake::create();
	this->marsSnake = MarsSnake::create();
//	this->snake->setMoveSteps(0);
//	this->marsSnake->setMoveSteps(0);
	
	SnakeNode ** snakeNodes = this->snake->getSnakeNodeList();			//init snake
	SnakeNode ** marsSnakeNodes = this->marsSnake->getSnakeNodeList();
	
	for(int i = 0 ; i < this->snake->getLen() ; i++)
	{
		this->map->getTmxMap()->addChild(snakeNodes[i]->getSprite(),1);
		
	}

	for(int i = 0; i < this->marsSnake->getLen(); i++) {
		this->map->getTmxMap()->addChild(marsSnakeNodes[i]->getSprite(), 1);
		
	}
	//this->map->getTmxMap()->addChild(this->snake->getEffect(),2);
	//this->map->getTmxMap()->addChild(this->marsSnake->getEffect(),2);
	cout << "snakes init success!" << endl; 
	this->foodFactory = FoodFactory::create();
	this->putNewFood();
	this->gameTime = 0;
	this->scoreAndTimePanel = ScoreAndTimePanel::create();
	this->map->getTmxMap()->addChild(scoreAndTimePanel,3);
	return true;
}

void Mediator::snakeMove(float dt) {
	this->snake->move();
}

/*
*mars snake move
*/
void Mediator::marsSnakeMove(float dt) {
	DIR ret = this->marsSnake->findWay(this->food->getLocation(), this->snake, this->map);
	this->marsSnake->setDirection(ret);
	this->marsSnake->move();
}

bool Mediator::snakeDectectCollision() {
	CCPoint nowLocation = this->snake->getHead()->getLocation();

	this->isGameOver = (!this->map->isPointInner(nowLocation) || this->snake->isSelfCollision(nowLocation)
		|| this->marsSnake->isCollision(nowLocation));
	if(this->isGameOver) {
		cout << "you fail!" << endl;
	}
	return this->isGameOver;
}

bool Mediator::marsSDectectCollision() {
	CCPoint nowLocation = this->marsSnake->getHead()->getLocation();

	this->isGameOver =  (!this->map->isPointInner(nowLocation) || this->marsSnake->isSelfCollision(nowLocation)
		|| this->snake->isCollision(nowLocation));	
	if(this->isGameOver) {
		this->isNextLvl = true;
		cout << "the mars snake is fail!" << endl;
	}
	return this->isGameOver;
}

void Mediator::dectectCollision() {
	if(snakeDectectCollision()) return;
	if(marsSDectectCollision()) return;
}

bool Mediator::dectectFood() {
	CCPoint snakeHead = this->snake->getHead()->getLocation();
	CCPoint foodLocation = this->food->getLocation();
	CCPoint marsSnakehead = this->marsSnake->getHead()->getLocation();

	if(snakeHead.x == foodLocation.x && snakeHead.y == foodLocation.y
		|| marsSnakehead.x == foodLocation.x && marsSnakehead.y == foodLocation.y)
	{
		
		
		this->food->getSprite()->setVisible(false);
		this->food->getSprite()->removeFromParent();
		

		this->snakeEatFood();
		delete this->food;
		this->putNewFood();
		return true;
	}
	return false;
}

void Mediator::snakeEatFood() {
	CCPoint snakeHead = this->snake->getHead()->getLocation();
	CCPoint foodLocation = this->food->getLocation();
	CCPoint marsSnakehead = this->marsSnake->getHead()->getLocation();
	SnakeNode *last = NULL;
	
	if(snakeHead.x == foodLocation.x && snakeHead.y == foodLocation.y) {
		last = this->snake->addTail();
		int score = this->snake->getScore() + 10; //暂时默认食物是10分
		this->snake->setScore(score);
		this->scoreAndTimePanel->setEarthSnakeScore(this->snake->getScore());
		
	}
	else if(marsSnakehead.x == foodLocation.x && marsSnakehead.y == foodLocation.y) {
		last = this->marsSnake->addTail();
		int score = this->marsSnake->getScore() + 10; //暂时默认食物是10分
		this->marsSnake->setScore(score);
		this->scoreAndTimePanel->setMarsSnakeScore(this->marsSnake->getScore());
		
	}
	if(last) {
		this->map->getTmxMap()->addChild(last->getSprite(),1);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/EatFood.mp3");

	}
	else{
		this->isGameOver = true;
	}
}

bool Mediator::end() {
	return this->isGameOver;
}

void Mediator::putNewFood() {
	
	while(true)
	{
		this->food = this->foodFactory->genFood();
		if(this->map->isCanPutFood(this->food->getLocation()) && !this->snake->isCollision(this->food->getLocation())
			&& !this->marsSnake->isCollision(this->food->getLocation()))
		{
			this->map->getTmxMap()->addChild(this->food->getSprite(),1);
			//this->map->getTmxMap()->addChild(this->food->getEffect(),1);
			break;
		}
		//delete this->food;
		//this->food = NULL;
	}
}


bool Mediator::loadConfig(){
	return true;
}


Mediator::~Mediator(){
	delete mdInstance;
}


void Mediator::keyEvent(DIR dir)
{
	switch (dir)
	{
	case UP:
		this->snake->addKeyDown(UP);
		break;
	case LEFT:
		this->snake->addKeyDown(LEFT);
		break;
	case DOWN:
		this->snake->addKeyDown(DOWN);
		break;
	case RIGHT:
		this->snake->addKeyDown(RIGHT);
		break;
	default:
		break;
	}
}


bool Mediator::next()
{
	return this->isNextLvl;
}

