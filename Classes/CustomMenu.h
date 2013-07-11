/*
 * CustomMenu.h
 *
 *  Created on: 08-Jul-2013
 *      Author: sramanujan
 */

#ifndef CUSTOMMENU_H_
#define CUSTOMMENU_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class CustomMenu : public CCMenu
{
	bool m_customIsSelected;

public:
    // implement the "static node()" method manually
    CREATE_FUNC(CustomMenu);

    static CustomMenu* createWithArray(CCArray* pArrayOfItems)
    {
    	CustomMenu *pRet = new CustomMenu();
        if (pRet && pRet->initWithArray(pArrayOfItems))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pRet);
        }

        return pRet;
    }


    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event)
    {
        CC_UNUSED_PARAM(event);
        if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !isEnabled())
        {
            return false;
        }

        for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
        {
            if (c->isVisible() == false)
            {
                return false;
            }
        }

        m_pSelectedItem = this->itemForTouch(touch);
        if (m_pSelectedItem)
        {
            m_eState = kCCMenuStateTrackingTouch;
            m_pSelectedItem->selected();
            CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
            if (m_pSelectedItem)
            {
                m_pSelectedItem->unselected();
                m_pSelectedItem->activate();
            }
            m_eState = kCCMenuStateWaiting;
            //return true;
        }
        return false;
    }
};



#endif /* CUSTOMMENU_H_ */
