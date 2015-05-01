#ifndef SELECTLAYER_H
#define SELECTLAYER_H



#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "MainUIScene.h"
#include "LevelScene.h"
#include "Music.h"

using namespace CocosDenshion;


class CSelectLayer :
	public CCLayer
{
public:
	CSelectLayer(void);
	~CSelectLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(CSelectLayer);
	void keyBackClicked();
public:

private:
	void addPlayerUI(const char* pszName, const char* pszInfo, CCMenu* pAttachMenu);
	void addAnimationToUI(CCMenuItemSprite* pMenuItem, const char* pszName);

	void selectPlayerCallback(CCObject* sender);
	void toMainCallback(CCObject* sender);

	void setLock(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];

	CCMenuItemSprite *m_pMenuItemBack;
	CCMenuItemSprite *m_pMenuItemShop;
	std::vector<CCMenuItemSprite*> m_vMenuPlayerVector;

	std::vector<CCSprite*> m_vLockSpriteVector;
	//CCLabelTTF *pLabel;
};


#endif