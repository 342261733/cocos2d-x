#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GameLayer.h"

class CGameScene :
	public CCScene
{
public:
	CGameScene(void);
	~CGameScene(void);
public:
	static CCScene* scene();
};

#endif