//
//  FlowWord.cpp
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#include "FlowWord.h"

FlowWord::FlowWord()
{
    
}

FlowWord::~FlowWord()
{
    
}

bool FlowWord::init()
{
    m_textLab = CCLabelTTF::create("", "Arial", 30);
    m_textLab->setColor(ccc3(255, 0, 0));
    m_textLab->setVisible(false);
    
    this->addChild(m_textLab);
    
    return true;
}

void FlowWord::showWord(const char *str, CCPoint pos)
{
    m_textLab->setString(str);
    m_textLab->setPosition(pos);
    m_textLab->setAnchorPoint(ccp(1, 0));
    m_textLab->setVisible(true);
    
    //先放大后缩小
    CCActionInterval *scaleLarge = CCScaleTo::create(0.3f, 2.5f,2.5f);
    CCActionInterval *scaleSmall = CCScaleTo::create(0.4f, 0.5f,0.5f);
    
    //回调动作，移除效果
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(FlowWord::flowEnd));
    CCFiniteTimeAction *actions = CCSequence::create(scaleLarge,scaleSmall,callFunc,NULL);
    
    m_textLab->runAction(actions);
    
}

void FlowWord::flowEnd(){
    m_textLab->setVisible(false);
    //true从父节点移除，并移除节点的动作和回调函数
    m_textLab->removeFromParentAndCleanup(true);
}



