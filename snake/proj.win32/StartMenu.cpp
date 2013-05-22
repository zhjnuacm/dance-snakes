#include "StartMenu.h"
#include "PlayScene.h"
#include "resource.h"

#include <iostream>
using std::cin;
using std::endl;
using std::cout;
using namespace cocos2d;

CCScene* StartMenu::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        StartMenu *layer = StartMenu::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

bool StartMenu::init()
{
    bool bRet = false;
    do 
    {


        CC_BREAK_IF(! CCLayer::init());

		////mediator
		////Mediator::getInstance()->addGameScene(this);
		////Mediator::getInstance()->addGameMap("maps/lvl1.tmx");
		////Mediator::getInstance()->init();
		

		//CCMenuItemImage *pStartItem = CCMenuItemImage::create(
		//	"load.png",
		//	"load_.png",
		//	this,
		//	menu_selector(StartMenu::startGameCallBack));

		CCMenuItemImage *pStartItem = CCMenuItemImage::create(
			"load.png",
			"load_.png",
			this,
			menu_selector(StartMenu::startGameCallBack));
		CC_BREAK_IF(! pStartItem);


		CCMenuItemImage *pExitItem = CCMenuItemImage::create(
			"exit.png",
			"exit_.png",
			this,
			menu_selector(StartMenu::exitMenuCallBack));
		CC_BREAK_IF(! pExitItem);	


		CCMenu* pMenu = CCMenu::create(pStartItem, pExitItem, NULL);
		
		int x = CCDirector::sharedDirector()->getWinSize().width;
		int y = CCDirector::sharedDirector()->getWinSize().height;

		pMenu->alignItemsVerticallyWithPadding(10);
		pMenu->setPosition(ccp(x / 2, y / 2));
		
		CC_BREAK_IF(!pMenu);
		this->addChild(pMenu, 1);

		bRet = true;
    } while (0);

    return bRet;
}


void StartMenu::exitMenuCallBack(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}


void StartMenu::startGameCallBack(CCObject* pSender)
{
	CCScene *pScene = PlayScene::scene();
	//CCTransitionJumpZoom::transitionWithDuration(1.2, pScene);
	CCDirector::sharedDirector()->replaceScene(pScene);
	//CCDirector::sharedDirector()->pushScene(pScene);
	if(CCDirector::sharedDirector()->isPaused())
		CCDirector::sharedDirector()->resume();
	return ;
}