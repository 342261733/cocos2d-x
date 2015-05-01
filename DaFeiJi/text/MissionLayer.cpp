#include "MissionLayer.h"

CMissionLayer::CMissionLayer(void)
{
	m_eCurState = MS_DEFAULT;

	m_nTotalPoint = CGlobalData::getSingleton()->getPlayerPoint();
	m_nSpeedPoint = CGlobalData::getSingleton()->getPlayerSpeed();
	m_nArmorPoint = CGlobalData::getSingleton()->getPlayerArmor();
	m_nAttackPoint = CGlobalData::getSingleton()->getPlayerAttack();
	m_nBonusPoint = CGlobalData::getSingleton()->getPlayerBouns();

	m_nTotalUIPoint = m_nTotalPoint;
	m_nSpeedUIPoint = m_nSpeedPoint;
	m_nArmorUIPoint = m_nArmorPoint;
	m_nAttackUIPoint = m_nAttackPoint;
	m_nBonusUIPoint = m_nBonusPoint;

	m_pConfigBG = NULL;
}

CMissionLayer::~CMissionLayer(void)
{
}

bool CMissionLayer::init(void)
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

	pMenuMission = CCMenu::create();

	//char szName[128] = {0};
	//for (int i=0;i<LEVEL_MAX; i++)
	//{
	//	sprintf(szName, "%s%02d", "Level", i+1);
	//	addLevelUI(szName, pMenu);
	//}
	//m_pCurCache->addSpriteFramesWithFile("temp/temp.plist", "temp/temp.png");
	//CCMenuItemSprite *pMenuItem = NULL;
	CCSprite *pSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("MainBG.png"));
	pSprite->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	pSprite->setColor(ccc3(51,51,51));
	addChild(pSprite);

	sprintf(szName, "%sMission%02d.png",m_sPrefix, CGlobalData::getSingleton()->getCurLevelData().mLevel);

	CCMenuItemSprite *pMenuSprite =CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)));
	//pMenuSprite->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	pMenuMission->addChild(pMenuSprite);

	//CCLabelBMFont *pFontLib20 = CCLabelBMFont::create("浠诲姟1", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelMission = CCMenuItemLabel::create(pFontLib20);
	//pLabelMission->setPosition(ccp(0.0f, mScreenSize.height * 0.3f));
	//pMenuMission->addChild(pLabelMission);

	//CCLabelBMFont *pFontLib24 = CCLabelBMFont::create("鏀诲嚮,鐚棘琛屽姩!", "font/Font24.fnt");
	//CCMenuItemLabel *pLabel = CCMenuItemLabel::create(pFontLib24);
	//pLabel->setPosition(ccp(0.0f, mScreenSize.height * 0.25f));
	//pMenuMission->addChild(pLabel);

	//CCLabelBMFont *pFontInfo = CCLabelBMFont::create("灏介噺鍑绘瘉鏁屾満,闃绘瀵规柟鐨勯琛屾暍姝婚槦.", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelInfo = CCMenuItemLabel::create(pFontInfo);
	//pLabelInfo->setPosition(ccp(0.0f, mScreenSize.height * 0.15f));
	//pMenuMission->addChild(pLabelInfo);

	sprintf(szName, "%sStartGame.png",m_sPrefix);
	m_pMenuItemStart = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMissionLayer::startGameCallback) );
	m_pMenuItemStart->setPosition(-mScreenSize.width * 0.5f + m_pMenuItemStart->getContentSize().width * 0.6f,m_pMenuItemStart->getContentSize().height * 0.6f - mScreenSize.height * 0.5f);
	pMenuMission->addChild(m_pMenuItemStart);

	sprintf(szName, "%sAdjustFighter.png",m_sPrefix);
	m_pMenuAdjustFighter = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMissionLayer::adjustFighterCallback) );
	m_pMenuAdjustFighter->setPosition(mScreenSize.width * 0.5f - m_pMenuAdjustFighter->getContentSize().width * 0.6f, m_pMenuAdjustFighter->getContentSize().height * 0.6f - mScreenSize.height * 0.5f);
	pMenuMission->addChild(m_pMenuAdjustFighter);

	this->addChild(pMenuMission);

	m_pConfigureNode = CCNode::create();

	sprintf(szName, "%sConfigBG.png", m_sPrefix);
	m_pConfigBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pConfigBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.9f - m_pConfigBG->getContentSize().height * 0.5f));
	m_pConfigureNode->addChild(m_pConfigBG);

	pMenuConfigure = CCMenu::create();
	m_pConfigureNode->addChild(pMenuConfigure);
	this->addChild(m_pConfigureNode);

	sprintf(szName, "%sBack.png", m_sPrefix);
	m_pMenuItemBack = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMissionLayer::toMissionCallback) );
	m_pMenuItemBack->setPosition(-mScreenSize.width * 0.5f + m_pMenuItemBack->getContentSize().width * 0.6f,m_pMenuItemBack->getContentSize().height * 0.6f - mScreenSize.height * 0.5f);
	pMenuConfigure->addChild(m_pMenuItemBack);

	sprintf(szName, "%sSave.png", m_sPrefix);
	m_pMenuSave = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMissionLayer::saveSetCallback) );
	m_pMenuSave->setPosition(mScreenSize.width * 0.5f - m_pMenuSave->getContentSize().width * 0.6f, m_pMenuSave->getContentSize().height * 0.6f - mScreenSize.height * 0.5f);
	pMenuConfigure->addChild(m_pMenuSave);


	//CCLabelBMFont *pFontTotalP = CCLabelBMFont::create("XP鎬绘暟:", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelTotalP = CCMenuItemLabel::create(pFontTotalP);
	//pLabelTotalP->setPosition(mScreenSize.width * 0.35f,mScreenSize.height * 0.86f);
	//m_pConfigureNode->addChild(pLabelTotalP);

	m_pTotalXP = CCLabelAtlas::create("00", "font/Number_32.png", 15, 19, '/');
	m_pTotalXP->setPosition(mScreenSize.width * 0.5f,mScreenSize.height * 0.734f);
	m_pConfigureNode->addChild(m_pTotalXP);

	//CCLabelBMFont *pFontFreeP = CCLabelBMFont::create("XP鐐规暟:", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelFreeP = CCMenuItemLabel::create(pFontFreeP);
	//pLabelFreeP->setPosition(mScreenSize.width * 0.35f,mScreenSize.height * 0.81f);
	//m_pConfigureNode->addChild(pLabelFreeP);

	m_pFreeXP = CCLabelAtlas::create("00", "font/Number_32.png", 15, 19, '/');
	m_pFreeXP->setPosition(mScreenSize.width * 0.5f,mScreenSize.height * 0.686f);
	m_pConfigureNode->addChild(m_pFreeXP);

	//CCLabelBMFont *pFontTips = CCLabelBMFont::create("浣犲彲浠ヤ负浣犵殑鎴樻満鍒嗛厤灞炴�鐐�", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelTips = CCMenuItemLabel::create(pFontTips);
	//pLabelTips->setPosition(mScreenSize.width * 0.5f,mScreenSize.height * 0.7f);
	//m_pConfigureNode->addChild(pLabelTips);
	float fBeginPosY = 0.49f;
	//speed
	//CCLabelBMFont *pFontSpeed = CCLabelBMFont::create("閫熷害", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelSpeed = CCMenuItemLabel::create(pFontSpeed);
	//pLabelSpeed->setAnchorPoint(ccp(0.0f,0.5f));
	//pLabelSpeed->setPosition(mScreenSize.width * 0.2f,mScreenSize.height * (fBeginPosY + 0.05f));
	//m_pConfigureNode->addChild(pLabelSpeed);

	m_pSpeedBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_BG.png"));
	m_pSpeedBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * fBeginPosY));
	m_pConfigureNode->addChild(m_pSpeedBG);

	m_pMenuSpeed = CCProgressTimer::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_Top.png")));
	m_pMenuSpeed->setType(kCCProgressTimerTypeBar);
	m_pMenuSpeed->setMidpoint(ccp(0,0.5));
	m_pMenuSpeed->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuSpeed->setBarChangeRate(ccp(1, 0));
	m_pMenuSpeed->setPosition(ccp(0,m_pMenuSpeed->getContentSize().height * 0.5f));
	m_pMenuSpeed->setPercentage(m_nSpeedPoint * 5);
	m_pSpeedBG->addChild(m_pMenuSpeed);

	m_pSpeedReduce = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")), this, menu_selector(CMissionLayer::reduceSpeedCallback) );
	m_pSpeedReduce->setPosition(-m_pSpeedBG->getContentSize().width * 0.5f - m_pSpeedReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pSpeedReduce);

	m_pSpeedAdd = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")), this, menu_selector(CMissionLayer::addSpeedCallback) );
	m_pSpeedAdd->setPosition(m_pSpeedBG->getContentSize().width * 0.5f + m_pSpeedReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pSpeedAdd);

	fBeginPosY -= 0.1f;
	//Armor
	//CCLabelBMFont *pFontArmor = CCLabelBMFont::create("闃插尽", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelArmor = CCMenuItemLabel::create(pFontArmor);
	//pLabelArmor->setAnchorPoint(ccp(0.0f,0.5f));
	//pLabelArmor->setPosition(mScreenSize.width * 0.2f,mScreenSize.height * (fBeginPosY + 0.05f));
	//m_pConfigureNode->addChild(pLabelArmor);

	m_pArmorBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_BG.png"));
	m_pArmorBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * fBeginPosY));
	m_pConfigureNode->addChild(m_pArmorBG);

	m_pMenuArmor = CCProgressTimer::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_Top.png")));
	m_pMenuArmor->setType(kCCProgressTimerTypeBar);
	m_pMenuArmor->setMidpoint(ccp(0,0));
	m_pMenuArmor->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuArmor->setBarChangeRate(ccp(1, 0));
	m_pMenuArmor->setPosition(ccp(0,m_pMenuArmor->getContentSize().height * 0.5f));
	m_pMenuArmor->setPercentage(m_nArmorPoint * 5);
	m_pArmorBG->addChild(m_pMenuArmor);

	m_pArmorReduce = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")), this, menu_selector(CMissionLayer::reduceArmorCallback) );
	m_pArmorReduce->setPosition(-m_pArmorBG->getContentSize().width * 0.5f - m_pArmorReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pArmorReduce);

	m_pArmorAdd = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")), this, menu_selector(CMissionLayer::addArmorCallback) );
	m_pArmorAdd->setPosition(m_pArmorBG->getContentSize().width * 0.5f + m_pArmorReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pArmorAdd);

	fBeginPosY -= 0.1f;
	//Attack
	//CCLabelBMFont *pFontAttack = CCLabelBMFont::create("瀛愬脊鐏姏", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelAttack = CCMenuItemLabel::create(pFontAttack);
	//pLabelAttack->setAnchorPoint(ccp(0.0f,0.5f));
	//pLabelAttack->setPosition(mScreenSize.width * 0.2f,mScreenSize.height * (fBeginPosY + 0.05f));
	//m_pConfigureNode->addChild(pLabelAttack);

	m_pAttackBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_BG.png"));
	m_pAttackBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * fBeginPosY));
	m_pConfigureNode->addChild(m_pAttackBG);

	m_pMenuAttack = CCProgressTimer::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_Top.png")));
	m_pMenuAttack->setType(kCCProgressTimerTypeBar);
	m_pMenuAttack->setMidpoint(ccp(0,0));
	m_pMenuAttack->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuAttack->setBarChangeRate(ccp(1, 0));
	m_pMenuAttack->setPosition(ccp(0,m_pMenuAttack->getContentSize().height * 0.5f));
	m_pMenuAttack->setPercentage(m_nAttackPoint * 5);
	m_pAttackBG->addChild(m_pMenuAttack);

	m_pAttackReduce = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")), this, menu_selector(CMissionLayer::reduceAttackCallback) );
	m_pAttackReduce->setPosition(-m_pAttackBG->getContentSize().width * 0.5f - m_pAttackReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pAttackReduce);

	m_pAttackAdd = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")), this, menu_selector(CMissionLayer::addAttackCallback) );
	m_pAttackAdd->setPosition(m_pAttackBG->getContentSize().width * 0.5f + m_pAttackReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pAttackAdd);

	fBeginPosY -= 0.1f;
	//Bonus
	//CCLabelBMFont *pFontBonus = CCLabelBMFont::create("鐗规畩姝﹀櫒鐏姏", "font/Font20.fnt");
	//CCMenuItemLabel *pLabelBonus = CCMenuItemLabel::create(pFontBonus);
	//pLabelBonus->setAnchorPoint(ccp(0.0f,0.5f));
	//pLabelBonus->setPosition(mScreenSize.width * 0.2f,mScreenSize.height * (fBeginPosY + 0.05f));
	//m_pConfigureNode->addChild(pLabelBonus);

	m_pBonusBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_BG.png"));
	m_pBonusBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * fBeginPosY));
	m_pConfigureNode->addChild(m_pBonusBG);

	m_pMenuBonus = CCProgressTimer::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Property_Top.png")));
	m_pMenuBonus->setType(kCCProgressTimerTypeBar);
	m_pMenuBonus->setMidpoint(ccp(0,0));
	m_pMenuBonus->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuBonus->setBarChangeRate(ccp(1, 0));
	m_pMenuBonus->setPosition(ccp(0,m_pMenuBonus->getContentSize().height * 0.5f));
	m_pMenuBonus->setPercentage(m_nBonusPoint * 5);
	m_pBonusBG->addChild(m_pMenuBonus);

	m_pBonusReduce = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Reduce.png")), this, menu_selector(CMissionLayer::reduceBonusCallback) );
	m_pBonusReduce->setPosition(-m_pBonusBG->getContentSize().width * 0.5f - m_pBonusReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pBonusReduce);

	m_pBonusAdd = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Add.png")), this, menu_selector(CMissionLayer::addBonusCallback) );
	m_pBonusAdd->setPosition(m_pBonusBG->getContentSize().width * 0.5f + m_pBonusReduce->getContentSize().width * 0.5f, mScreenSize.height * (fBeginPosY - 0.5f));
	pMenuConfigure->addChild(m_pBonusAdd);

	m_pConfigureNode->setVisible(false);

	m_eCurState = MS_MISSION;
	//pLabel = CCLabelTTF::create("This is MainUI!", "Arial", 24);
	//pLabel->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));

	//this->addChild(pLabel);
	Music::playMainUIBgMusic();

	setKeypadEnabled(true);
	return true;
}

void CMissionLayer::setConfigurePoint(void)
{
	char szName[128] = {0};
	sprintf(szName, "%02d", m_nTotalUIPoint + m_nSpeedUIPoint + m_nArmorUIPoint + m_nAttackUIPoint + m_nBonusUIPoint);
	m_pTotalXP->setString(szName);
	sprintf(szName, "%02d", m_nTotalUIPoint);
	m_pFreeXP->setString(szName);
}

void CMissionLayer::keyBackClicked()
{
	Music::playClickEffect();
	CCScene *pScene = CMainUIScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CMissionLayer::startGameCallback(CCObject* sender)
{
	Music::playClickEffect();
	CCScene *pScene = CGameScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CMissionLayer::adjustFighterCallback(CCObject* sender)
{
	Music::playClickEffect();
	m_eCurState = MS_CONFIGUR;
	pMenuMission->setVisible(false);
	m_pConfigureNode->setVisible(true);

	m_nTotalUIPoint = m_nTotalPoint;
	m_nSpeedUIPoint = m_nSpeedPoint;
	m_nArmorUIPoint = m_nArmorPoint;
	m_nAttackUIPoint = m_nAttackPoint;
	m_nBonusUIPoint = m_nBonusPoint;

	m_pMenuSpeed->setPercentage(m_nSpeedUIPoint * 5);
	m_pMenuArmor->setPercentage(m_nArmorUIPoint * 5);
	m_pMenuAttack->setPercentage(m_nAttackUIPoint * 5);
	m_pMenuBonus->setPercentage(m_nBonusUIPoint * 5);

	setConfigurePoint();
}

void CMissionLayer::toMissionCallback(CCObject* sender)
{
	Music::playClickEffect();
	m_eCurState = MS_MISSION;
	m_pConfigureNode->setVisible(false);
	pMenuMission->setVisible(true);
}

void CMissionLayer::saveSetCallback(CCObject* sender)
{
	Music::playClickEffect();

	m_eCurState = MS_MISSION;
	m_pConfigureNode->setVisible(false);
	pMenuMission->setVisible(true);

	m_nTotalPoint = m_nTotalUIPoint;
	m_nSpeedPoint = m_nSpeedUIPoint;
	m_nArmorPoint = m_nArmorUIPoint;
	m_nAttackPoint = m_nAttackUIPoint;
	m_nBonusPoint = m_nBonusUIPoint;

	CGlobalData::getSingleton()->setPlayerPoint(m_nTotalPoint);
	CGlobalData::getSingleton()->setPlayerSpeed(m_nSpeedPoint);
	CGlobalData::getSingleton()->setPlayerArmor(m_nArmorPoint);
	CGlobalData::getSingleton()->setPlayerAttack(m_nAttackPoint);
	CGlobalData::getSingleton()->setPlayerBouns(m_nBonusPoint);
	CGlobalData::getSingleton()->saveFighterConfigure();
}

void CMissionLayer::addSpeedCallback(CCObject* sender)
{
	if (m_nTotalUIPoint > 0 && m_nSpeedUIPoint < 20)
	{
		m_nSpeedUIPoint ++;
		m_nTotalUIPoint --;
		m_pMenuSpeed->setPercentage(m_nSpeedUIPoint * 5);
		setConfigurePoint();
		m_pMenuSpeed->getSprite()->getContentSize().width;
		//CCLOG("meun width:%f", m_pMenuSpeed->getContentSize().width);
		//CCLOG("sprite width:%f", m_pMenuSpeed->getSprite()->getContentSize().width);
		//CCLOG("tab value:%d", m_nSpeedUIPoint * 5);
	}

}

void CMissionLayer::reduceSpeedCallback(CCObject* sender)
{
	if (m_nSpeedUIPoint > 0)
	{
		m_nSpeedUIPoint --;
		m_nTotalUIPoint ++;
		m_pMenuSpeed->setPercentage(m_nSpeedUIPoint * 5);
		setConfigurePoint();
	}
}

void CMissionLayer::addArmorCallback(CCObject* sender)
{
	if (m_nTotalUIPoint > 0 && m_nArmorUIPoint < 20)
	{
		m_nArmorUIPoint ++;
		m_nTotalUIPoint --;
		m_pMenuArmor->setPercentage(m_nArmorUIPoint * 5);
		setConfigurePoint();
	}
}

void CMissionLayer::reduceArmorCallback(CCObject* sender)
{
	if (m_nArmorUIPoint > 0)
	{
		m_nArmorUIPoint --;
		m_nTotalUIPoint ++;
		m_pMenuArmor->setPercentage(m_nArmorUIPoint * 5);
		setConfigurePoint();
	}
}

void CMissionLayer::addAttackCallback(CCObject* sender)
{
	if (m_nTotalUIPoint > 0 && m_nAttackUIPoint < 20)
	{
		m_nAttackUIPoint ++;
		m_nTotalUIPoint --;
		m_pMenuAttack->setPercentage(m_nAttackUIPoint * 5);
		setConfigurePoint();
	}
}

void CMissionLayer::reduceAttackCallback(CCObject* sender)
{
	if (m_nAttackUIPoint > 0)
	{
		m_nAttackUIPoint --;
		m_nTotalUIPoint ++;
		m_pMenuAttack->setPercentage(m_nAttackUIPoint * 5);
		setConfigurePoint();
	}
}

void CMissionLayer::addBonusCallback(CCObject* sender)
{
	if (m_nTotalUIPoint > 0 && m_nBonusUIPoint < 20)
	{
		m_nBonusUIPoint ++;
		m_nTotalUIPoint --;
		m_pMenuBonus->setPercentage(m_nBonusUIPoint * 5);
		setConfigurePoint();
	}
}

void CMissionLayer::reduceBonusCallback(CCObject* sender)
{
	if (m_nBonusUIPoint > 0)
	{
		m_nBonusUIPoint --;
		m_nTotalUIPoint ++;
		m_pMenuBonus->setPercentage(m_nBonusUIPoint * 5);
		setConfigurePoint();
	}
}
