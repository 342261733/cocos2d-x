//
//  Entity.h
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#ifndef __text__Entity__
#define __text__Entity__

#include <iostream>

//绑定一个精灵,返回一个精灵,基类

#include "cocos2d.h"

using namespace cocos2d;

class Entity:public CCNode
{
public:
    Entity();
    ~Entity();
    
    CCSprite *getSprite();
    
    void bindSprite(CCSprite *sprite);
    
private:
    CCSprite *m_sprite;
    
};



#endif /* defined(__text__Entity__) */
