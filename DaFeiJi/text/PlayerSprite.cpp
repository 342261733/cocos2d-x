#include "PlayerSprite.h"

CPlayerSprite::CPlayerSprite(void)
{
	m_vPlayerSpriteVector.clear();
	m_sCurData.mIndex = 1;
	m_sCurData.mWeapon = PW_DEFAULT;
	m_eCurState = PS_DEFAULT;

	m_fTime = 0.0f;
	m_nCurFrame = 0;
	m_fBtime = 0.0f;
	m_fFireHoldTime = 0.0f;
	m_fIronCurtainTime = 0.0f;
	m_fFireBallSlot = FIREBALL_SLOT;
	m_fFireBallTime = 0.0f;
	m_fTarckRocketSlot = TARCKROCKET_SLOT;
	m_fSuperGunTime = 0.0f;
	m_fSuperGunSlot = SUPERGUN_SLOT;
	m_fSuperGunPos = 0.0f;
	m_fSideBulletTime = 0.0f;
	m_fSideBulletSlot = SIDEBULLET_SLOT;
	m_fWingManTime = 0.0f;
	m_fWingManSlot = WINGMAN_SLOT;
	m_nFireLevel = 0;
	m_bIsNormal = true;

	m_fBRoundTime = 0.0f;
	m_nBNumber = 0;
	m_pFireFlashSprite = NULL;
	m_fFlashTime = 0.0f;
	m_eHoldItem = IK_DEFAULT;
	m_fPlayerTime = 0.0f;
}

CPlayerSprite::~CPlayerSprite(void)
{
}

CPlayerSprite* CPlayerSprite::createPlayer(PLAYER_KINDS eKind)
{
	CPlayerSprite *pPlayer = new CPlayerSprite();
	pPlayer->createSprite(eKind);
	pPlayer->setTag(PALYER_TYPE);
	return pPlayer;
}

void CPlayerSprite::createSprite(PLAYER_KINDS eKind)
{
	//std::string tString = CGlobalData::getSingleton()->getNameByEnum(eKind);
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_sCurData = CGlobalData::getSingleton()->getDataByKind(eKind);
	m_sInitData = CGlobalData::getSingleton()->getDataByKind(eKind);
	//属性加成
	//m_sCurData.mArmor = ;
	//m_sCurData.mAttack = ;
	//m_sCurData.mBonusAttack = ;
	//m_sCurData.mSpeed = m_sCurData.mSpeed * (1 + CGlobalData::get);
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	char szName[128] = {0};

	setContentSize(CCSizeMake(25.0f,27.5f));
	setAnchorPoint(ccp(0.5f, 0.5f));

	m_pShadow = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Shadow.png"));
	m_pShadow->setPosition(ccp(getContentSize().width * 0.5f + m_pShadow->getContentSize().width * 0.5f, getContentSize().height * 0.5f - m_pShadow->getContentSize().height * 0.5f));
	m_pShadow->setRotation(180);
	m_pShadow->setScale(0.8f);
	addChild(m_pShadow);

	//m_pFireFlashSprite = CCSprite::create();
	//m_pFireFlashSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 1.2f));
	//addChild(m_pFireFlashSprite);
	//sprintf(szName, "%s%02d_01.png", "Plane", m_sCurData);
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%04d.png", "PC_Plane", m_sCurData.mIndex, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}

		CCSprite *pPlayerSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
		pPlayerSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
		pPlayerSprite->setVisible(false);
		addChild(pPlayerSprite);

		m_vPlayerSpriteVector.push_back(pPlayerSprite);
	}

	//ShieldTaken
	m_pShieldTaken = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("ShieldTaken_01.png"));
	m_pShieldTaken->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	m_pShieldTaken->setVisible(false);
	addChild(m_pShieldTaken);

	//set middle frame
	if (m_vPlayerSpriteVector.size() > 0)
	{
		m_vPlayerSpriteVector[m_vPlayerSpriteVector.size() / 2]->setVisible(true);
		m_nCurFrame = m_vPlayerSpriteVector.size() / 2;
	}

	m_pEffectSprite = CCSprite::create();
	m_pEffectSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	addChild(m_pEffectSprite);

	setPosition(ccp(mScreenSize.width * 0.5f, -mScreenSize.height * 0.1f));
	setTargetPoint(getPosition());
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::activatePlayer));
	runAction((CCActionInterval*)(CCSequence::create( CCSpawn::create(
																		CCMoveTo::create(1.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.2f)), 
																		CCBlink::create(1.1f,5),NULL
																		),pCallback,NULL)));
	
	m_eCurState = PS_AUTOMOVE;

	this->schedule(schedule_selector(CPlayerSprite::playerUpdate));

	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vPlayerSpriteVector[0]);
	m_sOriginalColor = pRGBAProtocol->getColor();

}

void CPlayerSprite::activatePlayer(void)
{
	m_eCurState = PS_MOVE;	
	setTargetPoint(getPosition());
}

void CPlayerSprite::playerUpdate(float fEscapeTime)
{
	m_fTime += fEscapeTime;
	if (m_eCurState <= PS_LANDING && m_fTime > PFRAME_TIME && m_eCurState > PS_AUTOMOVE)
	{
		m_fTime -= PFRAME_TIME;
		//CCLOG("offset: %f", m_tTargetPosition.x - getPosition().x);
		setFlyingAttitude(m_tTargetPosition.x - getPosition().x);
	}

	switch(m_eCurState)
	{
	case PS_DEFAULT:
		break;
	case PS_AUTOMOVE:
		break;
	case PS_MOVE:
		{
			if (CGlobalData::getSingleton()->isGravityControl())
			{
				//m_sGravityOffset;
				//m_tTargetPosition = getPosition()
				CCPoint mPos = ccpAdd(getPosition(),ccpMult(m_sGravityOffset, m_sCurData.mSpeed * fEscapeTime));
				if (mPos.x < getContentSize().width * 0.5f)
				{
					mPos.x = getContentSize().width * 0.5f;
				}

				if (mPos.x > mScreenSize.width - getContentSize().width * 0.5f)
				{
					mPos.x = mScreenSize.width - getContentSize().width * 0.5f;
				}

				if (mPos.y < getContentSize().height * 0.5f + TOUCH_OFFSET)
				{
					mPos.y = getContentSize().height * 0.5f + TOUCH_OFFSET;
				}

				if (mPos.y > mScreenSize.height - getContentSize().height * 0.5f - BANNER_HEIGHT)
				{
					mPos.y = mScreenSize.height - getContentSize().height * 0.5f - BANNER_HEIGHT;
				}
				setPosition(mPos);
				m_tTargetPosition = ccpAdd(getPosition(),ccpMult(m_sGravityOffset, m_sCurData.mSpeed));
				break;
			}

			CCPoint p = ccpSub(m_tTargetPosition, getPosition());
			p = ccpNormalize(p);
			p = ccpMult(p, m_sCurData.mSpeed * fEscapeTime);
			if (ccpDistance(getPosition(), m_tTargetPosition) > ccpLength(p))
			{
				setPosition(ccpAdd(getPosition(),p));
			}
			else
			{
				setPosition(m_tTargetPosition);
			}

		}
		break;
	case PS_AUTOFLY:
		if (ccpDistance(getPosition(), m_tTargetPosition) > OFFSET_MAX)
		{
			CCPoint p = ccpSub(m_tTargetPosition, getPosition());
			p = ccpNormalize(p);	
			setPosition(ccpAdd(getPosition(),ccpMult(p, m_sCurData.mSpeed * fEscapeTime)));
		}
		else
		{
			setPosition(m_tTargetPosition);
			m_eCurState = PS_LANDING;
		}
		break;
	case PS_LANDING:
		break;
	case PS_EXPLODE:
		break;
	case PS_HIDE:
		break;
	}


	//m_fTime += fEscapeTime;
	//if (m_eCurState <= PS_LANDING && m_fTime > FRAME_TIME && m_eCurState > PS_AUTOMOVE)
	//{
	//	m_fTime -= FRAME_TIME;
	//	setFlyingAttitude(m_tTargetPosition.x - getPosition().x);
	//}

	if (m_eCurState < PS_AUTOFLY && m_eCurState > PS_AUTOMOVE)
	{
		fireBullet(fEscapeTime);
		itemUpdate(fEscapeTime);
	}


	if (!m_bIsNormal)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			for (unsigned int i=0; i<m_vPlayerSpriteVector.size(); i++)
			{
				CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vPlayerSpriteVector[i]);
				pRGBAProtocol->setColor(color);
			}
			
			m_bIsNormal = true;
		}
	}

	if (m_pShieldTaken->isVisible())
	{
		m_pShieldTaken->setRotation(m_pShieldTaken->getRotation() + fEscapeTime * 1080);
	}

}

void CPlayerSprite::fireBullet(float fEscapeTime)
{
	m_fPlayerTime += fEscapeTime;

	m_fBRoundTime += fEscapeTime;
	if (m_fBRoundTime > 0.28f)
	{
		if (m_fBRoundTime > 0.42f)
		{
			m_fBRoundTime = 0.0f;
		}
		return ;
	}
	m_fBtime += fEscapeTime;
	if (m_fBtime > 0.07f)
	{
		m_fBtime = 0.0f;
		BULLET_DATA mData;
		mData.mAttack = m_sCurData.mAttack;
		mData.mDirection = ccp(0.0f, 1.0f);
		mData.mKind = BK_DEFAULT;
		mData.mMoveSpeed = 900.0f;
		CBullet *pBullet = NULL;
		
		switch (m_nFireLevel)
		{
		case 0:
			if (m_sCurData.mKind == PK_DEFAULT)
			{
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_HURRICANE)
			{
				mData.mMoveSpeed = 450.0f;
				mData.mKind = BK_SINBALL;
				mData.m_fAmplitude = 45.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_SINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_USINBALL;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_USINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_WOLFANG)
			{
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_EAGLEEYE)
			{
				mData.mMoveSpeed = 500.0f;
				mData.mKind = BK_CRESCEN;
				mData.m_fAmplitude = 1.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_CRESCEN);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_UCRESCEN;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_UCRESCEN);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_KINGKONG)
			{
				mData.mDirection.x = sin(m_fPlayerTime * 3.14f) * 0.113f;
				mData.mDirection.y = 0.993f;
				mData.mDirection = ccpNormalize(mData.mDirection);
				mData.mMoveSpeed = 500.0f;
				mData.mKind = BK_BLUE;
				mData.m_fAmplitude = 1.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mDirection.x = -mData.mDirection.x;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else
			{
				//pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				//pBullet->setPosition(getPosition());
				//getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			break;
		case 1:
			mData.mAttack = m_sCurData.mAttack;

			if (m_sCurData.mKind == PK_DEFAULT)
			{
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.75f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.75f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_HURRICANE)
			{
				mData.mMoveSpeed = 450.0f;
				mData.mKind = BK_SINBALL;
				mData.m_fAmplitude = 90.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_SINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_USINBALL;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_USINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mMoveSpeed = 450.0f;
				mData.mKind = BK_SINBALL;
				mData.m_fAmplitude = 45.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_SINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_USINBALL;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_USINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_WOLFANG)
			{
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection = ccp(-0.7f, 3.732f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mDirection = ccp(0.7f, 3.732f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_EAGLEEYE)
			{
				mData.mMoveSpeed = 500.0f;
				mData.mKind = BK_CRESCEN;
				mData.m_fAmplitude = 1.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_CRESCEN);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_UCRESCEN;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_UCRESCEN);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mKind = BK_CRESCEN;
				mData.m_fAmplitude = 7.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_CRESCEN);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_UCRESCEN;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_UCRESCEN);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_KINGKONG)
			{
				mData.mDirection.x = sin(m_fPlayerTime * 3.14f) * 0.113f;
				mData.mDirection.y = 0.993f;
				mData.mDirection = ccpNormalize(mData.mDirection);
				mData.mMoveSpeed = 500.0f;
				mData.mKind = BK_BLUE;
				mData.m_fAmplitude = 1.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 1.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection.x = -mData.mDirection.x;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 1.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else
			{
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection = ccp(-0.8f, 3.732f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mDirection = ccp(0.8f, 3.732f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			break;
		case 2:
			mData.mAttack = m_sCurData.mAttack;
			if (m_sCurData.mKind == PK_DEFAULT)
			{
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.75f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.75f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 1.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.66f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 1.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.66f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_HURRICANE)
			{
				mData.mMoveSpeed = 450.0f;
				mData.mKind = BK_SINBALL;
				mData.m_fAmplitude = 45.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_SINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_USINBALL;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_USINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mKind = BK_SINBALL;
				mData.m_fAmplitude = 90.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_SINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_USINBALL;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_USINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mKind = BK_SINBALL;
				mData.m_fAmplitude = 150.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_SINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_USINBALL;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_USINBALL);
				pBullet->setPositionX(getPosition().x);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_WOLFANG)
			{
				mData.mDirection = ccp(-0.7f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 1.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mDirection = ccp(-0.4f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection = ccp(0.0f, 1.0f);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection = ccp(0.4f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mDirection = ccp(0.7f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_LASER);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 1.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_EAGLEEYE)
			{
				mData.mMoveSpeed = 500.0f;
				mData.mKind = BK_CRESCEN;
				mData.m_fAmplitude = 1.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_CRESCEN);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_UCRESCEN;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_UCRESCEN);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mKind = BK_CRESCEN;
				mData.m_fAmplitude = 7.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_CRESCEN);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_UCRESCEN;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_UCRESCEN);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mKind = BK_CRESCEN;
				mData.m_fAmplitude = 12.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_CRESCEN);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mKind = BK_UCRESCEN;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_UCRESCEN);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else if (m_sCurData.mKind == PK_KINGKONG)
			{
				mData.mDirection.x = sin(m_fPlayerTime * 3.14f) * 0.113f;
				mData.mDirection.y = 0.993f;
				mData.mDirection = ccpNormalize(mData.mDirection);
				mData.mMoveSpeed = 500.0f;
				mData.mKind = BK_BLUE;
				mData.m_fAmplitude = 1.0f;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 2.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 1.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection.x = -mData.mDirection.x;
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 2.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_BLUE);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 1.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			else
			{
				mData.mDirection = ccp(-0.8f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 1.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mDirection = ccp(-0.5f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection = ccp(0.0f, 1.0f);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x - pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.5f);
				pBullet->setPositionY(getPosition().y);
				getParent()->addChild(pBullet, PBULLET_ZORDER);

				mData.mDirection = ccp(0.5f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 0.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
				mData.mDirection = ccp(0.8f, 2.5f);
				mData.mDirection = ccpNormalize(mData.mDirection);
				pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT01);
				pBullet->setPositionX(getPosition().x + pBullet->getContentSize().width * 1.25f);
				pBullet->setPositionY(getPosition().y - pBullet->getContentSize().height * 0.33f);
				getParent()->addChild(pBullet, PBULLET_ZORDER);
			}
			break;
		}

		Music::playFireEffect();

		//Fire Flash
		if (m_pFireFlashSprite)
		{
			//detachChild(m_pFireFlashSprite, true);
			removeChild(m_pFireFlashSprite, true);
			m_pFireFlashSprite = NULL;
		}
		m_pFireFlashSprite = CCSprite::create();
		m_pFireFlashSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 2.0f));
		addChild(m_pFireFlashSprite, -1);

		CCAnimation *pAnimation = CCAnimation::create();

		char szName[128] = {0};

		for (int i=0; i<ANIMATE_MAX; i++)
		{
			sprintf(szName, "Flash01_%02d.png", i+1);
			if (m_pCurCache->spriteFrameByName(szName) == NULL)
			{
				break;
			}
			pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
		}


		pAnimation->setDelayPerUnit(0.015f);
		pAnimation->setRestoreOriginalFrame(true);

		CCAnimate *pAnimate = CCAnimate::create(pAnimation);
		m_pFireFlashSprite->stopAllActions();
		m_pFireFlashSprite->runAction(pAnimate);
		
	}

}

void CPlayerSprite::setAutoFly(void)
{
	m_eCurState = PS_AUTOFLY;
	m_tTargetPosition = ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.2f);
	removeAllItem();
	//displayFrameByIndex(m_vPlayerSpriteVector.size() / 2);
}

void CPlayerSprite::setTargetPoint(const CCPoint& pos)
{
	if (m_eCurState >= PS_AUTOFLY)
	{
		return ;
	}
	if (m_eCurState <= PS_AUTOMOVE)
	{
		return ;
	}
	m_tTargetPosition = pos;
}

void CPlayerSprite::setFlyingAttitude(float fOffset)
{
	if (abs(fOffset) > FLYING_MAX)
	{
		if (fOffset > 0.0f)
		{
			m_nCurFrame ++;
			if (m_nCurFrame >= m_vPlayerSpriteVector.size())
			{
				m_nCurFrame = m_vPlayerSpriteVector.size() - 1;
			}
			//m_nCurFrame = m_vPlayerSpriteVector.size() - 1;
			displayFrameByIndex(m_nCurFrame);
		}

		if (fOffset < 0.0f)
		{
			m_nCurFrame --;
			if (m_nCurFrame <= 0)
			{
				m_nCurFrame = 0;
			}
			//m_nCurFrame = 0;
			displayFrameByIndex(m_nCurFrame);
		}

		//CCLOG("CURFRAME:%d", m_nCurFrame);
	}
	else 
	{
		if (m_nCurFrame > m_vPlayerSpriteVector.size() / 2)
		{
			m_nCurFrame --;
		}

		if (m_nCurFrame < m_vPlayerSpriteVector.size() / 2)
		{
			m_nCurFrame ++;
		}

		displayFrameByIndex(m_nCurFrame);
	}

	
}

void CPlayerSprite::displayFrameByIndex(unsigned int nIndex)
{
	for (unsigned int i=0; i<m_vPlayerSpriteVector.size(); i++)
	{
		m_vPlayerSpriteVector[i]->setVisible(false);
	}

	m_vPlayerSpriteVector[nIndex]->setVisible(true);
}

void CPlayerSprite::underAttack(int nHurt)
{
	if (m_eCurState >= PS_AUTOFLY)
	{
		return ;
	}

	if (m_eCurState <= PS_AUTOMOVE)
	{
		return ;
	}

	if (isExistItem(IK_IRONCURTAIN))
	{
		return ;
	}

	if (CGlobalData::getSingleton()->isLevelClear())
	{
		return ;
	}

	if (m_bIsNormal)
	{
		for (unsigned int i=0; i<m_vPlayerSpriteVector.size(); i++)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vPlayerSpriteVector[i]);
			color = pRGBAProtocol->getColor();
			pRGBAProtocol->setColor(ccc3(255,0,0));
		}
		m_bIsNormal = false;

	}
	int mHurt = 0;
	if (nHurt > m_sCurData.mArmor + nHurt * 0.3f)
	{
		mHurt = nHurt - m_sCurData.mArmor;
	}
	else
	{
		mHurt = nHurt * 0.3f;
	}
	CCLOG("hurt:%d",mHurt);
	m_sCurData.mHealthPoint -= mHurt;
	if (m_sCurData.mHealthPoint < 0)
	{
		m_sCurData.mHealthPoint = 0;
		m_eCurState = PS_EXPLODE;
		stopAllActions();
		for (unsigned int i=0; i<m_vPlayerSpriteVector.size(); i++)
		{
			m_vPlayerSpriteVector[i]->setVisible(false);
			//m_vPlayerSpriteVector[i]->getParent()->removeChild(m_vPlayerSpriteVector[i], true);
		}
		lostPower();
		runEffect();
	}
}

void CPlayerSprite::addHealthPoint(int nValue)
{
	m_sCurData.mHealthPoint += nValue + nValue * m_sCurData.mBonusAttack * 0.05f;
	if (m_sCurData.mHealthPoint > m_sInitData.mHealthPoint)
	{
		m_sCurData.mHealthPoint = m_sInitData.mHealthPoint;
	}
}

bool CPlayerSprite::isDead(void)
{
	if (m_eCurState >= PS_EXPLODE)
	{
		return true;
	}

	return false;
}

float CPlayerSprite::getHPPercentage(void)
{
	return (float)m_sCurData.mHealthPoint / m_sInitData.mHealthPoint;
}

//void CPlayerSprite::addFire(void)
//{
//	if (m_nFireLevel == 2)
//	{
//		m_fFireHoldTime = 0.0f;
//	}
//	else
//	{
//		m_nFireLevel ++;
//	}
//}

void CPlayerSprite::runLand(const CCPoint& pos)
{
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel % 4 == 1)
	{
		CCAction*  action = CCSpawn::create(CCMoveTo::create(1.5f, pos),CCScaleTo::create( 1.5f, 0.5f),NULL);
		runAction(action);
		m_pShadow->runAction(CCMoveTo::create(1.5f, ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f)));
	}
	else
	{
		runAction(CCMoveTo::create(1.5f,ccp(getPositionX(), mScreenSize.height + getContentSize().height)));
	}

}

void CPlayerSprite::runEffect(void)
{
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


	pAnimation->setDelayPerUnit(0.08f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,pCallback,NULL) );
	m_pEffectSprite->runAction(pAction);
}

void CPlayerSprite::returnNormalTexture(void)
{
	m_bIsNormal = true;
	//runAction(CCTintBy::create(0.1f,0,-255,-255));
	for (unsigned int i=0; i<m_vPlayerSpriteVector.size(); i++)
	{
		m_vPlayerSpriteVector[i]->runAction(CCTintBy::create(0.0f,0,-255,-255));
	}
}

void CPlayerSprite::removeSelf(void)
{
	m_eCurState = PS_HIDE;
}

void CPlayerSprite::addPower(void)
{
	m_nFireLevel ++;
	if (m_nFireLevel == FIRE_MAX)
	{
		m_vItemVector.push_back(IK_FIREPOWER);
		m_fFireHoldTime = 0.0f;
	}
	//CCLOG("Add Power! Now is level:%d", m_nFireLevel);
}

void CPlayerSprite::addFireBall(void)
{
	;
}

void CPlayerSprite::addIronCurtain(void)
{
	if (!m_bIsNormal)
	{
		removeIronCurtain();
		m_bIsNormal = true;
	}
	for (unsigned int i=0; i<m_vPlayerSpriteVector.size(); i++)
	{
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vPlayerSpriteVector[i]);
		pRGBAProtocol->setColor(ccc3(250,150,35));
	}
}

void CPlayerSprite::removeIronCurtain(void)
{
	for (unsigned int i=0; i<m_vPlayerSpriteVector.size(); i++)
	{
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vPlayerSpriteVector[i]);
		pRGBAProtocol->setColor(m_sOriginalColor);
	}
}

void CPlayerSprite::addShieldTaken(void)
{
	
}

void CPlayerSprite::addWingMan(void)
{
	char szName[128] = {0};
	sprintf(szName, "%s%02d_%04d.png", "PC_Plane", m_sCurData.mIndex, m_vPlayerSpriteVector.size() / 2 + 1);
	m_pLeftWingMan = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pLeftWingMan->setAnchorPoint(ccp(0.5f,0.5f));
	m_pLeftWingMan->setScale(0.8f);
	m_pLeftWingMan->setPositionX(-getContentSize().width - getPositionX());
	m_pLeftWingMan->setPositionY(-getContentSize().height - getPositionY());
	addChild(m_pLeftWingMan);

	CCSprite *pShadow = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Shadow.png"));
	pShadow->setRotation(180);
	pShadow->setScale(0.8f);
	pShadow->setPosition(ccp(m_pLeftWingMan->getContentSize().width, -m_pLeftWingMan->getContentSize().height));
	m_pLeftWingMan->addChild(pShadow);

	m_pLeftWingMan->runAction(CCMoveTo::create(1.5f, ccp(-getContentSize().width * 0.5f, -getContentSize().height)));

	m_pRightWingMan = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pRightWingMan->setAnchorPoint(ccp(0.5f,0.5f));
	m_pRightWingMan->setScale(0.8f);
	m_pRightWingMan->setPositionX(getContentSize().width + mScreenSize.width - getPositionX());
	m_pRightWingMan->setPositionY(-getContentSize().height - getPositionY());
	addChild(m_pRightWingMan);

	pShadow = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Shadow.png"));
	pShadow->setRotation(180);
	pShadow->setScale(0.8f);
	pShadow->setPosition(ccp(m_pRightWingMan->getContentSize().width, -m_pRightWingMan->getContentSize().height));
	m_pRightWingMan->addChild(pShadow);

	m_pRightWingMan->runAction(CCMoveTo::create(1.5f, ccp(getContentSize().width * 1.5f, -getContentSize().height)));
}

void CPlayerSprite::removeWingMan(void)
{
	m_pLeftWingMan->removeAllChildrenWithCleanup(true);
	m_pRightWingMan->removeAllChildrenWithCleanup(true);
	removeChild(m_pLeftWingMan, true);
	removeChild(m_pRightWingMan, true);
	m_pLeftWingMan = NULL;
	m_pRightWingMan = NULL;
	CGlobalData::getSingleton()->setIsWingman(false);
}

void CPlayerSprite::removeAllItem(void)
{
	for (unsigned int i=0; i<m_vItemVector.size(); i++)
	{
		removeItemByKind(m_vItemVector[i]);
	}
	m_vItemVector.clear();
}
void CPlayerSprite::addItemKind(ITEM_KINDS eKind)
{
	if (CGlobalData::getSingleton()->isRunControl())
	{
		addItem(eKind);
		return ;
	}

	switch(eKind)
	{
	case IK_FIREPOWER:
	case IK_TRACKROCKET:
	case IK_SIDEBULLET:
		addItem(eKind);
		break;
	case IK_IRONCURTAIN:
	case IK_FIREBALL:
	case IK_SHIELDTAKEN:
	case IK_SUPERGUN:
	case IK_WINGMAN:
		CGlobalData::getSingleton()->setHoldItem(eKind);
		break;
	}
}

void CPlayerSprite::usingHoldItem(void)
{
	addItem(CGlobalData::getSingleton()->getHoldItem());
	CGlobalData::getSingleton()->setHoldItem(IK_DEFAULT);
}

void CPlayerSprite::addItem(ITEM_KINDS eKind)
{
	//if (m_eCurState )
	//{
	//}
	switch(eKind)
	{
	case IK_DEFAULT:
		break;
	case IK_FIREPOWER:
		if (isExistItem(eKind))
		{
			m_fFireHoldTime = 0.0f;
		}
		else
		{
			addPower();
		}
		break;
	case IK_IRONCURTAIN:
		if (isExistItem(eKind))
		{
			m_fIronCurtainTime = 0.0f;
		}
		else
		{
			m_vItemVector.push_back(eKind);
			addIronCurtain();
			m_fIronCurtainTime = 0.0f;
		}
		break;
	case IK_FIREBALL:
		if (isExistItem(eKind))
		{
			m_fFireBallTime = 0.0f;
		}
		else
		{
			m_vItemVector.push_back(eKind);
			addFireBall();
			m_fFireBallTime = 0.0f;
		}
		break;
	case IK_TRACKROCKET:
		if (isExistItem(eKind))
		{
			CGlobalData::getSingleton()->addRocket(ROCKET_NUM);
		}
		else
		{
			m_vItemVector.push_back(eKind);
			CGlobalData::getSingleton()->addRocket(ROCKET_NUM);
		}
		break;
	case IK_SHIELDTAKEN:
		if (isExistItem(eKind))
		{
			m_fShieldTakenTime = 0.0f;
		}
		else
		{
			m_vItemVector.push_back(eKind);
			//addShieldTaken();
			m_pShieldTaken->setVisible(true);
			m_fShieldTakenTime = 0.0f;
		}
		break;
	case IK_SUPERGUN:
		if (isExistItem(eKind))
		{
			m_fSuperGunTime = 0.0f;
		}
		else
		{
			m_vItemVector.push_back(eKind);
			m_fSuperGunTime = 0.0f;
		}
		break;
	case IK_SIDEBULLET:
		if (isExistItem(eKind))
		{
			m_fSideBulletTime = 0.0f;
		}
		else
		{
			m_vItemVector.push_back(eKind);
			m_fSideBulletTime = 0.0f;
		}
		break;
	case IK_WINGMAN:
		if (isExistItem(eKind))
		{
			m_fWingManTime = 0.0f;
		}
		else
		{
			m_vItemVector.push_back(eKind);
			addWingMan();
			m_fWingManTime = 0.0f;
			CGlobalData::getSingleton()->setIsWingman(true);
		}
		break;
	}
	//m_vItemVector.push_back(eKind);
}

void CPlayerSprite::itemUpdate(float fEscapeTime)
{
	for (unsigned int i=0; i<m_vItemVector.size(); i++)
	{
		switch(m_vItemVector[i])
		{
		case IK_DEFAULT:
			break;
		case IK_FIREPOWER:
			{
				m_fFireHoldTime += fEscapeTime;
				if (m_fFireHoldTime > FIRE_HOLD)
				{
					m_fFireHoldTime = 0.0f;
					removeItemByKind(IK_FIREPOWER);
					m_vItemVector[i] = IK_DEFAULT;
				}
			}
			break;
		case IK_IRONCURTAIN:
			{
				m_fIronCurtainTime += fEscapeTime;
				if (m_fIronCurtainTime > IRON_HOLD + 5.0f * m_sCurData.mBonusAttack * 0.05f)
				{
					m_fIronCurtainTime = 0.0f;
					removeItemByKind(IK_IRONCURTAIN);
					m_vItemVector[i] = IK_DEFAULT;
				}
			}
			break;
		case IK_FIREBALL:
			{
				m_fFireBallTime += fEscapeTime;
				m_fFireBallSlot += fEscapeTime;
				if (m_fFireBallTime > FIRE_HOLD)
				{
					m_fFireBallTime = 0.0f;
					m_fFireBallSlot = FIREBALL_SLOT;
					removeItemByKind(IK_FIREBALL);
					m_vItemVector[i] = IK_DEFAULT;
				}
				if (m_fFireBallSlot > FIREBALL_SLOT)
				{
					m_fFireBallSlot = 0.0f;
					BULLET_DATA mData;
					mData.mAttack = 20 + 20 * m_sCurData.mBonusAttack * 0.05f;
					mData.mDirection = ccp(0.0f, 1.0f);
					mData.mKind = BK_FIREBALL;
					mData.mMoveSpeed = 600.0f;
					CBullet *pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_FIREBALL);
					pBullet->setPositionX(getPosition().x);
					pBullet->setPositionY(getPosition().y);
					getParent()->addChild(pBullet, PBULLET_ZORDER);
				}
			}
			break;
		case IK_TRACKROCKET:
			{
				m_fTarckRocketSlot += fEscapeTime;
				if (CGlobalData::getSingleton()->getRocket() <= 0)
				{
					m_fTarckRocketSlot = TARCKROCKET_SLOT;
					removeItemByKind(IK_TRACKROCKET);
					m_vItemVector[i] = IK_DEFAULT;
				}

				if (m_fTarckRocketSlot > TARCKROCKET_SLOT)
				{

					CCObject* pObj = NULL;
					CCARRAY_FOREACH(getParent()->getChildren(), pObj)
					{
						CCNode* pNode = (CCNode*) pObj;
						if (pNode->getTag() == ENEMY_TYPE || pNode->getTag() == HELI_TYPE || pNode->getTag() == ARMY_TYPE || pNode->getTag() == BOSS_TYPE)
						{

							m_fTarckRocketSlot = 0.0f;
							CGlobalData::getSingleton()->reduceRocket(1);
							BULLET_DATA mData;
							mData.mAttack = 200 + 200 * m_sCurData.mBonusAttack * 0.05f;
							mData.mDirection = ccp(0.0f, 1.0f);
							mData.mKind = BK_TARCKROCKET;
							mData.mMoveSpeed = 700.0f;
							CBullet *pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_TARCKROCKET);
							pBullet->setPositionX(getPosition().x);
							pBullet->setPositionY(getPosition().y);
							getParent()->addChild(pBullet, PBULLET_ZORDER);
							break;
						}
					}


				}
			}
			break;
		case IK_SHIELDTAKEN:
			{
				m_fShieldTakenTime += fEscapeTime;
				if (m_fShieldTakenTime > FIRE_HOLD + 5.0f * m_sCurData.mBonusAttack * 0.05f)
				{
					m_fShieldTakenTime = 0.0f;
					m_pShieldTaken->setVisible(false);
					//removeItemByKind(IK_FIREBALL);
					m_vItemVector[i] = IK_DEFAULT;
				}
			}
			break;
		case IK_SUPERGUN:
			{
				m_fSuperGunTime += fEscapeTime;
				m_fSuperGunSlot += fEscapeTime;
				if (m_fSuperGunTime > FIRE_HOLD)
				{
					m_fSuperGunTime = 0.0f;
					m_fSuperGunSlot = SUPERGUN_SLOT;
					removeItemByKind(IK_SUPERGUN);
					m_vItemVector[i] = IK_DEFAULT;
				}
				if (m_fSuperGunSlot > SUPERGUN_SLOT)
				{
					m_fSuperGunSlot = 0.0f;
					BULLET_DATA mData;
					mData.mAttack = 10 + 10 * m_sCurData.mBonusAttack * 0.05f;
					mData.mDirection = ccp(0.0f, 1.0f);
					mData.mKind = BK_SUPERGUN;
					mData.mMoveSpeed = 1000.0f;
					CBullet *pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_SUPERGUN);
					m_fSuperGunPos += 0.628f;
					pBullet->setPositionX(getPosition().x + sin(m_fSuperGunPos) * getContentSize().width * 0.5f);
					pBullet->setPositionY(getPosition().y);
					getParent()->addChild(pBullet, PBULLET_ZORDER);
				}
			}
			break;
		case IK_SIDEBULLET:
			{
				m_fSideBulletTime += fEscapeTime;
				m_fSideBulletSlot += fEscapeTime;
				if (m_fSideBulletTime > FIRE_HOLD)
				{
					m_fSideBulletTime = 0.0f;
					m_fSideBulletSlot = SIDEBULLET_SLOT;
					removeItemByKind(IK_SIDEBULLET);
					m_vItemVector[i] = IK_DEFAULT;
				}
				if (m_fSideBulletSlot > SIDEBULLET_SLOT)
				{
					m_fSideBulletSlot = 0.0f;
					BULLET_DATA mData;
					mData.mAttack = 100 + 100 * m_sCurData.mBonusAttack * 0.05f;
					mData.mDirection = ccp(1.0f, 0.0f);
					mData.mKind = BK_DEFAULT;
					mData.mMoveSpeed = 700.0f;
					CBullet *pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
					pBullet->setPositionX(getPosition().x);
					pBullet->setPositionY(getPosition().y);
					getParent()->addChild(pBullet, PBULLET_ZORDER);
					mData.mDirection = ccp(-1.0f, 0.0f);
					pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
					pBullet->setPositionX(getPosition().x);
					pBullet->setPositionY(getPosition().y);
					getParent()->addChild(pBullet, PBULLET_ZORDER);
				}
			}
			break;
		case IK_WINGMAN:
			{
				m_fWingManTime += fEscapeTime;
				m_fWingManSlot += fEscapeTime;
				if (m_fWingManTime > WINGMAN_HOLD)
				{
					m_fWingManTime = 0.0f;
					m_fWingManSlot = WINGMAN_SLOT;
					//m_pShieldTaken->setVisible(false);
					removeItemByKind(IK_WINGMAN);
					m_vItemVector[i] = IK_DEFAULT;
				}

				if (m_fWingManSlot > WINGMAN_SLOT)
				{
					m_fWingManSlot = 0.0f;
					BULLET_DATA mData;
					mData.mAttack = 30 + 30 * m_sCurData.mBonusAttack * 0.05f;
					mData.mDirection = ccp(0.0f, 1.0f);
					mData.mKind = BK_DEFAULT;
					mData.mMoveSpeed = 700.0f;
					CBullet *pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
					pBullet->setPositionX(getPosition().x + m_pLeftWingMan->getPositionX() - getContentSize().width * 0.5f);
					pBullet->setPositionY(getPosition().y + m_pLeftWingMan->getPositionY());
					getParent()->addChild(pBullet, PBULLET_ZORDER);
					pBullet = CBullet::createBullet(PALYER_BULLET, mData, BK_DEFAULT);
					pBullet->setPositionX(getPosition().x + m_pRightWingMan->getPositionX() - getContentSize().width * 0.5f);
					pBullet->setPositionY(getPosition().y + m_pRightWingMan->getPositionY());
					getParent()->addChild(pBullet, PBULLET_ZORDER);
				}
			}
			break;
		}
	}

	removeItemIndex(IK_DEFAULT);
}

void CPlayerSprite::itemLogic(ITEM_KINDS eKind, float fEscapeTime)
{
	
}

void CPlayerSprite::removeItemIndex(ITEM_KINDS eKind)
{
	std::vector<ITEM_KINDS>::iterator it = m_vItemVector.begin();
	for (; it!=m_vItemVector.end(); it++)
	{
		if (eKind == (*it))
		{
			m_vItemVector.erase(it);
			return ;
		}
	}

}

void CPlayerSprite::removeItemByKind(ITEM_KINDS eKind)
{
	switch(eKind)
	{
	case IK_DEFAULT:
		break;
	case IK_FIREPOWER:
		m_nFireLevel --;
		//CCLOG("Add Power! Now is level:%d", m_nFireLevel);
		break;
	case IK_IRONCURTAIN:
		removeIronCurtain();
		break;
	case IK_FIREBALL:
		//removeIronCurtain();
		break;
	case IK_SHIELDTAKEN:
		m_pShieldTaken->setVisible(false);
		break;
	case IK_WINGMAN:
		{
			CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CPlayerSprite::removeWingMan));
			CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( CCMoveTo::create(1.5f, ccp(-480.0f, -480.0f)),pCallback,NULL) );
			m_pLeftWingMan->runAction(pAction);
			m_pRightWingMan->runAction(CCMoveTo::create(1.5f, ccp(480.0f, -480.0f)));
		}
		break;
	}
}

bool CPlayerSprite::isExistItem(ITEM_KINDS eKind)
{
	for (unsigned int i=0; i<m_vItemVector.size(); i++)
	{
		if (eKind == m_vItemVector[i])
		{
			return true;
		}
	}

	return false;
}

bool CPlayerSprite::isShieldTaken(void)
{
	if (isExistItem(IK_SHIELDTAKEN))
	{
		return true;
	}
	return false;
}

void CPlayerSprite::lostPower(void)
{
	ITEM_KINDS mKind = IK_DEFAULT;
	for (unsigned int i=0; i<m_vItemVector.size(); i++)
	{
		CItemSprite *pItem = CItemSprite::createItem(m_vItemVector[i]);
		pItem->setPosition(getPosition());
		getParent()->addChild(pItem, PLAYER_ZORDER);
	}

	CItemSprite *pItem = CItemSprite::createItem(IK_FIREPOWER);
	pItem->setPosition(getPosition());
	getParent()->addChild(pItem, PLAYER_ZORDER);
}