//
//  Monster.cpp
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#include "Monster.h"


Monster::Monster()
{
    
}

Monster::~Monster()
{
    
}

bool Monster::init()
{
    return true;
}

void Monster::show()
{
    if (getSprite()!=NULL) {
        this->setVisible(true);
        m_isAlive = true;//标记为活动状态
    }
}

void Monster::hide()
{
    if (getSprite()!=NULL) {
        this->setVisible(false);
        reset();
        m_isAlive = false;//标记为活动状态
    }
}

void Monster::reset()
{
    if (getSprite()!=NULL) {
        //初始化怪物坐标,宽度800-2800 高度100-200
        this->setPosition(ccp(800+CCRANDOM_0_1()*2000, 200-CCRANDOM_0_1()*100));
    }
    
    
}

bool Monster::isAlive()
{
    return m_isAlive;
}


bool Monster::isCollideWithPlayer(Player *player)//检测碰撞?
{
    CCRect playerRect = player->getBoundingBox();
    CCPoint monsterPos = getPosition();
    
    //判断是否有交集
    return playerRect.containsPoint(monsterPos);
    
}





