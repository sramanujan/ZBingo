/*
 * ToggleButton.h
 *
 *  Created on: 08-Jul-2013
 *      Author: sramanujan
 */

#ifndef TOGGLEBUTTON_H_
#define TOGGLEBUTTON_H_

#include "cocos2d.h"

using namespace cocos2d;
using namespace CocosDenshion;

class ToggleButton : public CCMenuItemToggle
{
	int m_id;
	bool m_customIsSelected;

public:

    // implement the "static node()" method manually
    CREATE_FUNC(ToggleButton);

    ToggleButton(int id = 0) : CCMenuItemToggle()
    {
    	m_id = id;
    	m_customIsSelected = false;
    }

    static ToggleButton* createWithTarget(int id, CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, ...)
    {
        va_list args;
        va_start(args, item);
        ToggleButton *pRet = new ToggleButton(id);
        pRet->initWithTarget(target, selector, item, args);
        pRet->autorelease();
        va_end(args);
        return pRet;
    }

    virtual int customId()
    {
    	return m_id;
    }

    virtual bool customIsSelected()
    {
    	return m_customIsSelected;
    }

    virtual void customSelect()
    {
    	m_customIsSelected = true;
    	selected();
    }

    virtual void customUnselect()
    {
    	m_customIsSelected = false;
    	unselected();
    }

};

#endif /* TOGGLEBUTTON_H_ */
