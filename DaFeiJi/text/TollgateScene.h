//
//  TollgateScene.h
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#ifndef __text__TollgateScene__
#define __text__TollgateScene__

//创建游戏场景类,所有游戏的效果都在这上面展示
#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Player.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class TollgateScene : public CCLayer {
public:
    static CCScene *scene();
    virtual bool init();
    
    CREATE_FUNC(TollgateScene);
    virtual void update(float delta);
    
private:
    void initBG();//初始化关卡背景
    void createJumpBtn();//创建跳跃按钮
    void jumpEvent(CCObject *pSender,CCControlEvent event);//响应按钮点击事件
    
    void createScoreLab();//创建分数标签
    void createTimeSlider();//创建时间条
    
    void buttonClick();//
    
private:
    CCSprite *m_bgSprite1;
    CCSprite *m_bgSprite2;
    
    Player *m_player;
    
    CCLabelTTF *m_scoreLab;//分数标签
    CCControlSlider *m_TimeSlider;//时间条
    
    int m_score;//得分
    int m_curTime;//当前得分
    
};

#endif /* defined(__text__TollgateScene__) */
