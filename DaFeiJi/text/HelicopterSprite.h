#ifndef HELICOPTERSPRITE_H
#define HELICOPTERSPRITE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"
#include "Assess.h"
#include "ItemSprite.h"

#include "Music.h"

using namespace CocosDenshion;

#define FRAME_TIME	0.05f

enum HELI_STATE
{
	HS_DEFAULT,
	HS_MOVE,
	HS_SEARCH,
	HS_FIRE,
	HS_ESC,
	HS_GAS,
	HS_EXPLODE,
	HS_HIDE,
};

class CHelicopterSprite :
	public CCNode
{
public:
	CHelicopterSprite(void);
	~CHelicopterSprite(void);
public:
	static CHelicopterSprite* createHeli(ENEMY_KINDS eKind, FLY_DATA sData);
	void underAttack(int nHurt);
	bool isCheck(void);
	void createShadow(void);
	void onEnter();
	void onExit();
private:
	void createSprite(ENEMY_KINDS eKind);
	void enemyUpdate(float fEscapeTime);
	//void setFlyingAttitude(float fOffset);				//设置飞行姿态
	void runEffect(void);
	void removeSelf(void);
	void fireBullet(void);
	void nextAction(void);
	void boundPlayer(void);
	bool isInScene(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	ENEMY_DATA m_sCurData;
	CCSprite *m_pBaseSprite;
	CCSprite *m_pPropellerSprite;				//旋翼
	CCPoint m_tTargetPosition;

	CCSprite *m_pEffectSprite;
	int m_nCurFrame;
	//CPlayerWeapon *m_pPlayerWeapon;
	//CCRect m_tRect;
	HELI_STATE m_eCurState;

	CCSprite *m_pShadow;

	bool m_bIsNormal;
	//temp
	float m_fFireTime;
	float m_fTime;
	float m_fHoverTime;
	FLY_DATA m_sCurFlyData;
	CCAction *m_pFlashAction;
	int m_nFireNum;
	BULLET_DATA mData;

	ccColor3B color;
	float m_fFlashTime;
};


#endif