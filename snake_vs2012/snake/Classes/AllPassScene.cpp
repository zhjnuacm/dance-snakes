#include "AllPassScene.h"
#include "PlayScene.h"
#include "resource.h"
#include "Tools.h"
#include "StartMenu.h"
#include <iostream>
using std::cin;
using std::endl;
using std::cout;
using namespace cocos2d;

CCScene* AllPassScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		AllPassScene *layer = AllPassScene::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);
	} while (0);

	return scene;
}

bool AllPassScene::init()
{
	bool bRet = false;
	do 
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CC_BREAK_IF(! CCLayer::init());


		CCSprite *bg_allpass = CCSprite::create("img/bg_allpass.jpg");
		bg_allpass ->setAnchorPoint(ccp(0,0));
		this->addChild(bg_allpass);

		CCLabelTTF *text = CCLabelTTF::create("",simhei,38);
		text->setString(Tools::a2u("Snake: 少年，你都通关了，你还想怎样！！").c_str());
		text->setPosition(ccp(size.width/2,size.height/2));
		text->setColor(ccc3(30,30,30));
		this->addChild(text);


		CCMenuItemImage *p1 = CCMenuItemImage::create(
			"img/restart.png",
			"img/restart_.png",
			this,
			menu_selector(AllPassScene::startGameCallBack));
		CC_BREAK_IF(! p1);	

		CCMenuItemImage *p2 = CCMenuItemImage::create(
			"img/mainmenu.png",
			"img/mainmenu_.png",
			this,
			menu_selector(AllPassScene::mainMenuCallBack));
		CC_BREAK_IF(! p2);	

		CCMenu* pMenu = CCMenu::create(p1, p2, NULL);
		
		int x = CCDirector::sharedDirector()->getWinSize().width;
		int y = CCDirector::sharedDirector()->getWinSize().height;
		pMenu->alignItemsHorizontallyWithPadding(20);
		pMenu->setPosition(ccp(x -200, 50));
		

		this->addChild(pMenu, 1);





		bRet = true;
	} while (0);

	return bRet;
}




void AllPassScene::startGameCallBack(CCObject* pSender)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("lvl",1);
	CCScene *pScene = PlayScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	return ;
}

void AllPassScene::mainMenuCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(StartMenu::scene());
}