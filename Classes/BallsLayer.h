/*
 * BallsLayer.h
 *
 *  Created on: 09-Jul-2013
 *      Author: sramanujan
 */

#ifndef BALLSLAYER_H_
#define BALLSLAYER_H_

#include "cocos2d.h"
#include "Ball.h"

using namespace cocos2d;
using namespace CocosDenshion;

class BallsLayer : public CCLayer
{
	//0 - top (going to mid), 1 - mid (going to left), 2 - left (going to center), 3 - center (going to right)
	//4 - right ( going to destroy) //5 - destroying...
public:

	CCSprite* _sprite;
	Ball* _balls[6];
	CCFiniteTimeAction* _moveTopToMid;
	CCFiniteTimeAction* _moveTopToMidDone;
	CCFiniteTimeAction* _moveMidToLeft;
	CCFiniteTimeAction* _moveMidToLeftDone;
	CCFiniteTimeAction* _moveLeftToCenter;
	CCFiniteTimeAction* _moveLeftToCenterDone;
	CCFiniteTimeAction* _moveCenterToRight;
	CCFiniteTimeAction* _moveCenterToRightDone;
	CCFiniteTimeAction* _moveRightToDestroy;
	CCFiniteTimeAction* _moveRightToDestroyDone;

	CCSequence* _ball4Anim;
	CCSequence* _ball3Anim;
	CCSequence* _ball2Anim;
	CCSequence* _ball1Anim;
	CCSequence* _ball0Anim;

	float _ballSize;
	float _padding;
	float _spacing;

	BallsLayer()
	{
		_ballSize = 67;
		_spacing = 15;
		_padding = 22;
	}

	CREATE_FUNC(BallsLayer);

    virtual bool init()
    {
        if ( !CCLayer::init() )
        {
            return false;
        }

        this->setAnchorPoint(ccp(0.5,0.5));

        _sprite = CCSprite::create("ComingBingosPlate.png");
        this->setContentSize(_sprite->getContentSize());
        _sprite->setPosition( ccp(0,0) );
        _sprite->setAnchorPoint( ccp(0,0));
        this->addChild(_sprite, 1);


        _moveTopToMid = CCMoveTo::create( (float)1,  ccp(this->getContentSize().width/2 - _ballSize/2, this->getContentSize().height/2 - _ballSize/2) );
        _moveMidToLeft = CCMoveTo::create( (float)1,  ccp(_padding, _padding) );
        _moveLeftToCenter = CCMoveTo::create( (float)1,  ccp(this->getContentSize().width/2 - _ballSize/2, _padding) );
        _moveCenterToRight = CCMoveTo::create( (float)1,  ccp(this->getContentSize().width - _padding - _ballSize, _padding) );
        _moveRightToDestroy = CCMoveTo::create( (float)1,  ccp(this->getContentSize().width, _padding) );

        _moveTopToMidDone = CCCallFuncN::create( this,  callfuncN_selector(BallsLayer::actionDoneTopToMid));
        _moveMidToLeftDone = CCCallFuncN::create( this,  callfuncN_selector(BallsLayer::actionDoneMidToLeft));
        _moveLeftToCenterDone = CCCallFuncN::create( this,  callfuncN_selector(BallsLayer::actionDoneLeftToCenter));
        _moveCenterToRightDone = CCCallFuncN::create( this,  callfuncN_selector(BallsLayer::actionDoneCenterToRight));
        _moveRightToDestroyDone = CCCallFuncN::create( this,  callfuncN_selector(BallsLayer::actionDoneRightToDestroy));

        _ball4Anim = CCSequence::create(_moveRightToDestroy, _moveRightToDestroyDone, NULL);
        _ball4Anim->retain();
        _ball3Anim = CCSequence::create(_moveCenterToRight, _moveCenterToRightDone, NULL);
        _ball3Anim->retain();
        _ball2Anim = CCSequence::create(_moveLeftToCenter, _moveLeftToCenterDone, NULL);
        _ball2Anim->retain();
        _ball1Anim = CCSequence::create(_moveMidToLeft, _moveMidToLeftDone, NULL);
        _ball1Anim->retain();
        _ball0Anim = CCSequence::create(_moveTopToMid, _moveTopToMidDone, NULL);
        _ball0Anim->retain();

		//_balls[0]->setAnchorPoint( ccp(0,0));

        int i = 0;
        for(;i < 5; i++)
        {
        	_balls[i] = Ball::create(0);
        	this->addChild(_balls[i], 2);

        }

		_balls[0]->setPosition( ccp(this->getContentSize().width/2 - _ballSize/2 , this->getContentSize().height - _padding - _ballSize) );
		_balls[1]->setPosition( ccp(this->getContentSize().width/2 - _ballSize/2, this->getContentSize().height/2 - _ballSize/2) );
		_balls[2]->setPosition( ccp(_padding, _padding) );
		_balls[3]->setPosition( ccp(this->getContentSize().width/2 - _ballSize/2, _padding) );
		_balls[4]->setPosition( ccp(this->getContentSize().width - _padding - _ballSize, _padding) );

		_balls[4]->runAction(_ball4Anim);
        return true;
    }

    void addNewNumber(int number)
    {
    	//find out where to add the new ball
    	_balls[0] = Ball::create(number);// put it at top for now
    	_balls[0]->setPosition( ccp(this->getContentSize().width/2 - _ballSize/2 , this->getContentSize().height - _padding - _ballSize) );
    	this->addChild(_balls[0], 2);
    	_balls[4]->runAction(_ball4Anim);
    }

    void actionDoneTopToMid(CCNode* node)
    {
    	Ball* ball = (Ball*)node;
    	this->removeChild(ball);
    	_balls[1] = ball;
    	this->addChild(_balls[1], 2);
    	addNewNumber(ServerImitator::callOutNumber()); // start the loop allover!!
    }

    void actionDoneMidToLeft(CCNode* node)
    {
    	Ball* ball = (Ball*)node;
    	this->removeChild(ball);
    	_balls[2] = ball;
    	this->addChild(_balls[2], 2);
    	_balls[0]->runAction(_ball0Anim);
    }

    void actionDoneLeftToCenter(CCNode* node)
    {
    	Ball* ball = (Ball*)node;
    	this->removeChild(ball);
    	_balls[3] = ball;
    	this->addChild(_balls[3], 2);
    	_balls[1]->runAction(_ball1Anim);
    }

    void actionDoneCenterToRight(CCNode* node)
    {
    	Ball* ball = (Ball*)node;
    	this->removeChild(ball);
    	_balls[4] = ball;
    	this->addChild(_balls[4], 2);
    	_balls[2]->runAction(_ball2Anim);;
    }

    void actionDoneRightToDestroy(CCNode* node)
    {
    	Ball* ball = (Ball*)node;
    	this->removeChild(ball); // it will be autoreleased, so basically will be deleted!!
    	_balls[3]->runAction(_ball3Anim);
    }
};

#endif /* BALLSLAYER_H_ */
