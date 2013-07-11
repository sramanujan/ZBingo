/*
 * Ticket.h
 *
 *  Created on: 07-Jul-2013
 *      Author: sramanujan
 */

#ifndef TICKET_H_
#define TICKET_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

struct TicketGrid
{
   static const float columnCenters[5];
   static const float rowCenters[5];
   static const float blobSize;
};
const float TicketGrid::columnCenters[5] = {
		33,
		76.5,
		119.5,
		162.5,
		206
};
const float TicketGrid::rowCenters[5] = {
		58.5,
		96.5,
		135,
		173,
		211.5
};

class Ticket : public CCLayer
{
	int* _ticketArray;
	CCSprite* _sprite;
	CCSprite* _redSprite;
	CCSprite* _greenSprite;
	//int ticketNumbers[5][5];
	CCLabelTTF* _ticketCells[5][5];
	CCSprite* _blobSprites[5][5];
	bool _cellSelected[5][5];
	CCArray* _togglersArray;

	bool _ticketOver;
public:

	Ticket(int* ticketArray)
	{
		_ticketArray = ticketArray;
		_ticketOver = false;
	}

    // implement the "static node()" method manually
	static Ticket* create(int* ticketArray)
	{
	    Ticket *pRet = new Ticket(ticketArray);
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

    // on "init" you need to initialize your instance
    virtual bool init()
    {
        //////////////////////////////
        // 1. super init first
        if ( !CCLayer::init() )
        {
            return false;
        }
        // enable touches so we can drag
		//this->setTouchEnabled(true);

        _togglersArray = CCArray::create();

        _sprite = CCSprite::create("BingoCardMC.png");
        this->setContentSize(_sprite->getContentSize());
        _sprite->setPosition( ccp(0,0) );
        _sprite->setAnchorPoint( ccp(0,0));
        this->addChild(_sprite, 1);

        _redSprite = CCSprite::create("BingoCardMC-RED.png");
        this->setContentSize(_redSprite->getContentSize());
        _redSprite->setPosition( ccp(0,0) );
        _redSprite->setAnchorPoint( ccp(0,0));
        _redSprite->setOpacity(100);
        _redSprite->setVisible(false);
        this->addChild(_redSprite, 5);

        _greenSprite = CCSprite::create("BingoCardMC-GREEN.png");
        this->setContentSize(_greenSprite->getContentSize());
        _greenSprite->setPosition( ccp(0,0) );
        _greenSprite->setAnchorPoint( ccp(0,0));
        _greenSprite->setOpacity(100);
        _greenSprite->setVisible(false);
        this->addChild(_greenSprite, 6);

        CCSprite* blobSprite = CCSprite::create("02.png");

        int k = 0;
        for(int i = 0; i < 5; i ++)
        {
        	for(int j= 0; j < 5; j++)
        	{

        		char buffer [50];
				int n, a=5, b=3;
				_ticketArray[k] == 0 ? sprintf(buffer, "*") : sprintf (buffer, "%d", _ticketArray[k]);
        		//ticketNumbers[i][j] = 4;
        		_ticketCells[i][j] = CCLabelTTF::create( buffer, "Thonburi", 28);
        		_ticketCells[i][j]->setFontFillColor(ccBLACK, true);
        		_ticketCells[i][j]->setPosition(ccp((TicketGrid::columnCenters[j]), (_sprite->getContentSize().height - TicketGrid::rowCenters[i])));
        		_cellSelected[i][j] = _ticketArray[k] == 0 ? true : false;

        		_blobSprites[i][j] = duplicateSprite(blobSprite);
        		_blobSprites[i][j]->setPosition(ccp((TicketGrid::columnCenters[j]), (_sprite->getContentSize().height - TicketGrid::rowCenters[i])));
        		_blobSprites[i][j]->setVisible(_ticketArray[k] == 0 ? true : false);
        		_blobSprites[i][j]->setScaleX(_ticketCells[i][j]->getContentSize().height/blobSprite->getContentSize().height);
        		_blobSprites[i][j]->setScaleY(_ticketCells[i][j]->getContentSize().height/blobSprite->getContentSize().height);

        		this->addChild(_blobSprites[i][j], 2);
        		this->addChild(_ticketCells[i][j], 3);
        		k++;
        	}
        }

        this->setAnchorPoint( ccp(0,0));
        this->setPosition( ccp(0,0));

        return true;
    }


    CCSprite* duplicateSprite(cocos2d::CCSprite *sprite) {
        CCSprite* pRet = CCSprite::createWithTexture(sprite->getTexture());
        if (sprite->getChildrenCount() > 0) {
            for (int child = 0; child < sprite->getChildrenCount(); child++) {
                CCSprite* spriteChild = (CCSprite*)sprite->getChildren()->objectAtIndex(child);
                CCSprite* clone = duplicateSprite((CCSprite*)spriteChild);
                clone->boundingBox() = spriteChild->boundingBox();
                clone->setContentSize(spriteChild->getContentSize());
                clone->setPosition(spriteChild->getPosition());
                clone->setAnchorPoint(spriteChild->getAnchorPoint());
                pRet->addChild(clone, spriteChild->getZOrder(), spriteChild->getTag());
            }
        }
        return pRet;
    }

    CCRect rect()
    {
        return CCRectMake( m_obPosition.x - m_obContentSize.width * m_obAnchorPoint.x,
                          m_obPosition.y - m_obContentSize.height * m_obAnchorPoint.y,
                          m_obContentSize.width, m_obContentSize.height);
    }

    CCRect rect(CCNode* item)
    {
    	return CCRectMake( item->getPosition().x - item->getContentSize().width * item->getAnchorPoint().x,
        		item->getPosition().y - item->getContentSize().height * item->getAnchorPoint().y,
        		item->getContentSize().width, item->getContentSize().height);
    }

    void gotTouch(CCPoint position)
    {
    	if(_ticketOver) return;
		itemForTouch(position);
    }

    void finish(bool isBingo)
    {
    	_ticketOver = true;
    	isBingo ? _greenSprite->setVisible(true) : _redSprite->setVisible(true);
    }

    int itemForTouch(CCPoint touchLocation)
    {

        for(int i = 0; i < 5; i ++)
        {
        	for(int j= 0; j < 5; j++)
        	{
    			CCPoint local = _ticketCells[i][j]->convertToNodeSpace(touchLocation);
                CCRect r = rect(_ticketCells[i][j]);
                r.origin = CCPointZero;

                if (r.containsPoint(local))
                {
					if(_cellSelected[i][j])
					{
						_blobSprites[i][j]->setVisible(false);
						_cellSelected[i][j] = false;
					}
					else
					{
						_blobSprites[i][j]->setVisible(true);
						_cellSelected[i][j] = true;
					}
                	return i;
                }
        	}
        }
        return -1;
    }
};

#endif /* TICKET_H_ */
