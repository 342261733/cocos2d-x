//
//  StartLayer.h
//  BuYuGame
//
//  Created by xunianqiang on 14-10-14.
//
//

#ifndef __BuYuGame__StartLayer__
#define __BuYuGame__StartLayer__

#include <iostream>
#include "cocos2d.h"

class StartLayer:public cocos2d::CCLayer{
public:
    bool init();
    
    void addMenu();
    void clickSingleMenu(cocos2d::CCObject *sender);
    void clickMultipleMenu(cocos2d::CCObject *sender);//clickOtherMenu
    void clickOtherMenu(cocos2d::CCObject *sender);//clickOtherMenu
};

#endif /* defined(__BuYuGame__StartLayer__) */
