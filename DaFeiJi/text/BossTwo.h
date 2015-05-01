#ifndef BOSSTWO_H
#define BOSSTWO_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"

#define  BOSSTWO_STAGE01_HP	7500		//第一阶段血量
#define  BOSSTWO_STAGE02_HP	7500		//第二阶段血量
#define  BOSSTWO_STAGE03_HP	1000		//第三阶段血量


//第一阶段
#define STAGE01_SLOT			0.5f	//开火间隔
#define STAGE01_BULLETNUM		3		//一次发射数量
//圆形散弹
#define STAGE01_COOL		5.0f	//冷却周期
#define B2FIRE_SLOT		0.5f	//开火间隔
#define B2BULLET_NUM	30		//一次发射数量
#define B2FIRE_NUM		3		//一周期发射次数
//第二阶段
#define STAGE02_NOMALCOOL	2.0f		//普通攻击冷却周期
#define STAGE02_NOMALFIRENUM		8	//一周期发射次数
#define STAGE02_NOMALSLOT		0.2f	//开火间隔
#define STAGE02_BSPEED		200.0f		//子弹速度
//螺旋散弹
#define STAGE02_COOL		0.0f		//冷却周期
#define STAGE02_SLOT		0.1f		//开火间隔
#define STAGE02_FIRENUM		30			//一周期发射次数

class CBossTwo :
	public CCNode
{
public:
	CBossTwo(void);
	~CBossTwo(void);
public:
	static CBossTwo* createBoss(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void bossUpdate(float fEscapeTime);
	//直升机BOSS 02
	void bossCallback(void);
	void flareWeapon(void);
	void destroyWeapon(void);
	void stage1Fire(void);
	void stage2Fire(void);
	void runEffect(void);
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

	//level02 data
	int m_nNomalFireNum;
	float m_fNomalFireRound;			//开火冷却期
	//STAGE 01
	int m_nFireNum;
	float m_fFireRound;			//开火冷却期
	float m_fShotFireSlot;		//发射子弹间隔
	CCSprite *m_pPropeller;		//螺旋桨
	//STAGE 01
	CCSprite *m_pLeftWeapon;	//左武器
	CCSprite *m_pLeftFlashSprite;
	CCSprite *m_pRightFlashSprite;
	CCSprite *m_pRightWeapon;	//右武器
	CCSprite *m_pLeftExplode;	//左爆炸
	CCSprite *m_pRightExplode;	//右爆炸

	float m_fEnemyTime;			//敌人小飞机出现时间
};

#endif