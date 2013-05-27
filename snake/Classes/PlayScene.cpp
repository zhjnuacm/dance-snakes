#include "PlayScene.h"
#include <iostream>
#include <string>
#include "StartMenu.h"
#include "Tools.h"
#include "AllPassScene.h"
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
	Mediator::getInstance()->keyEvent();
	Mediator::getInstance()->dectectCollision();
	Mediator::getInstance()->dectectFood();

	if(Mediator::getInstance()->end() )
	{
		CCDirector::sharedDirector()->pause(); 

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
	this->setVisible(false);
	CCDirector::sharedDirector()->resume();
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


CCLayer * PlayScene::genMenus(std::vector<string> menuItems , std::vector<cocos2d::SEL_MenuHandler> handlers, std::string msg)
{
	CCLayer * ret = CCLayer::create();
	CCLayerColor* bg = CCLayerColor::create(ccc4(0, 0, 0, 180), 300, 300);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	bg->setPosition(ccp(size.width / 2 - 150, size.height / 2 - 150));
	CCLabelTTF* msgLabel = CCLabelTTF::create(Tools::a2u(msg.c_str()).c_str(), simhei, 38);
	msgLabel->setColor(ccc3(255,0,0));
	msgLabel->setPosition(ccp(150, 250));
	bg->addChild(msgLabel);

	CCArray * pItems  = CCArray::create();
	pItems->retain();

	for(unsigned int i = 0 ; i < menuItems.size() ; i++)
	{
		CCMenuItemLabel *pItem = CCMenuItemLabel::create(
			CCLabelTTF::create(Tools::a2u(menuItems[i].c_str()).c_str(),simhei,32));
		pItem->setTarget(ret,handlers[i]);
		pItems->addObject(pItem);
	}
	CCMenu* pMenu = CCMenu::create();
	pMenu->initWithArray(pItems);
	pMenu->alignItemsVerticallyWithPadding(15);
	pMenu->setPosition(ccp(150, 130));
	bg->addChild(pMenu);
	ret->addChild(bg);
	return ret;
}

void PlayScene::initMenus()
{
	std::vector<string> itemsText;
	std::vector<SEL_MenuHandler> handlers;

	itemsText.push_back("重新开始");
	itemsText.push_back("主菜单");
	itemsText.push_back("退出游戏");
	handlers.push_back(menu_selector(PlayScene::restartGameCallBack));
	handlers.push_back(menu_selector(PlayScene::mainMenuCallBack));
	handlers.push_back(menu_selector(PlayScene::exitGameCallback));
	this->gameOverMenu = genMenus(itemsText,handlers,"真逗，你挂了！");
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
}