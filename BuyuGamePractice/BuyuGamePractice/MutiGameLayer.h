//
//  MutiGameLayer.h
//  BuyuGamePractice
//
//  Created by xunianqiang on 14/11/7.
//
//

#ifndef __BuyuGamePractice__MutiGameLayer__
#define __BuyuGamePractice__MutiGameLayer__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

using namespace cocos2d;

class MutiGameLayer:public CCLayer{
    
public:
    bool init();
    CREATE_FUNC(MutiGameLayer);
    
//    void backClick(CCObject *sender);
};

#endif /* defined(__BuyuGamePractice__MutiGameLayer__) */
