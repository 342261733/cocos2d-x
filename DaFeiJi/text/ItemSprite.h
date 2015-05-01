#ifndef ITEMSPRITE_H
#define ITEMSPRITE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "PlayerSprite.h"
#include "Assess.h"

#include "Music.h"

using namespace CocosDenshion;


enum ITEMT_STATE
{
	IS_DEFAULT,
	IS_MOVE,
	IS_HIDE,
};

#define ITEM_SPEED 300.0f

class CItemSprite :
	public CCSprite
{
public:
	CItemSprite(void);
	~CItemSprite(void);
public:
	static CItemSprite* createItem(ITEM_KINDS eKind);
	void onEnter();
public:
private:
	void createSprite(ITEM_KINDS eKind);
	void itemUpdate(float fEscapeTime);
	void collisionLogic(void); 
	void randomItem(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	CCRect m_tCollisionRect;
	ITEMT_STATE m_eCurState;
	ITEM_KINDS m_eKind;
	float m_fLifeTime;
	int m_nScaleLevel;

	float m_fSpeedX;
	float m_fSpeedY;
};

#endif