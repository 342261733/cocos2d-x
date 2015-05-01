//
//  OtherGameLayer.h
//  BuyuGamePractice
//
//  Created by xunianqiang on 14/11/7.
//
//

#ifndef __BuyuGamePractice__OtherGameLayer__
#define __BuyuGamePractice__OtherGameLayer__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

using namespace cocos2d;

class OtherGameLayer:public CCLayer {
public:
    bool init();
    
    CREATE_FUNC(OtherGameLayer);
};

#endif /* defined(__BuyuGamePractice__OtherGameLayer__) */
