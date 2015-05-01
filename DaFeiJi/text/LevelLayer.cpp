#include "LevelLayer.h"

CLevelLayer::CLevelLayer(void)
{
	m_vLevelMenuVector.clear();
}

CLevelLayer::~CLevelLayer(void)
{
}

bool CLevelLayer::init(void)
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

	CCMenu* pMenu = CCMenu::create();

	CCSprite *pSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("MainBG.png"));
	pSprite->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	pSprite->setColor(ccc3(51,51,51));
	addChild(pSprite);

	for (int i=0;i<LEVEL_MAX; i++)
	{
		sprintf(szName, "%s%02d", "任务", i+1);
		addLevelUI(szName, pMenu);
	}

	setLock();

	//m_pCurCache->addSpriteFramesWithFile("temp/temp.plist", "temp/temp.png");

	sprintf(szName, "%sBack.png", m_sPrefix);
	m_pMenuItemBack = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CLevelLayer::toPlayerCallback) );
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

void CLevelLayer::addLevelUI(const char* pszName, CCMenu* pAttachMenu)
{
	char szName[128] = {0};
	sprintf(szName, "%sLevel%02d.png", m_sPrefix, m_vLevelMenuVector.size() + 1);
	CCMenuItemSprite *pMenuItem = NULL;
	pMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CLevelLayer::selectLevelCallback) );
	pMenuItem->setPosition(0.0f, mScreenSize.height * 0.3f - pMenuItem->getContentSize().height * 1.01f * m_vLevelMenuVector.size());
	pMenuItem->setUserData((void*)m_vLevelMenuVector.size());
	m_vLevelMenuVector.push_back(pMenuItem);
	//char szName[128] = {0};
	//CCLabelBMFont *pFontLib20 = CCLabelBMFont::create(pszName, "font/Font20.fnt");
	//CCMenuItemLabel *pLabelMission = CCMenuItemLabel::create(pFontLib20);
	//pLabelMission->setPosition(ccp(pMenuItem->getContentSize().width * 0.5f, pMenuItem->getContentSize().height * 0.7f));
	//pMenuItem->addChild(pLabelMission);
	//CCLabelBMFont *pFontLib24 = CCLabelBMFont::create("攻击,猫鼬行动!", "font/Font24.fnt");
	//CCMenuItemLabel *pLabel = CCMenuItemLabel::create(pFontLib24);
	//pLabel->setPosition(ccp(pMenuItem->getContentSize().width * 0.5f, pMenuItem->getContentSize().height * 0.3f));
	//pMenuItem->addChild(pLabel);
	CCSprite *pLock = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Lock.png"));
	pLock->setPosition(ccp(pMenuItem->getContentSize().width - 9.0f, pMenuItem->getContentSize().height * 0.5f));
	pMenuItem->addChild(pLock);
	m_vLockSpriteVector.push_back(pLock);

	pAttachMenu->addChild(pMenuItem);
}
void CLevelLayer::keyBackClicked()
{
	toPlayerCallback(NULL);
}

void CLevelLayer::selectLevelCallback(CCObject* sender)
{
	Music::playClickEffect();

	CCMenuItemSprite *pMenu = (CCMenuItemSprite*)sender;
	unsigned int mLevelID = (unsigned int)pMenu->getUserData();

	if (mLevelID > CGlobalData::getSingleton()->getCurUnlockLevel() && mLevelID != 7)
	{
		return ;
	}

	CGlobalData::getSingleton()->setLevelID(mLevelID);
	CCScene *pScene = CMissionScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CLevelLayer::toPlayerCallback(CCObject* sender)
{
	Music::playClickEffect();
	CCScene *pScene = CSelectScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CLevelLayer::setLock(void)
{
	for (unsigned int i=0; i<m_vLockSpriteVector.size(); i++)
	{
		if (i>CGlobalData::getSingleton()->getCurUnlockLevel() && i != 7)
		{
			m_vLockSpriteVector[i]->setVisible(true);
		}
		else
		{
			m_vLockSpriteVector[i]->setVisible(false);
		}
	}
}
