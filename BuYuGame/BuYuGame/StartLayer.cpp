//
//  StartLayer.cpp
//  BuYuGame/Users/chenyuxiang/Desktop/Good Good Study/游戏cocos2d-x/BuYuGame/BuYuGame.xcodeproj
//
//  Created by xunianqiang on 14-10-14.
//
//

#include "StartLayer.h"

#include "GameLayer.h"

using namespace cocos2d;

bool StartLayer::init(){
    bool ret = cocos2d::CCLayer::init();
    if (ret == false) {
        return false;
    }
    
    cocos2d::CCSprite *bgSprite = new cocos2d::CCSprite();
    bgSprite->initWithFile("loading-hd.png");
    
    cocos2d::CCDirector *d = cocos2d::CCDirector::sharedDirector();
    CCSize size = d->getWinSize();
    CCLog("width is :%f,height:%f",size.width,size.height);
    
    bgSprite->setPosition(ccp(size.width/2, size.height/2));
    
    this->addChild(bgSprite);
    
    //添加一个菜单
    addMenu();
    
    return true;
    
}

void StartLayer::addMenu()
{
    
    CCMenuItemImage *singleItem = CCMenuItemImage::create("btn_start_single_1-hd.png", "btn_start_single_2-hd.png");
    
    singleItem->setTarget(this, menu_selector(StartLayer::clickSingleMenu));
    singleItem->setPosition(-210,-122);
    
    
    CCMenuItemImage *multipleItm = CCMenuItemImage::create("btn_start_multi_1-hd.png", "btn_start_multi_2-hd.png", this, menu_selector(StartLayer::clickMultipleMenu));
    multipleItm->setPosition(223, -120);
    
    CCMenuItemImage *otherItm = CCMenuItemImage::create("btn_start_updatead_1-hd.png","btn_start_updatead_2-hd.png", this, menu_selector(StartLayer::clickOtherMenu));
    otherItm->setPosition(80, -228);
    
    CCMenu *menu = CCMenu::create(singleItem,multipleItm,otherItm, NULL);
    addChild(menu);
    
}

void StartLayer::clickSingleMenu(CCObject *sender)
{
    printf("单击");
    GameLayer *gl = new GameLayer();
    gl->init();
    //以上两句可以合并为create();
    
    CCScene *s = new CCScene;
    s->init();
    
    s->addChild(gl);
    gl->release();
    
    CCDirector *d = CCDirector ::sharedDirector();
    
    CCTransitionSplitRows *anni = CCTransitionSplitRows::create(1.0f, s);
    s->release();
    d->replaceScene(anni);//页面跳转
    
}

void StartLayer::clickMultipleMenu(CCObject *sender)
{
    printf("多击");
}

void StartLayer::clickOtherMenu(CCObject *sender)
{
    CCLog("其他的");
}

































