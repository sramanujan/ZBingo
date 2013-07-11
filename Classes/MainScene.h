/*
 * MainScene.h
 *
 *  Created on: 06-Jul-2013
 *      Author: sramanujan
 */

#ifndef MAINSCENE_H_
#define MAINSCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "TicketLayer.h"
#include "ScrollWheel.h"
#include "CustomObject.h"
#include "BallsLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class MainScene : public cocos2d::CCScene
{
	TicketLayer* _ticketLayer;
	CCSprite* _bg;
	CCMenu* _pMenu;
	ScrollWheel* _wheel;
	BallsLayer* _ballsLayer;
	int ticketCount;
	int numRows;
	int numColumns;
	float wheelAngleDegrees;
	float wheelScale;
public:

	static MainScene* staticInstance;

	MainScene()
	{
		ticketCount = 10;
		numRows = 5;
		numColumns = 2;
		wheelAngleDegrees = 70;
		wheelScale = 2;
		MainScene* staticInstance = this;
	}

	virtual bool init()
	{
		//Make the scene occupy entire screen - duh? (set width and height)
		if( !CCScene::init() )
		{
			return false;
		}

		// ask director the window size
		CCSize size = CCDirector::sharedDirector()->getWinSize();

        // add "HelloWorld" splash screen"
		_bg = CCSprite::create("bg.png");
		float scaleX = size.width / _bg->getContentSize().width ;
		float scaleY = size.height / _bg->getContentSize().height;
        // position the sprite on the center of the screen
		_bg->setScaleX(scaleX);
		_bg->setScaleY(scaleY);
		_bg->setPosition( ccp(size.width/2, size.height/2) );
        // add the sprite as a child to this layer
        this->addChild(_bg, 0);

        // add a "close" icon to exit the progress. it's an autorelease object
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MainScene::menuCloseCallback) );
        pCloseItem->setPosition( ccp(size.width - 20, 20) );
        // create menu, it's an autorelease object
        _pMenu = CCMenu::create(pCloseItem, NULL);
        _pMenu->setPosition( CCPointZero );
        this->addChild(_pMenu, 1);

        _wheel = ScrollWheel::create();
        _wheel->setSelector(this, callfuncO_selector(MainScene::wheelMove));
        _wheel->setScaleTo(wheelScale);
        _wheel->setAngleTo(wheelAngleDegrees);
        _wheel->setPagesTo(numRows);
        _wheel->setPositionY(size.height/2);
        this->addChild(_wheel,2);

        _ticketLayer = TicketLayer::create(ticketCount, numRows, numColumns);
        //CCLOG("Ticket layer size!!! width: %f height: %f", _ticketLayer->getContentSize().width, _ticketLayer->getContentSize().height);
        this->addChild(_ticketLayer, 1);

        _ballsLayer = BallsLayer::create();
        _ballsLayer->setPosition(size.width - 225, size.height/2 - 100);
        _ballsLayer->setScale(1.3);
        this->addChild(_ballsLayer, 1);

        return true;
	}

	void wheelMove(CCObject* param)
	{
		CustomObject* customParam = (CustomObject *)param;
		if(customParam->getFloatData() != 0)
		{
			_ticketLayer->scrollAll(customParam->getFloatData());
		}
		else
		{
			_ticketLayer->scrollAll(customParam->getIntData());
		}
	}

	void wheelMoveAbsolute(int page)
	{
		_ticketLayer->scrollAll(page);
	}

	void wheelMoveRelative(float delta)
	{
		_ticketLayer->scrollAll(delta);
	}

	TicketLayer* getTicketLayer()
	{
		return _ticketLayer;
	}

    void menuCloseCallback(CCObject* pSender)
    {
        CCDirector::sharedDirector()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
    }
};

#endif /* MAINSCENE_H_ */
