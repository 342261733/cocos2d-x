#include "Bullet.h"

CBullet::CBullet(void)
{
	m_sCurData.mMoveSpeed = 900.0f;
	m_sCurData.mDirection = ccp(0.0f, 1.0f);
	m_sCurData.mAttack = 10;

	m_pTarget = NULL;
	m_nTargetType = 0;
	m_fLastRatation = 0.0f;
	m_fTrackTime = 0.0f;

	m_nCurLevel = 0;
	m_eCurState = BS_DEFAULT;
	m_fBulletTime = 0.0f;

	m_nHP = 30;
}

CBullet::~CBullet(void)
{
}

void CBullet::onEnter(void)
{
	m_sFirstPos = getPosition();
	CCSprite::onEnter();
}

CBullet* CBullet::createBullet(int nBulletType, BULLET_DATA sData, BULLET_KINDS eKind)
{
	CBullet *pBullet = new CBullet();
	pBullet->m_sCurData = sData;
	pBullet->setTag(nBulletType);
	pBullet->m_nCurLevel = CGlobalData::getSingleton()->getCurLevelData().mLevel;
	if (eKind == BK_FIREBALL)
	{
		pBullet->createFireBall(eKind);
	}
	else if (eKind == BK_TARCKROCKET)
	{
		pBullet->createTrackRocket(eKind);
	}
	else if (eKind == BK_SUPERGUN)
	{
		pBullet->createSuperGun(eKind);
	}
	else if (eKind == BK_LASER)
	{
		pBullet->createLaser(eKind);
	}
	else if (eKind == BK_THUNDERBALL)
	{
		pBullet->createThunderBall(eKind);
	}
	else if (eKind == BK_SINBALL || eKind == BK_USINBALL)
	{
		pBullet->createSinBall(eKind);
	}
	else if (eKind == BK_CRESCEN || eKind == BK_UCRESCEN)
	{
		pBullet->createCrescentBullet(eKind);
	}
	else
	{
		pBullet->createSprite(eKind);
	}

	pBullet->schedule(schedule_selector(CBullet::bulletUpdate));

	pBullet->autorelease();
	return pBullet;
}

void CBullet::createSprite(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	
	char szName[128] = {0};
	sprintf(szName, "%s_%02d.png", "Bullet", (int)eKind + 1);
	initWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));

	float at = (float) CC_RADIANS_TO_DEGREES( atanf( m_sCurData.mDirection.x/m_sCurData.mDirection.y) );
	if( m_sCurData.mDirection.y < 0 ) 
	{
		if(  m_sCurData.mDirection.x < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);    
	}
	setRotation(at);

	//if (m_sCurData.mKind != BK_DEFAULT)
	//{
	//	setScale(0.5f);
	//}
	m_eCurState = BS_MOVE;
}

void CBullet::createFireBall(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Bullet05_01.png"));
	//setContentSize(CCSizeMake(50,55));
	setAnchorPoint(ccp(0.5f, 0.5f));
	char szName[128] = {0};
	CCAnimation *pAnimation = CCAnimation::create();
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%02d.png", "Bullet", (int)eKind + 1, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}

	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	runAction(CCRepeatForever::create(pAction));

	m_eCurState = BS_MOVE;
}

void CBullet::createTrackRocket(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Bullet06_01.png"));
	//setContentSize(CCSizeMake(50,55));
	setAnchorPoint(ccp(0.5f, 0.5f));
	char szName[128] = {0};
	CCAnimation *pAnimation = CCAnimation::create();
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%02d.png", "Bullet", (int)eKind + 1, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}

	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	runAction(CCRepeatForever::create(pAction));

	if (getTag() == ENEMY_BULLET)
	{
		setScale(0.5f);
		runAction(CCScaleTo::create(2.0f, 1.0f));

		float at = (float) CC_RADIANS_TO_DEGREES( atanf( m_sCurData.mDirection.x/m_sCurData.mDirection.y) );
		if( m_sCurData.mDirection.y < 0 ) 
		{
			if(  m_sCurData.mDirection.x < 0 )
				at = 180 + fabs(at);
			else
				at = 180 - fabs(at);    
		}
		setRotation(at);

		m_pEffectSprite = CCSprite::create();
		addChild(m_pEffectSprite);
	}
	m_eCurState = BS_MOVE;
}

void CBullet::createSuperGun(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Bullet07_01.png"));
	//setContentSize(CCSizeMake(50,55));
	setAnchorPoint(ccp(0.5f, 0.5f));
	char szName[128] = {0};
	CCAnimation *pAnimation = CCAnimation::create();
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%02d.png", "Bullet", (int)eKind + 1, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}

	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	runAction(CCRepeatForever::create(pAction));

	m_eCurState = BS_MOVE;
}

void CBullet::createLaser(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Bullet08_01.png"));
	//setContentSize(CCSizeMake(50,55));
	setAnchorPoint(ccp(0.5f, 0.5f));
	char szName[128] = {0};
	CCAnimation *pAnimation = CCAnimation::create();
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%02d.png", "Bullet", (int)eKind + 1, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}

	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	runAction(CCRepeatForever::create(pAction));

	float at = (float) CC_RADIANS_TO_DEGREES( atanf( m_sCurData.mDirection.x/m_sCurData.mDirection.y) );
	if( m_sCurData.mDirection.y < 0 ) 
	{
		if(  m_sCurData.mDirection.x < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);    
	}
	setRotation(at);

	m_eCurState = BS_MOVE;
}

void CBullet::createThunderBall(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Bullet09_01.png"));
	//setContentSize(CCSizeMake(50,55));
	setAnchorPoint(ccp(0.5f, 0.5f));
	char szName[128] = {0};
	CCAnimation *pAnimation = CCAnimation::create();
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%02d.png", "Bullet", (int)eKind + 1, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}

	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	runAction(CCRepeatForever::create(pAction));
	setRotation(180.0f);
	setScale(0.3f);
	runAction(CCScaleTo::create(2.0f,1.0f));

	m_eCurState = BS_MOVE;
}

void CBullet::createSinBall(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Bullet11_01.png"));
	setAnchorPoint(ccp(0.5f, 0.5f));
	//char szName[128] = {0};
	//CCAnimation *pAnimation = CCAnimation::create();
	//for (int i=0; i<ANIMATE_MAX; i++)
	//{
	//	sprintf(szName, "%s%02d_%02d.png", "Bullet", (int)eKind + 1, i+1);
	//	if (m_pCurCache->spriteFrameByName(szName) == NULL)
	//	{
	//		break;
	//	}
	//	pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	//}

	//pAnimation->setDelayPerUnit(0.1f);
	//pAnimation->setRestoreOriginalFrame(true);

	//CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	//CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	//runAction(CCRepeatForever::create(pAction));
	//runAction(CCRepeatForever::create(CCRotateTo::create(0.5f,360.0f)));

	m_eCurState = BS_MOVE;
}

void CBullet::createCrescentBullet(BULLET_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Bullet13_01.png"));
	setAnchorPoint(ccp(0.5f, 0.5f));
	setRotation(CCRANDOM_0_1() * 360.0f);

	m_eCurState = BS_MOVE;
}

void CBullet::bulletUpdate(float fEscapeTime)
{
	switch(m_eCurState)
	{
	case BS_DEFAULT:
		break;
	case BS_MOVE:
		if (getPosition().y < -getContentSize().height || getPosition().y > mScreenSize.height + getContentSize().height || getPosition().x < -getContentSize().width || getPosition().x > mScreenSize.width + getContentSize().width)
		{
			m_eCurState = BS_HIDE;
		}
		moveLogic(fEscapeTime);
		//setPosition(ccpAdd(getPosition(),ccpMult(m_sCurData.mDirection, m_sCurData.mMoveSpeed * fEscapeTime)));
		break;
	case BS_EXPLODE:
		break;
	case BS_HIDE:
		getParent()->removeChild(this, true);
		break;
	}
	fighterLogic();
	if (m_sCurData.mKind == BK_ARMY01 || m_sCurData.mKind == BK_ENEMY01 || m_sCurData.mKind == BK_SINBALL  || m_sCurData.mKind == BK_USINBALL)
	{
		setRotation(getRotation() + fEscapeTime * 360);
	}
	if (m_sCurData.mKind == BK_CRESCEN || m_sCurData.mKind == BK_UCRESCEN)
	{
		setRotation(getRotation() + fEscapeTime * 1080);
	}

	m_fBulletTime += fEscapeTime;
}

void CBullet::moveLogic(float fEscapeTime)
{
	switch(m_nTargetType)
	{
	case ENEMY_TYPE:
		{
			CEnemySprite* pEnemy = (CEnemySprite*)m_pTarget;
			if (!pEnemy->isCheck())
			{
				checkTarget();
			}
		}
		break;
	case ARMY_TYPE:
		{
			CArmySprite* pEnemy = (CArmySprite*)m_pTarget;
			if (!pEnemy->isCheck())
			{
				checkTarget();
			}
		}
		break;
	case HELI_TYPE:
		{
			CHelicopterSprite* pEnemy = (CHelicopterSprite*)m_pTarget;
			if (!pEnemy->isCheck())
			{
				checkTarget();
			}
		}
		break;
	case PALYER_TYPE:
		{
			CPlayerSprite* pPlayer = (CPlayerSprite*)m_pTarget;
			if (pPlayer->isDead())
			{
				checkTarget();
			}
		}
		break;
	case 0:
		if (m_sCurData.mKind == BK_TARCKROCKET || m_sCurData.mKind == BK_THUNDERBALL)
		{
			checkTarget();
		}
		break;
	}

	m_fLastRatation = getRotation();
	switch(m_sCurData.mKind)
	{
	case BK_THUNDERBALL:
		{
			m_fTrackTime += fEscapeTime;
			if (m_fTrackTime > TRACK_TIME)
			{
				break;
			}
			CCPoint p = ccpSub(m_pTarget->getPosition(), getPosition());
			float at = (float) CC_RADIANS_TO_DEGREES( atanf(p.x/p.y) );
			if( p.y < 0 ) 
			{
				if(  p.x < 0 )
					at = 180 + fabs(at);
				else
					at = 180 - fabs(at);  
			}
			if (m_fLastRatation > 0)
			{
				m_fLastRatation = fmodf(m_fLastRatation, 360.0f);
			}
			else
			{
				m_fLastRatation = fmodf(m_fLastRatation, -360.0f);
			}

			float m_fDiffAngle = at - m_fLastRatation;
			if (m_fDiffAngle > 180)
			{
				m_fDiffAngle -= 360;
			}

			if (m_fDiffAngle < -180)
			{
				m_fDiffAngle += 360;
			}

			if (m_fDiffAngle > 0)
			{
				m_fDiffAngle = ROTATE_MAX;
			}
			else
			{
				m_fDiffAngle = -ROTATE_MAX;
			}
			float fRotateDelta = m_fDiffAngle * fEscapeTime;
			if (abs(fRotateDelta) > abs(m_fDiffAngle))
			{
				fRotateDelta = m_fDiffAngle;
			}
			setRotation(m_fLastRatation + fRotateDelta);
			m_sCurData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
		}
		break;
	case BK_TARCKROCKET:
		{
			switch(m_nTargetType)
			{
			case ENEMY_TYPE:
				{
					CEnemySprite* pEnemy = (CEnemySprite*)m_pTarget;

					CCPoint p = ccpSub(pEnemy->boundingBox().origin, getPosition());
					float at = (float) CC_RADIANS_TO_DEGREES( atanf(p.x/p.y) );
					if( p.y < 0 ) 
					{
						if(  p.x < 0 )
							at = 180 + fabs(at);
						else
							at = 180 - fabs(at);  
					}
					if (m_fLastRatation > 0)
					{
						m_fLastRatation = fmodf(m_fLastRatation, 360.0f);
					}
					else
					{
						m_fLastRatation = fmodf(m_fLastRatation, -360.0f);
					}

					float m_fDiffAngle = at - m_fLastRatation;
					if (m_fDiffAngle > 180)
					{
						m_fDiffAngle -= 360;
					}

					if (m_fDiffAngle < -180)
					{
						m_fDiffAngle += 360;
					}
					float fRotateDelta = m_fDiffAngle * fEscapeTime * 4.0f;
					if (abs(fRotateDelta) > abs(m_fDiffAngle))
					{
						fRotateDelta = m_fDiffAngle;
					}
					setRotation(m_fLastRatation + fRotateDelta);
					m_sCurData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
					
				}
				break;
			case ARMY_TYPE:
				{
					CArmySprite* pEnemy = (CArmySprite*)m_pTarget;
					CCPoint p = ccpSub(pEnemy->boundingBox().origin, getPosition());
					float at = (float) CC_RADIANS_TO_DEGREES( atanf(p.x/p.y) );
					if( p.y < 0 ) 
					{
						if(  p.x < 0 )
							at = 180 + fabs(at);
						else
							at = 180 - fabs(at);  
					}
					if (m_fLastRatation > 0)
					{
						m_fLastRatation = fmodf(m_fLastRatation, 360.0f);
					}
					else
					{
						m_fLastRatation = fmodf(m_fLastRatation, -360.0f);
					}

					float m_fDiffAngle = at - m_fLastRatation;
					if (m_fDiffAngle > 180)
					{
						m_fDiffAngle -= 360;
					}

					if (m_fDiffAngle < -180)
					{
						m_fDiffAngle += 360;
					}
					setRotation(m_fLastRatation + m_fDiffAngle * fEscapeTime * 2);
					m_sCurData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
				}
				break;
			case HELI_TYPE:
				{
					CHelicopterSprite* pEnemy = (CHelicopterSprite*)m_pTarget;

					CCPoint p = ccpSub(pEnemy->boundingBox().origin, getPosition());
					float at = (float) CC_RADIANS_TO_DEGREES( atanf(p.x/p.y) );
					if( p.y < 0 ) 
					{
						if(  p.x < 0 )
							at = 180 + fabs(at);
						else
							at = 180 - fabs(at);  
					}
					if (m_fLastRatation > 0)
					{
						m_fLastRatation = fmodf(m_fLastRatation, 360.0f);
					}
					else
					{
						m_fLastRatation = fmodf(m_fLastRatation, -360.0f);
					}

					float m_fDiffAngle = at - m_fLastRatation;
					if (m_fDiffAngle > 180)
					{
						m_fDiffAngle -= 360;
					}

					if (m_fDiffAngle < -180)
					{
						m_fDiffAngle += 360;
					}
					setRotation(m_fLastRatation + m_fDiffAngle * fEscapeTime * 2);
					m_sCurData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
				}
				break;
			case BOSS_TYPE:
				break;
			case PALYER_TYPE:
				{
					m_fTrackTime += fEscapeTime;
					if (m_fTrackTime > TRACK_TIME)
					{
						m_fRotate = BOSS_FLY;
					}
					else
					{
						m_fRotate = BOSS_MAX;
					}
					CCPoint p = ccpSub(m_pTarget->getPosition(), getPosition());
					float at = (float) CC_RADIANS_TO_DEGREES( atanf(p.x/p.y) );
					if( p.y < 0 ) 
					{
						if(  p.x < 0 )
							at = 180 + fabs(at);
						else
							at = 180 - fabs(at);  
					}
					if (m_fLastRatation > 0)
					{
						m_fLastRatation = fmodf(m_fLastRatation, 360.0f);
					}
					else
					{
						m_fLastRatation = fmodf(m_fLastRatation, -360.0f);
					}

					float m_fDiffAngle = at - m_fLastRatation;
					if (m_fDiffAngle > 180)
					{
						m_fDiffAngle -= 360;
					}

					if (m_fDiffAngle < -180)
					{
						m_fDiffAngle += 360;
					}

					if (m_fDiffAngle > 0)
					{
						m_fDiffAngle = m_fRotate;
					}
					else
					{
						m_fDiffAngle = -m_fRotate;
					}
					float fRotateDelta = m_fDiffAngle * fEscapeTime;
					if (abs(fRotateDelta) > abs(m_fDiffAngle))
					{
						fRotateDelta = m_fDiffAngle;
					}
					setRotation(m_fLastRatation + fRotateDelta);
					m_sCurData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
				}
				break;
			}
		}
		break;
	case BK_SINBALL:
		{
			setPositionX(m_sFirstPos.x + sin(6.28f * m_fBulletTime * (m_sCurData.mMoveSpeed / 360.0f)) * m_sCurData.m_fAmplitude);
		}
		break;
	case BK_USINBALL:
		{
			setPositionX(m_sFirstPos.x - sin(6.28f * m_fBulletTime * (m_sCurData.mMoveSpeed / 360.0f)) * m_sCurData.m_fAmplitude);
		}
		break;
	case BK_CRESCEN:
		{
			setPositionX(getPositionX() + m_fBulletTime * m_sCurData.m_fAmplitude);
		}
		break;
	case BK_UCRESCEN:
		{
			setPositionX(getPositionX() - m_fBulletTime * m_sCurData.m_fAmplitude);
		}
		break;
	}

	setPosition(ccpAdd(getPosition(),ccpMult(m_sCurData.mDirection, m_sCurData.mMoveSpeed * fEscapeTime)));
}

void CBullet::checkTarget(void)
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(getParent()->getChildren(), pObj)
	{
		CCNode* pNode = (CCNode*) pObj;
		if (getTag() == PALYER_BULLET && pNode->getTag() == ENEMY_TYPE)
		{
			CEnemySprite* pEnemy = (CEnemySprite*)pObj;
			if (pEnemy->isCheck())
			{
				m_pTarget = pEnemy;
				m_nTargetType = ENEMY_TYPE;
				return;
			}
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == ARMY_TYPE)
		{
			CArmySprite* pEnemy = (CArmySprite*)pObj;
			if (pEnemy->isCheck())
			{
				m_pTarget = pEnemy;
				m_nTargetType = ARMY_TYPE;
				return;
			}
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == HELI_TYPE)
		{
			CHelicopterSprite* pEnemy = (CHelicopterSprite*)pObj;
			if (pEnemy->isCheck())
			{
				m_pTarget = pEnemy;
				m_nTargetType = HELI_TYPE;
				return;
			}
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == BOSS_TYPE)
		{
		}

		if (pNode->getTag() == PALYER_TYPE && getTag() == ENEMY_BULLET)
		{
			CPlayerSprite* pPlayer = (CPlayerSprite*)pObj;
			if (!pPlayer->isDead())
			{
				m_pTarget = pPlayer;
				m_nTargetType = PALYER_TYPE;
				return;
			}
		}
	}

	m_pTarget = NULL;
	m_nTargetType = 0;
}

void CBullet::fighterLogic(void)
{
	if (m_eCurState >= BS_EXPLODE)
	{
		return ;
	}
	CCObject* pObj = NULL;

	CCARRAY_FOREACH(getParent()->getChildren(), pObj)
	{
		CCNode* pNode = (CCNode*) pObj;
		if (getTag() == PALYER_BULLET && pNode->getTag() == ENEMY_TYPE)
		{
			CEnemySprite* pEnemy = (CEnemySprite*)pObj;
			if (pEnemy->isCheck() && boundingBox().intersectsRect(pEnemy->boundingBox()))
			{
				pEnemy->underAttack(m_sCurData.mAttack);
				m_eCurState = BS_HIDE;
				CGlobalData::getSingleton()->addBombPercentage();
				break;
			}
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == ARMY_TYPE)
		{
			CArmySprite* pEnemy = (CArmySprite*)pObj;
			if (pEnemy->isCheck() && boundingBox().intersectsRect(pEnemy->boundingBox()))
			{
				pEnemy->underAttack(m_sCurData.mAttack);
				m_eCurState = BS_HIDE;
				CGlobalData::getSingleton()->addBombPercentage();
				break;
			}
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == HELI_TYPE)
		{
			CHelicopterSprite* pHeli = (CHelicopterSprite*)pObj;
			if (pHeli->isCheck() && boundingBox().intersectsRect(pHeli->boundingBox()))
			{
				pHeli->underAttack(m_sCurData.mAttack);
				m_eCurState = BS_HIDE;
				CGlobalData::getSingleton()->addBombPercentage();
				break;

			}
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == BOSS_TYPE)
		{
			int nLevel = m_nCurLevel;
			if (nLevel == 8)
			{
				nLevel = CGlobalData::getSingleton()->getEndlessBossID();
			}
			switch(nLevel)
			{
			case 2:
				{
					CBossTwo* pBoss = (CBossTwo*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(m_sCurData.mAttack);
						m_eCurState = BS_HIDE;
						return ;
					}
				}
				break;
			case 3:
				{
					CBossThree* pBoss = (CBossThree*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(m_sCurData.mAttack);
						m_eCurState = BS_HIDE;
						return ;
					}
				}
				break;
			case 4:
				{
					CBossFour* pBoss = (CBossFour*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(m_sCurData.mAttack);
						m_eCurState = BS_HIDE;
						return ;
					}
				}
				break;
			case 5:
				{
					CBossFive* pBoss = (CBossFive*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(m_sCurData.mAttack);
						m_eCurState = BS_HIDE;
						return ;
					}
				}
				break;
			case 6:
				{
					CBossSix* pBoss = (CBossSix*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(m_sCurData.mAttack);
						m_eCurState = BS_HIDE;
						return ;
					}
				}
				break;
			case 7:
				{
					CBossSeven* pBoss = (CBossSeven*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(m_sCurData.mAttack);
						m_eCurState = BS_HIDE;
						return ;
					}
				}
				break;
			}
			
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == DRONE_TYPE)
		{
			CDrone* pBoss = (CDrone*)pObj;
			//CCRect ppp = pBoss->getCurBoundbox();
			//CCRect rrr = pBoss->boundingBox();
			if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
			{
				pBoss->underAttack(m_sCurData.mAttack);
				m_eCurState = BS_HIDE;
				break;
			}
		}

		if (getTag() == PALYER_BULLET && pNode->getTag() == ENEMY_BULLET)
		{
			CBullet* pRocket = (CBullet*)pObj;
			if (pRocket->isCheck() && pRocket->getKind() == BK_TARCKROCKET && boundingBox().intersectsRect(pRocket->boundingBox()))
			{
				pRocket->underAttack(m_sCurData.mAttack);
				m_eCurState = BS_HIDE;
				break;

			}
		}

		if (getTag() == ENEMY_BULLET && pNode->getTag() == PALYER_TYPE)
		{
			CPlayerSprite* pPlayer = (CPlayerSprite*)pObj;
			if (!pPlayer->isDead())
			{
				if ((m_sCurData.mKind != BK_LASER || m_sCurData.mKind != BK_TARCKROCKET) && getPositionY() > pPlayer->getPositionY() && pPlayer->isShieldTaken() && ccpDistance(getPosition(), pPlayer->getPosition()) < SHIELD_DES)
				{
					setTag(PALYER_BULLET);
					m_sCurData.mDirection = ccpNormalize(ccpSub(getPosition(), pPlayer->getPosition()));
					break;
				}

				if (boundingBox().intersectsRect(pPlayer->boundingBox()))
				{
					pPlayer->underAttack(m_sCurData.mAttack);
					m_eCurState = BS_HIDE;
					break;
				}
			}
		}
	}
}

bool CBullet::isCheck(void)
{
	if (m_eCurState < BS_EXPLODE)
	{
		return true;
	}

	return false;
}

void CBullet::underAttack(int nHurt)
{
	if (m_eCurState >= BS_EXPLODE)
	{
		return ;
	}

	m_nHP -= nHurt;



	//if (m_bIsNormal)
	//{
	//	for (unsigned int i=0; i<m_vEnemySpriteVector.size(); i++)
	//	{
	//		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vEnemySpriteVector[i]);
	//		color = pRGBAProtocol->getColor();
	//		pRGBAProtocol->setColor(ccc3(255,0,0));
	//	}
	//	m_bIsNormal = false;

	//}

	if (m_nHP < 0)
	{
		m_nHP = 0;
		m_eCurState = BS_EXPLODE;
		stopAllActions();
		setDisplayFrame(m_pCurCache->spriteFrameByName("Bullet06_EX.png"));
		//CGlobalData::getSingleton()->addScore(m_sCurData.mScoreValue);
		//m_pCurAudio->playEffect("sounds/Explode01.ogg");
		//CGlobalData::getSingleton()->addDesAirScore(m_sCurFlyData.mKind);
		runEffect();
	}
}

void CBullet::runEffect(void)
{
	CCAnimation *pAnimation = CCAnimation::create();

	char szName[128] = {0};
	//sprintf(szName, "%s%02d-%02d_0001.png", m_cName, m_sCurData.mAction, m_sCurData.mDirection);

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
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CBullet::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,pCallback,NULL) );
	m_pEffectSprite->runAction(pAction);
}

void CBullet::removeSelf(void)
{
	m_eCurState = BS_HIDE;
}