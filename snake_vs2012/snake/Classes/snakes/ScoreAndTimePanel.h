#pragma once
#ifndef SCORE_AND_TIME_PANEL
#define SCORE_AND_TIME_PANEL
#include "cocos2d.h"

using namespace cocos2d;
class ScoreAndTimePanel : public CCLayer
{
private :
	CCLabelBMFont *timeLabel;
	CCLabelBMFont *earthSnakeScoreLabel;
	CCLabelBMFont *marsSnakeScoreLabel;
	CCLabelBMFont *gameLvlLabel;
	long long gameTime ;
public:
	CCLabelBMFont * getTimeLabel()				{return this->timeLabel;}
	CCLabelBMFont * getEarthSnakeScoreLabel()	{return this->earthSnakeScoreLabel;}
	CCLabelBMFont * getMarsSnakeScoreLabel()	{return this->marsSnakeScoreLabel;}
	static ScoreAndTimePanel * create();
	void setEarthSnakeScore(int score);
	void setMarsSnakeScore(int score);
	ScoreAndTimePanel(void);
	~ScoreAndTimePanel(void);
	void step(float dt);
	bool init();
};

#endif