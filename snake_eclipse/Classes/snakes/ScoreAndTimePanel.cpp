#include "ScoreAndTimePanel.h"
#include <string>
using std::string;

ScoreAndTimePanel::ScoreAndTimePanel(void)
{
}


ScoreAndTimePanel::~ScoreAndTimePanel(void)
{
}


ScoreAndTimePanel * ScoreAndTimePanel::create()
{
	ScoreAndTimePanel * ret = new ScoreAndTimePanel();
	if(ret && ret->init())
		return ret;
	return NULL;
}


bool ScoreAndTimePanel::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->gameTime = 0;
	this->timeLabel	= CCLabelBMFont::create("Time 00:00","fonts/konqa32.fnt");
	this->timeLabel->setPosition(ccp(size.width-100,size.height-20));
	this->timeLabel->setScale(0.8f);
	this->addChild(this->timeLabel);

	int lvl = CCUserDefault::sharedUserDefault()->getIntegerForKey("lvl");
	char buffer[30];
	sprintf(buffer,"Lvl%d",lvl);
	this->gameLvlLabel	= CCLabelBMFont::create(buffer,"fonts/konqa32.fnt");
	this->gameLvlLabel->setPosition(ccp(size.width-210,size.height-20));
	this->gameLvlLabel->setScale(0.8f);
	this->addChild(this->gameLvlLabel);
	schedule(schedule_selector(ScoreAndTimePanel::step), 1);
	
	this->earthSnakeScoreLabel	= CCLabelBMFont::create("Your Score  : 0","fonts/futura-48.fnt");
	this->earthSnakeScoreLabel->setPosition(ccp(100,size.height-20));
	this->earthSnakeScoreLabel->setScale(0.5f);
	this->earthSnakeScoreLabel->setOpacity(175);
	this->addChild(this->earthSnakeScoreLabel);

	this->marsSnakeScoreLabel	= CCLabelBMFont::create("She's Score : 0","fonts/futura-48.fnt");
	this->marsSnakeScoreLabel->setPosition(ccp(100,size.height-60));
	this->marsSnakeScoreLabel->setOpacity(175);
	this->marsSnakeScoreLabel->setScale(0.5f);
	this->addChild(this->marsSnakeScoreLabel);

	
	return true;
}


void ScoreAndTimePanel::step(float dt)
{
	char ret[] = {"00:00"};
	
	long long t = this->gameTime++;
	string show = string("Time ");
	if(t == 0)
		show += "00:00";
	else{
		int s = t % 60;
		int m = t / 60;

		ret[0] = m / 10 + '0', ret[1] = m % 10 + '0';

		ret[3] = s / 10 + '0', ret[4] = s % 10 + '0';
		show += string(ret);
	}
	this->timeLabel->setString(show.c_str());
}

void ScoreAndTimePanel::setEarthSnakeScore(int score)
{
	char buffer[50];
	sprintf(buffer,"%s%d","Your Score  : ",score);
	
	this->earthSnakeScoreLabel->setString(buffer);
	this->earthSnakeScoreLabel->runAction(
		CCSequence::create(CCScaleTo::create(0.05f,0.8f,0.8f),CCScaleTo::create(0.05f,0.5,0.5),
		NULL
		)
	);
}

void ScoreAndTimePanel::setMarsSnakeScore(int score)
{
	char buffer[50];
	sprintf(buffer,"%s%d","She's Score  : ",score);
	this->marsSnakeScoreLabel->setString(buffer);
	this->marsSnakeScoreLabel->runAction(
		CCSequence::create(CCScaleTo::create(0.05f,0.8f,0.8f),CCScaleTo::create(0.05f,0.5,0.5),
		NULL
		)
	);
}