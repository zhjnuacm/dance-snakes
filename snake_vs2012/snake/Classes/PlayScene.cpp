#include "PlayScene.h"
#include <iostream>
#include <string>
#include "StartMenu.h"
#include "Tools.h"
#include "AllPassScene.h"
#include "SimpleAudioEngine.h"
#include "ControlButton.h"
using std::cin;
using std::endl;
using std::cout;
using std::string;
using namespace cocos2d;

#define GAME_OVER_LBAEL_TAG  1000

const int scoreLabelTag = 3;

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
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/BackGround.mp3",true);
		//CCUserDefault::sharedUserDefault()->setIntegerForKey("total",7);
		int lvl = CCUserDefault::sharedUserDefault()->getIntegerForKey("lvl");
		int total = CCUserDefault::sharedUserDefault()->getIntegerForKey("total");
		
		if(lvl == 0){
			lvl = 1;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("lvl",1);
		}
	
		char mapPath[20];
		sprintf(mapPath,"maps/lvl%d.tmx",lvl);
		Mediator::getInstance()->addGameScene(this);
		Mediator::getInstance()->addGameMap(mapPath);
		
		Mediator::getInstance()->init();
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		addPauseButton();
		initMenus();
		CCLayer * control = ControlButton::create();
		this->addChild(control,2);
		// Loops
		schedule(schedule_selector(PlayScene::snakeMove),0.3f); //0.3f
		schedule(schedule_selector(PlayScene::mainLoop),0.05f);
	
		//schedule(schedule_selector(PlayScene::showScore), 1);
		//CCDirector::sharedDirector()->pause();
		bRet = true;
	} while (0);
	return bRet;
}

void PlayScene::snakeMove(float dt) {
	Mediator::getInstance()->snakeMove(dt);
	Mediator::getInstance()->marsSnakeMove(dt);
}

void PlayScene::mainLoop(float dt) {


#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// win32 key
	if(KEY_DOWN(VK_UP))
	{
		Mediator::getInstance()->keyEvent(UP);
		return;
	}
	if(KEY_DOWN(VK_DOWN))
	{
		Mediator::getInstance()->keyEvent(DOWN);;
		return;
	}
	if(KEY_DOWN(VK_LEFT))
	{
		Mediator::getInstance()->keyEvent(LEFT);

		return;
	}
	if(KEY_DOWN(VK_RIGHT))
	{
		Mediator::getInstance()->keyEvent(RIGHT);
		return;
	}
	
#endif
	

	Mediator::getInstance()->dectectCollision();
	Mediator::getInstance()->dectectFood();

	if(Mediator::getInstance()->end() )
	{
		CCDirector::sharedDirector()->pause(); 
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/GameOver.mp3");
		if(Mediator::getInstance()->next())	//下一关
		{
			this->gameNextMenu->setVisible(true);
		}
		else
		{
			this->gameOverMenu->setVisible(true);
		}
	}
}

void PlayScene::menuPauseCallback(CCObject* pSender) {
	if(CCDirector::sharedDirector()->isPaused())
		return;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CCDirector::sharedDirector()->pause();
	this->gamePauseMenu->setVisible(true);
	
}

void PlayScene::nextGameCallBack(CCObject* pSender)
{
	
	int lvl = CCUserDefault::sharedUserDefault()->getIntegerForKey("lvl");
	int total = CCUserDefault::sharedUserDefault()->getIntegerForKey("total");
	CCUserDefault::sharedUserDefault()->setIntegerForKey("lvl",lvl+1);
	if(lvl+1 > total)
		CCDirector::sharedDirector()->replaceScene(AllPassScene::scene());
	else
		CCDirector::sharedDirector()->replaceScene(PlayScene::scene());
	CCDirector::sharedDirector()->resume();
}
void PlayScene::mainMenuCallBack(CCObject* pSender)
{
	CCScene *mScene = StartMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}

void PlayScene::resumeGameCallBack(CCObject* pSender)
{
	gamePauseMenu->setVisible(false);
	CCDirector::sharedDirector()->resume();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void PlayScene::saveGameCallback(CCObject* pSender)
{

}
void PlayScene::exitGameCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void PlayScene::restartGameCallBack(CCObject* pSender)
{
	if(CCDirector::sharedDirector()->isPaused())
		CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->replaceScene(PlayScene::scene());
}

void PlayScene::addPauseButton()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *pPauseItem = CCMenuItemImage::create(
		"img/pause.png",
		"img/pause.png",
		this,
		menu_selector(PlayScene::menuPauseCallback));
	pPauseItem->setPosition(ccp(0, size.height/2-30));
	CCMenu * menu = CCMenu::create(pPauseItem,NULL);
	menu->setOpacity(170);
	this->addChild(menu,3);
}


CCLayer * PlayScene::genMenus(std::vector<std::string> menuItems , std::vector<cocos2d::SEL_MenuHandler> handlers, std::string msg)
{
	CCLayer * ret = CCLayer::create();
	CCLayerColor* bg = CCLayerColor::create(ccc4(0, 0, 0, 125), 300, 250);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	bg->setPosition(ccp(size.width / 2 - 150, size.height / 2 - 50));

	CCLabelTTF* msgLabel = CCLabelTTF::create(Tools::a2u(msg.c_str()).c_str(), simhei, 24);
	msgLabel->setColor(ccc3(255,0,0));
	msgLabel->setPosition(ccp(150, 250));
	bg->addChild(msgLabel);

	CCArray * pItems  = CCArray::create();
	pItems->retain();

	for(unsigned int i = 0 ; i < menuItems.size() ; i++)
	{
		CCMenuItemLabel *pItem = CCMenuItemLabel::create(
			CCLabelTTF::create(Tools::a2u(menuItems[i].c_str()).c_str(),simhei,24));
		pItem->setTarget(ret,handlers[i]);
		pItems->addObject(pItem);
	}
	CCMenu* pMenu = CCMenu::create();
	pMenu->initWithArray(pItems);
	pMenu->alignItemsVerticallyWithPadding(10);
	pMenu->setPosition(ccp(150, 130));
	bg->addChild(pMenu);
	ret->addChild(bg);
	return ret;
}

CCLayer * PlayScene::getMenus(CCMenu* pMenu, std::string msg)
{
	CCLayer * ret = CCLayer::create();
	CCLayerColor* bg = CCLayerColor::create(ccc4(0, 0, 0, 125), 320, 180);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	bg->setPosition(ccp(size.width / 2 - 150, size.height / 2 - 50));

	CCLabelTTF* msgLabel = CCLabelTTF::create(Tools::a2u(msg.c_str()).c_str(), simhei, 32);
	msgLabel->setColor(ccc3(255,255,255));
	msgLabel->setPosition(ccp(150, 130));
	bg->addChild(msgLabel);

	pMenu->alignItemsHorizontallyWithPadding(30);
	pMenu->setPosition(ccp(150, 50));
	bg->addChild(pMenu);
	ret->addChild(bg);
	return ret;
}



void PlayScene::initMenus()
{
	//std::vector<string> itemsText;
	//std::vector<SEL_MenuHandler> handlers;
	do{
	CCMenuItemImage *p1 = CCMenuItemImage::create(
			"img/restart2.png",
			"img/restart2_.png",
			this,
			menu_selector(PlayScene::restartGameCallBack));
		CC_BREAK_IF(! p1);

	CCMenuItemImage *p2 = CCMenuItemImage::create(
			"img/menu.png",
			"img/menu_.png",
			this,
			menu_selector(PlayScene::mainMenuCallBack));
		CC_BREAK_IF(! p2);

	CCMenuItemImage *p3 = CCMenuItemImage::create(
			"img/exit2.png",
			"img/exit2_.png",
			this,
			menu_selector(PlayScene::exitGameCallback));
		CC_BREAK_IF(! p3);

	CCMenu* pMenu1 = CCMenu::create(p1, p2, p3, NULL);

	this->gameOverMenu = getMenus(pMenu1, "真逗，你挂了！");
	this->gameOverMenu->setVisible(false);
	this->addChild(gameOverMenu,1);


	/////////////////////////////////

	CCMenuItemImage *p4 = CCMenuItemImage::create(
			"img/resume.png",
			"img/resume_.png",
			this,
			menu_selector(PlayScene::resumeGameCallBack));
		CC_BREAK_IF(! p4);

	CCMenuItemImage *p5 = CCMenuItemImage::create(
			"img/save.png",
			"img/save_.png",
			this,
			menu_selector(PlayScene::saveGameCallback));
		CC_BREAK_IF(! p5);

	CCMenuItemImage *p6 = CCMenuItemImage::create(
			"img/menu.png",
			"img/menu_.png",
			this,
			menu_selector(PlayScene::mainMenuCallBack));
		CC_BREAK_IF(! p6);

	CCMenu* pMenu2 = CCMenu::create(p4, p5, p6, NULL);

	this->gamePauseMenu = getMenus(pMenu2,"少侠，休息一会");
	this->gamePauseMenu->setVisible(false);
	this->addChild(gamePauseMenu,1);

	//////////////////////////////////////////////


	CCMenuItemImage *p7 = CCMenuItemImage::create(
			"img/next.png",
			"img/next_.png",
			this,
			menu_selector(PlayScene::nextGameCallBack));
		CC_BREAK_IF(! p7);

	CCMenuItemImage *p8 = CCMenuItemImage::create(
			"img/save.png",
			"img/save_.png",
			this,
			menu_selector(PlayScene::saveGameCallback));
		CC_BREAK_IF(! p8);

	CCMenuItemImage *p9 = CCMenuItemImage::create(
			"img/menu.png",
			"img/menu_.png",
			this,
			menu_selector(PlayScene::mainMenuCallBack));
		CC_BREAK_IF(! p9);
	CCMenu* pMenu3 = CCMenu::create(p7, p8, p9, NULL);

	this->gameNextMenu = getMenus(pMenu3,"少侠，你赢了！");
	this->gameNextMenu->setVisible(false);
	this->addChild(gameNextMenu,1);

	}while(0);


	/*

	itemsText.push_back("restart");
	itemsText.push_back("主菜单");
	itemsText.push_back("退出游戏");
	this->gameOverMenu = genMenus(handlers, "真逗，你挂了！");
	this->gameOverMenu->setVisible(false);
	this->addChild(gameOverMenu,1);

	itemsText.clear();
	handlers.clear();
	itemsText.push_back("继续游戏");
	itemsText.push_back("保存游戏");
	itemsText.push_back("主菜单");
	handlers.push_back(menu_selector(PlayScene::resumeGameCallBack));
	handlers.push_back(menu_selector(PlayScene::saveGameCallback));
	handlers.push_back(menu_selector(PlayScene::mainMenuCallBack));
	this->gamePauseMenu = genMenus(itemsText,handlers,"少侠，休息一会");
	this->gamePauseMenu->setVisible(false);
	this->addChild(gamePauseMenu,1);

	itemsText.clear();
	handlers.clear();
	itemsText.push_back("下一关");
	itemsText.push_back("保存游戏");
	itemsText.push_back("主菜单");
	handlers.push_back(menu_selector(PlayScene::nextGameCallBack));
	handlers.push_back(menu_selector(PlayScene::saveGameCallback));
	handlers.push_back(menu_selector(PlayScene::mainMenuCallBack));
	this->gameNextMenu = genMenus(itemsText,handlers,"少侠，你赢了！");
	this->gameNextMenu->setVisible(false);
	this->addChild(gameNextMenu,1);
	*/

}