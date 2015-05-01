//
//  GameLayer.h
//  BuYuGame
//
//  Created by xunianqiang on 14-10-14.
//
//

#ifndef __BuYuGame__GameLayer__
#define __BuYuGame__GameLayer__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class GameLayer:public CCLayer
{
public:
    bool init();
    
    void onEnter();
    void onEnterTransitionDidFinish();
    void onExit();
    
    void addStaticFish();
    void fishTimer(float dt);
    void trunHead(CCObject *sender);
    void removeFish(CCObject *sender);
    
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    void hit();//我自己添加的
    void actionEnded();
    
};


#endif /* defined(__BuYuGame__GameLayer__) */
