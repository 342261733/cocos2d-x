#include "HelicopterSprite.h"

CHelicopterSprite::CHelicopterSprite(void)
{
	m_eCurState = HS_DEFAULT;
	m_pEffectSprite = NULL;
	m_fTime = 2.0f;
	m_fHoverTime = 0.0f;
	m_pFlashAction = NULL;
	m_pShadow = NULL;
	m_bIsNormal = true;
	m_nFireNum = 0;
	m_fFlashTime = 0.0f;
}

CHelicopterSprite::~CHelicopterSprite(void)
{
}

void CHelicopterSprite::onEnter()
{
	createShadow();
	m_eCurState = HS_MOVE;
	//CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CHelicopterSprite::nextAction));
	runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create(1.0f,ccpAdd(getPosition(), ccp(0, - mScreenSize.height * 0.3f))),pCallback,NULL)));
	//runAction(CCMoveTo::create(2.5f,ccpAdd(getPosition(), ccp(0, - mScreenSize.height * 0.4f))));
	if (m_sCurData.mKind == EK_HELI02)
	{
		m_nFireNum = 1;
	}
	CCNode::onEnter();
}

void CHelicopterSprite::onExit()
{
	if (m_pShadow != NULL)
	{
		m_pShadow->getParent()->removeChild(m_pShadow, true);
	}
	CCNode::onExit();
}

CHelicopterSprite* CHelicopterSprite::createHeli(ENEMY_KINDS eKind, FLY_DATA sData)
{
	CHelicopterSprite *pHelicopter = new CHelicopterSprite();
	pHelicopter->m_sCurFlyData = sData;
	pHelicopter->createSprite(eKind);
	pHelicopter->setTag(HELI_TYPE);
	return pHelicopter;
}

void CHelicopterSprite::createSprite(ENEMY_KINDS eKind)
{
	//std::string tString = CGlobalData::getSingleton()->getNameByEnum(eKind);
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_sCurData = CGlobalData::getSingleton()->getDataByKind(eKind);
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	char szName[128] = {0};
	//sprintf(szName, "%s%02d_01.png", "Plane", m_sCurData);

	setContentSize(CCSizeMake(38,96));
	sprintf(szName, "%s%02d.png", "NPC_Plane", m_sCurData.mIndex);
	if (m_pCurCache->spriteFrameByName(szName) == NULL)
	{
		return ;
	}
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	addChild(m_pBaseSprite);

	if (m_pCurCache->spriteFrameByName("Propeller.png") == NULL)
	{
		return ;
	}
	m_pPropellerSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Propeller.png"));
	m_pPropellerSprite->setPosition(ccp(m_pBaseSprite->getContentSize().width * 0.5f, m_pBaseSprite->getContentSize().height * 0.36f));
	m_pBaseSprite->addChild(m_pPropellerSprite);

	m_pEffectSprite = CCSprite::create();
	m_pEffectSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	addChild(m_pEffectSprite);

	//create and mount weapon
	//m_pPlayerWeapon = CPlayerWeapon::createWeapon();
	//addChild(m_pPlayerWeapon);

	setPosition(m_sCurFlyData.mPosition);
	setAnchorPoint(ccp(0.5f,0.5f));
	m_fFireTime = 0.25f;

	this->schedule(schedule_selector(CHelicopterSprite::enemyUpdate));
}

void CHelicopterSprite::createShadow(void)
{
	m_pShadow = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Shadow_H.png"));
	m_pShadow->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width, 0.0f)));
	m_pShadow->setRotation(getRotation());
	m_pShadow->setScale(0.8f);
	getParent()->addChild(m_pShadow, LCLOUD_ZORDER);
}

void CHelicopterSprite::enemyUpdate(float fEscapeTime)
{
	switch(m_eCurState)
	{
	case HS_DEFAULT:
		break;
	case HS_MOVE:

		break;
	case HS_FIRE:

		break;
	case HS_ESC:

		break;
	case HS_EXPLODE:
		break;
	case HS_HIDE:

		getParent()->removeChild(this, true);
		break;
	}

	if (m_eCurState < HS_EXPLODE)
	{
		m_pShadow->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width, 0.0f)));
		m_pShadow->setRotation(getRotation());
		m_pPropellerSprite->setRotation(m_pPropellerSprite->getRotation() + fEscapeTime * 180);
		boundPlayer();
	}

	if (!m_bIsNormal)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
			pRGBAProtocol->setColor(color);
			m_bIsNormal = true;
		}
	}
}

void CHelicopterSprite::nextAction(void)
{
	switch(m_eCurState)
	{
	case HS_DEFAULT:
		break;
	case HS_MOVE:
		{
			CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));
			if (m_pTarget)
			{
				m_eCurState = HS_SEARCH;
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
				//mData.mDirection = ccpNormalize(ccpSub(m_pTarget->getPosition(), getPosition()));
				//m_pBaseSprite->setRotation(180 + at);
				CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CHelicopterSprite::nextAction));
				runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(0.5f,180 + at),pCallback,NULL)));
			}
		}
		break;
	case HS_SEARCH:
		{
			if (m_nFireNum < 3)
			{
				m_eCurState = HS_MOVE;
				m_nFireNum ++;
			}
			else
			{
				m_eCurState = HS_ESC;
			}
			CCCallFunc* pCallFire = CCCallFunc::create(this, callfunc_selector(CHelicopterSprite::fireBullet));
			CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CHelicopterSprite::nextAction));
			if (m_sCurData.mKind == EK_HELI01)
			{
				runAction((CCActionInterval*)(CCSequence::create(pCallFire, CCDelayTime::create(m_fFireTime),pCallFire/*, CCDelayTime::create(m_fFireTime),pCallFire, CCDelayTime::create(m_fFireTime),pCallFire*/, pCallback,NULL)));
			}

			if (m_sCurData.mKind == EK_HELI02)
			{
				runAction((CCActionInterval*)(CCSequence::create(pCallFire, CCDelayTime::create(1.0f), pCallback,NULL)));
			}
		}
		break;
	case HS_FIRE:
		{
		}
		break;
	case HS_ESC:
		{
			m_eCurState = HS_GAS;
			float o = 0.0f;
			float a = 1.0f;
			float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

			if( a < 0 ) 
			{
				if(  o < 0 )
					at = 180 + fabs(at);
				else
					at = 180 - fabs(at);    
			}
			CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CHelicopterSprite::nextAction));
			runAction((CCActionInterval*)(CCSequence::create(CCRotateTo::create(1.0f, 180 + at), CCMoveTo::create(1.5f,ccp(getPositionX(), mScreenSize.height)),pCallback,NULL)));
		}
		break;
	case HS_GAS:
		m_eCurState = HS_HIDE;
		break;
	case HS_EXPLODE:
		break;
	case HS_HIDE:

		break;
	}
}

void CHelicopterSprite::underAttack(int nHurt)
{
	if (m_eCurState >= HS_EXPLODE)
	{
		return ;
	}
	if (m_bIsNormal)
	{
		m_bIsNormal = false;
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
		color = pRGBAProtocol->getColor();
		pRGBAProtocol->setColor(ccc3(255,0,0));
	}
	m_sCurData.mHealthPoint -= nHurt;
	if (m_sCurData.mHealthPoint < 0)
	{
		Music::playExplode2Effect();

		m_sCurData.mHealthPoint = 0;
		m_eCurState = HS_EXPLODE;
		m_pBaseSprite->setVisible(false);
		m_pPropellerSprite->setVisible(false);
		m_pShadow->setVisible(false);
		CGlobalData::getSingleton()->addScore(m_sCurData.mScoreValue);
		CGlobalData::getSingleton()->addDesAirScore(m_sCurFlyData.mKind);

		ASSESS_DATA mData;
		if (CCRANDOM_0_1() > 0.5f)
		{
			mData.mKind = ASK_PERFECT;
		}
		else
		{
			mData.mKind = ASK_DEFAULT;
		}
		mData.mPos = getPosition();
		CAssess *pAssess = CAssess::createAssess(mData);
		getParent()->addChild(pAssess, ASSESS_ZORDER);
		mData.mKind = ASK_ADD100;
		mData.mPos = ccpAdd(mData.mPos, ccp(0, getContentSize().height * 0.5f));
		pAssess = CAssess::createAssess(mData);
		getParent()->addChild(pAssess, ASSESS_ZORDER);
		m_pShadow->getParent()->removeChild(m_pShadow, true);
		m_pShadow = NULL;
		stopAllActions();
		runEffect();
	}
}

void CHelicopterSprite::runEffect(void)
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


	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CHelicopterSprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,pCallback,NULL) );
	m_pEffectSprite->runAction(pAction);
}

void CHelicopterSprite::removeSelf(void)
{
	if (CGlobalData::getSingleton()->isDropItem())
	{
		if (CCRANDOM_0_1() < 0.6f)
		{
			CGlobalData::getSingleton()->recordDropTime();
			//create item

			CItemSprite *pItem = CItemSprite::createItem(IK_DEFAULT);
			pItem->setPosition(getPosition());
			getParent()->addChild(pItem, PLAYER_ZORDER);
		}
	}
	m_eCurState = HS_HIDE;
}

bool CHelicopterSprite::isCheck(void)
{
	if (m_eCurState < HS_EXPLODE && isInScene())
	{
		return true;
	}

	return false;
}

bool CHelicopterSprite::isInScene(void)
{
	if (boundingBox().getMidX() > 0 && boundingBox().getMidX() < mScreenSize.width && boundingBox().getMidY() > 0 && boundingBox().getMidY() < mScreenSize.height - BANNER_HEIGHT)
	{
		return true;
	}
	return false;
}

void CHelicopterSprite::fireBullet(void)
{
	m_fTime = 0.0f;
	
	if (m_sCurData.mKind == EK_HELI01)
	{
		//CCLOG("%d",m_sCurData.mAttack);
		mData.mAttack = m_sCurData.mAttack;
		mData.mKind = BK_ARMY01;
		mData.mMoveSpeed = 300.0f;

		mData.mDirection = ccpRotateByAngle(ccp(0, -1), ccp(0,0), -CC_DEGREES_TO_RADIANS(getRotation()));
		CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
		pBullet->setPosition(getPosition());
		getParent()->addChild(pBullet, ABULLET_ZORDER);

		mData.mDirection =  ccpRotateByAngle(mData.mDirection, ccp(0,0), CC_DEGREES_TO_RADIANS(25));
		pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
		pBullet->setPosition(getPosition());
		getParent()->addChild(pBullet, ABULLET_ZORDER);

		mData.mDirection =  ccpRotateByAngle(mData.mDirection, ccp(0,0), -CC_DEGREES_TO_RADIANS(50));
		pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
		pBullet->setPosition(getPosition());
		getParent()->addChild(pBullet, ABULLET_ZORDER);
	}

	if (m_sCurData.mKind == EK_HELI02)
	{
		BULLET_DATA mData;
		mData.mKind = BK_TARCKROCKET;
		mData.mAttack = m_sCurData.mAttack * 2;
		mData.mMoveSpeed = 200.0f;
		mData.mDirection = ccp(-1.0f, 0.0f);
		CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
		pBullet->setPosition(ccp(getPositionX(), getPositionY()));
		getParent()->addChild(pBullet, ABULLET_ZORDER);
	}

}

void CHelicopterSprite::boundPlayer(void)
{
	if (m_eCurState >= HS_EXPLODE)
	{
		return ;
	}
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(getParent()->getChildren(), pObj)
	{
		CCNode* pNode = (CCNode*) pObj;
		if (pNode->getTag() == PALYER_TYPE)
		{
			CPlayerSprite* pPlayer = (CPlayerSprite*)pObj;

			if (!pPlayer->isDead() && boundingBox().intersectsRect(pPlayer->boundingBox()))
			{
				pPlayer->underAttack(m_sCurData.mAttack + 1000);
				break;
			}

		}

	}
}
