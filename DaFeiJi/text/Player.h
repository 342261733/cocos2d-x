//
//  Player.h
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#ifndef __text__Player__
#define __text__Player__

#include <iostream>

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

#define JUMP_ACTION_TAG 1;

class Player: public Entity
{
public:
    Player();
    ~Player();
    
    CREATE_FUNC(Player);
    virtual bool init();
    
public:
    void jump();
    void jumpEnd();
    void hit();//主角和怪物撞击（玩家受伤害）
    
    int getMoney();
    CCRect getBoundingBox();//获取碰撞范围
    void resetData();
    void actionEnd();
    
private:
    bool m_isJumping;
    int m_money;//金钱
    
        
};


#endif /* defined(__text__Player__) */
