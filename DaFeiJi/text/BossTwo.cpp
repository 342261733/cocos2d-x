#include "BossTwo.h"

CBossTwo::CBossTwo(void)
{
	Music::stopBackgroundMusic(false);	
}

CBossTwo::~CBossTwo(void)
{
}

CBossTwo* CBossTwo::createBoss(void)
{
	CBossTwo *pBoss = new CBossTwo();
	pBoss->createSprite();
	pBoss->setTag(BOSS_TYPE);
	//pBoss->m_eBossKind = eKind;
	return pBoss;
}

void CBossTwo::createSprite(void)
{
	Music::playWarnEffect();

	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	this->schedule(schedule_selector(CBossTwo::bossUpdate));
}

bool CBossTwo::isCheck(void)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02)
	{
		return true;
	}
	return false;
}

CCRect CBossTwo::getCurBoundbox(void)
{
	return boundingBox();
}

void CBossTwo::onEnter(void)
{
	setAnchorPoint(ccp(0.5f,0.5f));
	setContentSize(CCSizeMake(70,253));
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_Base.png"));
	m_pBaseSprite->setAnchorPoint(ccp(0.5f,0.5f));
	addChild(m_pBaseSprite, BOSS_ZORDER);
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	m_pPropeller = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_Propeller.png"));
	m_pPropeller->setPosition(ccp(m_pBaseSprite->getContentSize().width * 0.5f, m_pBaseSprite->getContentSize().height * 0.387f));
	m_pBaseSprite->addChild(m_pPropeller);
	m_pPropeller->runAction(CCRepeatForever::create((CCActionInterval*)CCRotateBy::create(0.5f,360.0f)));

	m_pLeftWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WL02_01.png"));
	m_pLeftWeapon->setPosition(ccp(m_pBaseSprite->getContentSize().width * 0.5f, m_pBaseSprite->getContentSize().height * (0.5f -  0.229f)));
	addChild(m_pLeftWeapon, BOSS_ZORDER - 1);

	m_pRightWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WR02_01.png"));
	m_pRightWeapon->setPosition(ccp(m_pBaseSprite->getContentSize().width * 0.5f, m_pBaseSprite->getContentSize().height * (0.5f -  0.229f)));
	addChild(m_pRightWeapon, BOSS_ZORDER - 1);

	m_pExplode = CCSprite::create();
	m_pExplode->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	addChild(m_pExplode, BOSS_ZORDER);
	//m_pBaseSprite->setPosition(ccp(200.0f, 600.0f));
	//m_pLeftPos = CCNode::create();
	//getParent()->addChild()
	m_pLeftFlashSprite = NULL;
	m_pRightFlashSprite = NULL;
	m_pLeftExplode = NULL;
	m_pRightExplode = NULL;

	m_nBossHP = BOSSTWO_STAGE01_HP;
	m_fEnemyTime = 0.0f;


	m_fShotFireSlot = B2FIRE_SLOT;
	m_fFireRound = 0.0f;
	m_nFireNum = 0;
	m_fNomalFireRound = 0.0f;
	m_nNomalFireNum = 0;


	//执行出场流程
	setPosition(ccp(240.0f, mScreenSize.height + m_pBaseSprite->getContentSize().height - BANNER_HEIGHT));
	setScale(0.2f);
	//延时
	CCDelayTime *pDelayTime = CCDelayTime::create(3.0f);
	//飞出
	CCMoveTo *pMoveDown = CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f - BANNER_HEIGHT));
	//放大
	CCScaleTo *pScaleTo = CCScaleTo::create(3.0f, 1.0f);
	//后退
	CCMoveTo *pMoveBack =CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.7f - BANNER_HEIGHT));
	//合成（放大+后退）
	CCAction *pSpawn = CCSpawn::create(pScaleTo, pMoveBack,NULL);
	//展开武器回调
	CCCallFunc *pFlareWeapon = CCCallFunc::create(this, callfunc_selector(CBossTwo::flareWeapon));
	//飞到指定位置
	CCMoveTo *pMoveLeft = CCMoveTo::create(0.5f,ccp(mScreenSize.width * 0.3f, mScreenSize.height * 0.7f - BANNER_HEIGHT));
	//回调
	CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossTwo::bossCallback));

	//序列
	//CCSequence *pSequence = CCSequence::create(pDelayTime,pMoveDown,pScaleTo,pMoveLeft,pCallback,NULL);
	runAction(CCSequence::create(pDelayTime,pMoveDown,pSpawn,pFlareWeapon,pDelayTime,pMoveLeft,pCallback,NULL));


	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
	m_sBaseColor = pRGBAProtocol->getColor();
	m_fFlashTime = 0.0f;
	m_bBaseNormal = true;
	m_eCurStage = STAGE_READY01;

	Music::playBoss_1_BgMusic();

	CCNode::onEnter();
}

void CBossTwo::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}


void CBossTwo::bossUpdate(float fEscapeTime)
{
	switch(m_eCurStage)
	{
	case STAGE_DEFAULT:
		break;
	case STAGE_ACTION01:
		{
			//underAttack(2);
			m_fTime += fEscapeTime;
			//if (m_fTime >= STAGE01_SLOT && m_fFireRound <= STAGE01_COOL - 0.5f)
			//{
			//	m_fTime = 0.0f;

			//	BULLET_DATA mData;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 150.0f;
			//	for (int i=0;i<STAGE01_BULLETNUM;i++)
			//	{
			//		CCPoint mDirect = ccpNormalize(ccp(-1.0f, -1.0f));
			//		mData.mDirection = ccpRotateByAngle(mDirect, ccp(0,0), CC_DEGREES_TO_RADIANS(90.0f / (STAGE01_BULLETNUM - 1) * i));
			//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
			//		CCPoint mWorldPos = convertToWorldSpace(m_pLeftWeapon->getPosition());
			//		pBullet->setPosition(ccpAdd(mWorldPos, ccp(-10.0f, -28.0f)));
			//		getParent()->addChild(pBullet, ABULLET_ZORDER);

			//		if (m_pLeftFlashSprite)
			//		{
			//			removeChild(m_pLeftFlashSprite, true);
			//			m_pLeftFlashSprite = NULL;
			//		}
			//		m_pLeftFlashSprite = CCSprite::create();
			//		m_pLeftFlashSprite->setPosition(ccpAdd(m_pLeftWeapon->getPosition(), ccp(-10.0f, -28.0f)));
			//		addChild(m_pLeftFlashSprite);

			//		CCAnimation *pAnimation = CCAnimation::create();

			//		char szName[128] = {0};

			//		for (int i=0; i<ANIMATE_MAX; i++)
			//		{
			//			sprintf(szName, "Flash02_%02d.png", i+1);
			//			if (m_pCurCache->spriteFrameByName(szName) == NULL)
			//			{
			//				break;
			//			}
			//			pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
			//		}


			//		pAnimation->setDelayPerUnit(0.015f);
			//		pAnimation->setRestoreOriginalFrame(true);

			//		CCAnimate *pAnimate = CCAnimate::create(pAnimation);
			//		m_pLeftFlashSprite->runAction(pAnimate);
			//	}

			//	for (int i=0;i<STAGE01_BULLETNUM;i++)
			//	{
			//		CCPoint mDirect = ccpNormalize(ccp(-1.0f, -1.0f));
			//		mData.mDirection = ccpRotateByAngle(mDirect, ccp(0,0), CC_DEGREES_TO_RADIANS(90.0f / (STAGE01_BULLETNUM - 1) * i));
			//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
			//		CCPoint mWorldPos = convertToWorldSpace(m_pRightWeapon->getPosition());
			//		pBullet->setPosition(ccpAdd(mWorldPos, ccp(10.0f, -28.0f)));
			//		getParent()->addChild(pBullet, ABULLET_ZORDER);

			//		if (m_pRightFlashSprite)
			//		{
			//			removeChild(m_pRightFlashSprite, true);
			//			m_pRightFlashSprite = NULL;
			//		}
			//		m_pRightFlashSprite = CCSprite::create();
			//		m_pRightFlashSprite->setPosition(ccpAdd(m_pRightWeapon->getPosition(), ccp(10.0f, -28.0f)));
			//		addChild(m_pRightFlashSprite);

			//		CCAnimation *pAnimation = CCAnimation::create();

			//		char szName[128] = {0};

			//		for (int i=0; i<ANIMATE_MAX; i++)
			//		{
			//			sprintf(szName, "Flash02_%02d.png", i+1);
			//			if (m_pCurCache->spriteFrameByName(szName) == NULL)
			//			{
			//				break;
			//			}
			//			pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
			//		}


			//		pAnimation->setDelayPerUnit(0.015f);
			//		pAnimation->setRestoreOriginalFrame(true);

			//		CCAnimate *pAnimate = CCAnimate::create(pAnimation);
			//		m_pRightFlashSprite->runAction(pAnimate);
			//	}
			//}

			m_fShotFireSlot += fEscapeTime;
			m_fFireRound += fEscapeTime;
			if (m_fFireRound > STAGE01_COOL && m_fShotFireSlot > B2FIRE_SLOT)
			{
				m_fShotFireSlot = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 10;
				mData.mMoveSpeed = 200.0f;
				for (int i=0;i<B2BULLET_NUM;i++)
				{
					mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * i));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
					pBullet->setPosition(getPosition());
					getParent()->addChild(pBullet, ABULLET_ZORDER);
				}


				m_nFireNum ++;

				if (m_nFireNum >= B2FIRE_NUM)
				{
					m_fFireRound = 0.0f;
					m_nFireNum = 0;
				}
			}

		}
		break;
	case STAGE_ACTION02:
		{
			//m_fTime += fEscapeTime;
			//m_fNomalFireRound += fEscapeTime;
			//if (m_fTime >=STAGE02_NOMALSLOT && m_fNomalFireRound > STAGE02_NOMALCOOL)
			//{
			//	m_fTime = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mAttack = 10;
			//	mData.mMoveSpeed = 200.0f;
			//	mData.mDirection = ccp(0.0f, -1.0f);
			//	CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_SUPERGUN);
			//	pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.5f));
			//	getParent()->addChild(pBullet, ABULLET_ZORDER);
			//	m_nNomalFireNum ++;

			//	if (m_nNomalFireNum >= STAGE02_NOMALFIRENUM)
			//	{
			//		m_fNomalFireRound = 0.0f;
			//		m_nNomalFireNum = 0;
			//	}
			//}

			m_fShotFireSlot += fEscapeTime;
			m_fFireRound += fEscapeTime;
			if (m_fFireRound > STAGE02_COOL && m_fShotFireSlot > STAGE02_SLOT)
			{
				m_fShotFireSlot = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 10;
				mData.mMoveSpeed = 140.0f;
				for (int i=0;i<1;i++)
				{
					mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * m_nFireNum));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
					pBullet->setPosition(m_pLeftWeapon->getPosition());
					getParent()->addChild(pBullet, ABULLET_ZORDER);
				}

				for (int i=0;i<1;i++)
				{
					mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * m_nFireNum));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
					pBullet->setPosition(m_pRightWeapon->getPosition());
					getParent()->addChild(pBullet, ABULLET_ZORDER);
				}
				m_nFireNum ++;

				if (m_nFireNum >= STAGE02_FIRENUM)
				{
					m_fFireRound = 0.0f;
					m_nFireNum = 0;
				}
			}
		}
		break;
	case STAGE_ACTION03:
		break;
	case STAGE_ACTION04:
		break;
	case STAGE_ACTION05:
		break;
	}

	if (!m_bBaseNormal)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
			pRGBAProtocol->setColor(m_sBaseColor);
			m_bBaseNormal = true;
		}
	}

	//酱油飞机
	m_fEnemyTime += fEscapeTime;
	if (m_fEnemyTime > LACKEY_TIME)
	{
		m_fEnemyTime = 0.0f;
		FLY_DATA mFdata;
		mFdata.mKind = (ENEMY_KINDS)((int)(CCRANDOM_0_1() * 4));
		mFdata.m_fTime = 4.0f;
		mFdata.mAttitude = FA_DEFAULT;
		mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
		mFdata.mPosition = CGlobalData::getSingleton()->getPosByFlyAttitude(mFdata.mAttitude);
		CEnemySprite *pSprite = CEnemySprite::createEnemy(mFdata.mKind, mFdata);
		getParent()->addChild(pSprite, AIR_ZORDER);
		CGlobalData::getSingleton()->addAirScore(mFdata.mKind);
	}

	//三子弹
	//环形散弹
	//if (m_fFireRound > B2FIRE_COOL && m_fShotFireSlot > B2FIRE_SLOT)
	//{
	//	m_fShotFireSlot = 0.0f;
	//	BULLET_DATA mData;
	//	mData.mAttack = 5;
	//	mData.mMoveSpeed = 250.0f;
	//	for (int i=0;i<B2BULLET_NUM;i++)
	//	{
	//		mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * i));
	//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
	//		pBullet->setPosition(m_pBaseSprite->boundingBox().origin);
	//		getParent()->addChild(pBullet, BBULLET_ZORDER);
	//	}

	//	for (int i=0;i<B2BULLET_NUM;i++)
	//	{
	//		mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * i));
	//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
	//		pBullet->setPosition(ccp(280.0f, 600.0f));
	//		getParent()->addChild(pBullet, BBULLET_ZORDER);
	//	}
	//	m_nFireNum ++;

	//	if (m_nFireNum >= B2FIRE_NUM)
	//	{
	//		m_fFireRound = 0.0f;
	//		m_nFireNum = 0;
	//	}
	//}

	//螺旋散弹
	//if (m_fFireRound > B2FIRE_COOL && m_fShotFireSlot > B2FIRE_SLOT)
	//{
	//	m_fShotFireSlot = 0.0f;
	//	BULLET_DATA mData;
	//	mData.mAttack = 5;
	//	mData.mMoveSpeed = 140.0f;
	//	for (int i=0;i<1;i++)
	//	{
	//		mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * m_nFireNum));
	//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
	//		pBullet->setPosition(m_pBaseSprite->getPosition());
	//		getParent()->addChild(pBullet, BBULLET_ZORDER);
	//	}

	//	for (int i=0;i<1;i++)
	//	{
	//		mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * m_nFireNum));
	//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
	//		pBullet->setPosition(m_pBaseSprite->getPosition());
	//		getParent()->addChild(pBullet, BBULLET_ZORDER);
	//	}
	//	m_nFireNum ++;

	//	if (m_nFireNum >= B2BULLET_NUM)
	//	{
	//		m_fFireRound = 0.0f;
	//		m_nFireNum = 0;
	//	}
	//}

	//交错弹墙
	//if (m_fFireRound > 1.0f && m_fShotFireSlot > 0.1f)
	//{
	//	m_fShotFireSlot = 0.0f;
	//	BULLET_DATA mData;
	//	mData.mAttack = 5;
	//	mData.mMoveSpeed = 250.0f;
	//	CGameLayer *pLayer = (CGameLayer*)getParent();
	//	CCPoint ttt = pLayer->getChildByTag(PALYER_TYPE)->boundingBox().origin;
	//	ttt = ccpNormalize(ccpSub(ttt, m_pBaseSprite->getPosition()));
	//	for (int i=0;i<1;i++)
	//	{
	//		mData.mDirection = ccpRotateByAngle(ttt, ccp(0,0), -CC_DEGREES_TO_RADIANS(-15.0f));
	//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
	//		pBullet->setPosition(m_pBaseSprite->getPosition());
	//		getParent()->addChild(pBullet, BBULLET_ZORDER);
	//	}

	//	CCPoint ttt2 = pLayer->getChildByTag(PALYER_TYPE)->boundingBox().origin;
	//	ttt2 = ccpNormalize(ccpSub(ttt, ccp(280.0f, 600.0f)));
	//	for (int i=0;i<1;i++)
	//	{
	//		mData.mDirection = ccpRotateByAngle(ttt2, ccp(0,0), CC_DEGREES_TO_RADIANS(15.0f));
	//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
	//		pBullet->setPosition(ccp(280.0f, 600.0f));
	//		getParent()->addChild(pBullet, BBULLET_ZORDER);
	//	}
	//	m_nFireNum ++;

	//	if (m_nFireNum >= 8)
	//	{
	//		m_fFireRound = 0.0f;
	//		m_nFireNum = 0;
	//	}
	//}
}

void CBossTwo::underAttack(int nHurt)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02)
	{
		if (m_bBaseNormal)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
			pRGBAProtocol->setColor(ccc3(255,0,0));
			m_bBaseNormal = false;

		}
	}

	switch(m_eCurStage)
	{
	case STAGE_ACTION01:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= 0)
			{
				m_eCurStage = STAGE_READY02;
				m_nBossHP = BOSSTWO_STAGE02_HP;
				//停止移动
				stopAction(m_pMoveAction);
				//武器毁坏
				CCPoint mLeftPos = m_pLeftWeapon->getPosition();
				CCPoint mRightPos = m_pRightWeapon->getPosition();
				m_pLeftWeapon->removeFromParentAndCleanup(true);
				m_pRightWeapon->removeFromParentAndCleanup(true);

				m_pLeftWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WL02_02.png"));
				m_pLeftWeapon->setPosition(mLeftPos);
				addChild(m_pLeftWeapon, -1);
				m_pRightWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WR02_02.png"));
				m_pRightWeapon->setPosition(mRightPos);
				addChild(m_pRightWeapon, -1);
				//执行爆炸
				if (m_pLeftExplode)
				{
					m_pLeftExplode->removeFromParentAndCleanup(true);
				}

				m_pLeftExplode = CCSprite::create();
				m_pLeftExplode->setPosition(ccpAdd(m_pLeftWeapon->getPosition(), ccp(-10.0f, -28.0f)));
				addChild(m_pLeftExplode);
				CCAnimation *pAnimation = CCAnimation::create();

				char szName[128] = {0};
				for (int i=0; i<ANIMATE_MAX; i++)
				{
					sprintf(szName, "Explode01_%02d.png", i+1);
					if (m_pCurCache->spriteFrameByName(szName) == NULL)
					{
						break;
					}
					pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
				}


				pAnimation->setDelayPerUnit(0.066f);
				pAnimation->setRestoreOriginalFrame(true);

				CCAnimate *pAnimate = CCAnimate::create(pAnimation);
				CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
				m_pLeftExplode->runAction(pAction);

				if (m_pRightExplode)
				{
					m_pRightExplode->removeFromParentAndCleanup(true);
				}

				m_pRightExplode = CCSprite::create();
				m_pRightExplode->setPosition(ccpAdd(m_pRightWeapon->getPosition(), ccp(10.0f, -28.0f)));
				addChild(m_pRightExplode);

				CCDelayTime *pExplodeOffset = CCDelayTime::create(1.0f);
				//等待2秒
				CCDelayTime *pDelayTime = CCDelayTime::create(2.0f);
				//原武器废弃 + 弹出新型武器
				CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossTwo::flareWeapon));
				m_pRightExplode->runAction(CCSequence::create(pExplodeOffset,pAction,pDelayTime,pCallback,NULL));


				//
			}
		}
		break;
	case STAGE_ACTION02:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= 0)
			{
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				//m_nBossHP = STAGE03_HP;
				stopAllActions();
				runEffect();
			}
		}
		break;
	case STAGE_ACTION03:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= STAGEEND_HP)
			{
				//m_eCurStage = STAGE_READY03;
				m_nBossHP = STAGEEND_HP;
			}
		}
		break;
	}


}


void CBossTwo::bossCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			//出场后开始执行
			//向右飞
			CCMoveTo *pMoveRight = CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.7f, mScreenSize.height * 0.7f - BANNER_HEIGHT));
			//向左飞
			CCMoveTo *pMoveLeft = CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.3f, mScreenSize.height * 0.7f - BANNER_HEIGHT));
			//开火回调
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossTwo::stage1Fire));
			//延时
			CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			m_pMoveAction = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pCallback,pDelayTime,pCallback,pDelayTime,
				pCallback,pDelayTime,pCallback,pDelayTime,
				pCallback,pDelayTime,pCallback,pDelayTime,
				pCallback,pDelayTime,pCallback,pDelayTime,pMoveRight,
				pCallback,pDelayTime,pCallback,pDelayTime,
				pCallback,pDelayTime,pCallback,pDelayTime,
				pCallback,pDelayTime,pCallback,pDelayTime,
				pCallback,pDelayTime,pCallback,pDelayTime,pMoveLeft,NULL)));
			m_eCurState = BOS_FIRE_RUN;
			m_eCurStage = STAGE_ACTION01;
		}
		break;
	case STAGE_READY02:
		{
			//飞到指定位置
			CCMoveTo *pMoveOrigin = CCMoveTo::create(1.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.9f - BANNER_HEIGHT));
			CCDelayTime *pDelayTime = CCDelayTime::create(64.0f / STAGE02_BSPEED);
			CCMoveTo *pMoveLeft = CCMoveTo::create(1.0f,ccp(mScreenSize.width * 0.3f, mScreenSize.height * 0.7f - BANNER_HEIGHT));
			CCMoveTo *pMoveRight = CCMoveTo::create(1.0f,ccp(mScreenSize.width * 0.7f, mScreenSize.height * 0.7f - BANNER_HEIGHT));
			//开火回调
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossTwo::stage2Fire));
			runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pMoveOrigin,pCallback, pDelayTime,pCallback, pDelayTime,pCallback, pDelayTime,
				pMoveLeft,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,
				pMoveRight,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,
				NULL)));
			m_eCurStage = STAGE_ACTION02;
		}
		break;
	}
}

void CBossTwo::stage1Fire(void)
{
	CCPoint mTarget;
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(getParent()->getChildren(), pObj)
	{
		CCNode* pNode = (CCNode*) pObj;
		if (pNode->getTag() == PALYER_TYPE)
		{
			mTarget = pNode->getPosition();
			break;
		}
	}

	BULLET_DATA mData;
	mData.mAttack = 10;
	mData.mMoveSpeed = 150.0f;
	CCPoint mWorldPos = convertToWorldSpace(m_pLeftWeapon->getPosition());
	mData.mDirection = ccpNormalize(ccpSub(mTarget, ccpAdd(mWorldPos, ccp(-10.0f, -28.0f))));
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
	pBullet->setPosition(ccpAdd(mWorldPos, ccp(-10.0f, -28.0f)));
	getParent()->addChild(pBullet, ABULLET_ZORDER);

	//if (m_pLeftFlashSprite)
	//{
	//	removeChild(m_pLeftFlashSprite, true);
	//	m_pLeftFlashSprite = NULL;
	//}
	//m_pLeftFlashSprite = CCSprite::create();
	//m_pLeftFlashSprite->setPosition(ccpAdd(m_pLeftWeapon->getPosition(), ccp(-10.0f, -28.0f)));
	//addChild(m_pLeftFlashSprite);

	//CCAnimation *pAnimation = CCAnimation::create();

	//char szName[128] = {0};

	//for (int i=0; i<ANIMATE_MAX; i++)
	//{
	//	sprintf(szName, "Flash02_%02d.png", i+1);
	//	if (m_pCurCache->spriteFrameByName(szName) == NULL)
	//	{
	//		break;
	//	}
	//	pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	//}


	//pAnimation->setDelayPerUnit(0.015f);
	//pAnimation->setRestoreOriginalFrame(true);

	//CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//m_pLeftFlashSprite->runAction(pAnimate);

	mWorldPos = convertToWorldSpace(m_pRightWeapon->getPosition());
	mData.mDirection = ccpNormalize(ccpSub(mTarget, ccpAdd(mWorldPos, ccp(10.0f, -28.0f))));
	pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
	pBullet->setPosition(ccpAdd(mWorldPos, ccp(10.0f, -28.0f)));
	getParent()->addChild(pBullet, ABULLET_ZORDER);

	//if (m_pRightFlashSprite)
	//{
	//	removeChild(m_pRightFlashSprite, true);
	//	m_pRightFlashSprite = NULL;
	//}
	//m_pRightFlashSprite = CCSprite::create();
	//m_pRightFlashSprite->setPosition(ccpAdd(m_pRightWeapon->getPosition(), ccp(10.0f, -28.0f)));
	//addChild(m_pRightFlashSprite);
	//m_pRightFlashSprite->runAction(pAnimate);
}

void CBossTwo::stage2Fire(void)
{
	BULLET_DATA mData;
	mData.mAttack = 10;
	mData.mMoveSpeed = STAGE02_BSPEED;
	mData.mDirection = ccp(0.0f, -1.0f);
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_LASER);
	pBullet->setPosition(ccp(getPositionX(), getPositionY() - m_pBaseSprite->getContentSize().height * 0.5f));
	getParent()->addChild(pBullet, ABULLET_ZORDER);
}

void CBossTwo::flareWeapon(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			float fPosY = m_pLeftWeapon->getPositionY();
			m_pLeftWeapon->runAction(CCMoveTo::create(1.0f, ccp(m_pBaseSprite->getContentSize().width * 0.5f - 43.0f,fPosY)));
			m_pRightWeapon->runAction(CCMoveTo::create(1.0f, ccp(m_pBaseSprite->getContentSize().width * 0.5f + 43.0f,fPosY)));
		}
		break;
	case STAGE_READY02:
		{
			m_pLeftWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WL01_01.png"));
			m_pLeftWeapon->setPosition(getPosition());
			getParent()->addChild(m_pLeftWeapon, AIR_ZORDER);
			m_pRightWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WR01_01.png"));
			m_pRightWeapon->setPosition(getPosition());
			getParent()->addChild(m_pRightWeapon, AIR_ZORDER);

			m_pLeftWeapon->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360.0f)));
			CCAction *pRight = CCRotateBy::create(1.0f, 360.0f)->reverse();
			m_pRightWeapon->runAction(CCRepeatForever::create((CCActionInterval*)pRight));
			m_pLeftWeapon->runAction(CCMoveTo::create(2.0f, ccp(mScreenSize.width * 0.2f, mScreenSize.height * 0.8f - BANNER_HEIGHT)));
			CCDelayTime *pDelayTime = CCDelayTime::create(2.0f);
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossTwo::bossCallback));
			m_pRightWeapon->runAction(CCSequence::create(CCMoveTo::create(2.0f, ccp(mScreenSize.width * 0.8f, mScreenSize.height * 0.8f - BANNER_HEIGHT)),pDelayTime,pCallback,NULL));

			//m_pRightWeapon->runAction(CCMoveTo::create(2.0f, ccp(mScreenSize.width * 0.8f, mScreenSize.height * 0.8f)));
		}
		break;
	}

}

void CBossTwo::runEffect(void)
{
	if (!m_bBaseNormal)
	{
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
		pRGBAProtocol->setColor(m_sBaseColor);
	}

	CCAnimation *pAnimation = CCAnimation::create();
	char szName[128] = {0};
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "Explode03_%02d.png", i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}


	pAnimation->setDelayPerUnit(0.066f);
	pAnimation->setRestoreOriginalFrame(true);

	//CCPlace
	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CBossTwo::removeSelf));
	CCPoint mPos = getPosition();
	CCPoint mOffSet = ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f);
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,CCMoveTo::create(0.1f,ccp(CCRANDOM_0_1() * getContentSize().width, CCRANDOM_0_1() * getContentSize().height * 0.5f)),
		pAnimate,CCMoveTo::create(0.1f,ccp(CCRANDOM_0_1() * getContentSize().width, CCRANDOM_0_1() * getContentSize().height * 0.5f)),
		pAnimate,CCMoveTo::create(0.1f,ccp(CCRANDOM_0_1() * getContentSize().width, CCRANDOM_0_1() * getContentSize().height * 0.5f)),
		pAnimate,CCMoveTo::create(0.1f,ccp(CCRANDOM_0_1() * getContentSize().width, CCRANDOM_0_1() * getContentSize().height * 0.5f)),
		pAnimate,CCMoveTo::create(0.1f,ccp(CCRANDOM_0_1() * getContentSize().width, CCRANDOM_0_1() * getContentSize().height * 0.5f)),
		pAnimate,pCallback,NULL) );
	m_pExplode->runAction(pAction);
	
	if (m_eCurState = BOS_EXPLODE)
	{
		runAction(CCScaleTo::create(10.0f, 0.5f));
	}
}

void CBossTwo::removeSelf(void)
{
	m_eCurState = BOS_HIDE;
	m_pLeftWeapon->removeFromParentAndCleanup(true);
	m_pRightWeapon->removeFromParentAndCleanup(true);
	removeFromParentAndCleanup(true);

	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		CGlobalData::getSingleton()->resetEndlessData();
	}
	else
	{
		CGlobalData::getSingleton()->setLevelClear(true);
	}
}
