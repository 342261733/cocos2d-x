#include "BossSeven.h"

CBossSeven::CBossSeven(void)
{
	Music::stopBackgroundMusic(false);
}

CBossSeven::~CBossSeven(void)
{
}

CBossSeven* CBossSeven::createBoss(void)
{
	CBossSeven *pBoss = new CBossSeven();
	pBoss->createSprite();
	pBoss->setTag(BOSS_TYPE);
	//pBoss->m_eBossKind = eKind;
	return pBoss;
}

void CBossSeven::createSprite(void)
{
	Music::playWarnEffect();

	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	this->schedule(schedule_selector(CBossSeven::bossUpdate));
}

bool CBossSeven::isCheck(void)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02)
	{
		return true;
	}
	return false;
}

CCRect CBossSeven::getCurBoundbox(void)
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

void CBossSeven::onEnter(void)
{
	setAnchorPoint(ccp(0.5f,0.5f));
	setContentSize(CCSizeMake(440,352));
	setPosition(ccp(mScreenSize.width * 0.5f, - getContentSize().height * 0.5f));
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss07_Base.png"));
	m_pBaseSprite->setAnchorPoint(ccp(0.5f,0.5f));
	addChild(m_pBaseSprite);
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));

	//尾炮
	m_pTailGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss07_Gun02_01.png"));
	m_pTailGun->setPosition(ccp(getContentSize().width * 0.5f, m_pBaseSprite->getContentSize().height * 0.034f));
	addChild(m_pTailGun);

	//左翼左炮
	m_pLLeftGun = CDrone::createDrone();
	m_pLLeftGun->setPosition(ccp(getPositionX() - getContentSize().width * 0.35f, getPositionY() + getContentSize().height * 0.15f));
	getParent()->addChild(m_pLLeftGun, BOSS_ZORDER);
	//m_pLaserGun->runAction(CCRepeatForever::create((CCActionInterval*)CCRotateBy::create(0.5f,360.0f)));

	//左翼右炮
	m_pLRightGun = CDrone::createDrone();
	m_pLRightGun->setPosition(ccp(getPositionX() - getContentSize().width * 0.15f, getPositionY() + getContentSize().height * 0.15f));
	getParent()->addChild(m_pLRightGun, BOSS_ZORDER);

	//右翼左炮
	m_pRLeftGun = CDrone::createDrone();
	m_pRLeftGun->setPosition(ccp(getPositionX() + getContentSize().width * 0.15f, getPositionY() + getContentSize().height * 0.15f));
	getParent()->addChild(m_pRLeftGun, BOSS_ZORDER);

	//右翼右炮
	m_pRRightGun = CDrone::createDrone();
	m_pRRightGun->setPosition(ccp(getPositionX() + getContentSize().width * 0.35f, getPositionY() + getContentSize().height * 0.15f));
	getParent()->addChild(m_pRRightGun, BOSS_ZORDER);

	//中炮
	m_pMiddleGun = CDrone::createDrone();
	m_pMiddleGun->setPosition(ccp(getPositionX(), getPositionY() + getContentSize().height * 0.165f));
	getParent()->addChild(m_pMiddleGun, BOSS_ZORDER);

	m_pExplode = CCSprite::create();
	m_pExplode->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	addChild(m_pExplode, ARMY_ZORDER);

	m_pCurAttack = NULL;
	m_fTime = 0.0f;

	m_nBossHP = BOSS07_STAGE01_HP;
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		m_nBossHP = 4000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
	}
	m_fEnemyTime = 0.0f;


	//执行出场流程
	CCPoint mPos = ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.8f - BANNER_HEIGHT);
	//延时
	CCDelayTime *pDelayTime = CCDelayTime::create(3.0f);
	//驶出
	CCMoveTo *pMoveUp = CCMoveTo::create(2.5f,mPos);
	//回调
	CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossSeven::bossCallback));
	runAction(CCSequence::create(pDelayTime,pMoveUp,pDelayTime,pCallback,NULL));
	pMoveUp = CCMoveTo::create(2.5f,ccpAdd(mPos, ccp(- getContentSize().width * 0.35f, getContentSize().height * 0.15f)));
	m_pLLeftGun->runAction(CCSequence::create(pDelayTime,pMoveUp,pDelayTime,NULL));
	pMoveUp = CCMoveTo::create(2.5f,ccpAdd(mPos, ccp(- getContentSize().width * 0.15f, getContentSize().height * 0.15f)));
	m_pLRightGun->runAction(CCSequence::create(pDelayTime,pMoveUp,pDelayTime,NULL));
	pMoveUp = CCMoveTo::create(2.5f,ccpAdd(mPos, ccp(getContentSize().width * 0.15f, getContentSize().height * 0.15f)));
	m_pRLeftGun->runAction(CCSequence::create(pDelayTime,pMoveUp,pDelayTime,NULL));
	pMoveUp = CCMoveTo::create(2.5f,ccpAdd(mPos, ccp(getContentSize().width * 0.35f, getContentSize().height * 0.15f)));
	m_pRRightGun->runAction(CCSequence::create(pDelayTime,pMoveUp,pDelayTime,NULL));
	pMoveUp = CCMoveTo::create(2.5f,ccpAdd(mPos, ccp(0.0f, getContentSize().height * 0.165f)));
	m_pMiddleGun->runAction(CCSequence::create(pDelayTime,pMoveUp,pDelayTime,NULL));

	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTailGun);
	m_sBaseColor = pRGBAProtocol->getColor();
	m_fFlashTime = 0.0f;
	m_bBaseNormal = true;
	m_eCurStage = STAGE_READY01;

	Music::playBoss_1_BgMusic();

	CCNode::onEnter();
}

void CBossSeven::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}


void CBossSeven::bossUpdate(float fEscapeTime)
{
	switch(m_eCurStage)
	{
	case STAGE_DEFAULT:
		break;
	case STAGE_ACTION01:
		{
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
				mData.mAttack = 30;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(-1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX(), getPositionY()));
				getParent()->addChild(pBullet, AIR_ZORDER);
			}

			CDrone *pDroneLL = (CDrone*)m_pLLeftGun;
			CDrone *pDroneLR = (CDrone*)m_pLRightGun;
			CDrone *pDroneRL = (CDrone*)m_pRLeftGun;
			CDrone *pDroneRR = (CDrone*)m_pRRightGun;
			CDrone *pDroneMM = (CDrone*)m_pMiddleGun;
			if (pDroneLL->isDead() && pDroneLR->isDead() && pDroneRL->isDead() && pDroneRR->isDead() && pDroneMM->isDead())
			{
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				m_pCurAttack = m_pBaseSprite;
				runEffect();
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
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTailGun);
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

void CBossSeven::underAttack(int nHurt)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02 || m_eCurStage == STAGE_ACTION02)
	{
		if (m_bBaseNormal)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTailGun);
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
				m_nBossHP = STAGEEND_HP;
				//停止转动
				stopAllActions();
				//武器毁坏
				m_pTailGun->setVisible(false);
				runEffect();
				//
			}
		}
		break;
	case STAGE_ACTION02:
		{
			//m_nBossHP -= nHurt;
			//if (m_nBossHP <= 0)
			//{
			//}
			
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


void CBossSeven::bossCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			m_pCurAttack = m_pTailGun;
			//延时
			CCDelayTime *pDelayTime = CCDelayTime::create(2.0f);
			//开火
			CCCallFunc *pFire = CCCallFunc::create(this, callfunc_selector(CBossSeven::fireTarget));
			runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pDelayTime,pFire,NULL)));
			m_eCurState = BOS_FIRE_RUN;
			m_eCurStage = STAGE_ACTION01;
		}
		break;
	case STAGE_READY02:
		{
			m_eCurStage = STAGE_ACTION02;
		}
		break;
	}
}

void CBossSeven::fireTarget(void)
{
	BULLET_DATA mData;
	mData.mAttack = 20;
	mData.mMoveSpeed = 150.0f;
	for (int i=0;i<BOSS03_STAGE01_FIRENUM;i++)
	{
		mData.mDirection = ccpNormalize(ccp(-0.8f + 1.6f / (BOSS03_STAGE01_FIRENUM - 1) * i, -1.0f));
		CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
		pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.5f));
		getParent()->addChild(pBullet, ABULLET_ZORDER);
	}
}

void CBossSeven::runEffect(void)
{
	if (!m_bBaseNormal)
	{
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTailGun);
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
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CBossSeven::effectCallback));
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
	//runAction(CCScaleTo::create(3.0f, 0.5f));
}

void CBossSeven::effectCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY02:
		{
			m_pCurAttack = NULL;
			bossCallback();
		}
		break;
	case STAGE_EXPLODE:
		{
			setVisible(false);
			//m_pLLeftGun->setVisible(false);
			//m_pLRightGun->setVisible(false);
			//m_pRLeftGun->setVisible(false);
			//m_pRRightGun->setVisible(false);
			//m_pMiddleGun->setVisible(false);
			m_pLLeftGun->removeFromParentAndCleanup(true);
			m_pLRightGun->removeFromParentAndCleanup(true);
			m_pRLeftGun->removeFromParentAndCleanup(true);
			m_pRRightGun->removeFromParentAndCleanup(true);
			m_pMiddleGun->removeFromParentAndCleanup(true);
			//等待1秒
			CCDelayTime *pDelayTime = CCDelayTime::create(1.0f);
			//原武器废弃 + 弹出新型武器
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossSeven::removeSelf));
			runAction(CCSequence::create(pDelayTime,pCallback,NULL));
		}
		break;
	}
}

void CBossSeven::removeSelf(void)
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
