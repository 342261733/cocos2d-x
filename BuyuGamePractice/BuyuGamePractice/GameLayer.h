//
//  GameLayer.h
//  BuyuGamePractice
//
//  Created by xunianqiang on 14/11/7.
//
//

#ifndef __BuyuGamePractice__GameLayer__
#define __BuyuGamePractice__GameLayer__

#include <iostream>


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameLayer:public CCLayer {

    
public:
    bool init();
    CREATE_FUNC(GameLayer);
    
    void addMenu();
    
    //这几个函数会导致按钮点击失效
//    void onEnter();
//    void onEnterTransitionDidFinish();
//    void onExit();
    //
    void addStaticFish();
    void fishTimer(float dt);
    void trunHead(CCObject *sender);
    void removeFish(CCObject *sender);
    
    void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
//
//    void hit();//我自己添加的?
//    void actionEnded();
    
    void backClick(CCObject *sender);
    
    void checkHit(float dt);
    
private:
    CCSprite *fish;
    CCSprite *bullet;
};


#endif /* defined(__BuyuGamePractice__GameLayer__) */
