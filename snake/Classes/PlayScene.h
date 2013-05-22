#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "Mediator.h"
#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class PlayScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
	void snakeMove(float dt);
	void mainLoop(float dt);
	void showTime(float dt);
	void showScore(float dt);

	void gameOverMenu();
	void mainMenu(CCObject* pSender);
    CREATE_FUNC(PlayScene);
private:

};

#endif  // 