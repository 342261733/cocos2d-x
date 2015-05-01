#ifndef BOSSFOUR_H
#define BOSSFOUR_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"

//BOSS 04参数调整
#define  BOSS04_STAGE01_HP	15000		//第一阶段血量
#define  BOSS04_STAGE02_HP	20000		//第二阶段血量
#define  BOSS04_STAGE03_HP	1000		//第三阶段血量

#define  BOSSO4_SHOTFIRE_TIME		2.0f	//散弹时间间隔
#define  BOSSO4_SHOTFIRE_NUMBER		8		//散弹数量
//第一阶段
#define BOSS04_STAGE01_FIRETIME		1.0f	//开火间隔
#define BOSS04_STAGE01_FIRENUM		3		//一次发射数量

//第二阶段
#define BOSS04_STAGE02_SECTOR			90.0F	//散射角度
#define BOSS04_STAGE02_ROUNDS		6		//子弹波数

#define BOSS04_STAGE02_MISSLE		2.0f	//导弹间隔
//第三阶段
#define BOSS04_STAGE03_SECTOR			90.0F	//散射角度
#define BOSS04_STAGE03_NUMBER			8		//子弹个数


class CBossFour :
	public CCNode
{
public:
	CBossFour(void);
	~CBossFour(void);
public:
	static CBossFour* createBoss(void);
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
	void stage2Direction(void);
	void stage2Fire(void);
	//void stage3Fire(void);
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

	//boss04
	CCSprite *m_pMainBody;		//主机体
	CCSprite *m_pSecondBody;	//副机体
	CCSprite *m_pLeftGun;		//左炮
	CCSprite *m_pRightGun;		//右炮
	CCSprite *m_pTailGun;		//尾炮

	float m_fShotGunTime;

	int m_nRounds;
	BULLET_DATA m_sStage2Data;

	float m_fEnemyTime;			//敌人小飞机出现时间
};

#endif