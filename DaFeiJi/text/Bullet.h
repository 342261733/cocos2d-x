#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "EnemySprite.h"
#include "ArmySprite.h"
#include "HelicopterSprite.h"
#include "PlayerSprite.h"
#include "Drone.h"
#include "Boss.h"
#include "BossTwo.h"
#include "BossThree.h"
#include "BossFour.h"
#include "BossFive.h"
#include "BossSix.h"
#include "BossSeven.h"


enum BULLET_STATE
{
	BS_DEFAULT,
	BS_MOVE,
	BS_EXPLODE,
	BS_HIDE,
};

#define ROTATE_MAX	60.0f	//最大转角
#define BOSS_MAX	120.0f	//导弹最大转角
#define BOSS_FLY	6.0f	//导弹飞走时转角
#define TRACK_TIME	4.0f	//追踪时间

class CBullet :
	public CCSprite
{
public:
	CBullet(void);
	~CBullet(void);
public:
	static CBullet* createBullet(int nBulletType, BULLET_DATA sData, BULLET_KINDS eKind = BK_DEFAULT);
	void fighterLogic(void);
	void onEnter(void);

	//temp
	void underAttack(int nHurt);
	BULLET_KINDS getKind(void){return m_sCurData.mKind;}
	bool isCheck(void);
	void removeSelf(void);
public:
private:
	void createSprite(BULLET_KINDS eKind);
	void createFireBall(BULLET_KINDS eKind);
	void createTrackRocket(BULLET_KINDS eKind);
	void createSuperGun(BULLET_KINDS eKind);
	void createLaser(BULLET_KINDS eKind);
	void createThunderBall(BULLET_KINDS eKind);
	void createSinBall(BULLET_KINDS eKind);
	void createCrescentBullet(BULLET_KINDS eKind);
	void bulletUpdate(float fEscapeTime);
	void moveLogic(float fEscapeTime);

	void checkTarget(void);
	//void chengeZorder(void);
	void runEffect(void);
	//void removeSelf(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	BULLET_DATA m_sCurData;
	CCRect m_tCollisionRect;
	BULLET_STATE m_eCurState;
	CCNode *m_pTarget;
	int m_nTargetType;
	float m_fLastRatation;
	float m_fTrackTime;
	float m_fRotate;
	int m_nCurLevel;

	float m_fBulletTime;
	CCPoint m_sFirstPos;

	//temp
	int m_nHP;						//仅仅是敌人发射的导弹时生效
	CCSprite *m_pEffectSprite;		//爆炸，同上
};


#endif