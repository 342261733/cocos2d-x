#ifndef BOSSFIVE_H
#define BOSSFIVE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"


//BOSS 05参数调整
#define  BOSS05_STAGE01_HP	15000		//第一阶段血量
#define  BOSS05_STAGE02_HP	15000		//第二阶段血量
#define  BOSS05_STAGE03_HP	15000		//第三阶段血量
//第一阶段
#define  BOSS05_STAGE01_LASERSLOT	3.0f	//激光球炮开火间隔

#define  BOSS05_STAGE01_FIRESLOT	1.0f	//主炮开火间隔

#define BOSS05_STAGE02_MISSLE		2.0f	//导弹间隔

class CBossFive :
	public CCNode
{
public:
	CBossFive(void);
	~CBossFive(void);
public:
	static CBossFive* createBoss(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void bossUpdate(float fEscapeTime);
	void bossCallback(void);
	void stage1Fire(void);
	//void stage3Fire(void);
	void lockTarget(void);
	void lockFire(void);
	void runEffect(void);
	void effectCallback(void);
	void removeSelf(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	//BOSS_KINDS m_eBossKind;
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

	//当前可攻击部位
	CCSprite *m_pCurAttack;

	//level05 data
	CCSprite *m_pMainBody;			//主机体
	CCSprite *m_pLeftWing;			//左机翼
	CCSprite *m_pRightWing;			//右机翼
	CCSprite *m_pTailFin;			//尾翼

	CCSprite *m_pMainGun;		//主炮

	float m_fLaserTime;			//激光炮开火时间

	float m_fEnemyTime;			//敌人小飞机出现时间

};

#endif