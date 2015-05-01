#ifndef BOSSSEVEN_H
#define BOSSSEVEN_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Drone.h"
#include "Bullet.h"

#define BOSS07_STAGE01_HP 10000

class CBossSeven :
	public CCNode
{
public:
	CBossSeven(void);
	~CBossSeven(void);
public:
	static CBossSeven* createBoss(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void bossUpdate(float fEscapeTime);
	void bossCallback(void);
	void fireTarget(void);
	//void stage3Fire(void);
	void runEffect(void);
	void effectCallback(void);
	void removeSelf(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	BOSS_STATE m_eCurState;
	STAGE_BOSS m_eCurStage;

	float m_fTime;				//计时器
	int m_nBossHP;				//HP
	CCSprite *m_pBaseSprite;	//主体
	CCAction *m_pMoveAction;	//移动事件
	CCSprite *m_pExplode;		//爆炸

	//Base Flash Effect
	ccColor3B m_sBaseColor;
	float m_fFlashTime;
	bool m_bBaseNormal;
	//data
	CCNode *m_pLLeftGun;
	CCNode *m_pLRightGun;
	CCNode *m_pRLeftGun;
	CCNode *m_pRRightGun;
	CCNode *m_pMiddleGun;

	CCSprite *m_pTailGun;
	CCSprite *m_pCurAttack;

	float m_fEnemyTime;			//敌人小飞机出现时间
};

#endif