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

		

		CCLabelTTF *text = CCLabelTTF::create("",simhei,38);
		text->setString(Tools::a2u("少年， 你都通关了， 你还想怎样！！").c_str());
		text->setPosition(ccp(size.width/2,size.height/2));
		text->setColor(ccc3(0,255,0));
		this->addChild(text);



		CCMenuItemLabel *p1 = CCMenuItemLabel::create(
			CCLabelTTF::create(Tools::a2u("重新开始").c_str(),simhei,32)
			); 
		p1->setTarget(this,menu_selector(AllPassScene::startGameCallBack));

		CCMenuItemLabel *p2 = CCMenuItemLabel::create(
			CCLabelTTF::create(Tools::a2u("主菜单").c_str(),simhei,32)
			); 
		p2->setTarget(this,menu_selector(AllPassScene::mainMenuCallBack));

		CCMenu* pMenu = CCMenu::create(p1,p2, NULL);
		pMenu->alignItemsVerticallyWithPadding(10);
		pMenu->setPosition(ccp(size.width - 150 , 80));
		pMenu->alignItemsHorizontallyWithPadding(10);
		CC_BREAK_IF(!pMenu);
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