#ifndef __BILLING_H__
#define __BILLING_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

class Billing
{
public:
	static void forBigPacks();
};


#endif