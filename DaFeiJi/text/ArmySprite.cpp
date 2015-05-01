#include "ArmySprite.h"

CArmySprite::CArmySprite(void)
{
	m_eCurState = AS_DEFAULT;
	m_pEffectSprite = NULL;

	m_pBaseSprite = NULL;
	m_pTurretSprite = NULL;
	m_pWreckSprite = NULL;
	m_pCapSprite = NULL;

	m_fTime = 0.0f;
	m_bIsNormal = true;
	m_bIsHorizontal = false;
	m_fFlashTime = 0.0f;
	m_fFireCoolTime = 0.0f;
	m_nBulletNum = 0;
}

CArmySprite::~CArmySprite(void)
{
}

CArmySprite* CArmySprite::createArmy(ARMY_KINDS eKind, LAND_DATA sData)
{
	CArmySprite *pEnemy = new CArmySprite();
	pEnemy->m_sCurLandData = sData;
	//switch(eKind)
	//{
	//case AK_DEFAULT:
	//	break;
	//case AK_GREENGUN01:
	//	break;
	//case AK_BATTERY01:
	//	break;
	//case AK_BUNKER01:
	//	break;
	//}
	pEnemy->createSprite(eKind);
	pEnemy->setTag(ARMY_TYPE);

	pEnemy->autorelease();
	return pEnemy;
}

void CArmySprite::createSprite(ARMY_KINDS eKind)
{
	//std::string tString = CGlobalData::getSingleton()->getNameByEnum(eKind);
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_sCurData = CGlobalData::getSingleton()->getDataByKind(eKind);
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	char szName[128] = {0};
	//sprintf(szName, "%s%02d_01.png", "Plane", m_sCurData);NPC_Tank01_01
	

	setContentSize(CCSizeMake(98,176));

	if (CCRANDOM_0_1() > 0.5f && m_sCurData.mKind == AK_DEFAULT || m_sCurData.mKind == AK_MISSILEARMY)
	{
		m_bIsHorizontal = true;
	}

	sprintf(szName, "%s%02d_%02d.png", "NPC_Tank", m_sCurData.mIndex, 1);
	if (m_bIsHorizontal)
	{
		sprintf(szName, "%s%02d_%02d.png", "NPC_Tank", m_sCurData.mIndex, 2);
	}
	if (m_pCurCache->spriteFrameByName(szName) == NULL)
	{
		return ;
	}
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	addChild(m_pBaseSprite);

	sprintf(szName, "%s%02d_%02d.png", "NPC_Tank", m_sCurData.mIndex, 3);
	if (m_pCurCache->spriteFrameByName(szName) == NULL)
	{
		return ;
	}
	m_pTurretSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));

	//各地面武器偏移位置和基准大小
	CCPoint mBase = CCPointMake(0,0);
	CCPoint mOffset = CCPointMake(0,0);
	switch(eKind)
	{
	case AK_DEFAULT:
		mBase = ccp(0.5f, 0.4f);
		mOffset = ccp(0.5f, 0.75f);
		break;
	case AK_MISSILEARMY:
		mBase = ccp(0.5f, 0.5f);
		mOffset = ccp(0.5f, 0.714f);
		break;
	case AK_GREENGUN01:
		mBase = ccp(0.75f, 0.7f);
		mOffset = ccp(0.5f, 0.78f);
		break;
	case AK_GREENGUN02:
		mBase = ccp(0.75f, 0.5f);
		mOffset = ccp(0.5f, 0.68f);
		break;
	case AK_BATTERY01:
		mBase = ccp(0.55f, 0.5f);
		mOffset = ccp(0.5f, 0.7f);
		break;
	case AK_BATTERY02:
		mBase = ccp(0.5f, 0.5f);
		mOffset = ccp(0.5f, 0.7f);
		break;
	case AK_BUNKER01:
		mBase = ccp(0.5f, 0.5f);
		mOffset = ccp(0.5f, 0.5f);
		break;
	case AK_BUNKER02:
		mBase = ccp(0.5f, 0.5f);
		mOffset = ccp(0.5f, 0.5f);
		break;
	}
	m_pTurretSprite->setAnchorPoint(mOffset);
	m_pTurretSprite->setPosition(ccp(m_pBaseSprite->getContentSize().width * mBase.x, m_pBaseSprite->getContentSize().height * mBase.y));
	m_pBaseSprite->addChild(m_pTurretSprite);

	sprintf(szName, "%s%02d_%02d.png", "NPC_Tank", m_sCurData.mIndex, 4);
	if (m_bIsHorizontal)
	{
		sprintf(szName, "%s%02d_%02d.png", "NPC_Tank", m_sCurData.mIndex, 5);
	}

	m_pWreckSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	m_pWreckSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	m_pWreckSprite->setVisible(false);
	addChild(m_pWreckSprite);

	

	m_pEffectSprite = CCSprite::create();
	m_pEffectSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	addChild(m_pEffectSprite);

	//create and mount weapon
	//m_pPlayerWeapon = CPlayerWeapon::createWeapon();
	//addChild(m_pPlayerWeapon);

	setPosition(m_sCurLandData.mPosition);
	setAnchorPoint(ccp(0.5f,0.5f));
	//setScale(0.282f);
	m_fFireTime = CCRANDOM_0_1() + 2.0f;
	m_eCurState = AS_MOVE;
	if (m_sCurData.mKind == AK_GREENGUN01 || m_sCurData.mKind == AK_GREENGUN02)
	{
		addCap();
		m_eCurState = AS_READY;
	}
	this->schedule(schedule_selector(CArmySprite::enemyUpdate));
}

void CArmySprite::enemyUpdate(float fEscapeTime)
{
	switch(m_eCurState)
	{
	case AS_DEFAULT:
		break;
	case AS_MOVE:
		//if (getPosition().y < -getContentSize().height || getPosition().y > mScreenSize.height - BANNER_HEIGHT + getContentSize().height)
		//{
		//	m_eCurState = BS_HIDE;
		//}
		m_fFireCoolTime += fEscapeTime;
		if (m_fFireCoolTime > 2.0f)
		{
			fireBullet(fEscapeTime);
		}
		break;
	case AS_EXPLODE:
		break;
	case AS_HIDE:
		if(getPosition().y < -getContentSize().height * 0.5f)
		{
			getParent()->removeChild(this, true);
		}
		break;
	}

	if (m_eCurState < AS_EXPLODE && m_sCurData.mKind < AK_BUNKER01)
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
		m_pTurretSprite->setRotation(180 + at);
	}

	if (getPosition().y > -getContentSize().height * 0.5f)
	{
		setPosition(ccpAdd(getPosition(),ccpMult(ccp(0.0f, -1.0f), m_sCurData.mMoveSpeed * fEscapeTime)));
	}
	else
	{
		m_eCurState = AS_HIDE;
	}

	if (!m_bIsNormal)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTurretSprite);
			pRGBAProtocol->setColor(color);
			m_bIsNormal = true;
		}
	}
}

void CArmySprite::underAttack(int nHurt)
{
	if (m_eCurState >= AS_EXPLODE)
	{
		return ;
	}
	m_sCurData.mHealthPoint -= nHurt;
	if (m_bIsNormal)
	{
		m_bIsNormal = false;
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTurretSprite);
		color = pRGBAProtocol->getColor();
		pRGBAProtocol->setColor(ccc3(255,0,0));
	}

	if (m_sCurData.mHealthPoint < 0)
	{
		m_sCurData.mHealthPoint = 0;
		m_eCurState = AS_EXPLODE;
		m_pTurretSprite->setVisible(false);
		m_pBaseSprite->setVisible(false);
		if (m_pCapSprite)
		{
			m_pCapSprite->setVisible(false);
		}
		m_pWreckSprite->setVisible(true);
		CGlobalData::getSingleton()->addScore(m_sCurData.mScoreValue);

		Music::playExplode2Effect();

		CGlobalData::getSingleton()->addDesArmyScore(m_sCurLandData.mKind);
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
		runEffect();
	}
}

void CArmySprite::runEffect(void)
{
	CCAnimation *pAnimation = CCAnimation::create();

	char szName[128] = {0};
	//sprintf(szName, "%s%02d-%02d_0001.png", m_cName, m_sCurData.mAction, m_sCurData.mDirection);

	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "Explode02_%02d.png", i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}


	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CArmySprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,pCallback,NULL) );
	m_pEffectSprite->runAction(pAction);
}

void CArmySprite::removeSelf(void)
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

	m_eCurState = AS_HIDE;
}

bool CArmySprite::isCheck(void)
{
	if (m_eCurState > AS_READY && m_eCurState < AS_EXPLODE && isInScene())
	{
		return true;
	}

	return false;
}

bool CArmySprite::isInScene(void)
{
	if (boundingBox().getMidX() > 0 && boundingBox().getMidX() < mScreenSize.width && boundingBox().getMidY() > 0 && boundingBox().getMidY() < mScreenSize.height - BANNER_HEIGHT)
	{
		return true;
	}
	return false;
}

void CArmySprite::fireBullet(float fEscapeTime)
{
	CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));
	m_fTime += fEscapeTime;
	if (m_sCurData.mKind == AK_MISSILEARMY && m_fTime > 1.5f)
	{
		BULLET_DATA mData;
		mData.mAttack = m_sCurData.mAttack * 2;
		mData.mKind = BK_TARCKROCKET;
		mData.mMoveSpeed = 200.0f;
		mData.mDirection = ccpNormalize(ccpSub(m_pTarget->getPosition(), getPosition()));
		CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
		pBullet->setPosition(ccp(getPositionX(), getPositionY()));
		getParent()->addChild(pBullet, ABULLET_ZORDER);
	}
	if (m_fTime > 0.5f)
	{
		if (m_nBulletNum >= 2)
		{
			m_fFireCoolTime = 0.0f;
			m_nBulletNum = 0;
		}
		m_fTime = 0.0f;
		m_nBulletNum ++;
		BULLET_DATA mData;
		mData.mAttack = m_sCurData.mAttack;
		if (m_sCurData.mKind != AK_MISSILEARMY)
		{
			mData.mDirection = ccpNormalize(ccpSub(m_pTarget->getPosition(), getPosition()));
			mData.mKind = BK_ARMY01;
			mData.mMoveSpeed = 300.0f;
			CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			CCPoint mPos = ccpRotateByAngle(ccp(0, -48), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pTurretSprite->getRotation()));
			pBullet->setPosition(ccp(getPositionX() + mPos.x, getPositionY() + mPos.y));
			getParent()->addChild(pBullet, ABULLET_ZORDER);
		}

	}
}

void CArmySprite::addCap(void)
{
	m_pCapSprite = CCSprite::create();
	m_pCapSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	addChild(m_pCapSprite);
	CCAnimation *pAnimation = CCAnimation::create();

	char szName[128] = {0};
	//sprintf(szName, "%s%02d-%02d_0001.png", m_cName, m_sCurData.mAction, m_sCurData.mDirection);

	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%02d.png", "NPC_Tank", m_sCurData.mIndex, 10 + i);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}


	pAnimation->setDelayPerUnit(0.2f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CArmySprite::openCapCall));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,pCallback,NULL) );
	m_pCapSprite->runAction(pAction);
}

void CArmySprite::openCapCall(void)
{
	m_eCurState = AS_MOVE;
	char szName[128] = {0};
	sprintf(szName, "%s%02d_%02d.png", "NPC_Tank", m_sCurData.mIndex, 16);
	m_pCapSprite->setDisplayFrame(m_pCurCache->spriteFrameByName(szName));
}
