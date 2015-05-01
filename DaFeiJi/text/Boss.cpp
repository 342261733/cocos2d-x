#include "Boss.h"

CBoss::CBoss(void)
{
	m_eCurState = BOS_DEFAULT;
	m_fTime = 0.0f;
	m_pBaseSprite = NULL;
	m_eCurStage = STAGE_DEFAULT;
}

CBoss::~CBoss(void)
{
}

CBoss* CBoss::createBoss(BOSS_KINDS eKind)
{
	CBoss *pBoss = new CBoss();
	pBoss->createSprite(eKind);
	pBoss->setTag(BOSS_TYPE);
	pBoss->m_eBossKind = eKind;
	return pBoss;
}


void CBoss::createSprite(BOSS_KINDS eKind)
{
	Music::playWarnEffect();

	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	this->schedule(schedule_selector(CBoss::bossUpdate));
}

bool CBoss::isCheck(void)
{
	return false;
}

CCRect CBoss::getCurBoundbox(void)
{
	CCRect rect = CCRectMake(0,0,0,0);
	return rect;
}

void CBoss::onEnter()
{
	initCommandos();
	CCNode::onEnter();
}

void CBoss::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}

void CBoss::bossUpdate(float fEscapeTime)
{
	switch(m_eCurState)
	{
	case BOS_READY_RUN:
		m_fTime += fEscapeTime;
		if (m_fTime > 3.0f)
		{
			m_eCurState = BOS_FIRE;
			m_fTime = 0.0f;
		}
		break;
	case BOS_FIRE:
		commandosUpdate(fEscapeTime);
		break;
	}
	
}

void CBoss::underAttack(int nHurt)
{
}


void CBoss::initCommandos(void)
{
	m_nPlaneNum = 23;
	m_fDeltaTime = 1.0f;
}

void CBoss::commandosUpdate(float fEscapeTime)
{
	m_fTime += fEscapeTime;
	if (m_nPlaneNum <= 0)
	{
		if (m_fTime > 5.0f)
		{
			m_eCurState = BOS_HIDE;
			m_eCurStage = STAGE_EXPLODE;
			CGlobalData::getSingleton()->setLevelClear(true);
		}
		return ;
	}

	if (m_fTime > m_fDeltaTime)
	{
		m_nPlaneNum --;
		m_fTime = 0.0f;

		FLY_DATA mData;
		float mRand = CCRANDOM_0_1();
		if (mRand > 0.75f)
		{
			mData.mKind = EK_DEFAULT;
		}
		else if (mRand > 0.5f)
		{
			mData.mKind = EK_PLANE02;
		}
		else if (mRand > 0.25f)
		{
			mData.mKind = EK_PLANE03;
		}
		else 
		{
			mData.mKind = EK_PLANE04;
		}

		mData.m_fTime = 0.0f;
		mData.mAttitude = FA_DEFAULT;
		mData.mPosition = ccp( 100 + 140 * (m_nPlaneNum % 3), 800.0f - BANNER_HEIGHT);
		CEnemySprite *pSprite = CEnemySprite::createEnemy(mData.mKind, mData, EW_SCATTER);
		getParent()->addChild(pSprite, AIR_ZORDER);
		CGlobalData::getSingleton()->addAirScore(mData.mKind);
	}
}

void CBoss::runEffect(void)
{

}

void CBoss::removeSelf(void)
{
	m_eCurState = BOS_HIDE;
	CGlobalData::getSingleton()->setLevelClear(true);
}
