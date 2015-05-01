#include "EnemySprite.h"

CEnemySprite::CEnemySprite(void)
{
	m_sCurData.mIndex = 1;
	m_sCurData.mAttack = 2;
	m_sCurData.mHealthPoint = 5;
	m_sCurData.mMoveSpeed = 300.0f;
	m_eCurState = ES_DEFAULT;
	m_pEffectSprite = NULL;
	m_pShadow = NULL;

	m_fFireTime = 0.0f;
	m_fTime = 3.0f;
	m_nBulletNum = 0;
	m_bIsNormal = true;
	m_fFlashTime = 0.0f;
}

CEnemySprite::~CEnemySprite(void)
{
	
}

void CEnemySprite::onEnter()
{
	createShadow();
	CCNode::onEnter();
}

void CEnemySprite::onExit()
{
	if (m_pShadow != NULL)
	{
		m_pShadow->getParent()->removeChild(m_pShadow, true);
	}
	CCNode::onExit();
}

CEnemySprite* CEnemySprite::createEnemy(ENEMY_KINDS eKind, FLY_DATA sData, ENEMY_WEAPON wKind)
{
	CEnemySprite *pEnemy = new CEnemySprite();
	pEnemy->m_eWeaponKind = wKind;
	pEnemy->m_sCurFlyData = sData;
	pEnemy->createSprite(eKind);
	pEnemy->setTag(ENEMY_TYPE);

	pEnemy->autorelease();
	return pEnemy;
}

void CEnemySprite::createSprite(ENEMY_KINDS eKind)
{
	//std::string tString = CGlobalData::getSingleton()->getNameByEnum(eKind);
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_sCurData = CGlobalData::getSingleton()->getDataByKind(eKind);
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	char szName[128] = {0};

	setContentSize(CCSizeMake(84,67));

	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "%s%02d_%04d.png", "NPC_Plane", m_sCurData.mIndex, i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		CCSprite *pEnemySprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));
		pEnemySprite->setVisible(false);
		pEnemySprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
		//CCRect sfdsf = pEnemySprite->boundingBox();
		addChild(pEnemySprite);
		m_vEnemySpriteVector.push_back(pEnemySprite);
	}

	//set middle frame
	if (m_vEnemySpriteVector.size() > 0)
	{
		m_vEnemySpriteVector[m_vEnemySpriteVector.size() / 2]->setVisible(true);
		m_nCurFrame = m_vEnemySpriteVector.size() / 2;
	}

	m_pEffectSprite = CCSprite::create();
	m_pEffectSprite->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
	addChild(m_pEffectSprite);

	m_fFireTime = CCRANDOM_0_1() + 2.0f;
	//create and mount weapon
	//m_pPlayerWeapon = CPlayerWeapon::createWeapon();
	//addChild(m_pPlayerWeapon);
	setAnchorPoint(ccp(0.5f,0.5f));
	setPosition(m_sCurFlyData.mPosition);

	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CEnemySprite::finishCallback));
	switch(m_sCurFlyData.mAttitude)
	{
	case FA_DEFAULT:
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create(LIFT_TIME,ccp(m_sCurFlyData.mPosition.x, -100)),pCallback,NULL)));
		break;
	case FA_LEFTTORIGHT:
		setRotation(270);
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create(LIFT_TIME,ccp(580, m_sCurFlyData.mPosition.y)),pCallback,NULL)));
		break;
	case FA_RIGHTTOLEFT:
		setRotation(90);
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create(LIFT_TIME,ccp(-100, m_sCurFlyData.mPosition.y)),pCallback,NULL)));
		break;
	case FA_LEANLR:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame + 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setRotation(-30);
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create(LIFT_TIME,ccp(580, -100)),pCallback,NULL)));
		break;
	case FA_LEANRL:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame - 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setRotation(30);
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create(LIFT_TIME,ccp(-100, -100)),pCallback,NULL)));
		break;
	case FA_LROUNDTB:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame - 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(-3.5f, 0.5f));
		setRotation(-90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, 90),pCallback,NULL)));
		break;
	case FA_RROUNDTB:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame + 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(4.5f, 0.5f));
		setRotation(90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, -90),pCallback,NULL)));
		break;
	case FA_LROUNDBT:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame + 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(4.5f, 0.5f));
		setRotation(-90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, -270),pCallback,NULL)));
		break;
	case FA_RROUNDBT:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame - 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(-3.5f, 0.5f));
		setRotation(90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, 270),pCallback,NULL)));
		break;
	case FA_TROUNDLR:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame + 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(2.5f, 0.5f));
		//setRotation(-90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, -180),pCallback,NULL)));
		break;
	case FA_TROUNDRL:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame - 3;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(-1.5f, 0.5f));
		//setRotation(90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, 180),pCallback,NULL)));
		break;
	case FA_LQROUNDTB:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame - 2;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(-5.5f, 0.5f));
		setRotation(-90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, 0),pCallback,NULL)));
		break;
	case FA_RQROUNDTB:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame + 2;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(6.5f, 0.5f));
		setRotation(90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, 0),pCallback,NULL)));
		break;
	case FA_TQROUNDLR:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame + 2;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(5.5f, 0.5f));
		//setRotation(-90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, -90),pCallback,NULL)));
		break;
	case FA_TQROUNDRL:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
		m_nCurFrame = m_nCurFrame - 2;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(-4.5f, 0.5f));
		//setRotation(90);
		runAction((CCActionInterval*)(CCSequence::create( CCRotateTo::create(LIFT_TIME, 90),pCallback,NULL)));
		break;
	case FA_AIRMINE:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(0.5f, 0.5f));
		//setRotation(90);
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create((m_sCurFlyData.mPosition.y + 100) / m_sCurData.mMoveSpeed, ccp(-100, m_sCurFlyData.mPosition.y)),pCallback,NULL)));
		m_fFireTime = 1.1f;
		m_fTime = 0.0f;
		break;
	case FA_MINE:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(0.5f, 0.5f));
		//setRotation(90);
		mineAnimation();
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create( (m_sCurFlyData.mPosition.y + 100) / m_sCurData.mMoveSpeed, ccp(m_sCurFlyData.mPosition.x, -100)),pCallback,NULL)));
		m_fFireTime = 50.0f;
		break;
	case FA_ARMOR:
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(true);
		setAnchorPoint(ccp(0.5f, 0.5f));
		setScale(1.5f);
		runAction((CCActionInterval*)(CCSequence::create( CCMoveTo::create( (m_sCurFlyData.mPosition.y + 100) / m_sCurData.mMoveSpeed, ccp(m_sCurFlyData.mPosition.x, -100)),pCallback,NULL)));
		m_fFireTime = 0.8f;
		break;
	}

	
	if (m_sCurData.mKind < EK_HELI01)
	{
		m_sCurData.mHealthPoint += 2 * (CGlobalData::getSingleton()->getCurLevelData().mLevel - 1);
	}
	m_sCurData.mAttack += 2 * (CGlobalData::getSingleton()->getCurLevelData().mLevel - 1);
	m_eCurState = ES_MOVE;
	
	this->schedule(schedule_selector(CEnemySprite::enemyUpdate));
}

void CEnemySprite::createShadow(void)
{

	if (m_sCurFlyData.mAttitude == FA_MINE)
	{
		m_pShadow = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Shadow_Mine.png"));
	}
	else
	{
		m_pShadow = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Shadow.png"));
	}
	m_pShadow->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width, 0.0f)));
	m_pShadow->setRotation(getRotation());
	m_pShadow->setScale(0.8f);
	getParent()->addChild(m_pShadow, LCLOUD_ZORDER);
}

void CEnemySprite::enemyUpdate(float fEscapeTime)
{
	switch(m_eCurState)
	{
	case ES_DEFAULT:
		break;
	case ES_MOVE:
		if (m_pShadow != NULL)
		{
			m_pShadow->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width, 0.0f)));
			m_pShadow->setRotation(getRotation());
		}

		fireBullet(fEscapeTime);
		boundPlayer();
		break;
	case ES_EXPLODE:
		break;
	case ES_HIDE:
		getParent()->removeChild(this, true);
		break;
	}

	if (!m_bIsNormal)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			for (unsigned int i=0; i<m_vEnemySpriteVector.size(); i++)
			{
				CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vEnemySpriteVector[i]);
				pRGBAProtocol->setColor(color);
			}

			m_bIsNormal = true;
		}
	}
}

void CEnemySprite::underAttack(int nHurt)
{
	if (m_eCurState >= ES_EXPLODE)
	{
		return ;
	}
	m_sCurData.mHealthPoint -= nHurt;

	

	if (m_bIsNormal)
	{
		for (unsigned int i=0; i<m_vEnemySpriteVector.size(); i++)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_vEnemySpriteVector[i]);
			color = pRGBAProtocol->getColor();
			pRGBAProtocol->setColor(ccc3(255,0,0));
		}
		m_bIsNormal = false;

	}

	if (m_sCurData.mHealthPoint < 0)
	{
		Music::playExplode1Effect();

		m_sCurData.mHealthPoint = 0;
		m_eCurState = ES_EXPLODE;
		m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
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
		mData.mPos = boundingBox().origin;
		CAssess *pAssess = CAssess::createAssess(mData);
		getParent()->addChild(pAssess, ASSESS_ZORDER);
		mData.mKind = ASK_ADD50;
		mData.mPos = ccpAdd(mData.mPos, ccp(0, getContentSize().height * 0.5f));
		pAssess = CAssess::createAssess(mData);
		getParent()->addChild(pAssess, ASSESS_ZORDER);
		stopAllActions();
		m_pShadow->getParent()->removeChild(m_pShadow, true);
		m_pShadow = NULL;
		runEffect();
	}
}

void CEnemySprite::runEffect(void)
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
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CEnemySprite::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,pCallback,NULL) );
	m_pEffectSprite->runAction(pAction);
}

void CEnemySprite::removeSelf(void)
{
	if (CGlobalData::getSingleton()->isDropItem())
	{
		if (CCRANDOM_0_1() < 0.6f)
		{
			CGlobalData::getSingleton()->recordDropTime();
			//create item

			CItemSprite *pItem = CItemSprite::createItem(IK_DEFAULT);
			pItem->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f)));
			getParent()->addChild(pItem, PLAYER_ZORDER);
		}
		//CCLOG("NO Lucky!");
	}

	m_eCurState = ES_HIDE;
}

bool CEnemySprite::isCheck(void)
{
	if (m_eCurState < ES_EXPLODE && isInScene())
	{
		return true;
	}

	return false;
}

bool CEnemySprite::isInScene(void)
{
	if (boundingBox().getMidX() > 0 && boundingBox().getMidX() < mScreenSize.width && boundingBox().getMidY() > 0 && boundingBox().getMidY() < mScreenSize.height - 60.0f)
	{
		return true;
	}
	return false;
}

void CEnemySprite::fireBullet(float fEscapeTime)
{
	if (m_eWeaponKind == EW_AIRMINE)
	{
		if (m_nBulletNum > 8)
		{
			return ;
		}

		if (getPositionX() < (9 - m_nBulletNum) * mScreenSize.width * 0.1f)
		{
			FLY_DATA mData;
			mData.mKind = EK_MINE;
			mData.mPosition = getPosition();
			mData.mAttitude = FA_MINE;
			CEnemySprite *pSprite = CEnemySprite::createEnemy(EK_MINE, mData, EW_NONE);
			getParent()->addChild(pSprite, ABULLET_ZORDER);
			m_nBulletNum ++;
		}
		return ;
	}

	m_fTime += fEscapeTime;
	if (m_fTime > m_fFireTime)
	{
		m_fTime = 0.0f;
		BULLET_DATA mData;
		mData.mAttack = m_sCurData.mAttack + 2 * (CGlobalData::getSingleton()->getCurLevelData().mLevel - 1);
		CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));
		mData.mDirection = ccpNormalize(ccpSub(m_pTarget->getPosition(), boundingBox().origin));
		mData.mMoveSpeed = 250.0f;
		m_nBulletNum ++;
		mData.mKind = BK_ARMY01;
		if (m_eWeaponKind == EW_SCATTER)
		{
			if (m_nBulletNum > 1)
			{
				return ;
			}
			mData.mMoveSpeed = 400.0f;
			for (int i=0;i<10;i++)
			{
				mData.mDirection = ccpNormalize(ccp(-0.8f + 0.16f * i, -1.0f));
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
				pBullet->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f)));
				getParent()->addChild(pBullet, ABULLET_ZORDER);
			}
		}
		else if (m_eWeaponKind == EW_NONE)
		{
		}
		else if (m_eWeaponKind == EW_HOLDFIRE)
		{
			CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_BLUE);
			pBullet->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f)));
			getParent()->addChild(pBullet, ABULLET_ZORDER);
		}
		else
		{
			if (m_nBulletNum > 1 || CCRANDOM_0_1() > 0.6f)
			{
				return ;
			}
			CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ENEMY01);
			pBullet->setPosition(ccpAdd(boundingBox().origin, ccp(getContentSize().width * 0.5f, getContentSize().height * 0.5f)));
			getParent()->addChild(pBullet, ABULLET_ZORDER);
		}

	}

}

void CEnemySprite::finishCallback(void)
{
	getParent()->removeChild(this, true);
}

void CEnemySprite::boundPlayer(void)
{
	if (m_eCurState >= ES_EXPLODE)
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
			if (/*m_sCurData.mKind <= EK_PLANE04 && */!pPlayer->isDead() && boundingBox().intersectsRect(pPlayer->boundingBox()))
			{
				Music::playExplode1Effect();

				pPlayer->underAttack(m_sCurData.mAttack);
				m_sCurData.mHealthPoint = 0;
				m_eCurState = ES_EXPLODE;
				m_vEnemySpriteVector[m_nCurFrame]->setVisible(false);
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
				mData.mKind = ASK_ADD50;
				mData.mPos = ccpAdd(mData.mPos, ccp(0, getContentSize().height * 0.5f));
				pAssess = CAssess::createAssess(mData);
				getParent()->addChild(pAssess, ASSESS_ZORDER);
				stopAllActions();
				m_pShadow->getParent()->removeChild(m_pShadow, true);
				m_pShadow = NULL;
				runEffect();
				break;
			}

		}

	}
}

void CEnemySprite::mineAnimation(void)
{
	CCAnimation *pAnimation = CCAnimation::create();

	char szName[128] = {0};
	//sprintf(szName, "%s%02d-%02d_0001.png", m_cName, m_sCurData.mAction, m_sCurData.mDirection);

	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "NPC_Plane09_%04d.png", i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}


	pAnimation->setDelayPerUnit(0.111f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( pAnimate,NULL) );
	m_vEnemySpriteVector[m_nCurFrame]->runAction(CCRepeatForever::create(pAction));
}
