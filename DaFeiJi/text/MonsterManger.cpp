//
//  MonsterManger.cpp
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#include "MonsterManger.h"

#include "Monster.h"

MonsterManger::MonsterManger()
{
    
}


MonsterManger::~MonsterManger()
{
    
}

bool MonsterManger::init()
{
    bool bRet = false;
    do {
        createMonsters();//创建怪物
        this->scheduleUpdate();//启动update
        bRet = true;
    } while (0);
    
    return bRet;
}

void MonsterManger::createMonsters()
{
    m_monsterArr = CCArray::create();
    m_monsterArr->retain();//防止数组被释放
    
    Monster *monster = NULL;
    CCSprite *sprite = NULL;
    
    for (int i=0; i<MAX_MONSTER_NUM; i++) {
        monster = Monster::create();
        monster->reset();
        
        this->addChild(monster);//添加怪物到管理器ccnode中
        m_monsterArr->addObject(monster);//添加到数组中,便于管理
        
    }
    
}

void MonsterManger::update(float dt)
{
    CCObject *obj = NULL;
    Monster *monster = NULL;
    
    CCARRAY_FOREACH(m_monsterArr, obj)//循环遍历怪物数组,重复出现在屏幕上
    {
        monster = (Monster *)obj;
        if (monster->isAlive()) {
            //怪兽活跃状态
            monster->setPositionX(monster->getPositionX()-3);//左移
            if (monster->getPositionX()<0) {
                monster->hide();
            }
            else if(monster->isCollideWithPlayer(m_player))
            {
                m_player->hit();
                monster->hide();
            }
            
        }
        else{
            //怪兽非活跃状态
            monster->show();
        }
        
    }
}


void MonsterManger::bindPlayer(Player *player)
{
    this->m_player = player;
    this->m_player->retain();//引用计数+1
    
}




