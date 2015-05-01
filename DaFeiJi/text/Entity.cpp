//
//  Entity.cpp
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#include "Entity.h"


Entity::Entity()
{
    m_sprite = NULL;
}

Entity::~Entity()
{

};

CCSprite* Entity::getSprite()
{
    return this->m_sprite;
}

void Entity::bindSprite(CCSprite *sprite)
{
    this->m_sprite = sprite;
    this->addChild(m_sprite);
}