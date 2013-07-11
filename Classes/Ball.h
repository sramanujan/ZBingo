/*
 * Ball.h
 *
 *  Created on: 10-Jul-2013
 *      Author: sramanujan
 */

#ifndef BALL_H_
#define BALL_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class Ball : public CCLayer
{
	int _number;
	CCSprite* _bg;
	CCLabelTTF* _numberLabel;

public:
	Ball(int number)
	{
		_number = number;
	}

	static Ball* create(int number)
	{
		Ball *pRet = new Ball(number);
	    if (pRet && pRet->init())
	    {
	        pRet->autorelease();
	        return pRet;
	    }
	    else
	    {
	        delete pRet;
	        pRet = NULL;
	        return NULL;
	    }
	}

    virtual bool init()
    {
        if ( !CCLayer::init() )
        {
            return false;
        }

        if(_number > 60)
        {
        	_bg = CCSprite::create("O.png");
        }
        else if(_number > 45)
        {
        	_bg = CCSprite::create("G.png");
        }
        else if(_number > 30)
        {
        	_bg = CCSprite::create("N.png");
        }
        else if(_number > 15)
        {
        	_bg = CCSprite::create("I.png");
        }
        else if(_number > 0)
        {
        	_bg = CCSprite::create("B.png");
        }
        else
        {
        	_bg = CCSprite::create("Ball-Dummy.png");
        }
        this->setContentSize(_bg->getContentSize());
        _bg->setPosition( ccp(this->getContentSize().width/2, this->getContentSize().height/2) );
        _bg->setAnchorPoint( ccp(0.5,0.5));
		this->addChild(_bg, 1);

		char buffer [5];
		_number == 0 ? sprintf(buffer, "") : sprintf(buffer, "%d", _number);

		_numberLabel = CCLabelTTF::create( buffer, "Thonburi", 44);
		_numberLabel->setFontFillColor(ccBLACK, true);
		_numberLabel->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
		_numberLabel->setAnchorPoint( ccp(0.5,0.5));
		this->addChild(_numberLabel, 2);

        return true;
    }

};


#endif /* BALL_H_ */
