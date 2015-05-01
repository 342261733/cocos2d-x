#ifndef SHOPLAYER_H
#define SHOPLAYER_H

#include "cocos2d.h"

using namespace cocos2d;

#include "MainUILayer.h"


class CShopLayer :
	public CCLayer
{
public:
	CShopLayer(void);
	~CShopLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(CShopLayer);
private:
	void toBackCallback(CCObject* sender);

	void addAnimationToUI(CCMenuItemSprite* pMenuItem, int nRepeat = 1);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];

	CCSprite *m_pMenuShopBG;
	CCMenuItemSprite *m_pMenuItemBack;

	CCMenuItemSprite *m_pMenuBuy10XP;
	CCMenuItemSprite *m_pMenuBuy20XP;
	CCMenuItemSprite *m_pMenuBuy40XP;

	CCMenuItemSprite *m_pMenuBuyPlane;
	CCMenuItemSprite *m_pMenuBuyLevel;
	CCMenuItemSprite *m_pMenuPlaneAndLevel;
	CCMenuItemSprite *m_pMenuSuperBuy;
};

#endif