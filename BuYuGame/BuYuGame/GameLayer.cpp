//
//  GameLayer.cpp
//  BuYuGame
//
//  Created by xunianqiang on 14-10-14.
//
//


#include "GameLayer.h"


bool GameLayer::init()
{
    bool ret = CCLayer::init();
    if (ret == false) {
        return false;
    }
    
    setTouchEnabled(true);//缺省cclayer不能点,需要打开触摸
    
    cocos2d::CCSprite *bgSprite = new cocos2d::CCSprite();
    bgSprite->initWithFile("battle_bg2-hd.png");
    
    cocos2d::CCDirector *d = cocos2d::CCDirector::sharedDirector();
    CCSize size = d->getWinSize();
    
    bgSprite ->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bgSprite);
    
    addStaticFish();
    schedule(schedule_selector(GameLayer::fishTimer),1.0f);
    
    //
    
    return true;
    
}

void GameLayer::fishTimer(float dt)
{
    addStaticFish();
}

void GameLayer:: addStaticFish()
{
    cocos2d::CCSprite *fish = new cocos2d::CCSprite();
    fish->initWithFile("fish1313.png");
    cocos2d::CCDirector *d = cocos2d::CCDirector::sharedDirector();
    CCSize size = d->getWinSize();
    
    float x = size.width-arc4random()%100;
    float y = arc4random()%((int) size.height);
    
    float scale = arc4random()%5+5;
    fish -> setScale(5.0/scale);//鱼儿的大小不一样
    fish->setPosition(ccp(x, y));//位置不一样
    this->addChild(fish);
    
    //鱼儿游动
    CCPoint destPosition = CCPoint(size.width/2,y);
    CCMoveTo *move = CCMoveTo::create(1, destPosition);// 1表示时间1s  destPoint终点坐标  没有起点坐标
    
    CCPoint destPosit2 = CCPoint(50, y);
    CCJumpTo *jump = CCJumpTo::create(1, destPosit2, 100, 1); // 第一个1表示时间 100抛物线最高100  最后1挑1次
    
    CCPoint desPoint3 = CCPoint(size.width,y);
    CCMoveTo *move3 = CCMoveTo::create(1, desPoint3);
    
    //这个动作是一个函数调用动作是一个假动作
    CCCallFuncN *turnHead = CCCallFuncN::create(this, callfuncN_selector(GameLayer::trunHead));
    CCCallFuncN *removeAction = CCCallFuncN::create(this, callfuncN_selector(GameLayer::removeFish));
    
    CCFiniteTimeAction *allAction = CCSequence::create(move,jump,turnHead,move3,removeAction,NULL);
    fish->runAction(allAction);
    
}


void GameLayer::removeFish(CCObject *sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    sprite->removeFromParentAndCleanup(true);
}

void GameLayer::trunHead(CCObject *sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    sprite->setRotation(180);
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();
    
}

void GameLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
}


void GameLayer::onExit()
{
    CCLayer::onExit();
}


void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)//这个方法自动调用
{
    
//    printf("bullet touched ");
    
    CCTouch *oneTouch = (CCTouch *)pTouches->anyObject();
    //获取当前的触摸
    CCPoint touchPoint = oneTouch->getLocation();
    
    cocos2d::CCDirector *d = cocos2d::CCDirector::sharedDirector();
    CCSize size = d->getWinSize();
    
    CCPoint beginPoint = CCPoint(size.width/2,0);
    cocos2d::CCSprite *bullet = new cocos2d::CCSprite();
    
    bullet->initWithFile("bullet010_2.png");
    bullet->setPosition(beginPoint);
    bullet->setRotation(45);
    addChild(bullet);
    
    CCMoveTo *move = CCMoveTo::create(0.5, touchPoint);
    bullet->runAction(move);
    
    
//    CCLayer::ccTouchesEnded(pTouches, pEvent);
    
   
}


void GameLayer::hit()
{
    
    //创建4种动作对象
    CCMoveBy *backMove = CCMoveBy::create(0.1f, ccp(-20, 0));
    CCMoveBy *forwordMove = CCMoveBy::create(0.1f, ccp(20, 0));
    CCRotateBy *backRotate =CCRotateBy::create(0.1f, -5,0);
    CCRotateBy *forwordRotate = CCRotateBy::create(0.1f, 5,0);
    
    //分别组合成两种动作（同时进行
    CCFiniteTimeAction *backActions = CCSpawn::create(backMove,backRotate,NULL);//CCFiniteTimeAction从字面就能看出来（finite = 有限的），是有限次执行类，它是最为普通的行为，就是按时间顺序做一系列事情，做完后行为结束；
    CCFiniteTimeAction *forwordActions = CCSpawn::create(forwordMove,forwordRotate,NULL);
    
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GameLayer::actionEnded));
    
    CCFiniteTimeAction *actions = CCSequence::create(backActions,forwordActions,callFunc,NULL);
    
    //this->stopAllActions();
    //resetData();
    
    this->runAction(actions);
}


void GameLayer::actionEnded()
{
    CCLog("\n hit action ended");
}









