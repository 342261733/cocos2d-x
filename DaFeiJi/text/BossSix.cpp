#include "BossSix.h"

CBossSix::CBossSix(void)
{
	Music::stopBackgroundMusic(false);
}

CBossSix::~CBossSix(void)
{
}


CBossSix* CBossSix::createBoss(void)
{
	CBossSix *pBoss = new CBossSix();
	pBoss->createSprite();
	pBoss->setTag(BOSS_TYPE);
	//pBoss->m_eBossKind = eKind;
	return pBoss;
}

void CBossSix::createSprite(void)
{
	Music::playWarnEffect();

	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	this->schedule(schedule_selector(CBossSix::bossUpdate));
}

bool CBossSix::isCheck(void)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02)
	{
		return true;
	}
	return false;
}

CCRect CBossSix::getCurBoundbox(void)
{
	CCRect mRect = m_pCollideBody->boundingBox();

	mRect.origin.x = mRect.origin.x + getPositionX() - getContentSize().width * 0.5f;
	mRect.origin.y = mRect.origin.y + getPositionY() - getContentSize().height * 0.5f;

	return mRect;
}

void CBossSix::onEnter(void)
{
	setAnchorPoint(ccp(0.5f,0.5f));
	setContentSize(CCSizeMake(400,275));
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Base.png"));
	m_pBaseSprite->setAnchorPoint(ccp(0.5f,0.5f));
	addChild(m_pBaseSprite, BOSS_ZORDER);
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	m_pBaseSprite->setVisible(false);

	m_pCollideBody = CCSprite::create();
	m_pCollideBody->setContentSize(CCSizeMake(400,60));
	m_pCollideBody->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.385f));
	addChild(m_pCollideBody);

	m_pMainBody = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Body01_01.png"));
	m_pMainBody->setPosition(ccp(getContentSize().width * 0.5f, m_pMainBody->getContentSize().height * 0.5f));
	addChild(m_pMainBody);


	m_pLeftBody = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Body02_01.png"));
	m_pLeftBody->setPosition(ccp(getContentSize().width * 0.195f, getContentSize().height * 0.633f));
	addChild(m_pLeftBody);

	m_pRightBody = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Body03_01.png"));
	m_pRightBody->setPosition(ccp(getContentSize().width * 0.805f, getContentSize().height * 0.633f));
	addChild(m_pRightBody);

	m_pLeftEngine = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Body04_01.png"));
	m_pLeftEngine->setPosition(ccp(getContentSize().width * 0.355f,getContentSize().height * 0.287f));
	addChild(m_pLeftEngine);

	m_pRightEngine = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Body04_01.png"));
	m_pRightEngine->setPosition(ccp(getContentSize().width * 0.645f,getContentSize().height * 0.287f));
	addChild(m_pRightEngine);

	m_pLeftGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Gun01_01.png"));
	m_pLeftGun->setPosition(ccp(getContentSize().width * 0.355f,getContentSize().height * 0.487f));
	m_pLeftGun->setAnchorPoint(ccp(0.5f,0.755f));
	addChild(m_pLeftGun);

	m_pRightGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss06_Gun01_01.png"));
	m_pRightGun->setPosition(ccp(getContentSize().width * 0.645f,getContentSize().height * 0.487f));
	m_pRightGun->setAnchorPoint(ccp(0.5f,0.755f));
	addChild(m_pRightGun);

	m_pExplode = CCSprite::create();
	m_pExplode->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	addChild(m_pExplode, BOSS_ZORDER);

	m_pCurAttack = NULL;
	//m_pRightFlashSprite = NULL;
	//m_pLeftExplode = NULL;
	//m_pRightExplode = NULL;

	m_nBossHP = BOSS06_STAGE01_HP;
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		m_nBossHP = 10000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
	}
	m_fEnemyTime = 0.0f;


	//执行出场流程
	setPosition(ccp(mScreenSize.width, mScreenSize.height + getContentSize().height - BANNER_HEIGHT));
	setScale(2.5f);
	//延时
	CCDelayTime *pDelayTime = CCDelayTime::create(3.0f);
	//飞出
	CCMoveTo *pMoveDown = CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.7f - BANNER_HEIGHT));
	//缩小
	CCScaleTo *pScaleTo = CCScaleTo::create(2.0f, 1.0f);
	//后退
	CCMoveTo *pMoveBack =CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.8f - BANNER_HEIGHT));
	//合成（放大+后退）
	CCAction *pSpawn = CCSpawn::create(pScaleTo, pMoveBack,NULL);
	//展开武器回调
	//CCCallFunc *pFlareWeapon = CCCallFunc::create(this, callfunc_selector(CBossThree::flareWeapon));
	//飞到指定位置
	//CCMoveTo *pMoveLeft = CCMoveTo::create(0.5f,ccp(mScreenSize.width * 0.3f, mScreenSize.height * 0.8f));
	//回调
	CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossSix::bossCallback));

	//序列
	//CCSequence *pSequence = CCSequence::create(pDelayTime,pMoveDown,pScaleTo,pMoveLeft,pCallback,NULL);
	runAction(CCSequence::create(pDelayTime,pMoveDown,pSpawn,/*pDelayTime,*/pCallback,NULL));


	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pMainBody);
	m_sBaseColor = pRGBAProtocol->getColor();
	m_fFlashTime = 0.0f;
	m_bBaseNormal = true;
	m_fTime = BOSS03_STAGE01_FIRETIME;
	m_fShotGunTime = 0.0f;
	m_eCurStage = STAGE_READY01;

	Music::playBoss_1_BgMusic();

	CCNode::onEnter();
}

void CBossSix::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}


void CBossSix::bossUpdate(float fEscapeTime)
{
	switch(m_eCurStage)
	{
	case STAGE_DEFAULT:
		break;
	case STAGE_ACTION01:
		{
			//m_fTime += fEscapeTime;
			//if (m_fTime > BOSS04_STAGE01_FIRETIME)
			//{
			//	m_fTime = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 150.0f;
			//	for (int i=0;i<BOSS04_STAGE01_FIRENUM;i++)
			//	{
			//		mData.mDirection = ccpNormalize(ccp(-1.0f + 2.0f / (BOSS04_STAGE01_FIRENUM - 1) * i, -1.0f));
			//		CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			//		pBullet->setPosition(ccp(getPositionX() - m_pTailGun->getContentSize().width * 0.3f, getPositionY() - getContentSize().height * 0.5f));
			//		getParent()->addChild(pBullet, ABULLET_ZORDER);
			//		pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			//		pBullet->setPosition(ccp(getPositionX() + m_pTailGun->getContentSize().width * 0.3f, getPositionY() - getContentSize().height * 0.5f));
			//		getParent()->addChild(pBullet, ABULLET_ZORDER);
			//	}
			//}

			//m_fShotGunTime += fEscapeTime;
			//if (m_fShotGunTime > BOSSO4_SHOTFIRE_TIME)
			//{
			//	m_fShotGunTime = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 300.0f;
			//	for (int i=0;i<BOSSO4_SHOTFIRE_NUMBER;i++)
			//	{
			//		mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / BOSSO4_SHOTFIRE_NUMBER * i));
			//		CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			//		pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.034f));
			//		getParent()->addChild(pBullet, BBULLET_ZORDER);
			//	}
			//}

		}
		break;
	case STAGE_ACTION02:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS06_STAGE02_MISSLE)
			{
				m_fTime = 0.0f;

				BULLET_DATA mData;
				mData.mKind = BK_TARCKROCKET;
				mData.mAttack = 28;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(-1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX(), getPositionY()));
				getParent()->addChild(pBullet, AIR_ZORDER);
			}

			m_fShotGunTime += fEscapeTime;
			if (m_fShotGunTime > BOSSO6_SHOTFIRE_TIME)
			{
				m_fShotGunTime = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 18;
				mData.mMoveSpeed = 300.0f;
				for (int i=0;i<BOSSO6_SHOTFIRE_NUMBER;i++)
				{
					mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / BOSSO6_SHOTFIRE_NUMBER * i));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
					pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.034f));
					getParent()->addChild(pBullet, BBULLET_ZORDER);
				}
			}
		}
		break;
	case STAGE_ACTION03:
		{
			//m_fTime += fEscapeTime;
			//if (m_fTime > BOSS03_STAGE02_MISSLE)
			//{
			//	m_fTime = 0.0f;

			//	BULLET_DATA mData;
			//	mData.mKind = BK_TARCKROCKET;
			//	mData.mAttack = 28;
			//	mData.mMoveSpeed = 250.0f;
			//	mData.mDirection = ccp(1.0f, 0.0f);
			//	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
			//	pBullet->setPosition(ccp(getPositionX(), getPositionY()));
			//	getParent()->addChild(pBullet, AIR_ZORDER);
			//}
		}
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
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pMainBody);
			pRGBAProtocol->setColor(m_sBaseColor);
			pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pLeftBody);
			pRGBAProtocol->setColor(m_sBaseColor);
			pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pRightBody);
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

void CBossSix::underAttack(int nHurt)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02)
	{
		if (m_bBaseNormal)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pMainBody);
			pRGBAProtocol->setColor(ccc3(255,0,0));
			pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pLeftBody);
			pRGBAProtocol->setColor(ccc3(255,0,0));
			pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pRightBody);
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
				m_nBossHP = BOSS06_STAGE02_HP;
				if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
				{
					m_nBossHP = 15000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
				}

				m_pLeftEngine->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss06_Body04_02.png"));
				m_pRightEngine->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss06_Body04_02.png"));
				//停止移动
				stopAction(m_pEngine);

				//runAction(CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.65f)));
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
				m_pLeftBody->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss06_Body02_02.png"));
				m_pRightBody->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss06_Body03_02.png"));
				m_pMainBody->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss06_Body01_02.png"));
				m_pLeftGun->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss06_Gun01_02.png"));
				m_pRightGun->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss06_Gun01_02.png"));
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				m_nBossHP = STAGEEND_HP;
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
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				//m_pRightWing->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss03_Body03_02.png"));
				//m_nBossHP = STAGE03_HP;
				stopAllActions();
				runEffect();
			}
		}
		break;
	}


}


void CBossSix::bossCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			//出场后开始执行

			//延时
			CCDelayTime *pFireTime = CCDelayTime::create(0.2f);
			//开火回调
			CCCallFunc *pFire = CCCallFunc::create(this, callfunc_selector(CBossSix::stage1Fire));
			//延时
			CCDelayTime *pCoolTime = CCDelayTime::create(1.5f);
			m_pEngine = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pFire,pFireTime,pFire,pFireTime,pFire,pFireTime,pFire,pFireTime,pCoolTime,NULL)));

			//锁定回调
			CCCallFunc *pLock = CCCallFunc::create(this, callfunc_selector(CBossSix::lockTarget));
			//锁定等待
			CCDelayTime *pLockTime = CCDelayTime::create(0.5f);
			//锁定开火
			CCCallFunc *pLockFire = CCCallFunc::create(this, callfunc_selector(CBossSix::lockFire));
			m_pGun = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pLock,pLockTime,pLockFire,pLockTime,NULL)));
			m_pCurAttack = m_pLeftEngine;
			m_eCurState = BOS_FIRE_RUN;
			m_eCurStage = STAGE_ACTION01;
		}
		break;
	case STAGE_READY02:
		{
			//m_nRounds = 0;
			////延时
			//CCDelayTime *pDelayTime = CCDelayTime::create(0.2f);
			////方向回调
			//CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossSix::stage2Direction));
			////开火回调
			//CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossSix::stage2Fire));
			//runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
			//	pDirection,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,NULL)));
			m_eCurStage = STAGE_ACTION02;
			m_pCurAttack = m_pRightEngine;
		}
		break;
	case STAGE_READY03:
		{
			//m_nRounds = 0;
			//延时
			CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			//方向回调
			//CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossThree::stage2Direction));
			//开火回调
			//CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossSix::stage3Fire));
			//runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
			//	pCallback,pDelayTime,NULL)));
			//m_eCurStage = STAGE_ACTION03;
			//m_pCurAttack = m_pRightWing;
		}
		break;
	}
}

void CBossSix::stage1Fire(void)
{
	BULLET_DATA mData;
	mData.mAttack = 18;
	mData.mMoveSpeed = 150.0f;
	for (int i=0;i<BOSS06_STAGE01_FIRENUM;i++)
	{
		mData.mDirection = ccpNormalize(ccp(-1.0f + 2.0f / (BOSS06_STAGE01_FIRENUM - 1) * i, -1.0f));
		CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
		pBullet->setPosition(ccp(getPositionX() - getContentSize().width * 0.145f, getPositionY() - getContentSize().height * 0.398f));
		getParent()->addChild(pBullet, ABULLET_ZORDER);
		pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
		pBullet->setPosition(ccp(getPositionX() + getContentSize().width * 0.145f, getPositionY() - getContentSize().height * 0.398f));
		getParent()->addChild(pBullet, ABULLET_ZORDER);
	}
}

void CBossSix::lockTarget(void)
{
	CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));

	float o = m_pTarget->getPosition().x - (getPosition().x - getContentSize().width * 0.15f);
	float a = m_pTarget->getPosition().y - getPosition().y;
	float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

	if( a < 0 ) 
	{
		if(  o < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);    
	}

	m_pLeftGun->runAction(CCRotateTo::create(0.5f,180.0f + at));

	o = m_pTarget->getPosition().x - (getPosition().x + getContentSize().width * 0.15f);
	a = m_pTarget->getPosition().y - getPosition().y;
	at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

	if( a < 0 ) 
	{
		if(  o < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);    
	}

	m_pRightGun->runAction(CCRotateTo::create(0.5f,180.0f + at));
}

void CBossSix::lockFire(void)
{
	BULLET_DATA mData;
	mData.mAttack = 28;
	mData.mMoveSpeed = 150.0f;
	mData.mKind = BK_LASER;
	mData.mDirection = ccpRotateByAngle(ccp(0,-1.0f), ccp(0,0),  -CC_DEGREES_TO_RADIANS(m_pLeftGun->getRotation()));
	CCPoint mLeftPos = ccpRotateByAngle(ccp(0, -56), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pLeftGun->getRotation()));
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, mData.mKind);
	pBullet->setPosition(ccp(getPosition().x - getContentSize().width * 0.15f + mLeftPos.x, getPositionY() + mLeftPos.y));
	pBullet->setRotation(m_pLeftGun->getRotation());
	getParent()->addChild(pBullet, AIR_ZORDER);

	mData.mDirection = ccpRotateByAngle(ccp(0,-1.0f), ccp(0,0),  -CC_DEGREES_TO_RADIANS(m_pRightGun->getRotation()));
	CCPoint mRightPos = ccpRotateByAngle(ccp(0, -56), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pRightGun->getRotation()));
	pBullet = CBullet::createBullet(ENEMY_BULLET, mData, mData.mKind);
	pBullet->setPosition(ccp(getPosition().x + getContentSize().width * 0.15f + mRightPos.x, getPositionY() + mRightPos.y));
	pBullet->setRotation(m_pRightGun->getRotation());
	getParent()->addChild(pBullet, AIR_ZORDER);
}


void CBossSix::runEffect(void)
{
	if (!m_bBaseNormal)
	{
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pMainBody);
		pRGBAProtocol->setColor(m_sBaseColor);
		pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pLeftBody);
		pRGBAProtocol->setColor(m_sBaseColor);
		pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pRightBody);
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
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CBossSix::effectCallback));
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

void CBossSix::effectCallback(void)
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
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossSix::removeSelf));
			runAction(CCSequence::create(pDelayTime,pCallback,NULL));
		}
		break;
	}
}

void CBossSix::removeSelf(void)
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
