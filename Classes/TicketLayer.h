/*
 * TicketLayer.h
 *
 *  Created on: 07-Jul-2013
 *      Author: sramanujan
 */

#ifndef TICKETLAYER_H_
#define TICKETLAYER_H_

#include "cocos2d.h"
#include "CCScrollView.h"
#include "Ticket.h"
#include "XTLayer.h"
#include "ServerImitator.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class TicketLayer : public XTLayer
{
	CCScrollView* _scrollViews[10];
	CCLayer* _scrollContainers[10];
	Ticket* _tickets[100];

	int** _cardArray;

public:

	float _ticketWidth;
	float _ticketHeight;
	int _numColumns;
	int _numRows;
	int _ticketCount;

	TicketLayer(int ticketCount = 20, int numRows = 10, int numColumns = 2)
	{
		_ticketCount = ticketCount;
//		_ticketWidth = 243.0;
//		_ticketHeight = 240.0;

		_ticketWidth = 360.0;
		_ticketHeight = 360.0;

		_numRows = numRows;
		_numColumns = numColumns;

		_cardArray = new int*[_ticketCount];
		for(int i = 0; i < _ticketCount; i++)
			_cardArray[i] = new int[25];

	}

	static TicketLayer* create(int ticketCount = 20, int numRows = 10, int numColumns = 2)
	{
	    TicketLayer *pRet = new TicketLayer(ticketCount, numRows, numColumns);
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

    // implement the "static node()" method manually
    //CREATE_FUNC(TicketLayer);

    virtual bool init()
    {
        if ( !CCLayer::init() )
        {
            return false;
        }

        // enable touches so we can drag
		this->setTouchEnabled(true);

        CCSize size = CCDirector::sharedDirector()->getWinSize();

        CCLabelTTF* pLabel = CCLabelTTF::create("Main Scene!!!", "Thonburi", 34);
        pLabel->setPosition( ccp(100, size.height - 20) );
        this->addChild(pLabel, 1);

        CCLOG("Ticket layer size1111!!! width: %f height: %f", this->getContentSize().width, this->getContentSize().height);

        ServerImitator::getTicketNumbers(_ticketCount, _cardArray);
        CCLOG("1111");

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        int j = 0, k = 0;
        for(;j < _numColumns; j++)
        {
        	_scrollContainers[j] = CCLayer::create();
        	_scrollContainers[j]->setPosition(CCPointZero);
        	_scrollContainers[j]->setContentSize(CCSizeMake(_ticketWidth, _numRows * _ticketHeight));

    		for(int i = 0;i < _numRows; i ++)
    		{
    			_tickets[k] = Ticket::create(_cardArray[k]);
    			_tickets[k]->setScaleX(_ticketWidth/_tickets[k]->getContentSize().width);
    			_tickets[k]->setScaleY(_ticketHeight/_tickets[k]->getContentSize().height);
    			_tickets[k]->setPosition(ccp(0, _ticketHeight*(float)i));
    			_scrollContainers[j]->addChild(_tickets[k++], 2);
    		}

    		_scrollViews[j] = CCScrollView::create(CCSizeMake(_ticketWidth, winSize.height), _scrollContainers[j]);
    		_scrollViews[j]->setPosition(ccp(winSize.width/2 - (_numColumns * _ticketWidth/2) + (j * _ticketWidth), 0.f));
    		_scrollViews[j]->setDirection(kCCScrollViewDirectionVertical);
    		// ScrollView initializes at the (left, bottom). The container also gets positioned relative to that and goes Y-up.
    		// Pre-set it to the value CCScrollView::minContainerOffset will return when it's scrolled to the top
    		// (note, this is a negative number, indicating the touch moving downwards, i.e. it's pre-scrolled such that the top of the content is visible when we begin)
    		_scrollViews[j]->setContentOffset(ccp(0.f, (winSize.height - (_numRows * _ticketHeight))), false);

    		addChild(_scrollViews[j]);
        }

        this->setContentSize( CCSizeMake(_numColumns * _ticketWidth, winSize.height));

        CCLOG("Ticket layer size22222!!! width: %f height: %f", this->getContentSize().width, this->getContentSize().height);

        return true;
    }

    virtual int numRows()
    {
    	return 3;
    }

    virtual int numColumns()
    {
    	return 2;
    }

    void scrollAll(int page)
    {
    	for(int j = 0;j < _numColumns; j++)
    	{
    		_scrollViews[j]->setContentOffset(ccp(0.f, (CCDirector::sharedDirector()->getWinSize().height - ((page + 1) * _ticketHeight))), true);
    	}
    }

    void scrollAll(float delta)
    {
    	for(int j = 0;j < _numColumns; j++)
    	{
    		float curPage = (CCDirector::sharedDirector()->getWinSize().height - _scrollViews[j]->getContentOffset().y) / _ticketHeight;
    		float page = fmin(fmax(1, curPage - delta), _numRows);
    		_scrollViews[j]->setContentOffset(ccp(0.f, (CCDirector::sharedDirector()->getWinSize().height - (page * _ticketHeight))), true);
    	}
    }

    int itemForTouch(CCPoint touchLocation)
    {
		for(int i = 0;i < _ticketCount; i ++)
		{
			CCPoint local = _tickets[i]->convertToNodeSpace(touchLocation);
            CCRect r = _tickets[i]->rect();
            r.origin = CCPointZero;

            if (r.containsPoint(local))
            {
                return i;
            }
		}
        return -1;
    }


    virtual void xtTapGesture(CCPoint position)
    {
    	int k = itemForTouch(position);
    	if(k != -1)
    	{
    		_tickets[k]->gotTouch(position);
    	}

	}

    virtual void xtLongTapGesture(CCPoint position)
    {
    	//check if this ticket won or loss
    	int k = itemForTouch(position);
    	if(k != -1)
    	{
    		_tickets[k]->finish(ServerImitator::checkForBingo(k));
    	}
	}

};

#endif /* TICKETLAYER_H_ */
