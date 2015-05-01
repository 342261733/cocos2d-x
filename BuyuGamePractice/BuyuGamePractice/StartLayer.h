//
//  StartLayer.h
//  BuyuGamePractice
//
//  Created by xunianqiang on 14/11/7.
//
//

#ifndef __BuyuGamePractice__StartLayer__
#define __BuyuGamePractice__StartLayer__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

class StartLayer:public CCLayer {
    
public:
    
    
    bool init();
    CREATE_FUNC(StartLayer);
    
    
    void addMenu();
    void clickSingleMenu(CCObject *sender);
    void clickMultipleMenu(CCObject *sender);
    void clickOtherMenu(CCObject *sender);
};

#endif /* defined(__BuyuGamePractice__StartLayer__) */
