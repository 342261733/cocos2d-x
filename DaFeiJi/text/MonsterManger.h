//
//  MonsterManger.h
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#ifndef __text__MonsterManger__
#define __text__MonsterManger__

//怪物管理类,管理怪物的显示和隐藏
#include <iostream>

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

#define MAX_MONSTER_NUM 10

class MonsterManger:public CCNode
{
public:
    MonsterManger();
    ~MonsterManger();
    CREATE_FUNC(MonsterManger);
    virtual bool init();
    void bindPlayer(Player *player);
    virtual void update(float dt);//重写update函数
private:
    void createMonsters();//创建Monster对象
    
private:
    CCArray *m_monsterArr;//存放怪物数组
    Player *m_player;
    
    
    
};



#endif /* defined(__text__MonsterManger__) */
