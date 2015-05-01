#ifndef MISSIONLAYER_H
#define MISSIONLAYER_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "GameScene.h"
#include "MainUIScene.h"

#include "Music.h"

using namespace CocosDenshion;

enum MISSION_STATE
{
	MS_DEFAULT,
	MS_MISSION,
	MS_CONFIGUR,
};

class CMissionLayer :
	public CCLayer
{
public:
	CMissionLayer(void);
	~CMissionLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(CMissionLayer);
	void keyBackClicked();
private:
	void adjustFighterCallback(CCObject* sender);
	void startGameCallback(CCObject* sender);
	void toMissionCallback(CCObject* sender);
	void saveSetCallback(CCObject* sender);

	void addSpeedCallback(CCObject* sender);
	void reduceSpeedCallback(CCObject* sender);
	void addArmorCallback(CCObject* sender);
	void reduceArmorCallback(CCObject* sender);
	void addAttackCallback(CCObject* sender);
	void reduceAttackCallback(CCObject* sender);
	void addBonusCallback(CCObject* sender);
	void reduceBonusCallback(CCObject* sender);

	void setConfigurePoint(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];

	CCMenuItemSprite *m_pMenuItemStart;
	CCMenuItemSprite *m_pMenuAdjustFighter;
	CCMenuItemSprite *m_pMenuItemBack;
	CCMenuItemSprite *m_pMenuSave;

	CCMenu* pMenuMission;
	CCMenu* pMenuConfigure;

	CCNode* m_pConfigureNode;

	CCLabelAtlas *m_pTotalXP;
	CCLabelAtlas *m_pFreeXP;

	CCMenuItemSprite *m_pSpeedAdd;
	CCMenuItemSprite *m_pSpeedReduce;
	CCSprite *m_pSpeedBG;
	CCProgressTimer *m_pMenuSpeed;

	CCMenuItemSprite *m_pArmorAdd;
	CCMenuItemSprite *m_pArmorReduce;
	CCSprite *m_pArmorBG;
	CCProgressTimer *m_pMenuArmor;

	CCMenuItemSprite *m_pAttackAdd;
	CCMenuItemSprite *m_pAttackReduce;
	CCSprite *m_pAttackBG;
	CCProgressTimer *m_pMenuAttack;

	CCMenuItemSprite *m_pBonusAdd;
	CCMenuItemSprite *m_pBonusReduce;
	CCSprite *m_pBonusBG;
	CCProgressTimer *m_pMenuBonus;


	MISSION_STATE m_eCurState;

	CCSprite *m_pConfigBG;

	//temp
	int m_nTotalPoint;
	int m_nSpeedPoint;
	int m_nArmorPoint;
	int m_nAttackPoint;
	int m_nBonusPoint;

	int m_nTotalUIPoint;
	int m_nSpeedUIPoint;
	int m_nArmorUIPoint;
	int m_nAttackUIPoint;
	int m_nBonusUIPoint;
};

#endif