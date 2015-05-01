#ifndef ARMYSPRITE_H
#define ARMYSPRITE_H


#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"
#include "ItemSprite.h"
#include "Assess.h"

#include "Music.h"

using namespace CocosDenshion;

enum ARMY_STATE
{
	AS_DEFAULT,
	AS_READY,
	AS_MOVE,
	AS_EXPLODE,
	AS_HIDE,
};

class CArmySprite :
	public CCNode
{
public:
	CArmySprite(void);
	~CArmySprite(void);
public:
	static CArmySprite* createArmy(ARMY_KINDS eKind, LAND_DATA sData);
	void underAttack(int nHurt);
	bool isCheck(void);
private:
	void createSprite(ARMY_KINDS eKind);
	void enemyUpdate(float fEscapeTime);
	//void setFlyingAttitude(float fOffset);				//ÉèÖÃ·ÉÐÐ×ËÌ¬
	void runEffect(void);
	void removeSelf(void);
	//void displayFrameByIndex(unsigned int nIndex);
	void fireBullet(float fEscapeTime);
	bool isInScene(void);
	void addCap(void);
	void openCapCall(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	ARMY_DATA m_sCurData;
	CCSprite *m_pBaseSprite;
	CCSprite *m_pTurretSprite;				//ÅÚËþ¾«Áé
	CCSprite *m_pWreckSprite;				//²Ðº¡
	CCSprite *m_pCapSprite;					//¶¥¸Ç¶¯»­¾«Áé
	CCPoint m_tTargetPosition;

	CCSprite *m_pEffectSprite;
	int m_nCurFrame;
	//CPlayerWeapon *m_pPlayerWeapon;
	//CCRect m_tRect;
	//CCNode *m_pTarget;
	ARMY_STATE m_eCurState;

	bool m_bIsNormal;
	//temp
	float m_fFireTime;
	float m_fTime;
	LAND_DATA m_sCurLandData;
	bool m_bIsHorizontal;

	ccColor3B color;
	float m_fFlashTime;
	float m_fFireCoolTime;
	int m_nBulletNum;
};

#endif