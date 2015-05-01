//
//  Player.cpp
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#include "Player.h"

#include "FlowWord.h"

Player::Player()
{
    m_isJumping = false;
    m_money = 0;//初始金钱
    
}

Player::~Player()
{
    
}

bool Player::init()
{
    return true;
}

void Player::jump()
{
    if (!getSprite()) {
        return;
    }
    if (m_isJumping) {//如果主角还在跳跃中，则不重复跳跃
        return;
    }
    
    m_isJumping = true;
    
    //创建动作，2s原地跳跃（既落地的地点相对于起跳的地点x偏移0，y偏移0）高度250
    
    CCJumpBy *jump = CCJumpBy::create(1.5f, ccp(0, 0), 200, 1);
    
    //callfunc 也是一个动作，作用是调用一个函数
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Player::jumpEnd));
    
    //组合动作
    CCFiniteTimeAction *jumpActions = CCSequence::create(jump,callFunc,NULL);//我改了
//    printf("111223");
    runAction(jumpActions);
    
    
    
}

void Player:: jumpEnd()
{
    m_isJumping = false;
}

void Player::hit()
{
    if (getSprite()==NULL) {
        return;
    }
    
    //加钱特效提示
    
    FlowWord *flowword = FlowWord::create();
    this->addChild(flowword);
    flowword->showWord("+15", getSprite()->getPosition());
    
    m_money += 15;
    
    //创建4种动作对象
    CCMoveBy *backMove = CCMoveBy::create(0.1f, ccp(-20, 0));
    CCMoveBy *forwordMove = CCMoveBy::create(0.1f, ccp(20, 0));
    CCRotateBy *backRotate =CCRotateBy::create(0.1f, -5,0);
    CCRotateBy *forwordRotate = CCRotateBy::create(0.1f, 5,0);
    
    //分别组合成两种动作（同时进行
    CCFiniteTimeAction *backActions = CCSpawn::create(backMove,backRotate,NULL);//CCFiniteTimeAction从字面就能看出来（finite = 有限的），是有限次执行类，它是最为普通的行为，就是按时间顺序做一系列事情，做完后行为结束；
    CCFiniteTimeAction *forwordActions = CCSpawn::create(forwordMove,forwordRotate,NULL);
    
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Player::actionEnd));
    
    CCFiniteTimeAction *actions = CCSequence::create(backActions,forwordActions,callFunc,NULL);
    
    //this->stopAllActions();
    //resetData();
    
    this->runAction(actions);
    
    
}


void Player::resetData()
{
    if (m_isJumping) {
        m_isJumping =false;
    }
    this->setPosition(ccp(200, 500/4));
    this->setScale(1.0f);
    setRotation(0);
}


int Player::getMoney()
{
    return m_money;
}

CCRect Player::getBoundingBox()
{
    if (getSprite() == NULL) {
        return CCRectMake(0, 0, 0, 0);
    }
    //由于sprite 是放在 player上的，所以要检测palyer 的碰撞范围
    CCSize spriteSize = getSprite()->getContentSize();
    
    CCPoint entityPos = this->getPosition();//获取player中心点
    
    //获取player左下角的坐标值
    int x = entityPos.x-spriteSize.width/2;
    int y = entityPos.y-spriteSize.height/2;
    
    return CCRectMake(x, y, spriteSize.width, spriteSize.height);
}


void Player::actionEnd()
{
    this->setScale(1.0f);
    setRotation(0);
}


