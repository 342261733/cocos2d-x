//
//  Monster.h
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#ifndef __text__Monster__
#define __text__Monster__
//怪物类(金币) 继承于实体类

#include <iostream>

#include "Entity.h"
#include "cocos2d.h"
#include "Player.h"
#include "ccMacros.h"//啥类?

USING_NS_CC;//啥东西?

class Monster:public Entity
{
public:
    Monster();
    ~Monster();
    
    CREATE_FUNC(Monster);
    virtual bool init();
    
public:
    void show();
    void hide();
    void reset();//重置怪物数据
    bool isAlive();//是否活动状态
    
    bool isCollideWithPlayer(Player *player);//检测是否碰撞
    
private:
    bool m_isAlive;
    
};


#endif /* defined(__text__Monster__) */
