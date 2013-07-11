/*
 * ScrollWheel.h
 *
 *  Created on: 07-Jul-2013
 *      Author: sramanujan
 */

#ifndef SCROLLWHEEL_H_
#define SCROLLWHEEL_H_

#define PI 3.14159265

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ToggleButton.h"
#include "CustomObject.h"

using namespace cocos2d;
using namespace CocosDenshion;
//using namespace cocos2d::extension;

class ScrollWheelWheel : public CCLayer
{
	CCSprite* _sprite;
	bool _touchStarted;
	float _angleStarted;
	float _radiusStarted;

	float _anglePrevious;

	float _scaleFactor;

	CCFiniteTimeAction* _rotateToCenter;
	CCFiniteTimeAction* _rotateToCenterDone;
	CCSequence* _rotateToCenterAnim;

	CCObject* _parent1;
	SEL_CallFuncO _selector1;


public:

    CREATE_FUNC(ScrollWheelWheel);

    // on "init" you need to initialize your instance
    virtual bool init()
    {
        if ( !CCLayer::init() )
        {
            return false;
        }
        _touchStarted = false;

        _sprite = CCSprite::create("Scroller01-DISC.png");
        this->setContentSize(_sprite->getContentSize());
        this->addChild(_sprite, 1);
        _scaleFactor = 1;

        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

        _rotateToCenter = CCRotateTo::create( 0.3, 0);
        _rotateToCenterAnim = CCSequence::create(_rotateToCenter, /*_rotateToCenterDone, */NULL);
        _rotateToCenterAnim->retain();
    }

    void setSelector(CCObject* parent, SEL_CallFuncO selector)
    {
    	_parent1 = parent;
    	_selector1 = selector;
    }

    void customSetScale(float scale)
    {
    	_scaleFactor = scale;
    	_sprite->setScale(scale);
    }

    CCRect rect(CCNode* item)
    {
    	return CCRectMake( item->getPosition().x - item->getContentSize().width*_scaleFactor * item->getAnchorPoint().x,
        		item->getPosition().y - item->getContentSize().height*_scaleFactor * item->getAnchorPoint().y,
        		item->getContentSize().width*_scaleFactor, item->getContentSize().height*_scaleFactor);
    }

    bool ccTouchBegan(CCTouch* _touch, cocos2d::CCEvent* event)
    {
    	_touchStarted = true;

    	CCPoint touchStartedPosition = convertTouchToNodeSpace(_touch);
    	_angleStarted = atan(touchStartedPosition.y/touchStartedPosition.x);
    	_radiusStarted = ccpDistance(touchStartedPosition, ccp(0,0));

    	_anglePrevious = _angleStarted * 180 / PI;

        CCRect r = rect(this);
        if (r.containsPoint(touchStartedPosition))
        {
            return true;
        }
        return false;
    }

    void ccTouchMoved(CCTouch* _touch, cocos2d::CCEvent* event)
    {

    	if(_touchStarted)
    	{
    		CCPoint currentPoint = convertTouchToNodeSpace(_touch);
    		float tAngle = (_angleStarted - atan(currentPoint.y / pow(pow(_radiusStarted, 2) - pow(fabs(currentPoint.y), 2), 0.5)))*180/PI;
    		_sprite->setRotation(tAngle);


    		CCLOG("page difference... : %f", (tAngle - _anglePrevious)/30);

    		CustomObject* obj = new CustomObject();
        	obj->setFloatData((tAngle - _anglePrevious)/30);
        	(_parent1->*_selector1)(obj);
        	_anglePrevious = tAngle;
    	}

    }


    void ccTouchEnded(CCTouch* _touch, cocos2d::CCEvent* event)
    {
		CCPoint currentPoint = convertTouchToNodeSpace(_touch);
		float tAngle = (_angleStarted - atan(currentPoint.y / pow(pow(_radiusStarted, 2) - pow(fabs(currentPoint.y), 2), 0.5)))*180/PI;

		//currently it was already rotated to tAngle, but now we need to rotate back by (float)((int)tAngle) - tAngle
/*		CustomObject* obj = new CustomObject();
    	obj->setFloatData(((float)((int)tAngle) - tAngle)/30);
    	(_parent1->*_selector1)(obj);*/

    	CCLOG("Total rotation = %f", tAngle);
    	_touchStarted = false;
    	_sprite->runAction(_rotateToCenterAnim);
    }

};


class ScrollWheel : public cocos2d::CCLayer
{
	ScrollWheelWheel* _wheel;

	CCSprite* _sprite1;
	float _scale;
	float _angle;
	int _numPages;
	float _angles[100];
	ToggleButton* _toggleBlobs[100];
	CCObject* _parent1;
	SEL_CallFuncO _selector1;

public:

	static const float drawAt = 0.8;
    // implement the "static node()" method manually
    CREATE_FUNC(ScrollWheel);

    // on "init" you need to initialize your instance
    virtual bool init()
    {
        if ( !CCLayer::init() )
        {
            return false;
        }

        // enable touches so we can drag
		//this->setTouchEnabled(true);

		_scale = 1;
		_angle = PI;

        _sprite1 = CCSprite::create("Scroller01.png");
        _sprite1->setPosition( CCPointZero );
        this->setContentSize(_sprite1->getContentSize());
        this->addChild(_sprite1, 1);

        _wheel = ScrollWheelWheel::create();
        _wheel->setPosition( CCPointZero );
        this->addChild(_wheel, 6);

        return true;
    }

    void setScaleTo(float scale)
    {
    	_scale = scale;
    	_sprite1->setScale(_scale);
    	_wheel->customSetScale(_scale);
    }


    void setAngleTo(float angleInDegrees)
    {
    	_angle = angleInDegrees*PI/180;
    	this->setPositionX(-this->getContentSize().width*_scale*cos(_angle)/2);
    }

    void setPagesTo(int numPages)
    {
    	_numPages = numPages;
    	int i = 0;
    	for(; i < _numPages; i++)
    	{
    		_angles[i] = (-_angle + (2*_angle*(i + 0.5)/_numPages)) * drawAt;

    		float x = drawAt * _scale * _sprite1->getContentSize().width*cos(_angles[i])/2;
    		float y = drawAt * _scale * _sprite1->getContentSize().width*sin(_angles[i])/2;

    		CCMenuItemImage* imag = CCMenuItemImage::create("Scroller05.png", "Scroller04.png", this, menu_selector(ScrollWheel::toggleButton));
    		imag->setScale(_scale);
    		_toggleBlobs[i] = ToggleButton::createWithTarget(i, this, menu_selector(ScrollWheel::toggleButton), imag, NULL);
    		CCMenu* menu = CCMenu::create(_toggleBlobs[i], NULL);
    		menu->setPosition( ccp(x,y) );
			this->addChild(menu, 1);
    	}
    	_toggleBlobs[i-1]->customSelect();

    }

    void toggleButton(CCObject* sender)
    {
    	ToggleButton* item = (ToggleButton*)sender;
    	int id = item->customId();
    	for(int i = 0; i < _numPages; i++)
    	{
    		if(i == id)
    		{
    			continue;
    		}
    		_toggleBlobs[i]->customUnselect();
    	}
    	if(item->customIsSelected())
    	{
    		item->customUnselect();
    	}
    	else
    	{
    		item->customSelect();
    	}


    	CustomObject* obj = new CustomObject();
    	obj->setIntData(id);

    	(_parent1->*_selector1)(obj);
    }

    void incrementPage()
    {

    }

    void decrementPage()
    {

    }

    void setSelector(CCObject* parent, SEL_CallFuncO selector)
    {
    	_parent1 = parent;
    	_selector1 = selector;
    	_wheel->setSelector(parent, selector);
    }
};

#endif /* SCROLLWHEEL_H_ */
