#include "Drone.h"

CDrone::CDrone(void)
{
}

CDrone::~CDrone(void)
{
}


CDrone* CDrone::createDrone(void)
{
	CDrone *pDrone = new CDrone();
	pDrone->createSprite();
	pDrone->setTag(DRONE_TYPE);
	return pDrone;
}

void CDrone::createSprite(void)
{
	Music::playWarnEffect();

	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	this->schedule(schedule_selector(CDrone::droneUpdate));
}

bool CDrone::isCheck(void)
{
	if (m_eCurStage == STAGE_ACTION01)
	{
		return true;
	}
	return false;
}

CCRect CDrone::getCurBoundbox(void)
{
	//CCRect mRect = CCRectMake(0,0,0,0);
	//if (m_pCurAttack)
	//{
	//	mRect = m_pCurAttack->boundingBox();
	//	mRect.origin.x = mRect.origin.x + getPositionX() - getContentSize().width * 0.5f;
	//	mRect.origin.y = mRect.origin.y + getPositionY() - getContentSize().height * 0.5f;
	//}

	return boundingBox();
}

void CDrone::onEnter(void)
{

	setAnchorPoint(ccp(0.5f,0.76f));
	setContentSize(CCSizeMake(27,50));
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss07_Gun01_01.png"));
	m_pBaseSprite->setAnchorPoint(ccp(0.5f,0.76f));
	addChild(m_pBaseSprite, BOSS_ZORDER);
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.76f));


	m_pExplode = CCSprite::create();
	m_pExplode->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	addChild(m_pExplode, BOSS_ZORDER);

	//m_pRightFlashSprite = NULL;
	//m_pLeftExplode = NULL;
	//m_pRightExplode = NULL;

	m_nBossHP = DRONE_HP;
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		m_nBossHP = 4000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
	}


	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
	m_sBaseColor = pRGBAProtocol->getColor();
	m_fFlashTime = 0.0f;
	m_bBaseNormal = true;
	m_fTime = BOSS03_STAGE01_FIRETIME;
	m_eCurStage = STAGE_READY01;

	//延时
	CCDelayTime *pDelayTime = CCDelayTime::create(6.5f);
	CCCallFunc *pCall = CCCallFunc::create(this, callfunc_selector(CDrone::droneCallback));

	runAction((CCActionInterval*)CCSequence::create(pDelayTime,pCall,NULL));

	CCNode::onEnter();
}

void CDrone::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}


void CDrone::droneUpdate(float fEscapeTime)
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
		}
		break;
	case STAGE_ACTION03:
		{
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
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
			pRGBAProtocol->setColor(m_sBaseColor);
			m_bBaseNormal = true;
		}
	}
}

void CDrone::underAttack(int nHurt)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02 || m_eCurStage == STAGE_ACTION03)
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
				m_nBossHP = STAGEEND_HP;

				m_pBaseSprite->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss07_Gun01_02.png"));
				//停止移动
				stopAllActions();

				runEffect();
				//
			}
		}
		break;
	case STAGE_ACTION02:
		{

		}
		break;
	case STAGE_ACTION03:
		{
		}
		break;
	}


}


void CDrone::droneCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			//出场后开始执行
			//延时
			CCDelayTime *pDelayTime = CCDelayTime::create(0.5f);
			//锁定并旋转
			CCCallFunc *pLock = CCCallFunc::create(this, callfunc_selector(CDrone::lockTarget));
			//开火
			CCCallFunc *pFire = CCCallFunc::create(this, callfunc_selector(CDrone::fireTarget));
			//延时
			CCDelayTime *pCoolTime = CCDelayTime::create(0.5f);

			runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pDelayTime,pLock,pCoolTime,pFire,NULL)));
			m_eCurState = BOS_FIRE_RUN;
			m_eCurStage = STAGE_ACTION01;
		}
		break;
	case STAGE_READY02:
		break;
	case STAGE_READY03:
		{
		}
		break;
	}
}


void CDrone::lockTarget(void)
{
	CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));

	float o = m_pTarget->getPosition().x - getPosition().x;
	float a = m_pTarget->getPosition().y - getPosition().y;
	float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

	if( a < 0 ) 
	{
		if(  o < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);    
	}

	runAction(CCRotateTo::create(0.5f,180.0f + at));
}

void CDrone::fireTarget(void)
{
	BULLET_DATA mData;
	mData.mAttack = 22;
	mData.mMoveSpeed = 150.0f + CCRANDOM_0_1() * 100.0f;
	mData.mKind = BK_ARMY01;
	mData.mDirection = ccpRotateByAngle(ccp(0,-1.0f), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation() + 8.0f));
	CCPoint mLeftPos = ccpRotateByAngle(ccp(-5, -38), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
	CCPoint mRightPos = ccpRotateByAngle(ccp(5, -38), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, mData.mKind);
	pBullet->setPosition(ccp(getPositionX() + mLeftPos.x, getPositionY() + mLeftPos.y));
	getParent()->addChild(pBullet, BBULLET_ZORDER);
	mData.mDirection = ccpRotateByAngle(ccp(0,-1.0f), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation() - 8.0f));
	pBullet = CBullet::createBullet(ENEMY_BULLET, mData, mData.mKind);
	pBullet->setPosition(ccp(getPositionX() + mRightPos.x, getPositionY() + mRightPos.y));
	getParent()->addChild(pBullet, BBULLET_ZORDER);
}


void CDrone::runEffect(void)
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
	CCPoint mPos = getPosition();
	CCPoint mOffSet;
	mOffSet.x = m_pBaseSprite->getPosition().x - m_pBaseSprite->getContentSize().width * 0.5f;
	mOffSet.y = m_pBaseSprite->getPosition().y - m_pBaseSprite->getContentSize().height * 0.5f;
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create(
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pBaseSprite->getContentSize().width, CCRANDOM_0_1() * m_pBaseSprite->getContentSize().height * 0.5f))),
		pAnimate,NULL) );
	m_pExplode->runAction(pAction);
}

bool CDrone::isDead(void)
{
	if (m_nBossHP == STAGEEND_HP)
	{
		return true;
	}
	return false;
}