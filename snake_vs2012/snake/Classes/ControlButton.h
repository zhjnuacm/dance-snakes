#ifndef __CONTROL_BUTTON__
#define __CONTROL_BUTTON__

#include "Mediator.h"
#include "cocos2d.h"


class ControlButton : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(ControlButton);
	void upMenuCallBack(CCObject* pSender);
	void downMenuCallBack(CCObject* pSender);
	void leftMenuCallBack(CCObject* pSender);
	void rightMenuCallBack(CCObject* pSender);

private:
	
};

#endif  // 