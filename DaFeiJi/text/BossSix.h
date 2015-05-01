#ifndef BOSSSIX_H
#define BOSSSIX_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"

//BOSS 04参数调整
#define  BOSS06_STAGE01_HP	27500		//第一阶段血量
#define  BOSS06_STAGE02_HP	27500		//第二阶段血量
//#define  BOSS06_STAGE03_HP	15000		//第三阶段血量

#define  BOSSO6_SHOTFIRE_TIME		2.0f	//散弹时间间隔
#define  BOSSO6_SHOTFIRE_NUMBER		8		//散弹数量
////第一阶段
#define BOSS06_STAGE01_FIRENUM			4		//一次发射数量
//
////第二阶段
//#define BOSS04_STAGE02_SECTOR			90.0F	//散射角度
//#define BOSS04_STAGE02_ROUNDS		6		//子弹波数
//
#define BOSS06_STAGE02_MISSLE		2.0f	//导弹间隔
////第三阶段
//#define BOSS04_STAGE03_SECTOR			90.0F	//散射角度
//#define BOSS06_STAGE02_NUMBER			8		//子弹个数


class CBossSix :
	public CCNode
{
public:
	CBossSix(void);
	~CBossSix(void);
public:
	static CBossSix* createBoss(void);
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
	void lockTarget(void);
	void lockFire(void);
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

	//boss06
	CCSprite *m_pCollideBody;	//碰撞体
	CCSprite *m_pMainBody;		//主机体
	CCSprite *m_pLeftBody;		//左机体
	CCSprite *m_pRightBody;		//右机体
	CCSprite *m_pLeftEngine;	//左引擎
	CCSprite *m_pRightEngine;	//右引擎
	CCSprite *m_pLeftGun;		//左炮
	CCSprite *m_pRightGun;		//右炮

	CCAction *m_pEngine;
	CCAction *m_pGun;

	float m_fShotGunTime;

	int m_nRounds;
	BULLET_DATA m_sStage2Data;

	float m_fEnemyTime;			//敌人小飞机出现时间
};


#endif