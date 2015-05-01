#ifndef ENEMYSPRITE_H
#define ENEMYSPRITE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"
#include "ItemSprite.h"
#include "Assess.h"

#include "Music.h"

using namespace CocosDenshion;

#define FRAME_TIME	0.05f

enum ENEMY_STATE
{
	ES_DEFAULT,
	ES_MOVE,
	ES_EXPLODE,
	ES_HIDE,
};

//temp
#define LIFT_TIME	3.0f
//特殊飞机屏幕内出现时间
#define HOLD_TIME	4.0f

class CEnemySprite :
	public CCNode
{
public:
	CEnemySprite(void);
	~CEnemySprite(void);
public:
	static CEnemySprite* createEnemy(ENEMY_KINDS eKind, FLY_DATA sData, ENEMY_WEAPON wKind = EW_DEFAULT);
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
	void displayFrameByIndex(unsigned int nIndex);
	void fireBullet(float fEscapeTime);
	void finishCallback(void);
	void boundPlayer(void);
	bool isInScene(void);
	void mineAnimation(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	ENEMY_DATA m_sCurData;
	std::vector<CCSprite*> m_vEnemySpriteVector;
	CCPoint m_tTargetPosition;

	CCSprite *m_pEffectSprite;
	int m_nCurFrame;
	//CPlayerWeapon *m_pPlayerWeapon;
	//CCRect m_tRect;
	ENEMY_STATE m_eCurState;

	CCSprite *m_pShadow;

	bool m_bIsNormal;
	//temp
	float m_fFireTime;
	float m_fTime;
	ENEMY_WEAPON m_eWeaponKind;
	int m_nBulletNum;
	FLY_DATA m_sCurFlyData;

	ccColor3B color;
	float m_fFlashTime;
};

#endif