/*
 * CustomObject.h
 *
 *  Created on: 09-Jul-2013
 *      Author: sramanujan
 */

#ifndef CUSTOMOBJECT_H_
#define CUSTOMOBJECT_H_

#include "cocos2d.h"

using namespace cocos2d;
using namespace CocosDenshion;

class CustomObject : public CCObject
{
	int m_intData;
	float m_floatData;
public:
	CustomObject()
	{
		m_intData = 0;
		m_floatData = 0;
	}

	int getIntData()
	{
		return m_intData;
	}

	void setIntData(int data)
	{
		m_intData = data;
	}

	float getFloatData()
	{
		return m_floatData;
	}

	void setFloatData(float data)
	{
		m_floatData = data;
	}
};


#endif /* CUSTOMOBJECT_H_ */
