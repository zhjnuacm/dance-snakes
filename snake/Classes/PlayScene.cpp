#include "PlayScene.h"
#include <iostream>
#include <string>
#include "StartMenu.h"
using std::cin;
using std::endl;
using std::cout;
using std::string;
using namespace cocos2d;

#define TimeLabelTag  2

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

		int x = CCDirector::sharedDirector()->getWinSize().width;
		int y = CCDirector::sharedDirector()->getWinSize().height;	

		CCLabelTTF* timeLabel = CCLabelTTF::create(Mediator::getInstance()->toString().c_str(), "Arial", 28);
		timeLabel->setPosition(ccp(x - 40, y - 20));

		/*CCLabelTTF* mySocreLabel = CCLabelTTF::create(Mediator::getInstance()->toString().c_str(), "Arial", 28);
		mySocreLabel->setPosition(ccp(x - 40, y - 20));
		CCLabelTTF* marsScoreLabel = CCLabelTTF::create(Mediator::getInstance()->toString().c_str(), "Arial", 28);
		marsScoreLabel->setPosition(ccp(x - 40, y - 40));*/

		//label->setOpacity(32);
		this->addChild(timeLabel, 1, TimeLabelTag);

		// Loops
		schedule(schedule_selector(PlayScene::snakeMove),0.3f); //0.3f
		schedule(schedule_selector(PlayScene::mainLoop),0.05f);
		schedule(schedule_selector(PlayScene::showTime), 1);
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

	if(Mediator::getInstance()->end())
	{
		cout << "Game over" << endl;
		CCDirector::sharedDirector()->pause();
		gameOverMenu();
	}
}

void PlayScene::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();
}

void PlayScene::showTime(float dt) {
	string t = Mediator::getInstance()->toString();
	(static_cast<CCLabelTTF *> (this->getChildByTag(TimeLabelTag)))->setString(t.c_str());
}


void PlayScene::gameOverMenu()
{
	CCLayerColor* menuLayer = CCLayerColor::create(ccc4(0, 0, 0, 255), 300, 300);
	int x = CCDirector::sharedDirector()->getWinSize().width;
	int y = CCDirector::sharedDirector()->getWinSize().height;
	menuLayer->setPosition(ccp(x / 2 - 150, y / 2 - 150));
	CCLabelTTF* timeLabel = CCLabelTTF::create("Game Over", "Arial", 28);
	timeLabel->setPosition(ccp(150, 200));
	menuLayer->addChild(timeLabel, 1);
	
	CCMenuItemImage *pStartItem = CCMenuItemImage::create(
			"load.png",
			"load_.png",
			this,
			menu_selector(PlayScene::mainMenu));
	CCMenuItemImage *pOptionsItem = CCMenuItemImage::create(
			"options.png",
			"options_.png",
			this,
			menu_selector(PlayScene::mainMenu));
	CCMenu* pMenu = CCMenu::create(pStartItem, pOptionsItem, NULL);
	pMenu->alignItemsVerticallyWithPadding(10);
	pMenu->setPosition(ccp(150, 130));

	menuLayer->addChild(pMenu, 1);

	this->addChild(menuLayer, 2);
}

void PlayScene::mainMenu(CCObject* pSender)
{
	CCScene *mScene = StartMenu::scene();
	//CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->replaceScene(mScene);
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(10, mScene));
}










