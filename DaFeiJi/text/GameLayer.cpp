#include "GameLayer.h"

CGameLayer::CGameLayer(void)
{
	m_vMapSpriteVector.clear();
	m_tDirection = ccp(0.0f, -1.0f);

	//m_sCurData.mMapSpeed = 110.0f;
	//m_sCurData.mBossTime = 5.0f;

	m_fTime = 0.0f;

	m_pPlayer = NULL;

	m_pMenuItemHP = NULL;
	m_pMenuFontScore = NULL;
	m_pMenuFontLife = NULL;
	m_pMenuItemPause = NULL;
	m_pMenuBackMain = NULL;
	m_pMenuContinue = NULL;
	m_pMenuItemFail = NULL;

	m_eCurState = GS_DEFAULT;
	m_fLevelTime = 0.0f;

	m_vCurPlaneData.clear();
	m_vLowCloudVector.clear();
	m_vHightCloudVector.clear();

	m_pHoldSpirte = NULL;
	m_eHoldItem = IK_DEFAULT;
}

CGameLayer::~CGameLayer(void)
{
}

bool CGameLayer::init(void)
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

	m_pCurCache->addSpriteFramesWithFile("level/Level01.plist", "level/Level01.png");
	m_pCurCache->addSpriteFramesWithFile("level/Level02.plist", "level/Level02.png");
	m_pCurCache->addSpriteFramesWithFile("level/Level03.plist", "level/Level03.png");
	m_pCurCache->addSpriteFramesWithFile("level/Level04.plist", "level/Level04.png");
	//m_pCurCache->addSpriteFramesWithFile("level/Level05.plist", "level/Level05.png");
	//m_pCurCache->addSpriteFramesWithFile("level/Level06.plist", "level/Level06.png");
	//m_pCurCache->addSpriteFramesWithFile("level/Level07.plist", "level/Level07.png");
	m_pCurCache->addSpriteFramesWithFile("enemy/NPC_Plane.plist", "enemy/NPC_Plane.png");
	m_pCurCache->addSpriteFramesWithFile("effect/Effect.plist", "effect/Effect.png");
	m_pCurCache->addSpriteFramesWithFile("army/Army.plist", "army/Army.png");
	m_pCurCache->addSpriteFramesWithFile("item/Item.plist", "item/Item.png");
	m_pCurCache->addSpriteFramesWithFile("bullet/Bullet.plist", "bullet/Bullet.png");
	m_pCurCache->addSpriteFramesWithFile("cloud/Cloud.plist", "cloud/Cloud.png");

	CGlobalData::getSingleton()->resetLevelScore();

	m_sCurData = CGlobalData::getSingleton()->getCurLevelData();

	CCMenu* pMenu = CCMenu::create();

	CCSprite *pSpriteBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("GameBG.png"));
	pSpriteBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height - pSpriteBG->getContentSize().height * 0.5f));
	addChild(pSpriteBG, GAMEUI_ZORDER - 1);

	//m_pFailSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("MissionFail.png"));
	//m_pFailSprite->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.6f));
	//m_pFailSprite->setVisible(false);
	//addChild(m_pFailSprite, GAMEUI_ZORDER);

	m_pMenuItemHP = CCProgressTimer::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("HP.png")));
	m_pMenuItemHP->setType(kCCProgressTimerTypeBar);
	m_pMenuItemHP->setMidpoint(ccp(0,0));
	m_pMenuItemHP->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuItemHP->setBarChangeRate(ccp(1, 0));
	m_pMenuItemHP->setPosition(ccp(pSpriteBG->getContentSize().width * 0.204f, pSpriteBG->getContentSize().height * 0.523f));
	m_pMenuItemHP->setPercentage(100.0f);
	pSpriteBG->addChild(m_pMenuItemHP);

	m_pHoldSpirte = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Item_HP_01.png"));
	m_pHoldSpirte->setPosition(ccp(pSpriteBG->getContentSize().width * 0.816f, pSpriteBG->getContentSize().height * 0.5f));
	m_pHoldSpirte->setScale(0.45f);
	m_pHoldSpirte->setVisible(false);
	pSpriteBG->addChild(m_pHoldSpirte);

	sprintf(szName, "%07d", CGlobalData::getSingleton()->getCurScore());
	m_pMenuFontScore = CCLabelAtlas::create(szName, "font/Number_20.png", 11, 14, '/');
	m_pMenuFontScore->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuFontScore->setPosition(ccp(pSpriteBG->getContentSize().width * 0.41f,pSpriteBG->getContentSize().height * 0.523f));
	pSpriteBG->addChild(m_pMenuFontScore);

	sprintf(szName, "%d", CGlobalData::getSingleton()->getLife());
	m_pMenuFontLife = CCLabelAtlas::create(szName, "font/Number_20.png", 11, 14, '/');
	m_pMenuFontLife->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuFontLife->setPosition(ccp(pSpriteBG->getContentSize().width * 0.9f,pSpriteBG->getContentSize().height * 0.437f));
	pSpriteBG->addChild(m_pMenuFontLife);

	sprintf(szName, "%2d", CGlobalData::getSingleton()->getRocket());
	m_pMenuFontRocket = CCLabelAtlas::create(szName, "font/Number_20.png", 11, 14, '/');
	m_pMenuFontRocket->setAnchorPoint(ccp(0.0f,0.5f));
	m_pMenuFontRocket->setPosition(ccp(pSpriteBG->getContentSize().width * 0.666f,pSpriteBG->getContentSize().height * 0.523f));
	pSpriteBG->addChild(m_pMenuFontRocket);

	m_pMenuItemPause = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Pause.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Pause.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Pause.png")), this, menu_selector(CGameLayer::pauseCallback));
	m_pMenuItemPause->setPosition(ccp(-mScreenSize.width * 0.425f, mScreenSize.height * 0.365f));
	pMenu->addChild(m_pMenuItemPause);

	m_pPauseBG = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("PauseBG.png"));
	m_pPauseBG->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	m_pPauseBG->setVisible(false);
	addChild(m_pPauseBG, GAMEUI_ZORDER - 1);

	sprintf(szName, "%sBackMain.png", m_sPrefix);
	m_pMenuBackMain = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CGameLayer::backMainCallback));
	m_pMenuBackMain->setPosition(ccp(0.0f, mScreenSize.height * 0.04f));
	m_pMenuBackMain->setVisible(false);
	pMenu->addChild(m_pMenuBackMain);

	sprintf(szName, "%sContinue.png", m_sPrefix);
	m_pMenuContinue = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CGameLayer::continueCallback));
	m_pMenuContinue->setPosition(ccp(0.0f, -mScreenSize.height * 0.04f));
	m_pMenuContinue->setVisible(false);
	pMenu->addChild(m_pMenuContinue);

	m_pSupperBomb = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("SupperBomb.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("SupperBomb.png")),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("SupperBomb.png")), this, menu_selector(CGameLayer::fireBombCallback));
	m_pSupperBomb->setPosition(ccp(mScreenSize.width * 0.5f - m_pSupperBomb->getContentSize().width * 0.5f, m_pSupperBomb->getContentSize().height * 0.5f - mScreenSize.height * 0.5f));
	pMenu->addChild(m_pSupperBomb);

	m_pBombTime = CCProgressTimer::create(CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("HP.png")));
	m_pBombTime->setType(kCCProgressTimerTypeBar);
	m_pBombTime->setMidpoint(ccp(0,0));
	m_pBombTime->setAnchorPoint(ccp(0.0f,0.5f));
	m_pBombTime->setBarChangeRate(ccp(1, 0));
	m_pBombTime->setPosition(ccp(m_pSupperBomb->getContentSize().width * 0.226f, m_pSupperBomb->getContentSize().height * 0.5f));
	m_pBombTime->setPercentage(0.0f);
	m_pSupperBomb->addChild(m_pBombTime);

	addChild(pMenu, GAMEUI_ZORDER + 1);

	sprintf(szName, "%sTouchBack.png", m_sPrefix);
	m_pMenuItemFail = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)),
		CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName)), this, menu_selector(CGameLayer::backMainCallback));
	m_pMenuItemFail->setPosition(ccp(0.0f, -mScreenSize.height * 0.4f));
	m_pMenuItemFail->setVisible(false);
	pMenu->addChild(m_pMenuItemFail);

	//玩家
	m_pPlayer = CPlayerSprite::createPlayer(CGlobalData::getSingleton()->getSelectKind());
	addChild(m_pPlayer, PLAYER_ZORDER);
	CGlobalData::getSingleton()->reduceLife();

	//地面
	sprintf(szName, "%s%02d.png", "LevelMap", (m_sCurData.mLevel - 1) % 4 + 1);
	//是否是挑战赛
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		sprintf(szName, "%s%02d.png", "LevelMap", ((int)(CCRANDOM_0_1() * 4.0f)) % 4 + 1);
	}
	CCSprite *pSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	pSprite->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	addChild(pSprite, MAP_ZORDER);
	m_vMapSpriteVector.push_back(pSprite);

	pSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	pSprite->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 1.5f));
	addChild(pSprite, MAP_ZORDER);
	m_vMapSpriteVector.push_back(pSprite);

	//过关统计界面
	m_pLevelScore = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("MainBG.png"));
	m_pLevelScore->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f));
	m_pLevelScore->setColor(ccc3(51,51,51));
	addChild(m_pLevelScore, GAMEUI_ZORDER);
	//统计分类
	float mPosY = 800.0f;
	sprintf(szName, "%sScoreTitle.png", m_sPrefix);
	m_pScoreTitle = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pScoreTitle->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height - m_pScoreTitle->getContentSize().height * 0.5f));
	m_pLevelScore->addChild(m_pScoreTitle);
	mPosY = mPosY - m_pScoreTitle->getContentSize().height;
	m_pScoreNum = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pScoreNum->setPosition(100,8);
	m_pScoreTitle->addChild(m_pScoreNum);
	m_pLevelXP = CCLabelAtlas::create("00", "font/Number_32.png", 15, 19, '/');
	m_pLevelXP->setPosition(313,8);
	m_pScoreTitle->addChild(m_pLevelXP);

	CCSprite *pScore = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("NPCScore.png"));
	pScore->setPosition(ccp(mScreenSize.width * 0.5f, mPosY - pScore->getContentSize().height * 0.5f));
	m_pLevelScore->addChild(pScore);
	mPosY = mPosY - pScore->getContentSize().height;

	m_pLevelPlane01 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane01->setPosition(0,225);
	pScore->addChild(m_pLevelPlane01);
	m_pLevelPlane02 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane02->setPosition(110,225);
	pScore->addChild(m_pLevelPlane02);
	m_pLevelPlane03 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane03->setPosition(220,225);
	pScore->addChild(m_pLevelPlane03);
	m_pLevelPlane04 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane04->setPosition(330,225);
	pScore->addChild(m_pLevelPlane04);
	m_pLevelPlane05 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane05->setPosition(0,100);
	pScore->addChild(m_pLevelPlane05);
	m_pLevelPlane06 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane06->setPosition(0,8);
	pScore->addChild(m_pLevelPlane06);

	//直升机2
	m_pLevelPlane07 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane07->setPosition(110,100);
	pScore->addChild(m_pLevelPlane07);

	//布雷机
	m_pLevelPlane08 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane08->setPosition(220,100);
	pScore->addChild(m_pLevelPlane08);

	//重甲机
	m_pLevelPlane09 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane09->setPosition(330,100);
	pScore->addChild(m_pLevelPlane09);

	//格林炮
	m_pLevelPlane10 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane10->setPosition(110,8);
	pScore->addChild(m_pLevelPlane10);

	//大炮
	m_pLevelPlane11 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane11->setPosition(220,8);
	pScore->addChild(m_pLevelPlane11);

	//地堡
	m_pLevelPlane12 = CCLabelAtlas::create("000/000", "font/Number_20.png", 11, 14, '/');
	m_pLevelPlane12->setPosition(330,8);
	pScore->addChild(m_pLevelPlane12);

	sprintf(szName, "%sLevelStar.png", m_sPrefix);
	pScore = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	pScore->setPosition(ccp(mScreenSize.width * 0.5f, mPosY - pScore->getContentSize().height * 0.5f));
	m_pLevelScore->addChild(pScore);
	m_pDesPercentage = CCLabelAtlas::create("000", "font/Number_32.png", 15, 19, '/');
	m_pDesPercentage->setPosition(200,95);
	pScore->addChild(m_pDesPercentage);
	m_pRewardXP = CCLabelAtlas::create("00", "font/Number_32.png", 15, 19, '/');
	m_pRewardXP->setPosition(310,3);
	pScore->addChild(m_pRewardXP);
	m_pRewarPoint = CCLabelAtlas::create("0000000", "font/Number_32.png", 15, 19, '/');
	m_pRewarPoint->setPosition(90,3);
	pScore->addChild(m_pRewarPoint);

	CCSprite *pStar = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("ScoreStar.png"));
	pStar->setPosition(ccp(68,60));
	pStar->setVisible(false);
	pScore->addChild(pStar);
	m_vDesStar.push_back(pStar);
	pStar = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("ScoreStar.png"));
	pStar->setPosition(ccp(130,60));
	pStar->setVisible(false);
	pScore->addChild(pStar);
	m_vDesStar.push_back(pStar);
	pStar = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("ScoreStar.png"));
	pStar->setPosition(ccp(192,60));
	pStar->setVisible(false);
	pScore->addChild(pStar);
	m_vDesStar.push_back(pStar);
	pStar = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("ScoreStar.png"));
	pStar->setPosition(ccp(254,60));
	pStar->setVisible(false);
	pScore->addChild(pStar);
	m_vDesStar.push_back(pStar);
	pStar = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("ScoreStar.png"));
	pStar->setPosition(ccp(316,60));
	pStar->setVisible(false);
	pScore->addChild(pStar);
	m_vDesStar.push_back(pStar);



	m_pLevelScore->setVisible(false);

	this->schedule(schedule_selector(CGameLayer::gameUpdate));
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);

	m_vCurPlaneData = CGlobalData::getSingleton()->getLevelPlaneData(m_sCurData.mLevel);
	it = m_vCurPlaneData.begin();

	m_vCurLandData = CGlobalData::getSingleton()->getLevelLandData(m_sCurData.mLevel);
	ite = m_vCurLandData.begin();
	
	m_eCurState = GS_RUN;

	Music::playLevel_1_BgMusic();


	//云层
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d.png", "Cloud_", i+1);
		CLOUD_DATA mData;
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		mData.mDirection = ccp(0.0f, -1.0f);
		mData.mSpeed = CCRANDOM_0_1() * 300.0f + 300.0f;
		mData.mCloud = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
		mData.mCloud->setScale(CCRANDOM_0_1() * 1.5f + 1.5f);
		mData.mCloud->setRotation(((int)(CCRANDOM_0_1() * 4.0f)) * 90.0f);
		mData.mCloud->setOpacity(170);
		mData.mIsMove = false;
		mData.mCloud->setPosition(ccp(mScreenSize.width * CCRANDOM_0_1(), mScreenSize.height + mData.mCloud->getContentSize().height));
		addChild(mData.mCloud,HCLOUD_ZORDER);
		m_vHightCloudVector.push_back(mData);
	}
	m_vHightCloudVector[0].mIsMove = true;

	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d.png", "Cloud_", (i%4)+1);
		CLOUD_DATA mData;
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		mData.mDirection = ccp(0.0f, -1.0f);
		mData.mSpeed = CCRANDOM_0_1() * 100.0f + 100.0f;
		mData.mCloud = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
		mData.mCloud->setScale(CCRANDOM_0_1() * 0.25f + 0.25f);
		mData.mCloud->setRotation(((int)(CCRANDOM_0_1() * 4.0f)) * 90.0f);
		//mData.mCloud->setOpacity(125);
		mData.mIsMove = true;
		mData.mCloud->setPosition(ccp(mScreenSize.width * CCRANDOM_0_1(), CCRANDOM_0_1() * mScreenSize.height * 2.0f));
		addChild(mData.mCloud,LCLOUD_ZORDER);
		m_vLowCloudVector.push_back(mData);
	}

	if (CGlobalData::getSingleton()->isGravityControl())
	{
		setAccelerometerEnabled(true);
	}


	//m_pTempX = CCLabelAtlas::create("0.0", "font/game_num.png", 16, 24, '.');
	//m_pTempX->setAnchorPoint(ccp(0.0f,0.5f));
	//m_pTempX->setPosition(ccp(mScreenSize.width * 0.1f,mScreenSize.height * 0.5f));
	//addChild(m_pTempX,GAMEUI_ZORDER);

	//m_pTempY = CCLabelAtlas::create("0.0", "font/game_num.png", 16, 24, '.');
	//m_pTempY->setAnchorPoint(ccp(0.0f,0.5f));
	//m_pTempY->setPosition(ccp(mScreenSize.width * 0.5f,mScreenSize.height * 0.5f));
	//addChild(m_pTempY,GAMEUI_ZORDER);

	setKeypadEnabled(true);
	return true;
}

void CGameLayer::keyBackClicked()
{
	if (m_pPauseBG->isVisible())
	{
		continueCallback(NULL);
	}
	else if (m_pMenuItemFail->isVisible())
	{
		backMainCallback(NULL);
	}
	else if (!m_pPauseBG->isVisible())
	{
		pauseCallback(NULL);
	}
}

void CGameLayer::pauseCallback(CCObject* sender)
{
	Music::playClickEffect();
	Music::pauseBackgroundMusic();

	CCDirector::sharedDirector()->pause();
	m_pMenuItemPause->setEnabled(false);
	m_pSupperBomb->setEnabled(false);
	m_pPauseBG->setVisible(true);
	m_pMenuBackMain->setVisible(true);
	m_pMenuContinue->setVisible(true);
}

void CGameLayer::backMainCallback(CCObject* sender)
{
	Music::playClickEffect();

	if (m_eCurState == GS_COUNTSCORE)
	{
		CGlobalData::getSingleton()->convertAllRewardScore();
		CGlobalData::getSingleton()->setRewardByLevel(m_sCurData.mLevel);
	}

	if (CGlobalData::getSingleton()->isLevelClear() && CGlobalData::getSingleton()->getCurLevelData().mLevel != 7)
	{
		CGlobalData::getSingleton()->setLevelID(CGlobalData::getSingleton()->getCurLevelData().mLevel);
		CCScene *pScene = CMissionScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
		CCDirector::sharedDirector()->resume();
		return ;
	}
	CCScene *pScene = CMainUIScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	CCDirector::sharedDirector()->resume();
}

void CGameLayer::continueCallback(CCObject* sender)
{
	Music::playClickEffect();
	Music::resumeBackgroundMusic();
	
	CCDirector::sharedDirector()->resume();
	m_pMenuItemPause->setEnabled(true);
	m_pSupperBomb->setEnabled(true);
	m_pMenuBackMain->setVisible(false);
	m_pMenuContinue->setVisible(false);
	m_pPauseBG->setVisible(false);
}

void CGameLayer::fireBombCallback(CCObject* sender)
{
	if (m_pBombTime->getPercentage() > 99.0f)
	{
		CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CGameLayer::fireSuperBomb));
		runAction((CCActionInterval*)(CCSequence::create(pCallback, CCDelayTime::create(0.1f),pCallback, 
			CCDelayTime::create(0.1f),pCallback, 
			CCDelayTime::create(0.1f),pCallback,
			CCDelayTime::create(0.1f),pCallback,
			CCDelayTime::create(0.1f),pCallback,
			CCDelayTime::create(0.1f),pCallback,
			CCDelayTime::create(0.1f),pCallback,
			CCDelayTime::create(0.1f),pCallback,
			CCDelayTime::create(0.1f),pCallback,
			NULL) ));
		CGlobalData::getSingleton()->resetBombPercentage();
	}

}

void CGameLayer::fireSuperBomb(void)
{
	CSuperBomb *pBomb = CSuperBomb::createSuperBomb();
	addChild(pBomb, BOMB_ZORDER);
}

bool CGameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	if (CGlobalData::getSingleton()->isDoubleControl() && m_fLevelTime - m_fFirstTime < DOUBLE_TIME)
	{
		m_pPlayer->usingHoldItem();
	}

	m_fFirstTime = m_fLevelTime;

	CCSize  size = CCDirector::sharedDirector()->getWinSize();
	if (pTouch->getLocation().y < size.height - BANNER_HEIGHT)
	{
		m_pPlayer->setTargetPoint(ccpAdd(pTouch->getLocation(), ccp(0,TOUCH_OFFSET)));
	}

	return true;
}
void CGameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCSize  size = CCDirector::sharedDirector()->getWinSize();
	if (pTouch->getLocation().y < size.height - BANNER_HEIGHT)
	{
		m_pPlayer->setTargetPoint(ccpAdd(pTouch->getLocation(), ccp(0,TOUCH_OFFSET)));
	}
}
void CGameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	;
}

void CGameLayer::didAccelerate(CCAcceleration* pAccelerationValue)
{
	//char szName[128] = {0};
	//sprintf(szName, "%d", (int)pAccelerationValue->x * 10000);
	//m_pTempX->setString(szName);

	//sprintf(szName, "%d", (int)pAccelerationValue->y * 10000);
	//m_pTempY->setString(szName);
	
	if (CGlobalData::getSingleton()->isGravityControl() && m_pPlayer)
	{
		m_pPlayer->setGravityOffset(ccp(pAccelerationValue->x, pAccelerationValue->y));
	}
	CCLayer::didAccelerate(pAccelerationValue);
}

void CGameLayer::gameUpdate(float fEscapeTime)
{
	
	CGlobalData::getSingleton()->upDateGameTime(fEscapeTime);
	switch(m_eCurState)
	{
	case GS_DEFAULT:
		break;
	case GS_INIT:
		break;
	case GS_RUN:
		moveMap(fEscapeTime);
		moveCloud(fEscapeTime);

		m_fLevelTime += fEscapeTime;
		if (m_fLevelTime > m_sCurData.mBossTime)
		{
			int nLevel = m_sCurData.mLevel;
			if (nLevel == 8)
			{
				nLevel = 2 + (int)(CCRANDOM_0_1() * 6.0f);
				CGlobalData::getSingleton()->setEndlessBossID(nLevel);
			}
			switch(nLevel)
			{
			case 1:
				{
					CBoss *pBoss = CBoss::createBoss(BOK_LEVEL01);
					addChild(pBoss, BOSS_ZORDER);
				}
				break;
			case 2:
				{
					CBossTwo *pBoss = CBossTwo::createBoss();
					addChild(pBoss, BOSS_ZORDER);
				}
				break;
			case 3:
				{
					CBossThree *pBoss = CBossThree::createBoss();
					addChild(pBoss, BOSS_ZORDER);
				}
				break;
			case 4:
				{
					CBossFour *pBoss = CBossFour::createBoss();
					addChild(pBoss, BOSS_ZORDER);
				}
				break;
			case 5:
				{
					CBossFive *pBoss = CBossFive::createBoss();
					addChild(pBoss, BOSS_ZORDER);
				}
				break;
			case 6:
				{
					CBossSix *pBoss = CBossSix::createBoss();
					addChild(pBoss, BOSS_ZORDER);
				}
				break;
			case 7:
				{
					CBossSeven *pBoss = CBossSeven::createBoss();
					addChild(pBoss, BOSS_ZORDER);
				}
				break;

			}

			m_eCurState = GS_BOSS;
		}

		if (it != m_vCurPlaneData.end())
		{
			if (m_fLevelTime > (*it).m_fTime)
			{
				switch((*it).mKind)
				{
				case EK_DEFAULT:
				case EK_PLANE02:
				case EK_PLANE03:
				case EK_PLANE04:
					{
						CEnemySprite *pSprite = CEnemySprite::createEnemy((*it).mKind, (*it));
						addChild(pSprite, AIR_ZORDER);
					}
					break;
				case EK_AIRMINE:
					{
						CEnemySprite *pSprite = CEnemySprite::createEnemy((*it).mKind, (*it), EW_AIRMINE);
						addChild(pSprite, AIR_ZORDER);
					}
					break;
				case EK_ARMOR:
					{
						CEnemySprite *pSprite = CEnemySprite::createEnemy((*it).mKind, (*it), EW_HOLDFIRE);
						addChild(pSprite, AIR_ZORDER);
					}
					break;
				case EK_HELI01:
				case EK_HELI02:
					{
						CHelicopterSprite *pHeli = CHelicopterSprite::createHeli((*it).mKind, (*it));
						addChild(pHeli, AIR_ZORDER);
					}
					break;
				}
				CGlobalData::getSingleton()->addAirScore((*it).mKind);
				m_vCurPlaneData.erase(it);
				it = m_vCurPlaneData.begin();
			}
		}

		if (ite != m_vCurLandData.end())
		{
			if (m_fLevelTime > (*ite).m_fTime)
			{
				CArmySprite *pArmy = CArmySprite::createArmy((*ite).mKind, (*ite));
				addChild(pArmy, ARMY_ZORDER);
				CGlobalData::getSingleton()->addArmyScore((*ite).mKind);
				m_vCurLandData.erase(ite);
				ite = m_vCurLandData.begin();
			}
		}

		playerUpdate();
		break;
	case GS_BOSS:
		moveMap(fEscapeTime);
		moveCloud(fEscapeTime);
		playerUpdate();
		CGlobalData::getSingleton()->recordDropTime();
		break;
	case GS_AUTOFLY:
		if (m_pAirport->getPositionY() < mScreenSize.height - m_pAirport->getContentSize().height * 0.5f - TOUCH_OFFSET)
		{
			m_eCurState = GS_LANDING;
			break;
		}
		moveMap(fEscapeTime);
		moveCloud(fEscapeTime);
		m_pAirport->setPosition(ccpAdd(m_pAirport->getPosition(), ccpMult(m_tDirection, fEscapeTime * m_sCurData.mMapSpeed)));
		break;
	case GS_LANDING:
		{
			//moveMap(fEscapeTime);
			moveCloud(fEscapeTime);
			m_pPlayer->runLand(ccp(mScreenSize.width * 0.5f, m_pAirport->getPositionY() + m_pAirport->getContentSize().height * 0.25f));
			m_eCurState = GS_SCORE;
		}
		break;
	case GS_SCORE:
		//moveMap(fEscapeTime);
		moveCloud(fEscapeTime);
		m_fTime += fEscapeTime;
		if (m_fTime > 2.0f)
		{
			scoreCurLevel();
		}
		break;
	case GS_COUNTSCORE:
		{
			m_fTime += fEscapeTime;
			if (m_fTime < 1.0f)
			{
				break;
			}

			if (m_fTime > 1.1f)
			{
				m_fTime = 1.0f;
				bool bFinish = CGlobalData::getSingleton()->convertRewardScore();
				if (bFinish)
				{
					m_eCurState = GS_END;
					CGlobalData::getSingleton()->setRewardByLevel(m_sCurData.mLevel);
				}
				char szName[128] = {0};
				sprintf(szName, "%07d", CGlobalData::getSingleton()->getCurScore());
				m_pScoreNum->setString(szName);
				sprintf(szName, "%02d", CGlobalData::getSingleton()->getCurPoint());
				m_pLevelXP->setString(szName);
				sprintf(szName, "%07d", CGlobalData::getSingleton()->getCurRewardScore());
				m_pRewarPoint->setString(szName);
				sprintf(szName, "%02d", CGlobalData::getSingleton()->getCurRewardPoint());
				m_pRewardXP->setString(szName);
			}
		}

		break;
	}

	char szName[128] = {0};
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getCurScore());
	m_pMenuFontScore->setString(szName);
	sprintf(szName, "%02d", CGlobalData::getSingleton()->getRocket());
	m_pMenuFontRocket->setString(szName);

	if (m_eCurState < GS_AUTOFLY)
	{
		m_pBombTime->setPercentage(CGlobalData::getSingleton()->getBombPercentage());
	}

	if (m_eHoldItem != CGlobalData::getSingleton()->getHoldItem())
	{
		m_eHoldItem = CGlobalData::getSingleton()->getHoldItem();
		setHoldItem(m_eHoldItem);
		if (m_eHoldItem == IK_DEFAULT)
		{
			m_pHoldSpirte->setVisible(false);
		}
	}
}

void CGameLayer::scoreCurLevel(void)
{
	CGlobalData::getSingleton()->countCurLevelReward(m_sCurData.mLevel);
	char szName[128] = {0};
	sprintf(szName, "%07d", CGlobalData::getSingleton()->getCurScore());
	m_pLevelScore->setVisible(true);
	m_pScoreNum->setString(szName);
	sprintf(szName, "%02d", CGlobalData::getSingleton()->getCurPoint());
	m_pLevelXP->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_DEFAULT),CGlobalData::getSingleton()->getAirScoreByIndex(EK_DEFAULT));
	m_pLevelPlane01->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_PLANE02),CGlobalData::getSingleton()->getAirScoreByIndex(EK_PLANE02));
	m_pLevelPlane02->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_PLANE03),CGlobalData::getSingleton()->getAirScoreByIndex(EK_PLANE03));
	m_pLevelPlane03->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_PLANE04),CGlobalData::getSingleton()->getAirScoreByIndex(EK_PLANE04));
	m_pLevelPlane04->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_HELI01),CGlobalData::getSingleton()->getAirScoreByIndex(EK_HELI01));
	m_pLevelPlane05->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesArmyScoreByIndex(AK_DEFAULT),CGlobalData::getSingleton()->getArmyScoreByIndex(AK_DEFAULT));
	m_pLevelPlane06->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_HELI02),CGlobalData::getSingleton()->getAirScoreByIndex(EK_HELI02));
	m_pLevelPlane07->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_AIRMINE),CGlobalData::getSingleton()->getAirScoreByIndex(EK_AIRMINE));
	m_pLevelPlane08->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesAirScoreByIndex(EK_ARMOR),CGlobalData::getSingleton()->getAirScoreByIndex(EK_ARMOR));
	m_pLevelPlane09->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesArmyScoreByIndex(AK_GREENGUN01),CGlobalData::getSingleton()->getArmyScoreByIndex(AK_GREENGUN01));
	m_pLevelPlane10->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesArmyScoreByIndex(AK_BATTERY01),CGlobalData::getSingleton()->getArmyScoreByIndex(AK_BATTERY01));
	m_pLevelPlane11->setString(szName);
	sprintf(szName, "%03d/%03d", CGlobalData::getSingleton()->getDesArmyScoreByIndex(AK_BUNKER01),CGlobalData::getSingleton()->getArmyScoreByIndex(AK_BUNKER01));
	m_pLevelPlane12->setString(szName);
	sprintf(szName, "%03d", CGlobalData::getSingleton()->getDesPercentage());
	m_pDesPercentage->setString(szName);

	sprintf(szName, "%07d", CGlobalData::getSingleton()->getCurRewardScore());
	m_pRewarPoint->setString(szName);

	sprintf(szName, "%02d", CGlobalData::getSingleton()->getCurRewardPoint());
	m_pRewardXP->setString(szName);
	for (unsigned int i=0;i<CGlobalData::getSingleton()->getDesPercentage() / 20;i++)
	{
		m_vDesStar[i]->setVisible(true);
	}
	m_pMenuItemFail->setVisible(true);
	m_pMenuItemPause->setVisible(false);
	m_pSupperBomb->setVisible(false);
	m_eCurState = GS_COUNTSCORE;
	m_fTime = 0.0f;
}

void CGameLayer::playerUpdate(void)
{
	if (m_pPlayer != NULL)
	{
		m_pMenuItemHP->setPercentage(100.0f * m_pPlayer->getHPPercentage());
	}

	char szName[128] = {0};
	if (CGlobalData::getSingleton()->getLife() == 0 && m_pPlayer->getCurState() >= PS_HIDE)
	{
		//m_pMenuItemFail->setVisible(true);
		m_pMenuItemPause->setEnabled(false);
		m_pSupperBomb->setEnabled(false);
		CCDirector::sharedDirector()->pause();
		//m_pFailSprite->setVisible(true);
		sprintf(szName, "%sFailScoreTitle.png", m_sPrefix);
		m_pScoreTitle->setDisplayFrame(m_pCurCache->spriteFrameByName(szName));
		scoreCurLevel();
		//m_eCurState = GS_SCORE;
	}

	else if (m_pPlayer->getCurState() >= PS_HIDE)
	{
		CGlobalData::getSingleton()->reduceLife();
		CGlobalData::getSingleton()->resetPlayerData();
		removeChild(m_pPlayer, true);
		m_pPlayer = CPlayerSprite::createPlayer(CGlobalData::getSingleton()->getSelectKind());
		addChild(m_pPlayer, PLAYER_ZORDER);
	}

	
	sprintf(szName, "%d", CGlobalData::getSingleton()->getLife());
	m_pMenuFontLife->setString(szName);

	//检测是否通过该关卡
	if (CGlobalData::getSingleton()->isLevelClear())
	{
		setLevelEnd();
	}

	//检测是否重置无尽模式数据
	if (CGlobalData::getSingleton()->isRefreshEndlessData())
	{
		m_vCurPlaneData = CGlobalData::getSingleton()->getLevelPlaneData(m_sCurData.mLevel);
		it = m_vCurPlaneData.begin();

		m_vCurLandData = CGlobalData::getSingleton()->getLevelLandData(m_sCurData.mLevel);
		ite = m_vCurLandData.begin();

		CGlobalData::getSingleton()->resetRefreshData(false);

		m_fLevelTime = 0.0f;
		m_eCurState = GS_RUN;
	}
}

void CGameLayer::setLevelEnd(void)
{
	m_eCurState = GS_AUTOFLY;
	m_pPlayer->setAutoFly();
	reorderChild(m_pPlayer, BOMB_ZORDER);
	m_pAirport = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Airport.png"));
	m_pAirport->setPosition(ccp(mScreenSize.width * 0.5f, mScreenSize.height + m_pAirport->getContentSize().height * 0.5f));
	addChild(m_pAirport, MAP_ZORDER);
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel % 4 != 1)
	{
		m_pAirport->setVisible(false);
	}
	//m_pPlayer->runAction(CCMoveTo::create(1.0f, ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.2f)));
}

void CGameLayer::moveMap(float fEscapeTime)
{
	for (unsigned int i=0; i<m_vMapSpriteVector.size(); i++)
	{
		m_vMapSpriteVector[i]->setPosition(ccpAdd(m_vMapSpriteVector[i]->getPosition(), ccpMult(m_tDirection, fEscapeTime * m_sCurData.mMapSpeed)));
	}

	if (m_vMapSpriteVector.size() > 1 && m_vMapSpriteVector[0]->getPosition().y < -mScreenSize.height * 0.5f)
	{
		CCSprite* pSprite = m_vMapSpriteVector.back();
		m_vMapSpriteVector[0]->setPositionY(pSprite->getPosition().y + mScreenSize.height);
		m_vMapSpriteVector.push_back(m_vMapSpriteVector[0]);
		m_vMapSpriteVector.erase(m_vMapSpriteVector.begin());
	}
}

void CGameLayer::moveCloud(float fEscapeTime)
{
	for (unsigned int i=0; i<m_vHightCloudVector.size(); i++)
	{
		if (m_vHightCloudVector[i].mIsMove)
		{
			m_vHightCloudVector[i].mCloud->setPosition(ccpAdd(m_vHightCloudVector[i].mCloud->getPosition(), ccpMult(m_vHightCloudVector[i].mDirection, fEscapeTime * m_vHightCloudVector[i].mSpeed)));

			if (m_vHightCloudVector[i].mCloud->getPosition().y < -m_vHightCloudVector[i].mCloud->getContentSize().height * 0.5f)
			{
				m_vHightCloudVector[i].mSpeed = CCRANDOM_0_1() * 300.0f + 300.0f;
				m_vHightCloudVector[i].mCloud->setScale(CCRANDOM_0_1() * 1.5f + 1.5f);
				m_vHightCloudVector[i].mCloud->setRotation(((int)(CCRANDOM_0_1() * 4.0f)) * 90.0f);
				m_vHightCloudVector[i].mCloud->setPosition(ccp(mScreenSize.width * CCRANDOM_0_1(), mScreenSize.height + m_vHightCloudVector[i].mCloud->getContentSize().height));

				m_vHightCloudVector[i].mIsMove = false;
				if (i == m_vHightCloudVector.size() - 1)
				{
					m_vHightCloudVector[0].mIsMove = true;
				}
				else
				{
					m_vHightCloudVector[i+1].mIsMove = true;
				}
			}
			break;
		}

	}

	for (unsigned int i=0; i<m_vLowCloudVector.size(); i++)
	{
		if (m_vLowCloudVector[i].mIsMove)
		{
			m_vLowCloudVector[i].mCloud->setPosition(ccpAdd(m_vLowCloudVector[i].mCloud->getPosition(), ccpMult(m_vLowCloudVector[i].mDirection, fEscapeTime * m_vLowCloudVector[i].mSpeed)));

			if (m_vLowCloudVector[i].mCloud->getPosition().y < -m_vLowCloudVector[i].mCloud->getContentSize().height * 0.5f)
			{
				m_vLowCloudVector[i].mSpeed = CCRANDOM_0_1() * 100.0f + 100.0f;
				m_vLowCloudVector[i].mCloud->setScale(CCRANDOM_0_1() * 0.25f + 0.25f);
				m_vLowCloudVector[i].mCloud->setRotation(((int)(CCRANDOM_0_1() * 4.0f)) * 90.0f);
				m_vLowCloudVector[i].mCloud->setPosition(ccp(mScreenSize.width * CCRANDOM_0_1(), mScreenSize.height * CCRANDOM_0_1() + mScreenSize.height + m_vLowCloudVector[i].mCloud->getContentSize().height));
			}
		}

	}
}

void CGameLayer::setHoldItem(ITEM_KINDS eKind)
{
	char szName[DATA_LENTH_MAX] = {0};
	switch(eKind)
	{
	case IK_IRONCURTAIN:
		sprintf(szName, "Item_IronCurtain_01.png");
		break;
	case IK_FIREBALL:
		sprintf(szName, "Item_FireBall_01.png");
		break;
	case IK_SHIELDTAKEN:
		sprintf(szName, "Item_ShieldTaken_01.png");
		break;
	case IK_SUPERGUN:
		sprintf(szName, "Item_SuperGun_01.png");
		break;
	case IK_WINGMAN:
		sprintf(szName, "Item_WingMan_01.png");
		break;
	}

	if (m_pCurCache->spriteFrameByName(szName) != NULL)
	{
		m_pHoldSpirte->setDisplayFrame(m_pCurCache->spriteFrameByName(szName));
		m_pHoldSpirte->setVisible(true);
	}
}
