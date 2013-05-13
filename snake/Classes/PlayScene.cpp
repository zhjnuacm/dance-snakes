#include "PlayScene.h"
#include <iostream>
using std::cin;
using std::endl;
using std::cout;
using namespace cocos2d;

CCScene* PlayScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        PlayScene *layer = PlayScene::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

bool PlayScene::init()
{
    bool bRet = false;
    do 
    {


        CC_BREAK_IF(! CCLayer::init());

		//mediator
		Mediator::getInstance()->addGameScene(this);
		Mediator::getInstance()->addGameMap("maps/lvl1.tmx");
		Mediator::getInstance()->init();



		// menu
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(PlayScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        this->addChild(pMenu, 1);

		// Loops
		schedule(schedule_selector(PlayScene::snakeMove),0.3f);
		schedule(schedule_selector(PlayScene::mainLoop),0.05f);
        
		
		bRet = true;
    } while (0);

    return bRet;
}

void PlayScene::snakeMove(float dt)
{
	Mediator::getInstance()->snakeMove(dt);
}


void PlayScene::mainLoop(float dt)
{
	Mediator::getInstance()->keyEvent();
	Mediator::getInstance()->dectectCollision();
	Mediator::getInstance()->dectectFood();


	if(Mediator::getInstance()->end())
	{
		cout << "Game over" << endl;
		CCDirector::sharedDirector()->pause();
	}
}

void PlayScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

