#include "ShopLayer.h"

CShopLayer::CShopLayer(void)
{
}

CShopLayer::~CShopLayer(void)
{
}

bool CShopLayer::init(void)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	char szName[128] = {0};
	m_eLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();

	memset(m_sPrefix,0,sizeof(m_sPrefix));


	if (m_eLanguageType == kLanguageChinese)
	{
		sprintf(m_sPrefix,"CN_");
	}
	else
	{
		sprintf(m_sPrefix,"EN_");
	}

	sprintf(szName, "%sShopBG.png", m_sPrefix);
	m_pMenuShopBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pMenuShopBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	addChild(m_pMenuShopBG);

	CCMenu* pMenu = CCMenu::create();

	sprintf(szName, "%sBack.png", m_sPrefix);
	m_pMenuItemBack = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuItemBack->setPosition(-mScreenSize.width * 0.5f + m_pMenuItemBack->getContentSize().width * 0.6f,m_pMenuItemBack->getContentSize().height * 0.6f - mScreenSize.height * 0.5f);
	pMenu->addChild(m_pMenuItemBack);

	sprintf(szName, "%sBuy.png", m_sPrefix);
	m_pMenuBuy10XP = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuBuy10XP->setPosition(-mScreenSize.width * 0.3f, mScreenSize.height * 0.08f);
	addAnimationToUI(m_pMenuBuy10XP);
	pMenu->addChild(m_pMenuBuy10XP);

	m_pMenuBuy20XP = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuBuy20XP->setPosition(0.0f, mScreenSize.height * 0.08f);
	addAnimationToUI(m_pMenuBuy20XP);
	addAnimationToUI(m_pMenuBuy20XP, 2);
	pMenu->addChild(m_pMenuBuy20XP);

	m_pMenuBuy40XP = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuBuy40XP->setPosition(mScreenSize.width * 0.3f, mScreenSize.height * 0.08f);
	addAnimationToUI(m_pMenuBuy40XP);
	addAnimationToUI(m_pMenuBuy40XP, 2);
	addAnimationToUI(m_pMenuBuy40XP, 3);
	pMenu->addChild(m_pMenuBuy40XP);

	m_pMenuBuyPlane = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuBuyPlane->setPosition(- mScreenSize.width * 0.3f, - mScreenSize.height * 0.1f);
	addAnimationToUI(m_pMenuBuyPlane);
	pMenu->addChild(m_pMenuBuyPlane);

	m_pMenuBuyLevel = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuBuyLevel->setPosition(mScreenSize.width * 0.3f, - mScreenSize.height * 0.1f);
	addAnimationToUI(m_pMenuBuyLevel);
	pMenu->addChild(m_pMenuBuyLevel);

	m_pMenuPlaneAndLevel = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuPlaneAndLevel->setPosition(- mScreenSize.width * 0.3f, - mScreenSize.height * 0.3f);
	addAnimationToUI(m_pMenuPlaneAndLevel);
	addAnimationToUI(m_pMenuPlaneAndLevel, 2);
	pMenu->addChild(m_pMenuPlaneAndLevel);

	m_pMenuSuperBuy = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CShopLayer::toBackCallback) );
	m_pMenuSuperBuy->setPosition(mScreenSize.width * 0.3f, - mScreenSize.height * 0.3f);
	addAnimationToUI(m_pMenuSuperBuy);
	addAnimationToUI(m_pMenuSuperBuy, 2);
	addAnimationToUI(m_pMenuSuperBuy, 3);
	pMenu->addChild(m_pMenuSuperBuy);


	addChild(pMenu);
	return true;
}

void CShopLayer::toBackCallback(CCObject* sender)
{
	//CMainUILayer* layer = CMainUILayer::create();  
	CCNode *pNode = NULL;
	pNode = getParent()->getChildByTag(MAIN_UI);
	if (pNode)
	{
		pNode->setVisible(true);
	}

	pNode = NULL;
	pNode = getParent()->getChildByTag(SELECT_UI);
	if (pNode)
	{
		pNode->setVisible(true);
	}

	pNode = NULL;
	pNode = getParent()->getChildByTag(MISSION_UI);
	if (pNode)
	{
		pNode->setVisible(true);
	}

	removeFromParentAndCleanup(true);
}

void CShopLayer::addAnimationToUI(CCMenuItemSprite* pMenuItem, int nRepeat)
{
	char szName[128] = {0};
	CCAnimation *pAnimation = CCAnimation::create();


	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s_%02d.png", "Coin", i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}
	pAnimation->setDelayPerUnit(0.1f + CCRANDOM_0_1() * 0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCSprite *pSprite = CCSprite::create();
	pSprite->runAction( CCRepeatForever::create( pAnimate ));
	pSprite->setAnchorPoint(ccp(0.5f, 0.5f));
	pSprite->setPosition(ccp(pMenuItem->getContentSize().width * 0.75f + 15.0f * nRepeat, pMenuItem->getContentSize().height * 0.25f));
	pMenuItem->addChild(pSprite);
}