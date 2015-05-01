//
//  StartLayer.cpp
//  BuyuGamePractice
//
//  Created by xunianqiang on 14/11/7.
//
//

#include "StartLayer.h"

#include "GameLayer.h"
#include "MutiGameLayer.h"
#include "OtherGameLayer.h"

USING_NS_CC;

bool StartLayer::init()
{
    bool ret = CCLayer::init();
    if (ret == false) {
        return false;
    }
    
    CCDirector *d = CCDirector::sharedDirector();
    CCSize size = d->getWinSize();
    
    CCSprite *bgSprite = new CCSprite();
    bgSprite->initWithFile("loading-hd.png");
    bgSprite->setPosition(ccp(0, 0));
    bgSprite->setAnchorPoint(ccp(0, 0));//有点意思...
    this->addChild(bgSprite);
    
    this->addMenu();
    
    return true;
    
}

void StartLayer::addMenu()
{
    CCMenuItemImage *singleItem = CCMenuItemImage::create("btn_start_single_1-hd.png", "btn_start_single_2-hd.png");
    singleItem->setTarget(this, menu_selector(StartLayer::clickSingleMenu));
    singleItem->setPosition(-210,-122);
    
    CCMenuItemImage *mutipleItem = CCMenuItemImage::create("btn_start_multi_1-hd.png", "btn_start_multi_2-hd.png");
    mutipleItem->setTarget(this, menu_selector(StartLayer::clickMultipleMenu));
    mutipleItem->setPosition(ccp(223, -120));
    
    
    CCMenuItemImage *otherItm = CCMenuItemImage::create("btn_start_updatead_1-hd.png","btn_start_updatead_2-hd.png", this, menu_selector(StartLayer::clickOtherMenu));
    otherItm->setPosition(80, -228);
    
    CCMenu *menu = CCMenu::create(singleItem,mutipleItem,otherItm,NULL);
    this->addChild(menu);
    
    
    
}



void StartLayer::clickSingleMenu(cocos2d::CCObject *sender)
{
    CCLog("单击了单人游戏");
    
    
    GameLayer *gl = GameLayer::create();
    //以上两句可以合并为create();
    
    CCScene *s = CCScene::create();
    s->addChild(gl);
//    gl->release();
    
    CCDirector *d = CCDirector ::sharedDirector();
    
    
    CCTransitionSplitRows *anni = CCTransitionSplitRows::create(1.0f, s);
//    s->release();
    d->replaceScene(anni);//页面跳转
    
}


void StartLayer::clickMultipleMenu(cocos2d::CCObject *sender)
{
    CCLog("单击了双人游戏");
    
    MutiGameLayer *mg = MutiGameLayer::create();
    CCScene *s = CCScene::create();
    s->addChild(mg);
//    mg->release();
    
    CCDirector *d = CCDirector::sharedDirector();
//    CCTransitionCrossFade *anni = CCTransitionCrossFade::create(1.0f, s);
    CCTransitionRotoZoom *anni = CCTransitionRotoZoom::create(1.0f, s);
//    s->release();
    d->replaceScene(anni);
    
    
}


void StartLayer::clickOtherMenu(cocos2d::CCObject *sender)
{
    CCLog("单击了其他");
    
    OtherGameLayer *otherGame =  OtherGameLayer::create();
    CCScene *s = CCScene::create();
    s->addChild(otherGame);
//    otherGame->release();
    
    CCTransitionShrinkGrow *anni = CCTransitionShrinkGrow::create(1.0f, s);
//    s->release();
    CCDirector *d = CCDirector::sharedDirector();
    d->replaceScene(anni);
    
    
}

