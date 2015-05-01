#include "SelectLayer.h"

CSelectLayer::CSelectLayer(void)
{
	m_vMenuPlayerVector.clear();
	m_vLockSpriteVector.clear();
}

CSelectLayer::~CSelectLayer(void)
{
}

bool CSelectLayer::init(void)
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

	CCSprite *pMenuBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("MainBG.png"));
	pMenuBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	pMenuBG->setColor(ccc3(51,51,51));
	addChild(pMenuBG);

	CCMenu* pMenu = CCMenu::create();

	for (int i=0;i<PLAYER_MAX; i++)
	{
		sprintf(szName, "%s%02d", "PC_Plane", i+1);
		//char szStr[64] = {0};
		//sprintf(szStr, "你的飞机");
		if (i == 0)
		{
			addPlayerUI(szName, "你的飞机", pMenu);
		}

		if (i == 1)
		{
			addPlayerUI(szName, "雷霆", pMenu);
		}

		if (i == 2)
		{
			addPlayerUI(szName, "雷霆", pMenu);
		}

		if (i == 3)
		{
			addPlayerUI(szName, "雷霆", pMenu);
		}

		if (i == 4)
		{
			addPlayerUI(szName, "雷霆", pMenu);
		}

		if (i == 5)
		{
			addPlayerUI(szName, "雷霆", pMenu);
		}
		
	}
	//m_pCurCache->addSpriteFramesWithFile("temp/temp.plist", "temp/temp.png");
	setLock();

	sprintf(szName, "%sBack.png", m_sPrefix);
	m_pMenuItemBack = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CSelectLayer::toMainCallback) );
	m_pMenuItemBack->setPosition(-mScreenSize.width * 0.5f + m_pMenuItemBack->getContentSize().width * 0.6f,m_pMenuItemBack->getContentSize().height * 0.6f - mScreenSize.height * 0.5f);
	pMenu->addChild(m_pMenuItemBack);
	//m_pMenuItemShop = CCMenuItemSprite::create(
	//	CCSprite::spriteWithSpriteFrame(m_pCurCache->spriteFrameByName("toExit.png")),
	//	CCSprite::spriteWithSpriteFrame(m_pCurCache->spriteFrameByName("toExit.png")),
	//	CCSprite::spriteWithSpriteFrame(m_pCurCache->spriteFrameByName("toExit.png")), this, menu_selector(CSelectLayer::toShopCallback) );
	//m_pMenuItemShop->setPosition(-mScreenSize.width * 0.5f + m_pMenuItemShop->getContentSize().width * 0.5f,-m_pMenuItemShop->getContentSize().height * 0.5f);


	this->addChild(pMenu);

	//pLabel = CCLabelTTF::create("This is MainUI!", "Arial", 24);
	//pLabel->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));

	//this->addChild(pLabel);

	Music::playMainUIBgMusic();

	setKeypadEnabled(true);
	return true;
}

void CSelectLayer::addPlayerUI(const char* pszName, const char* pszInfo, CCMenu* pAttachMenu)
{
	char szName[128] = {0};
	sprintf(szName, "%sPlane%02d.png", m_sPrefix, m_vMenuPlayerVector.size() + 1);
	CCMenuItemSprite *pMenuItem = NULL;
	pMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CSelectLayer::selectPlayerCallback) );
	pMenuItem->setPosition(0.0f, mScreenSize.height * 0.3f - pMenuItem->getContentSize().height * 1.1f * m_vMenuPlayerVector.size());
	pMenuItem->setUserData((void*)m_vMenuPlayerVector.size());
	m_vMenuPlayerVector.push_back(pMenuItem);
	//CCLabelBMFont *pFontLib24 = CCLabelBMFont::create(pszInfo, "font/Font24.fnt");
	//CCMenuItemLabel *pLabel = CCMenuItemLabel::create(pFontLib24);
	//pLabel->setPosition(ccp(pMenuItem->getContentSize().width * 0.5f, pMenuItem->getContentSize().height * 0.7f));
	//pMenuItem->addChild(pLabel);
	addAnimationToUI(pMenuItem,pszName);

	CCSprite *pLock = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Lock.png"));
	pLock->setPosition(ccp(pMenuItem->getContentSize().width - 13.0f, pMenuItem->getContentSize().height * 0.25f));
	pMenuItem->addChild(pLock);
	m_vLockSpriteVector.push_back(pLock);

	pAttachMenu->addChild(pMenuItem);
}

void CSelectLayer::addAnimationToUI(CCMenuItemSprite* pMenuItem, const char* pszName)
{
	char szName[128] = {0};
	//sprintf(szName, "%s_%04d.png", pszName, 1);
	CCSprite *pSprite = CCSprite::create();
	//CCSprite *pSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	CCAnimation *pAnimation = CCAnimation::create();


	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s_%04d.png", pszName, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}
	pAnimation->setDelayPerUnit(0.15f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
	//CCDelayTime *pDelay = CCDelayTime::create(1.2f/* * (m_vMenuPlayerVector.size() - 1)*/);
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,pAnimate->reverse(), NULL) );
	//pSprite->runAction( (CCActionInterval*)(CCSequence::create( pDelayTime,CCRepeatForever::create( pAction ),NULL) ));
	pSprite->runAction( CCRepeatForever::create( pAction ));
	pSprite->setContentSize(CCSizeMake(311,221));
	pSprite->setAnchorPoint(ccp(0.5f, 0.5f));
	pSprite->setPosition(ccp(75.0f, pMenuItem->getContentSize().height * 0.5f));
	pMenuItem->addChild(pSprite);
}

void CSelectLayer::keyBackClicked()
{
	toMainCallback(NULL);
}

void CSelectLayer::selectPlayerCallback(CCObject* sender)
{
	CCMenuItemSprite *pMenu = (CCMenuItemSprite*)sender;
	unsigned int mPlayerID = (unsigned int)pMenu->getUserData();

	/*if (mPlayerID > CGlobalData::getSingleton()->getUnlockPlane())
	{
		return ;
	}*/

	Music::playClickEffect();

	CGlobalData::getSingleton()->setSelectedPlayerID(mPlayerID);
	CCScene *pScene = CLevelScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CSelectLayer::toMainCallback(CCObject* sender)
{
	Music::playClickEffect();
	CCScene *pScene = CMainUIScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CSelectLayer::setLock(void)
{
	for (unsigned int i=0; i<m_vLockSpriteVector.size(); i++)
	{
		if (i>CGlobalData::getSingleton()->getUnlockPlane())
		{
			m_vLockSpriteVector[i]->setVisible(true);
		}
		else
		{
			m_vLockSpriteVector[i]->setVisible(false);
		}
	}
}
