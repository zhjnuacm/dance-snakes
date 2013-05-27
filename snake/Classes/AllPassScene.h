#ifndef __ALL_PASS__
#define __ALL_PASS__

#include "Mediator.h"
#include "cocos2d.h"


class AllPassScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    CREATE_FUNC(AllPassScene);

	void startGameCallBack(CCObject* pSender);
	void mainMenuCallBack(CCObject* pSender);
private:
	
};

#endif  // 