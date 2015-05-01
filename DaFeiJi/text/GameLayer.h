#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "MainUIScene.h"
#include "PlayerSprite.h"
#include "EnemySprite.h"
#include "ArmySprite.h"
#include "HelicopterSprite.h"
#include "Boss.h"
#include "BossTwo.h"
#include "BossThree.h"
#include "BossFour.h"
#include "BossFive.h"
#include "BossSix.h"
#include "BossSeven.h"
#include "Bullet.h"
#include "SuperBomb.h"

#include "Music.h"

using namespace CocosDenshion;

enum GAME_STATE
{
	GS_DEFAULT,
	GS_INIT,
	GS_RUN,				//游戏正在进行
	GS_BOSS,			//进入打Boss
	GS_AUTOFLY,			//指程序接管飞机飞行
	GS_LANDING,			//第一大关最后飞机着陆
	GS_SCORE,
	GS_COUNTSCORE,
	GS_END,
};

struct CLOUD_DATA
{
	float mSpeed;
	CCSprite *mCloud;
	CCPoint mDirection;
	bool mIsMove;
};

class CGameLayer :
	public CCLayer
{
public:
	CGameLayer(void);
	~CGameLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(CGameLayer);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	//CPlayerSprite * getCurPlayer(void)
	//{
	//	if (m_pPlayer != NULL)
	//	{
	//		return m_pPlayer;
	//	}
	//}
	void keyBackClicked();

	void setLevelEnd(void);

	//当前的保留技能
	void setHoldItem(ITEM_KINDS eKind);
private:
	void gameUpdate(float fEscapeTime);
	void moveMap(float fEscapeTime);

	void pauseCallback(CCObject* sender);
	void backMainCallback(CCObject* sender);
	void continueCallback(CCObject* sender);
	void fireBombCallback(CCObject* sender);
	void playerUpdate(void);

	void fireSuperBomb(void);
	void moveCloud(float fEscapeTime);

	void scoreCurLevel(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];

	//CCPoint *m_pPlayerPos;
	CPlayerSprite *m_pPlayer;
	std::vector<CCSprite*> m_vMapSpriteVector;
	CCPoint m_tDirection;
	LEVEL_DATA m_sCurData;

	//CLOUD
	std::vector<CLOUD_DATA> m_vLowCloudVector;
	std::vector<CLOUD_DATA> m_vHightCloudVector;

	//UI
	CCSprite *m_pHoldSpirte;			//保留技能图示
	ITEM_KINDS m_eHoldItem;				//保留技能

	//CCSprite *m_pFailSprite;			//失败提示
	CCSprite *m_pPauseBG;				//暂停背景
	CCMenuItemSprite *m_pMenuItemPause;	//暂停
	CCMenuItemSprite *m_pMenuBackMain;	//回主菜单
	CCMenuItemSprite *m_pMenuContinue;	//继续游戏
	CCMenuItemSprite *m_pMenuItemFail;	//失败后继续
	CCProgressTimer *m_pMenuItemHP;		//血条
	CCLabelAtlas *m_pMenuFontScore;		//得分
	CCLabelAtlas *m_pMenuFontLife;		//生命数
	CCLabelAtlas *m_pMenuFontRocket;	//导弹数

	CCMenuItemSprite *m_pSupperBomb;	//炸弹底儿
	CCProgressTimer *m_pBombTime;		//炸弹时间条

	CCSprite *m_pLevelScore;			//过关统计背景
	CCSprite *m_pScoreTitle;			//过关统计标题
	CCLabelAtlas *m_pScoreNum;			//过关统计分数
	CCLabelAtlas *m_pLevelXP;			//过关统计经验值
	CCMenuItemSprite *m_pMenuItemMain;	//点击后回到主菜单
	CCLabelAtlas *m_pLevelPlane01;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane02;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane03;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane04;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane05;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane06;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane07;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane08;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane09;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane10;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane11;			//过关统计经验值
	CCLabelAtlas *m_pLevelPlane12;			//过关统计经验值

	CCLabelAtlas *m_pDesPercentage;			//杀敌百分比
	CCLabelAtlas *m_pRewardXP;				//过关奖励经验值
	CCLabelAtlas *m_pRewarPoint;			//过关奖励点



	//评级星
	std::vector<CCSprite*> m_vDesStar;		//杀敌星级


	GAME_STATE m_eCurState;

	float m_fLevelTime;					//Level时间总计

	//启用双击事件
	float m_fFirstTime;
	//temp
	float m_fTime;

	//int m_nLifeNum;

	CCSprite *m_pAirport;
	//空军
	std::vector<FLY_DATA> m_vCurPlaneData;
	std::vector<FLY_DATA>::iterator it;

	//陆军
	std::vector<LAND_DATA> m_vCurLandData;
	std::vector<LAND_DATA>::iterator ite;


	//CCLabelAtlas *m_pTempX;				//过关奖励经验值
	//CCLabelAtlas *m_pTempY;				//过关奖励点
};


#endif