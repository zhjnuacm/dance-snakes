#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "snakes\Snake.h"

#include "snakes\Map.h"
#include "snakes\FoodFactory.h"
#include "snakes\Food.h"
#include "snakes\DIR.h"
#include "cocos2d.h"

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
	Map *map;
	FoodFactory *foodFactory;
	
	Food *food;
	
	bool isGameOver;
	
	static Mediator *mdInstance;

	CCLayer *gameScene;


	virtual ~Mediator();

public:

	//��ȡʵ��
	static Mediator* getInstance();

	//��ʼ���{��
	bool init();
	
	
	
	

	//��ײ�z�y
	bool dectectCollision();

	//�Д��Ƿ�Ե�ʳ��
	bool dectectFood();

	//�Д��[���Ƿ�Y��
	bool end();
	
	//ʳ�﹤�S�a��ʳ��
	void putNewFood();

	//�d�������ļ�
	bool loadConfig();
	
	void keyEvent();
	void addGameScene(CCLayer *layer);
	void addGameMap(char *path);
	bool gameOver();
	void snakeMove(float dt);
};

#endif