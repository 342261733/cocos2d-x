#ifndef BOSSTHREE_H
#define BOSSTHREE_H
#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"


//BOSS 03参数调整
#define  BOSS03_STAGE01_HP	8000		//第一阶段血量
#define  BOSS03_STAGE02_HP	8000		//第二阶段血量
#define  BOSS03_STAGE03_HP	9000		//第三阶段血量
//第一阶段
#define BOSS03_STAGE01_FIRETIME		1.0f	//开火间隔
#define BOSS03_STAGE01_FIRENUM		8		//一次发射数量
//第二阶段
#define BOSS03_STAGE02_SECTOR			90.0F	//散射角度
#define BOSS03_STAGE02_ROUNDS		6		//子弹波数

#define BOSS03_STAGE02_MISSLE		2.0f	//导弹间隔
//第三阶段
#define BOSS03_STAGE03_SECTOR			90.0F	//散射角度
#define BOSS03_STAGE03_NUMBER			8		//子弹个数

class CBossThree :
	public CCNode
{
public:
	CBossThree(void);
	~CBossThree(void);
public:
	static CBossThree* createBoss(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void bossUpdate(float fEscapeTime);
	//BOSS 03
	void bossCallback(void);
	void flareWeapon(void);
	void destroyWeapon(void);
	void stage1Fire(void);
	void stage2Direction(void);
	void stage2Fire(void);
	void stage3Fire(void);
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
	//level03 data
	//int m_nBoss03Stage2Num;		//子弹数量
	CCSprite *m_pMainBody;			//主机体
	CCSprite *m_pLeftWing;			//左机翼
	CCSprite *m_pRightWing;			//右机翼
	CCSprite *m_pTailFin;			//尾翼

	//stage2
	int m_nRounds;
	BULLET_DATA m_sStage2Data;

	float m_fEnemyTime;			//敌人小飞机出现时间
};

#endif