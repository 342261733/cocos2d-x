//
//  OtherGameLayer.cpp
//  BuyuGamePractice
//
//  Created by xunianqiang on 14/11/7.
//
//

#include "OtherGameLayer.h"

#include "GameLayer.h"


bool OtherGameLayer::init()
{
    bool ret = CCLayer::init();
    if (ret == false) {
        return false;
    }
    
    CCSprite *bgSprite = CCSprite::create("battle_bg4-hd.png");
    bgSprite->setPosition(ccp(0,0));
    bgSprite->setAnchorPoint(ccp(0,0));
    this->addChild(bgSprite);
    
    
    //返回按钮
    CCDirector *dic = CCDirector::sharedDirector();
    CCSize size = dic->getWinSize();
    
    CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage("btn_close_2-hd.png");
    CCScale9Sprite *backgroundButton = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrame::createWithTexture(texture, CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height)));
    CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("btn_close_1-hd.png", CCRect(0, 0, texture->getContentSize().width,texture->getContentSize().height));
    CCControlButton *m_button = CCControlButton::create(backgroundButton);
    m_button->setZoomOnTouchDown(false); //设置不现实按钮效果
    m_button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    m_button->setPreferredSize(CCSizeMake(80, 80));
    //m_button->setContentSize(CCSizeMake(size.height, size.height));
    m_button->setPosition(ccp(size.width-50,size.height-50));
    m_button->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backClick), CCControlEventTouchUpInside);
    addChild(m_button, 1);
    
        
    return true;
}