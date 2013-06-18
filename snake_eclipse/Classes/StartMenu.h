#ifndef __STARTMENU_H__
#define __STARTMENU_H__

#include "Mediator.h"
#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class StartMenu : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    CREATE_FUNC(StartMenu);
	void exitMenuCallBack(CCObject* pSender);
	void startGameCallBack(CCObject* pSender);

private:
	
};

#endif  // 