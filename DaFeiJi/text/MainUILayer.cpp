#include "MainUILayer.h"

CMainUILayer::CMainUILayer(void)
{
	m_pCurCache = NULL;
	m_eCurState = US_MAIN;
}

CMainUILayer::~CMainUILayer(void)
{
}

bool CMainUILayer::init(void)
{
	cc_timeval psv;
	CCTime::gettimeofdayCocos2d(&psv, NULL);
	unsigned long int seed = psv.tv_sec*1000 + psv.tv_usec / 1000;
	srand(seed);

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


	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_pCurCache->addSpriteFramesWithFile("UI/UI.plist", "UI/UI.png");
	m_pCurCache->addSpriteFramesWithFile("UI/UI_2.plist", "UI/UI_2.png");
	m_pCurCache->addSpriteFramesWithFile("UI/UI_3.plist", "UI/UI_3.png");
	m_pCurCache->addSpriteFramesWithFile("player/Player.plist", "player/Player.png");

	CCMenu* pMenu = CCMenu::create();
	pMenuBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("MainBG.png"));
	pMenuBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	addChild(pMenuBG);

	sprintf(szName, "%sTitle.png", m_sPrefix);
	pTile = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	pTile->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.742f));
	addChild(pTile);

	m_pOptionMenu = CCMenu::create();
	m_pOptionMenu->setVisible(false);
	

	sprintf(szName, "%sNewGame.png", m_sPrefix);
	CCMenuItemSprite *pMenuItem = NULL;
	pMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toMainCallback) );
	pMenuItem->setPosition(0.0f, -mScreenSize.height * 0.4f);
	m_vMenuItemVector.push_back(pMenuItem);
	pMenu->addChild(pMenuItem);

	sprintf(szName, "%sHighScores.png", m_sPrefix);
	pMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toMainCallback) );
	pMenuItem->setPosition(0.0f, -mScreenSize.height * 0.4f);
	m_vMenuItemVector.push_back(pMenuItem);
	pMenu->addChild(pMenuItem);

	sprintf(szName, "%sOptions.png", m_sPrefix);
	pMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toMainCallback) );
	pMenuItem->setPosition(0.0f, -mScreenSize.height * 0.4f);
	m_vMenuItemVector.push_back(pMenuItem);
	pMenu->addChild(pMenuItem);

	sprintf(szName, "%sHelps.png", m_sPrefix);
	pMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toMainCallback) );
	pMenuItem->setPosition(0.0f, -mScreenSize.height * 0.4f);
	m_vMenuItemVector.push_back(pMenuItem);
	pMenu->addChild(pMenuItem);

	sprintf(szName, "%sExit.png", m_sPrefix);
	pMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toMainCallback) );
	pMenuItem->setPosition(0.0f, -mScreenSize.height * 0.4f);
	m_vMenuItemVector.push_back(pMenuItem);
	pMenu->addChild(pMenuItem);

	m_pLeftArrow = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("LeftArrow.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("LeftArrow.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("LeftArrow.png")), this, menu_selector(CMainUILayer::toLeftCallback) );
	m_pLeftArrow->setPosition((pMenuItem->getContentSize().width + m_pLeftArrow->getContentSize().width) * (-0.5f), -mScreenSize.height * 0.4f);
	//addAnimationToUI(m_pLeftArrow, "LeftArrow");
	pMenu->addChild(m_pLeftArrow);


	m_pRightArrow = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("RightArrow.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("RightArrow.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("RightArrow.png")), this, menu_selector(CMainUILayer::toRightCallback) );
	m_pRightArrow->setPosition((pMenuItem->getContentSize().width + m_pRightArrow->getContentSize().width) * 0.5f - 6.0f, -mScreenSize.height * 0.4f);
	//addAnimationToUI(m_pRightArrow, "RightArrow");
	pMenu->addChild(m_pRightArrow);


	sprintf(szName, "%sISExit.png", m_sPrefix);
	m_pMenuImageBG = CCMenuItemImage::create();
	m_pMenuImageBG->setNormalSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pMenuImageBG->setPosition(0.0f, 0.0f);
	m_pMenuImageBG->setEnabled(false);
	m_pMenuImageBG->setVisible(false);
	pMenu->addChild(m_pMenuImageBG);

	sprintf(szName, "%sYes.png", m_sPrefix);
	m_pMenuYes = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toEnterCallback) );
	m_pMenuYes->setPosition(-m_pMenuImageBG->getContentSize().width * 0.25f, -m_pMenuImageBG->getContentSize().height * 0.25f);
	m_pMenuYes->setVisible(false);
	//m_pMenuYes->setPosition(-mScreenSize.width * 0.2f, -0.5f);
	pMenu->addChild(m_pMenuYes);

	sprintf(szName, "%sNo.png", m_sPrefix);
	m_pMenuNo = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toCancelCallback) );
	m_pMenuNo->setPosition(m_pMenuImageBG->getContentSize().width * 0.25f, -m_pMenuImageBG->getContentSize().height * 0.25f);
	m_pMenuNo->setVisible(false);
	//m_pMenuNo->setPosition(mScreenSize.width * 0.2f, -0.5f);
	pMenu->addChild(m_pMenuNo);

	sprintf(szName, "%sTouchBack.png", m_sPrefix);
	m_pTouchBack = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toTouchBackCall) );
	m_pTouchBack->setPosition(0.0f, -mScreenSize.height * 0.45f);
	m_pTouchBack->setVisible(false);
	//m_pMenuNo->setPosition(mScreenSize.width * 0.2f, -0.5f);
	pMenu->addChild(m_pTouchBack);

	sprintf(szName, "%sGameMute.png", m_sPrefix);
	m_pMenuMute = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toRateGame));
	m_pMenuMute->setPosition(-mScreenSize.width * 0.25f, -mScreenSize.height * 0.275f);
	pMenu->addChild(m_pMenuMute);

	sprintf(szName, "%sMoreGame.png", m_sPrefix);
	m_pMenuMoreGame = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toMoreGame));
	m_pMenuMoreGame->setPosition(mScreenSize.width * 0.25f, -mScreenSize.height * 0.275f);
	pMenu->addChild(m_pMenuMoreGame);

	sprintf(szName, "%sShop.png", m_sPrefix);
	m_pMenuGameShop = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CMainUILayer::toShopCallback) );
	m_pMenuGameShop->setPosition(mScreenSize.width * 0.25f, -mScreenSize.height * 0.175f);
	pMenu->addChild(m_pMenuGameShop);

	if (VERSION == 2)
	{
		m_pMenuGameShop->setVisible(false);
	}

	this->addChild(pMenu);

	sprintf(szName, "%sHighScore.png", m_sPrefix);
	m_pHighScore = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pHighScore->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	addChild(m_pHighScore);
	m_pHighScore->setVisible(false);

	//统计
	m_pLevelTotal = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevelTotal->setPosition(335,455);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getTotalScore());
	m_pLevelTotal->setString(szName);
	m_pHighScore->addChild(m_pLevelTotal);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,330);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(1));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,284);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(2));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,238);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(3));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,192);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(4));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,146);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(5));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,100);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(6));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,54);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(7));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	m_pLevel01 = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pLevel01->setPosition(335,8);
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getScoreByLevel(8));
	m_pLevel01->setString(szName);
	m_pHighScore->addChild(m_pLevel01);

	sprintf(szName, "%sHelp.png", m_sPrefix);
	m_pHelp = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pHelp->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	addChild(m_pHelp);
	m_pHelp->setVisible(false);

	//选项
	sprintf(szName, "%sOption.png", m_sPrefix);
	m_pOptionBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pOptionBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	addChild(m_pOptionBG);
	m_pOptionBG->setVisible(false);

	addChild(m_pOptionMenu);
	CCSprite *pOff = CCSprite::create();
	pOff->setContentSize(CCSizeMake(46,46));
	m_pMusicMute = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(CMainUILayer::toMusicOnAndOff), 
		CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png")),CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png"))),
		CCMenuItemSprite::create(pOff,pOff),
		NULL );
	m_pMusicMute->setPosition(ccp(-84.0f,232.0f));
	m_pOptionMenu->addChild(m_pMusicMute);
	if (CGlobalData::getSingleton()->isOpenMusic())
	{
		m_pMusicMute->setSelectedIndex(0);
	}
	else
	{
		m_pMusicMute->setSelectedIndex(1);
	}

	m_pMusicVolume = CCControlSlider::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_BG.png")),
											CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_bar.png")),
											CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_Thumb.png")));
	m_pMusicVolume->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.75f - 9.0f));
	m_pMusicVolume->setMaximumValue(1.0f);
	m_pMusicVolume->setMinimumValue(0.0f);
	m_pMusicVolume->setVisible(false);
	m_pMusicVolume->setTag(MUSIC_VOLUME);
	m_pMusicVolume->setValue(CGlobalData::getSingleton()->getMusicVolume());
	m_pMusicVolume->addTargetWithActionForControlEvents(this, cccontrol_selector(CMainUILayer::toSliderCallback), CCControlEventValueChanged);
	addChild(m_pMusicVolume);

	if (CGlobalData::getSingleton()->isOpenMusic())
	{
		Music::setBackgroundMusicVolume(0.0f);
		m_pMusicVolume->setEnabled(false);
	}
	else
	{
		Music::setBackgroundMusicVolume(CGlobalData::getSingleton()->getMusicVolume());
	}

	pOff = CCSprite::create();
	pOff->setContentSize(CCSizeMake(46,46));
	m_pFXMute = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(CMainUILayer::toFXOnAndOff), 
		CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png")),CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png"))),
		CCMenuItemSprite::create(pOff,pOff),
		NULL );
	m_pFXMute->setPosition(ccp(-84.0f,134.0f));
	m_pOptionMenu->addChild(m_pFXMute);
	if (CGlobalData::getSingleton()->isOpenFX())
	{
		m_pFXMute->setSelectedIndex(0);
	}
	else
	{
		m_pFXMute->setSelectedIndex(1);
	}
	

	m_pFXVolume = CCControlSlider::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_BG.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_bar.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_Thumb.png")));
	m_pFXVolume->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.625f - 9.0f));
	m_pFXVolume->setMaximumValue(1.0f);
	m_pFXVolume->setMinimumValue(0.0f);
	m_pFXVolume->setVisible(false);
	m_pFXVolume->setTag(FX_VOLUME);
	m_pFXVolume->setValue(CGlobalData::getSingleton()->getFXVolume());
	m_pFXVolume->addTargetWithActionForControlEvents(this, cccontrol_selector(CMainUILayer::toSliderCallback), CCControlEventValueChanged);
	addChild(m_pFXVolume);

	if (CGlobalData::getSingleton()->isOpenFX())
	{
		Music::setEffectVolume(0.0f);
		m_pFXVolume->setEnabled(false);
	}
	else
	{
		Music::setEffectVolume(CGlobalData::getSingleton()->getFXVolume());
	}
	
	m_pDifficultyVolume = CCControlSlider::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_BG.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Difficulty_bar.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Volume_Thumb.png")));
	m_pDifficultyVolume->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.4625f - 9.0f));
	m_pDifficultyVolume->setMaximumValue(1.0f);
	m_pDifficultyVolume->setMinimumValue(0.0f);
	m_pDifficultyVolume->setVisible(false);
	m_pDifficultyVolume->setTag(DIFFICULTY_VOLUME);
	m_pDifficultyVolume->setValue(CGlobalData::getSingleton()->getDifficultyVolume());
	m_pDifficultyVolume->addTargetWithActionForControlEvents(this, cccontrol_selector(CMainUILayer::toSliderCallback), CCControlEventValueChanged);
	addChild(m_pDifficultyVolume);


	pOff = CCSprite::create();
	pOff->setContentSize(CCSizeMake(46,46));
	m_pTouchControl = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(CMainUILayer::toTouchOnAndOff), 
		CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png")),CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png"))),
		CCMenuItemSprite::create(pOff,pOff),
		NULL );
	m_pTouchControl->setPosition(ccp(-44.0f,-175.0f));
	m_pOptionMenu->addChild(m_pTouchControl);
	if (CGlobalData::getSingleton()->isTouchControl())
	{
		m_pTouchControl->setSelectedIndex(0);
	}
	else
	{
		m_pTouchControl->setSelectedIndex(1);
	}

	pOff = CCSprite::create();
	pOff->setContentSize(CCSizeMake(46,46));
	m_pGravityControl = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(CMainUILayer::toGravityOnAndOff), 
		CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png")),CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png"))),
		CCMenuItemSprite::create(pOff,pOff),
		NULL );
	m_pGravityControl->setPosition(ccp(-44.0f,-224.0f));
	m_pOptionMenu->addChild(m_pGravityControl);
	if (CGlobalData::getSingleton()->isGravityControl())
	{
		m_pGravityControl->setSelectedIndex(0);
	}
	else
	{
		m_pGravityControl->setSelectedIndex(1);
	}

	pOff = CCSprite::create();
	pOff->setContentSize(CCSizeMake(46,46));
	m_pRunControl = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(CMainUILayer::toRunOnAndOff), 
		CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png")),CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png"))),
		CCMenuItemSprite::create(pOff,pOff),
		NULL );
	m_pRunControl->setPosition(ccp(152.0f,-175.0f));
	m_pOptionMenu->addChild(m_pRunControl);
	if (CGlobalData::getSingleton()->isRunControl())
	{
		m_pRunControl->setSelectedIndex(0);
	}
	else
	{
		m_pRunControl->setSelectedIndex(1);
	}

	pOff = CCSprite::create();
	pOff->setContentSize(CCSizeMake(46,46));
	m_pDoubleControl = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(CMainUILayer::toDoubleOnAndOff), 
		CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png")),CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Select.png"))),
		CCMenuItemSprite::create(pOff,pOff),
		NULL );
	m_pDoubleControl->setPosition(ccp(152.0f,-224.0f));
	m_pOptionMenu->addChild(m_pDoubleControl);
	if (CGlobalData::getSingleton()->isDoubleControl())
	{
		m_pDoubleControl->setSelectedIndex(0);
	}
	else
	{
		m_pDoubleControl->setSelectedIndex(1);
	}

	//pLabel = CCLabelTTF::create("This is MainUI!", "Arial", 24);
	//pLabel->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	//CC_BREAK_IF(! pLabel);
	//CGlobalData::getSingleton();

	//this->addChild(pLabel);
	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pMenuBG);
	m_sBaseColor = pRGBAProtocol->getColor();

	setMainMenuItem();
	m_eCurState = US_MAIN;
	
	Music::playMainUIBgMusic();

	setKeypadEnabled(true);
	return true;
}

void CMainUILayer::toMoreGame(CCObject* sender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/zmplay/ldzjjmkx/RsidenFighterAirRaid","moreGame", "()V");
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
	#endif
}

void CMainUILayer::toRateGame(CCObject* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/zmplay/ldzjjmkx/RsidenFighterAirRaid","rateGame", "()V");
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
}

void CMainUILayer::layerUpdate(float fEscapeTime)
{
	;
}

void CMainUILayer::addAnimationToUI(CCMenuItemSprite* pMenuItem, const char* pszName)
{
	//CCSprite *pSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("LeftArrow01.png"));
	CCSprite *pSprite = CCSprite::create();
	CCAnimation *pAnimation = CCAnimation::create();
	char szName[128] = {0};

	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d.png", pszName, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}
	pAnimation->setDelayPerUnit(0.3f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	pSprite->runAction( CCRepeatForever::create( pAction ) );
	pSprite->setPosition(ccp(pMenuItem->getContentSize().width * 0.5f, pMenuItem->getContentSize().height * 0.5f));
	pMenuItem->addChild(pSprite);
}

void CMainUILayer::toSliderCallback(CCObject *sender, CCControlEvent controlEvent)
{
	CCControlSlider* pSlider = (CCControlSlider*)sender;
	switch(pSlider->getTag())
	{
	case MUSIC_VOLUME:
		if (!CGlobalData::getSingleton()->isOpenMusic())
		{
			CGlobalData::getSingleton()->setMusicVolume(pSlider->getValue());
			Music::setBackgroundMusicVolume(pSlider->getValue());
		}
		else
		{
			pSlider->setValue(CGlobalData::getSingleton()->getMusicVolume());
		}
		break;
	case FX_VOLUME:
		if (!CGlobalData::getSingleton()->isOpenFX())
		{
			CGlobalData::getSingleton()->setFXVolume(pSlider->getValue());
			Music::setEffectVolume(pSlider->getValue());
		}
		else
		{
			pSlider->setValue(CGlobalData::getSingleton()->getFXVolume());
		}
		break;
	case DIFFICULTY_VOLUME:
		CGlobalData::getSingleton()->setDifficultyVolume(pSlider->getValue());
		break;
	}
}

void CMainUILayer::toMusicOnAndOff(CCObject* sender)
{
	CGlobalData::getSingleton()->setMusicONOFF(!CGlobalData::getSingleton()->isOpenMusic());
	if (CGlobalData::getSingleton()->isOpenMusic())
	{
		Music::setBackgroundMusicVolume(0.0f);
		m_pMusicVolume->setEnabled(false);
	}
	else
	{
		Music::setBackgroundMusicVolume(CGlobalData::getSingleton()->getMusicVolume());
		m_pMusicVolume->setEnabled(true);
	}
	
}

void CMainUILayer::toFXOnAndOff(CCObject* sender)
{
	CGlobalData::getSingleton()->setFXONOFF(!CGlobalData::getSingleton()->isOpenFX());
	if (CGlobalData::getSingleton()->isOpenFX())
	{
		Music::setEffectVolume(0.0f);
		m_pFXVolume->setEnabled(false);
	}
	else
	{
		Music::setEffectVolume(CGlobalData::getSingleton()->getFXVolume());
		m_pFXVolume->setEnabled(true);
	}
}

void CMainUILayer::toTouchOnAndOff(CCObject* sender)
{
	if(m_pTouchControl->getSelectedIndex() != 0)
	{
		m_pTouchControl->setSelectedIndex(0);
	}
	CGlobalData::getSingleton()->setGravityControl(false);
	CGlobalData::getSingleton()->setTouchControl(true);
	m_pGravityControl->setSelectedIndex(1);
}

void CMainUILayer::toGravityOnAndOff(CCObject* sender)
{
	if(m_pGravityControl->getSelectedIndex() != 0)
	{
		m_pGravityControl->setSelectedIndex(0);
	}
	CGlobalData::getSingleton()->setGravityControl(true);
	CGlobalData::getSingleton()->setTouchControl(false);
	m_pTouchControl->setSelectedIndex(1);
}

void CMainUILayer::toRunOnAndOff(CCObject* sender)
{
	if (m_pRunControl->getSelectedIndex() != 0)
	{
		m_pRunControl->setSelectedIndex(0);
		
	}
	CGlobalData::getSingleton()->setDoubleControl(false);
	CGlobalData::getSingleton()->setRunControl(true);
	m_pDoubleControl->setSelectedIndex(1);
}

void CMainUILayer::toDoubleOnAndOff(CCObject* sender)
{
	if (m_pDoubleControl->getSelectedIndex() != 0)
	{
		m_pDoubleControl->setSelectedIndex(0);
		
	}
	CGlobalData::getSingleton()->setDoubleControl(true);
	CGlobalData::getSingleton()->setRunControl(false);
	m_pRunControl->setSelectedIndex(1);
}

void CMainUILayer::toLeftCallback(CCObject* sender)
{
	Music::playClickEffect();

	if (m_eCurState == US_MAIN)
	{
		m_eCurState = US_EXIT;
	}
	else
	{
		int mState = (int)m_eCurState;
		m_eCurState = (UI_STATE)(mState -1);
	}

	setMainMenuItem();
}

void CMainUILayer::toRightCallback(CCObject* sender)
{
	Music::playClickEffect();

	if (m_eCurState == US_EXIT)
	{
		m_eCurState = US_MAIN;
	}
	else
	{
		int mState = (int)m_eCurState;
		m_eCurState = (UI_STATE)(mState +1);
	}
	
	setMainMenuItem();
}

void CMainUILayer::toTouchBackCall(CCObject* sender)
{
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pMenuBG);
	pRGBAProtocol->setColor(m_sBaseColor);
	m_pTouchBack->setVisible(false);
	m_pLeftArrow->setVisible(true);
	m_pMenuGameShop->setVisible(true);
	if (VERSION == 2)
	{
		m_pMenuGameShop->setVisible(false);
	}
	m_pRightArrow->setVisible(true);
	m_pMenuMute->setVisible(true);
	m_pMenuMoreGame->setVisible(true);
	m_pHighScore->setVisible(false);
	m_pHelp->setVisible(false);
	pTile->setVisible(true);
	m_pOptionMenu->setVisible(false);
	m_pOptionBG->setVisible(false);
	m_pMusicVolume->setVisible(false);
	m_pFXVolume->setVisible(false);
	m_pDifficultyVolume->setVisible(false);
	if (m_eCurState == US_OPTIONS)
	{
		CGlobalData::getSingleton()->setOption();
	}

	setMainMenuItem();
	Music::playClickEffect();
}

void CMainUILayer::toMainCallback(CCObject* sender)
{
	Music::playClickEffect();
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pMenuBG);
	switch(m_eCurState)
	{
	case US_MAIN:
		{
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			JniMethodInfo minfo;
			bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/zmplay/ldzjjmkx/RsidenFighterAirRaid","startGame", "()V");
			if (isHave) 
			{
				minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
			}
			#endif
			CCScene *pScene = CSelectScene::scene();
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
		break;
	case US_HIGHSCORES:
		//pLabel->setString("to HIGHSCORES!");
		pRGBAProtocol->setColor(ccc3(51,51,51));
		for (unsigned int i=0; i<m_vMenuItemVector.size(); i++)
		{
			m_vMenuItemVector[i]->setVisible(false);
		}
		m_pLeftArrow->setVisible(false);
		m_pMenuGameShop->setVisible(false);
		m_pRightArrow->setVisible(false);
		m_pMenuMute->setVisible(false);
		m_pMenuMoreGame->setVisible(false);
		m_pHighScore->setVisible(true);
		m_pTouchBack->setVisible(true);
		pTile->setVisible(false);
		break;
	case US_OPTIONS:
		//pLabel->setString("to OPTIONS");
		pRGBAProtocol->setColor(ccc3(51,51,51));
		for (unsigned int i=0; i<m_vMenuItemVector.size(); i++)
		{
			m_vMenuItemVector[i]->setVisible(false);
		}
		m_pLeftArrow->setVisible(false);
		m_pMenuGameShop->setVisible(false);
		m_pRightArrow->setVisible(false);
		m_pMenuMute->setVisible(false);
		m_pMenuMoreGame->setVisible(false);
		m_pTouchBack->setVisible(true);
		pTile->setVisible(false);
		m_pOptionMenu->setVisible(true);
		m_pOptionBG->setVisible(true);
		m_pMusicVolume->setVisible(true);
		m_pFXVolume->setVisible(true);
		m_pDifficultyVolume->setVisible(true);
		break;
	case US_HELP:
		//pLabel->setString("to HELP");
		pRGBAProtocol->setColor(ccc3(51,51,51));
		for (unsigned int i=0; i<m_vMenuItemVector.size(); i++)
		{
			m_vMenuItemVector[i]->setVisible(false);
		}
		m_pLeftArrow->setVisible(false);
		m_pMenuGameShop->setVisible(false);
		m_pRightArrow->setVisible(false);
		m_pMenuMute->setVisible(false);
		m_pMenuMoreGame->setVisible(false);
		m_pHelp->setVisible(true);
		m_pTouchBack->setVisible(true);
		pTile->setVisible(false);
		break;
	case US_EXIT:
		toPopExitDialog();
		break;
	}

}

void CMainUILayer::keyBackClicked()
{
	if (m_pMenuImageBG->isVisible())
	{
		toCancelCallback(NULL);
	}
	else if (m_eCurState == US_MAIN)
	{
		toPopExitDialog();
	}
	else
	{
		toTouchBackCall(NULL);
	}
}

void CMainUILayer::toPopExitDialog()
{
	for (unsigned int i=0; i<m_vMenuItemVector.size(); i++)
	{
		m_vMenuItemVector[i]->setVisible(false);
	}
	m_pLeftArrow->setVisible(false);
	m_pMenuGameShop->setVisible(false);
	m_pRightArrow->setVisible(false);
	m_pMenuMute->setVisible(false);
	m_pMenuMoreGame->setVisible(false);
	m_pMenuImageBG->setVisible(true);
	m_pMenuYes->setVisible(true);
	m_pMenuNo->setVisible(true);

	Music::playClickEffect();
}

void CMainUILayer::toEnterCallback(CCObject* sender)
{
	Music::playClickEffect();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/zmplay/ldzjjmkx/RsidenFighterAirRaid","exitGame", "()V");
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
	CCDirector::sharedDirector()->end();
}

void CMainUILayer::toCancelCallback(CCObject* sender)
{
	m_pMenuImageBG->setVisible(false);
	m_pMenuYes->setVisible(false);
	m_pMenuNo->setVisible(false);
	m_pLeftArrow->setVisible(true);
	m_pMenuGameShop->setVisible(true);
	if (VERSION == 2)
	{
		m_pMenuGameShop->setVisible(false);
	}
	m_pRightArrow->setVisible(true);
	m_pMenuMute->setVisible(true);
	m_pMenuMoreGame->setVisible(true);
	setMainMenuItem();

	Music::playClickEffect();
}

void CMainUILayer::setMainMenuItem(void)
{
	CCSize mMeunSize = m_vMenuItemVector[m_eCurState]->getContentSize();
	for (unsigned int i=0; i<m_vMenuItemVector.size(); i++)
	{
		m_vMenuItemVector[i]->setVisible(false);
		m_vMenuItemVector[i]->setScale(1.0f);
		m_vMenuItemVector[i]->setEnabled(false);
	}

	m_vMenuItemVector[m_eCurState]->setPosition(0.0f, -mScreenSize.height * 0.4f);
	m_vMenuItemVector[m_eCurState]->setVisible(true);
	m_vMenuItemVector[m_eCurState]->setEnabled(true);
	m_vMenuItemVector[m_eCurState]->setOpacity(255);

	if (m_eCurState == US_MAIN)
	{
		m_vMenuItemVector[US_EXIT]->setVisible(true);
		m_vMenuItemVector[US_EXIT]->setScale(0.6f);
		m_vMenuItemVector[US_EXIT]->setPosition(-mMeunSize.width * 0.5f - mMeunSize.width * 0.6f * 0.5f, -mScreenSize.height * 0.4f - mMeunSize.height * 0.15f);
		m_vMenuItemVector[US_EXIT]->setOpacity(150);
	}
	else
	{
		m_vMenuItemVector[m_eCurState-1]->setVisible(true);
		m_vMenuItemVector[m_eCurState-1]->setScale(0.6f);
		m_vMenuItemVector[m_eCurState-1]->setPosition(-mMeunSize.width * 0.5f - mMeunSize.width * 0.6f * 0.5f, -mScreenSize.height * 0.4f - mMeunSize.height * 0.15f);
		m_vMenuItemVector[m_eCurState-1]->setOpacity(150);
	}

	if (m_eCurState == US_EXIT)
	{
		m_vMenuItemVector[US_MAIN]->setVisible(true);
		m_vMenuItemVector[US_MAIN]->setScale(0.6f);
		m_vMenuItemVector[US_MAIN]->setPosition(mMeunSize.width * 0.5f + mMeunSize.width * 0.6f * 0.5f, -mScreenSize.height * 0.4f - mMeunSize.height * 0.15f);
		m_vMenuItemVector[US_MAIN]->setOpacity(150);
	}
	else
	{
		m_vMenuItemVector[m_eCurState+1]->setVisible(true);
		m_vMenuItemVector[m_eCurState+1]->setScale(0.6f);
		m_vMenuItemVector[m_eCurState+1]->setPosition(mMeunSize.width * 0.5f + mMeunSize.width * 0.6f * 0.5f, -mScreenSize.height * 0.4f - mMeunSize.height * 0.15f);
		m_vMenuItemVector[m_eCurState+1]->setOpacity(150);
	}
}

void CMainUILayer::toShopCallback(CCObject* sender)
{
	CShopLayer* layer = CShopLayer::create();  
	getParent()->addChild(layer);
	layer->setTag(SHOP_UI);
	setVisible(false);
	//removeFromParentAndCleanup(true);
}
