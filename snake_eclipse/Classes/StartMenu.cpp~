#include "StartMenu.h"
#include "PlayScene.h"

#include "AllPassScene.h"
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

		CCUserDefault::sharedUserDefault()->setIntegerForKey("total",7);
		CCSprite *bg = CCSprite::create("img/bg.png");
		bg ->setAnchorPoint(ccp(0, 0));
		this ->addChild(bg);


		CCMenuItemImage *pStartItem = CCMenuItemImage::create(
			"img/start.png",
			"img/start_.png",
			this,
			menu_selector(StartMenu::startGameCallBack));
		CC_BREAK_IF(! pStartItem);
		pStartItem -> setPosition(ccp(-253, 0));

		CCMenuItemImage *pLoadItem = CCMenuItemImage::create(
			"img/load.png",
			"img/load_.png",
			this,
			menu_selector(StartMenu::exitMenuCallBack));
		CC_BREAK_IF(! pLoadItem);
		pLoadItem -> setPosition(ccp(-81, 0));


		CCMenuItemImage *pScoreItem = CCMenuItemImage::create(
			"img/score.png",
			"img/score_.png",
			this,
			menu_selector(StartMenu::exitMenuCallBack));
		CC_BREAK_IF(! pScoreItem);	

		pScoreItem -> setPosition(ccp(81, 0));

			CCMenuItemImage *pAboutItem = CCMenuItemImage::create(
			"img/about.png",
			"img/about_.png",
			this,
			menu_selector(StartMenu::exitMenuCallBack));
		CC_BREAK_IF(! pAboutItem);	

		pAboutItem -> setPosition(ccp(360, 400));

		CCMenuItemImage *pExitItem = CCMenuItemImage::create(
			"img/exit.png",
			"img/exit_.png",
			this,
			menu_selector(StartMenu::exitMenuCallBack));
		CC_BREAK_IF(! pExitItem);	

		pExitItem -> setPosition(ccp(253, 0));



		CCMenu* pMenu = CCMenu::create(pStartItem, pLoadItem, pScoreItem, pAboutItem, pExitItem, NULL);
		
		int x = CCDirector::sharedDirector()->getWinSize().width;
		int y = CCDirector::sharedDirector()->getWinSize().height;

		pMenu->setPosition(ccp(x / 2, 50));
		
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
	int lvl = CCUserDefault::sharedUserDefault()->getIntegerForKey("lvl");
	int total = CCUserDefault::sharedUserDefault()->getIntegerForKey("total");
	if(lvl > total)
		CCDirector::sharedDirector()->replaceScene(AllPassScene::scene());
	else{
		CCScene *pScene = PlayScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
	if(CCDirector::sharedDirector()->isPaused())
		CCDirector::sharedDirector()->resume();
	return ;
}
