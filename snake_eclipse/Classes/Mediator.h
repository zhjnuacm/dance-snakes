#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "snakes/Snake.h"
#include "snakes/MarsSnake.h"
#include "snakes/Map.h"
#include "snakes/FoodFactory.h"
#include "snakes/Food.h"
#include "snakes/DIR.h"
#include "cocos2d.h"
#include "snakes/ScoreAndTimePanel.h"

#include <string>
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)   
#include <windows.h>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#endif
using namespace cocos2d;

class Mediator {

private:

    Mediator();

	Snake *snake;

	MarsSnake *marsSnake;

	Map *map;
	FoodFactory *foodFactory;
	
	Food *food;
	
	bool isGameOver;
	bool isNextLvl;
	static Mediator *mdInstance;

	CCLayer *gameScene;

	long long gameTime;

	virtual ~Mediator();

	ScoreAndTimePanel * scoreAndTimePanel;
public:

	//获取实例
	static Mediator* getInstance();

	//初始化調度
	bool init();
	
	//碰撞檢測
	void dectectCollision();
	bool snakeDectectCollision();
	bool marsSDectectCollision();

	//判斷是否吃到食物
	bool dectectFood();

	//判斷遊戲是否結束
	bool end();
	bool next();
	//食物工廠產生食物
	void putNewFood();

	//載入配置文件
	bool loadConfig();
	
	void keyEvent(DIR);
	void addGameScene(CCLayer *layer);
	void addGameMap(char *path);
	bool gameOver();
	void snakeMove(float dt);
	void marsSnakeMove(float dt);
	void snakeEatFood();

	//char *
};

#endif
