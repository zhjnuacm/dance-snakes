#include "ControlButton.h"
#include "AllPassScene.h"
#include <iostream>
using std::cin;
using std::endl;
using std::cout;
using namespace cocos2d;

CCScene* ControlButton::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        ControlButton *layer = ControlButton::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

bool ControlButton::init()
{
    bool bRet = false;
    do 
    {

        CC_BREAK_IF(! CCLayer::init());
		
		CCMenuItemImage *left = CCMenuItemImage::create(
			"img/left1.png",
			"img/left2.png",
			this,
			menu_selector(ControlButton::leftMenuCallBack));
		left->setPosition(ccp(-250,150));

		CCMenuItemImage *right = CCMenuItemImage::create(
			"img/left1.png",
			"img/left2.png",
			this,
			menu_selector(ControlButton::rightMenuCallBack));
		right->setRotation(180.0f);
		right->setPosition(ccp(-80,150));

		CCMenuItemImage *up = CCMenuItemImage::create(
			"img/up1.png",
			"img/up2.png",
			this,
			menu_selector(ControlButton::upMenuCallBack));
		up->setPosition(ccp(-160,250));

		CCMenuItemImage *down = CCMenuItemImage::create(
			"img/up1.png",
			"img/up2.png",
			this,
			menu_selector(ControlButton::downMenuCallBack));
		down->setRotation(180.f);
		down->setPosition(ccp(-160,60));

		CCMenu* control = CCMenu::create(left, right, up,down, NULL);
		control->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width,0));
		control->setOpacity(150);
		this->addChild(control);
		bRet = true;
    } while (0);

    return bRet;
}


void ControlButton::upMenuCallBack(CCObject* pSender){
	Mediator::getInstance()->keyEvent(UP);
}
void ControlButton::downMenuCallBack(CCObject* pSender){
	Mediator::getInstance()->keyEvent(DOWN);
}
void ControlButton::leftMenuCallBack(CCObject* pSender){
	Mediator::getInstance()->keyEvent(LEFT);
}
void ControlButton::rightMenuCallBack(CCObject* pSender){
	Mediator::getInstance()->keyEvent(RIGHT);
}
