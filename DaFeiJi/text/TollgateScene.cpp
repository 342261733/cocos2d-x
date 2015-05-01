////
////  TollgateScene.cpp
////  text
////
////  Created by xunianqiang on 14-10-10.
////
////
//
//#include "TollgateScene.h"
//
//
//#include "MonsterManger.h"
//
//using namespace cocos2d;
//
//CCScene *TollgateScene::scene()
//{
//    CCScene *scene = NULL;
//    do {
//        scene = CCScene::create();
//        CC_BREAK_IF(!scene);
//        
//        TollgateScene *layer = TollgateScene::create();
//        CC_BREAK_IF(!layer);
//        
//        scene->addChild(layer,1);
//    
//    } while (0);
//    return scene;
//}
//
//bool TollgateScene::init()
//{
//    bool bRet = false;
//    
//    do {
//        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//        
//        //游戏标题图片
//        CCSprite *sprite = CCSprite::create("diaochan.png");
//        m_player = Player::create();
//        m_player -> bindSprite(sprite);
//        m_player->setPosition(ccp(200, visibleSize.height/4));
//        
//        this->addChild(m_player,1);
//        
//        //初始化背景图片
//        initBG();
//        
//        //创建按钮
//        createJumpBtn();
//        
//        //设置启用CCNode的update()函数,游戏会在每一帧调用update()函数
//        this->scheduleUpdate();
//        
//        //创建怪物管理器(管理器里面放了很多怪物)
//        MonsterManger *monsterManger = MonsterManger::create();
//        monsterManger->bindPlayer(m_player);
//        this->addChild(monsterManger,4);
//        
//        //创建分数标签
//        createScoreLab();
//        //创建时间条
//        createTimeSlider();
//        
//        bRet = true;
//        
//        
//    } while (0);
//    
//    return bRet;
//}
//
//
//void TollgateScene::initBG()
//{
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    m_bgSprite1 = CCSprite::create("login.jpg");
//    m_bgSprite1->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
//    this->addChild(m_bgSprite1,0);
//    
//    m_bgSprite2 = CCSprite::create("youxi.png");
//    m_bgSprite2->setPosition(ccp(visibleSize.width/2+visibleSize.width/2, visibleSize.height/2));
//    m_bgSprite2->setFlipX(true);//??
//    this->addChild(m_bgSprite2,0);
//    
//}
//
//void TollgateScene::update(float delta)
//{
//    CCSize mapSize = m_bgSprite1->getContentSize();//地图大小
//    
//    int posX1 = m_bgSprite1->getPositionX();//地图1的x的坐标
//    int posX2 = m_bgSprite2->getPositionX();//地图2的x坐标
//    
//    int iSpeed = 2;//地图滚动的速度
//    
//    posX1 -= iSpeed;//两张图一起滚动
//    posX2 -= iSpeed;
//    
//    //创建无限循环
//    if (posX1 <= -mapSize.width/2) {
//        posX1 = mapSize.width+mapSize.width/2;
//        posX2 = mapSize.width/2;
//        
//    }
//    
//    if (posX2 <= -mapSize.width/2) {
//        posX1 = mapSize.width/2;
//        posX2 = mapSize.width+mapSize.width/2;
//    }
//    
//    m_bgSprite1->setPositionX(posX1);
//    m_bgSprite2->setPositionX(posX2);
//    
//    //分数增加
//    m_score = m_player->getMoney();
//    CCLog("score is %d",m_score);
////    CCLog("%s",CCString::createWithFormat("Score:%d",m_score)->getCString());
////    CCString *sss = CCString::createWithFormat("Score:%d",m_score);
//    m_scoreLab->setString(CCString::createWithFormat("%d",m_score)->getCString());
//    
//    
//    m_TimeSlider->setValue(--m_curTime);
//    
//    
//}
//
//void TollgateScene::createJumpBtn()
//{
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    
//    //按钮标题
//    CCLabelTTF *jumpLabel = CCLabelTTF::create("Jump","Arial",35);
//    
//    //按钮状态图片
//    CCScale9Sprite *jumpNorBG = CCScale9Sprite::create("msp_submit_selected.9.png");
//    CCScale9Sprite *jumpLightBG = CCScale9Sprite::create("msp_submit_selected.9.png");
////    CCSprite *jumpNorBG = CCSprite::create("button1.png");
////    CCSprite *jumpLightBG = CCSprite::create("button1.png");
//    
//    //创建按钮//有放大的效果,ccmenu没有放大的效果
//    CCControlButton *jumpBtn = CCControlButton::create(jumpLabel, jumpNorBG);
//    jumpBtn->setPosition(ccp(visibleSize.width-80, 50));
//    jumpBtn->setPreferredSize(CCSizeMake(100, 100));
//    jumpBtn->setBackgroundSpriteForState(jumpLightBG, CCControlStateHighlighted);//高亮图片
//    
//    
//    //添加事件
//    jumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(TollgateScene::jumpEvent), CCControlEventTouchDown);//touchdown在鼠标落下后即响应,touchUpinside在鼠标落下并抬起后
//    
//    this->addChild(jumpBtn);
//    
//    
//    CCMenuItemImage *btnImage = CCMenuItemImage::create("msp_submit_selected.9.png", "button.png",this,menu_selector(TollgateScene::buttonClick));
//    btnImage->setPosition(ccp(480+300, 100));
//    //    CC_BREAK_IF(!btnImage);
//    //    do {
//    //        CC_BREAK_IF(!btnImage);
//    //    } while (0);
//    
//    //    CCMenuItemSprite *btn = CCMenuItemSprite::create(btnImage, NULL);
//    //    this->addChild(btn,1);
//    CCMenu* pMenu = CCMenu::create(btnImage, NULL);
//    pMenu->setPosition(CCPointZero);
//    this->addChild(pMenu);
//    
//    
//}
//
//void TollgateScene::buttonClick()
//{
//    CCLog("buttn 点击");
//    m_player->jump();
//}
//
//void TollgateScene::jumpEvent(CCObject *pSender, CCControlEvent event)
//{
//    m_player->jump();
//}
//
//void TollgateScene::createScoreLab()
//{
//    m_score = m_player->getMoney();
////    CCString *m_scoreStr = CCString::createWithFormat("Score:%d",m_score);
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    m_scoreLab = CCLabelTTF::create("Score:","Arial", 35);//int 转成string??
//    m_scoreLab->setAnchorPoint(ccp(0, 1));
////    m_scoreLab->setPosition(ccp(0, visibleSize.height));
//    m_scoreLab->setPosition(ccp(100, 500));
//    this->addChild(m_scoreLab,5);
//    
//    
//}
//
//void TollgateScene::createTimeSlider()
//{
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    m_curTime = 1000;
//    m_TimeSlider = CCControlSlider::create(CCSprite::create("loading_progress_bg.png"), CCSprite::create("loading_process_val.png"), CCSprite::create("loading_point.png"));//加载条
//    m_TimeSlider->setPosition(ccp(m_TimeSlider->getContentSize().width/2, visibleSize.height-m_TimeSlider->getContentSize().height-m_scoreLab->getContentSize().height));
//    m_TimeSlider->setTouchEnabled(false);
//    m_TimeSlider->setMaximumValue(1000);
//    m_TimeSlider->setMinimumValue(0);
//    m_TimeSlider->setValue(m_curTime);
//    this->addChild(m_TimeSlider,3);
//}


//
//  TollgateScene.cpp
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#include "TollgateScene.h"


#include "MonsterManger.h"

using namespace cocos2d;

CCScene *TollgateScene::scene()
{
    CCScene *scene = NULL;
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        
        TollgateScene *layer = TollgateScene::create();
        CC_BREAK_IF(!layer);
        
        scene->addChild(layer,1);
        
    } while (0);
    return scene;
}

bool TollgateScene::init()
{
    bool bRet = false;
    
    do {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        
        //游戏标题图片
        CCSprite *sprite = CCSprite::create("diaochan.png");
        m_player = Player::create();
        m_player -> bindSprite(sprite);
        m_player->setPosition(ccp(200, visibleSize.height/4));
        
        this->addChild(m_player,1);
        //初始化背景图片
        this->initBG();
		this->createJumpBtn();
        //设置启用CCNode的update()函数,游戏会在每一帧调用update()函数
        this->scheduleUpdate();
        //创建怪物管理器(管理器里面放了很多怪物)
        MonsterManger *monsterManger = MonsterManger::create();
        monsterManger->bindPlayer(m_player);
        this->addChild(monsterManger,4);
        //创建分数标签
        this->createScoreLab();
        //创建时间条
        this->createTimeSlider();
        bRet = true;
        
        
    } while (0);
    
    return bRet;
}


void TollgateScene::initBG()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    m_bgSprite1 = CCSprite::create("login.jpg");
    m_bgSprite1->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(m_bgSprite1,0);
    
    m_bgSprite2 = CCSprite::create("youxi.png");
    m_bgSprite2->setPosition(ccp(visibleSize.width/2+visibleSize.width/2, visibleSize.height/2));
    m_bgSprite2->setFlipX(true);//??
    this->addChild(m_bgSprite2,0);
    
}

void TollgateScene::update(float delta)
{
    CCSize mapSize = m_bgSprite1->getContentSize();//地图大小
    
    int posX1 = m_bgSprite1->getPositionX();//地图1的x的坐标
    int posX2 = m_bgSprite2->getPositionX();//地图2的x坐标
    
    int iSpeed = 2;//地图滚动的速度
    
	posX1 -= iSpeed;//两张图一起滚动
	posX2 -= iSpeed;
    //创建无限循环
    if (posX1 <= -mapSize.width/2) {
        posX1 = mapSize.width+mapSize.width/2;
        posX2 = mapSize.width/2;
        
    }
    
    if (posX2 <= -mapSize.width/2) {
        posX1 = mapSize.width/2;
        posX2 = mapSize.width+mapSize.width/2;
    }
    
    m_bgSprite1->setPositionX(posX1);
    m_bgSprite2->setPositionX(posX2);
    
    //分数增加
    m_score = m_player->getMoney();
    m_scoreLab->setString(CCString::createWithFormat("%d",m_score)->getCString());
    m_TimeSlider->setValue(m_curTime);
    
    
}

void TollgateScene::createJumpBtn()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //按钮标题
    CCLabelTTF *jumpLabel = CCLabelTTF::create("Jump","Arial",35);
    
    //按钮状态图片
    CCScale9Sprite *jumpNorBG = CCScale9Sprite::create("msp_submit_selected.9.png");
    CCScale9Sprite *jumpLightBG = CCScale9Sprite::create("msp_submit_selected.9.png");
    //    CCSprite *jumpNorBG = CCSprite::create("button1.png");
    //    CCSprite *jumpLightBG = CCSprite::create("button1.png");
    
    //创建按钮//有放大的效果,ccmenu没有放大的效果
    CCControlButton *jumpBtn = CCControlButton::create(jumpLabel, jumpNorBG);
    jumpBtn->setPosition(ccp(visibleSize.width-80, 50));
    jumpBtn->setPreferredSize(CCSizeMake(100, 100));
    jumpBtn->setBackgroundSpriteForState(jumpLightBG, CCControlStateHighlighted);//高亮图片
    
    
    //添加事件
    jumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(TollgateScene::jumpEvent), CCControlEventTouchDown);//touchdown在鼠标落下后即响应,touchUpinside在鼠标落下并抬起后
    
    this->addChild(jumpBtn);
    
    
    /*  CCMenuItemImage *btnImage = CCMenuItemImage::create(
     "msp_submit_selected.9.png",
     "button.png",
     this,
     menu_selector(TollgateScene::buttonClick)
     );
     
     //  menu_selector(HelloWorld::menuCloseCallback));
     btnImage->setPosition(ccp(480+300, 100));
     //    CC_BREAK_IF(!btnImage);
     //    do {
     //        CC_BREAK_IF(!btnImage);
     //    } while (0);
     
     //    CCMenuItemSprite *btn = CCMenuItemSprite::create(btnImage, NULL);
     //    this->addChild(btn,1);
     CCMenu* pMenu = CCMenu::create(btnImage, NULL);
     pMenu->setPosition(CCPointZero);
     this->addChild(pMenu);
     */
    
}

void TollgateScene::buttonClick()
{
    CCLog("buttn 点击");
    m_player->jump();
}

void TollgateScene::jumpEvent(CCObject *pSender, CCControlEvent event)
{
    m_player->jump();
}

void TollgateScene::createScoreLab()
{
    m_score = m_player->getMoney();
    //    CCString *m_scoreStr = CCString::createWithFormat("Score:%d",m_score);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    m_scoreLab = CCLabelTTF::create("Score:","Arial", 35);//int 转成string??
    m_scoreLab->setAnchorPoint(ccp(0, 1));
    //    m_scoreLab->setPosition(ccp(0, visibleSize.height));
    m_scoreLab->setPosition(ccp(100, 100));
    this->addChild(m_scoreLab,5);
	
    
    
}

void TollgateScene::createTimeSlider()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    m_curTime = 10000;
    m_TimeSlider = CCControlSlider::create(CCSprite::create("loading_progress_bg.png"), CCSprite::create("loading_process_val.png"), CCSprite::create("loading_point.png"));//加载条
    m_TimeSlider->setPosition(ccp(m_TimeSlider->getContentSize().width/2, visibleSize.height-m_TimeSlider->getContentSize().height-m_scoreLab->getContentSize().height));
    m_TimeSlider->setTouchEnabled(false);
    m_TimeSlider->setMaximumValue(10000);
    m_TimeSlider->setMinimumValue(0);
    m_TimeSlider->setValue(m_curTime);
    this->addChild(m_TimeSlider,3);
}



