#include "BossThree.h"

CBossThree::CBossThree(void)
{
	Music::stopBackgroundMusic(false);
}

CBossThree::~CBossThree(void)
{
}


CBossThree* CBossThree::createBoss(void)
{
	CBossThree *pBoss = new CBossThree();
	pBoss->createSprite();
	pBoss->setTag(BOSS_TYPE);
	//pBoss->m_eBossKind = eKind;
	return pBoss;
}

void CBossThree::createSprite(void)
{
	Music::playWarnEffect();

	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	this->schedule(schedule_selector(CBossThree::bossUpdate));
}

bool CBossThree::isCheck(void)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02 || m_eCurStage == STAGE_ACTION03)
	{
		return true;
	}
	return false;
}

CCRect CBossThree::getCurBoundbox(void)
{
	CCRect mRect = CCRectMake(0,0,0,0);
	if (m_pCurAttack)
	{
		mRect = m_pCurAttack->boundingBox();
		mRect.origin.x = mRect.origin.x + getPositionX() - getContentSize().width * 0.5f;
		mRect.origin.y = mRect.origin.y + getPositionY() - getContentSize().height * 0.5f;
	}

	return mRect;
}

void CBossThree::onEnter(void)
{
	setAnchorPoint(ccp(0.5f,0.5f));
	setContentSize(CCSizeMake(525,429));
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss03_Base.png"));
	m_pBaseSprite->setAnchorPoint(ccp(0.5f,0.5f));
	addChild(m_pBaseSprite, BOSS_ZORDER);
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	m_pBaseSprite->setVisible(false);

	m_pMainBody = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss03_Body01_01.png"));
	m_pMainBody->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.627f));
	addChild(m_pMainBody);


	m_pLeftWing = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss03_Body02_01.png"));
	m_pLeftWing->setPosition(ccp(getContentSize().width * 0.22f, getContentSize().height * 0.66f));
	addChild(m_pLeftWing);

	m_pRightWing = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss03_Body03_01.png"));
	m_pRightWing->setPosition(ccp(getContentSize().width * 0.78f,getContentSize().height * 0.66f));
	addChild(m_pRightWing);

	m_pTailFin = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss03_Body04_01.png"));
	m_pTailFin->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.127f));
	addChild(m_pTailFin);

	m_pExplode = CCSprite::create();
	m_pExplode->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	addChild(m_pExplode, BOSS_ZORDER);

	m_pCurAttack = NULL;
	//m_pRightFlashSprite = NULL;
	//m_pLeftExplode = NULL;
	//m_pRightExplode = NULL;

	m_nBossHP = BOSS03_STAGE01_HP;
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		m_nBossHP = 8000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
	}
	m_fEnemyTime = 0.0f;


	//执行出场流程
	setPosition(ccp(mScreenSize.width * 0.0f, - getContentSize().height));
	setScale(1.5f);
	//延时
	CCDelayTime *pDelayTime = CCDelayTime::create(3.0f);
	//飞出
	CCMoveTo *pMoveDown = CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 1.2f - BANNER_HEIGHT));
	//缩小
	CCScaleTo *pScaleTo = CCScaleTo::create(1.0f, 1.0f);
	//后退
	CCMoveTo *pMoveBack =CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 1.0f - BANNER_HEIGHT));
	//合成（放大+后退）
	CCAction *pSpawn = CCSpawn::create(pScaleTo, pMoveBack,NULL);
	//展开武器回调
	//CCCallFunc *pFlareWeapon = CCCallFunc::create(this, callfunc_selector(CBossThree::flareWeapon));
	//飞到指定位置
	CCMoveTo *pMoveLeft = CCMoveTo::create(0.5f,ccp(mScreenSize.width * 0.2f, mScreenSize.height * 1.0f - BANNER_HEIGHT));
	//回调
	CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossThree::bossCallback));

	//序列
	//CCSequence *pSequence = CCSequence::create(pDelayTime,pMoveDown,pScaleTo,pMoveLeft,pCallback,NULL);
	runAction(CCSequence::create(pDelayTime,pMoveDown,pSpawn,/*pDelayTime,*/pMoveLeft,pCallback,NULL));


	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
	m_sBaseColor = pRGBAProtocol->getColor();
	m_fFlashTime = 0.0f;
	m_bBaseNormal = true;
	m_fTime = BOSS03_STAGE01_FIRETIME;
	m_eCurStage = STAGE_READY01;

	Music::playBoss_1_BgMusic();

	CCNode::onEnter();
}

void CBossThree::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}


void CBossThree::bossUpdate(float fEscapeTime)
{
	switch(m_eCurStage)
	{
	case STAGE_DEFAULT:
		break;
	case STAGE_ACTION01:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS03_STAGE01_FIRETIME)
			{
				m_fTime = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 12;
				mData.mMoveSpeed = 150.0f;
				for (int i=0;i<BOSS03_STAGE01_FIRENUM;i++)
				{
					mData.mDirection = ccpNormalize(ccp(-0.8f + 1.6f / (BOSS03_STAGE01_FIRENUM - 1) * i, -1.0f));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
					pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.4f));
					getParent()->addChild(pBullet, ABULLET_ZORDER);
				}
			}

		}
		break;
	case STAGE_ACTION02:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS03_STAGE02_MISSLE)
			{
				m_fTime = 0.0f;

				BULLET_DATA mData;
				mData.mKind = BK_TARCKROCKET;
				mData.mAttack = 22;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(-1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX(), getPositionY()));
				getParent()->addChild(pBullet, AIR_ZORDER);
			}
			
			//m_fShotFireSlot += fEscapeTime;
			//m_fFireRound += fEscapeTime;
			//if (m_fFireRound > STAGE02_COOL && m_fShotFireSlot > STAGE02_SLOT)
			//{
			//	m_fShotFireSlot = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 140.0f;
			//	for (int i=0;i<1;i++)
			//	{
			//		mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * m_nFireNum));
			//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
			//		pBullet->setPosition(m_pLeftWeapon->getPosition());
			//		getParent()->addChild(pBullet, ABULLET_ZORDER);
			//	}

			//	for (int i=0;i<1;i++)
			//	{
			//		mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), CC_DEGREES_TO_RADIANS(360.0f / B2BULLET_NUM * m_nFireNum));
			//		CBullet *pBullet = CBullet::createBullet(BOSS_TYPE, mData, BK_ENEMY01);
			//		pBullet->setPosition(m_pRightWeapon->getPosition());
			//		getParent()->addChild(pBullet, ABULLET_ZORDER);
			//	}
			//	m_nFireNum ++;

			//	if (m_nFireNum >= STAGE02_FIRENUM)
			//	{
			//		m_fFireRound = 0.0f;
			//		m_nFireNum = 0;
			//	}
			//}
		}
		break;
	case STAGE_ACTION03:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS03_STAGE02_MISSLE)
			{
				m_fTime = 0.0f;

				BULLET_DATA mData;
				mData.mKind = BK_TARCKROCKET;
				mData.mAttack = 22;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX(), getPositionY()));
				getParent()->addChild(pBullet, AIR_ZORDER);
			}
		}
		break;
	case STAGE_ACTION04:
		break;
	case STAGE_ACTION05:
		break;
	}

	if (!m_bBaseNormal && m_pCurAttack)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pCurAttack);
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
}

void CBossThree::underAttack(int nHurt)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02 || m_eCurStage == STAGE_ACTION03)
	{
		if (m_bBaseNormal && m_pCurAttack)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pCurAttack);
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
				m_nBossHP = BOSS03_STAGE02_HP;

				if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
				{
					m_nBossHP = 8000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
				}

				////回复本身颜色
				//CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pCurAttack);
				//pRGBAProtocol->setColor(m_sBaseColor);
				//m_pCurAttack = NULL;
				m_pMainBody->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss03_Body01_02.png"));
				m_pTailFin->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss03_Body04_02.png"));
				//停止移动
				stopAction(m_pMoveAction);
				//武器毁坏
				//CCPoint mLeftPos = m_pLeftWeapon->getPosition();
				//CCPoint mRightPos = m_pRightWeapon->getPosition();
				//m_pLeftWeapon->removeFromParentAndCleanup(true);
				//m_pRightWeapon->removeFromParentAndCleanup(true);

				//m_pLeftWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WL02_02.png"));
				//m_pLeftWeapon->setPosition(mLeftPos);
				//addChild(m_pLeftWeapon, -1);
				//m_pRightWeapon = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss02_WR02_02.png"));
				//m_pRightWeapon->setPosition(mRightPos);
				//addChild(m_pRightWeapon, -1);
				//执行爆炸
				//if (m_pLeftExplode)
				//{
				//	m_pLeftExplode->removeFromParentAndCleanup(true);
				//}

				//m_pLeftExplode = CCSprite::create();
				//m_pLeftExplode->setPosition(ccpAdd(m_pLeftWeapon->getPosition(), ccp(-10.0f, -28.0f)));
				//addChild(m_pLeftExplode);
				//CCAnimation *pAnimation = CCAnimation::create();

				//char szName[128] = {0};
				//for (int i=0; i<ANIMATE_MAX; i++)
				//{
				//	sprintf(szName, "Explode01_%02d.png", i+1);
				//	if (m_pCurCache->spriteFrameByName(szName) == NULL)
				//	{
				//		break;
				//	}
				//	pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
				//}


				//pAnimation->setDelayPerUnit(0.066f);
				//pAnimation->setRestoreOriginalFrame(true);

				//CCAnimate *pAnimate = CCAnimate::create(pAnimation);
				//CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
				//m_pLeftExplode->runAction(pAction);

				//if (m_pRightExplode)
				//{
				//	m_pRightExplode->removeFromParentAndCleanup(true);
				//}

				//m_pRightExplode = CCSprite::create();
				//m_pRightExplode->setPosition(ccpAdd(m_pRightWeapon->getPosition(), ccp(10.0f, -28.0f)));
				//addChild(m_pRightExplode);

				runAction(CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.75f, mScreenSize.height * 0.65f - BANNER_HEIGHT)));
				runEffect();
				//
			}
		}
		break;
	case STAGE_ACTION02:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= 0)
			{
				m_eCurStage = STAGE_READY03;
				m_nBossHP = BOSS03_STAGE03_HP;
				if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
				{
					m_nBossHP = 9000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
				}
				m_pLeftWing->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss03_Body02_02.png"));
				stopAllActions();
				runAction(CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.25f, mScreenSize.height * 0.65f - BANNER_HEIGHT)));
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
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				m_pRightWing->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss03_Body03_02.png"));
				//m_nBossHP = STAGE03_HP;
				stopAllActions();
				runEffect();
			}
		}
		break;
	}


}


void CBossThree::bossCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			//出场后开始执行
			//向右飞
			CCMoveTo *pMoveRight = CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.8f, mScreenSize.height * 1.0f - BANNER_HEIGHT));
			//向左飞
			CCMoveTo *pMoveLeft = CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.2f, mScreenSize.height * 1.0f - BANNER_HEIGHT));
			//开火回调
			//CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossThree::stage1Fire));
			//延时
			//CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			//m_pMoveAction = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,pMoveRight,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,pMoveLeft,NULL)));
			m_pMoveAction = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pMoveRight,pMoveLeft,NULL)));
			m_pCurAttack = m_pTailFin;
			m_eCurState = BOS_FIRE_RUN;
			m_eCurStage = STAGE_ACTION01;
		}
		break;
	case STAGE_READY02:
		{
			//飞到指定位置
			//CCMoveTo *pMoveOrigin = CCMoveTo::create(1.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.9f));
			//CCDelayTime *pDelayTime = CCDelayTime::create(64.0f / STAGE02_BSPEED);
			//CCMoveTo *pMoveLeft = CCMoveTo::create(1.0f,ccp(mScreenSize.width * 0.3f, mScreenSize.height * 0.7f));
			//CCMoveTo *pMoveRight = CCMoveTo::create(1.0f,ccp(mScreenSize.width * 0.7f, mScreenSize.height * 0.7f));
			m_nRounds = 0;
			//延时
			CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			//方向回调
			CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossThree::stage2Direction));
			//开火回调
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossThree::stage2Fire));
			runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pDirection,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,NULL)));
			m_eCurStage = STAGE_ACTION02;
			m_pCurAttack = m_pLeftWing;
		}
		break;
	case STAGE_READY03:
		{
			m_nRounds = 0;
			//延时
			CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			//方向回调
			//CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossThree::stage2Direction));
			//开火回调
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossThree::stage3Fire));
			runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pCallback,pDelayTime,NULL)));
			m_eCurStage = STAGE_ACTION03;
			m_pCurAttack = m_pRightWing;
		}
		break;
	}
}

void CBossThree::stage2Direction(void)
{
	CCPoint mDirection = ccpNormalize(ccp(-1.0f,-1.0f));
	m_sStage2Data.mAttack = 12;
	m_sStage2Data.mMoveSpeed = 150.0f;
	m_sStage2Data.mKind = BK_ARMY01;
	m_sStage2Data.mDirection = ccpRotateByAngle(mDirection, ccp(0,0), CC_DEGREES_TO_RADIANS(BOSS03_STAGE02_SECTOR * m_nRounds / (BOSS03_STAGE02_ROUNDS - 1)));
	m_nRounds ++;
	if (m_nRounds >= BOSS03_STAGE02_ROUNDS)
	{
		m_nRounds = 0;
	}
}

void CBossThree::stage2Fire(void)
{
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, m_sStage2Data, m_sStage2Data.mKind);
	pBullet->setPosition(ccp(getPositionX() - getContentSize().width * 0.5f + m_pLeftWing->getPositionX(), getPositionY() + m_pLeftWing->getPositionY() - getContentSize().height * 0.5f));
	getParent()->addChild(pBullet, ABULLET_ZORDER);
}

void CBossThree::stage3Fire(void)
{
	BULLET_DATA mData;
	CCPoint mDirection = ccpNormalize(ccp(-1.0f,-1.0f));
	mData.mAttack = 12;
	mData.mMoveSpeed = 150.0f;
	mData.mKind = BK_ARMY01;
	mData.mDirection = ccpRotateByAngle(mDirection, ccp(0,0), CC_DEGREES_TO_RADIANS(BOSS03_STAGE03_SECTOR * m_nRounds / (BOSS03_STAGE03_NUMBER - 1)));
	m_nRounds ++;
	if (m_nRounds >= BOSS03_STAGE03_NUMBER)
	{
		m_nRounds = 0;
	}
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, mData.mKind);
	pBullet->setPosition(ccp(getPositionX() - getContentSize().width * 0.5f + m_pRightWing->getPositionX(), getPositionY() + m_pRightWing->getPositionY() - getContentSize().height * 0.5f));
	getParent()->addChild(pBullet, ABULLET_ZORDER);
}

void CBossThree::runEffect(void)
{
	if (!m_bBaseNormal)
	{
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pCurAttack);
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
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CBossThree::effectCallback));
	CCPoint mPos = getPosition();
	CCPoint mOffSet;
	mOffSet.x = m_pCurAttack->getPosition().x - m_pCurAttack->getContentSize().width * 0.5f;
	mOffSet.y = m_pCurAttack->getPosition().y - m_pCurAttack->getContentSize().height * 0.5f;
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create(
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,pCallback,NULL) );
	m_pExplode->runAction(pAction);
	
	if (m_eCurState == BOS_EXPLODE)
	{
		runAction(CCScaleTo::create(10.0f, 0.5f));
	}
}

void CBossThree::effectCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY02:
		{
			m_pCurAttack = NULL;
			bossCallback();
		}
		break;
	case STAGE_READY03:
		{
			m_pCurAttack = NULL;
			bossCallback();
		}
		break;
	case STAGE_EXPLODE:
		{
			setVisible(false);
			//等待1秒
			CCDelayTime *pDelayTime = CCDelayTime::create(1.0f);
			//原武器废弃 + 弹出新型武器
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossThree::removeSelf));
			runAction(CCSequence::create(pDelayTime,pCallback,NULL));
		}
		break;
	}
}

void CBossThree::removeSelf(void)
{
	m_eCurState = BOS_HIDE;
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
