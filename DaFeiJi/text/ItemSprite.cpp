#include "ItemSprite.h"

CItemSprite::CItemSprite(void)
{
	m_eCurState = IS_DEFAULT;
	m_fLifeTime = 0.0f;
	m_nScaleLevel = 0;
	m_eKind = IK_DEFAULT;
	m_fSpeedX = 0.0f;
	m_fSpeedY = 0.0f;
}

CItemSprite::~CItemSprite(void)
{
}

void CItemSprite::onEnter()
{
	//CCLOG("SHOW!");
	ccpNormalize(ccpSub(ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f), getPosition()));
	//runAction(CCMoveTo::create(5.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.5f)));
/*	m_fSpeedX = 0.5f + CCRANDOM_0_1() * 0.5f;
	m_fSpeedY = 0.5f + CCRANDOM_0_1() * 0.5f*/;

	m_fSpeedX = 0.75f;
	m_fSpeedY = 0.75f;

	if (CCRANDOM_0_1() > 0.5f)
	{
		m_fSpeedX = - m_fSpeedX;
	}

	if (CCRANDOM_0_1() > 0.5f)
	{
		m_fSpeedY = - m_fSpeedY;
	}
	CCSprite::onEnter();
}

CItemSprite* CItemSprite::createItem(ITEM_KINDS eKind)
{
	CItemSprite *pItem = new CItemSprite();
	pItem->createSprite(eKind);
	pItem->schedule(schedule_selector(CItemSprite::itemUpdate));
	return pItem;
}

void CItemSprite::createSprite(ITEM_KINDS eKind)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if (eKind == IK_DEFAULT)
	{
		randomItem();
	}
	else
	{
		m_eKind = eKind;
	}

	initWithSpriteFrame(m_pCurCache->spriteFrameByName("Item_HP_01.png"));

	CCAnimation *pAnimation = CCAnimation::create();

	char szName[128] = {0};

	for (int i=0; i<ANIMATE_MAX; i++)
	{
		switch(m_eKind)
		{
		case IK_HP:
			sprintf(szName, "Item_HP_%02d.png", i+1);
			break;
		case IK_FIREPOWER:
			sprintf(szName, "Item_FireDefault_%02d.png", i+1);
			break;
		case IK_IRONCURTAIN:
			sprintf(szName, "Item_IronCurtain_%02d.png", i+1);
			break;
		case IK_FIREBALL:
			sprintf(szName, "Item_FireBall_%02d.png", i+1);
			break;
		case IK_TRACKROCKET:
			sprintf(szName, "Item_TrackRocket_%02d.png", i+1);
			break;
		case IK_SHIELDTAKEN:
			sprintf(szName, "Item_ShieldTaken_%02d.png", i+1);
			break;
		case IK_LIFE:
			sprintf(szName, "Item_Life_%02d.png", i+1);
			break;
		case IK_SUPERGUN:
			sprintf(szName, "Item_SuperGun_%02d.png", i+1);
			break;
		case IK_WINGMAN:
			sprintf(szName, "Item_WingMan_%02d.png", i+1);
			break;
		case IK_SIDEBULLET:
			sprintf(szName, "Item_SideBullet_%02d.png", i+1);
			break;
		}

		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}


	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	runAction( CCRepeatForever::create( (CCActionInterval*)(CCSequence::create( pAnimate,NULL) ) ) );
	//runAction(pAnimate);

	m_eCurState = IS_MOVE;

}

void CItemSprite::itemUpdate(float fEscapeTime)
{
	switch(m_eCurState)
	{
	case IS_DEFAULT:
		break;
	case IS_MOVE:
		m_fLifeTime += fEscapeTime;
		if (m_fLifeTime > ITEM_LIFE)
		{
			setVisible(false);
			m_eCurState = IS_HIDE;
		}

		if (m_fLifeTime > ITEM_LIFE * 0.2f * m_nScaleLevel)
		{

			setScale((10.0f - m_nScaleLevel) / 10.0f);
			m_nScaleLevel ++;
		}
		break;
	case IS_HIDE:
		getParent()->removeChild(this, true);
		break;
	}
	collisionLogic();
	CCPoint mPos = ccpAdd(getPosition(), ccpMult(ccp(m_fSpeedX, m_fSpeedY), fEscapeTime * ITEM_SPEED));
	if (mPos.x > mScreenSize.width)
	{
		mPos.x = mScreenSize.width * 2.0f - mPos.x;
		m_fSpeedX = - 0.75f;
	}

	if (mPos.x < 0.0f)
	{
		mPos.x = - mPos.x;
		m_fSpeedX = 0.75f;
	}

	if (mPos.y > mScreenSize.height - 60.0f)
	{
		mPos.y = (mScreenSize.height - 60.0f) * 2.0f - mPos.y;
		m_fSpeedY = - 0.75f;
	}

	if (mPos.y < 0.0f)
	{
		mPos.y =  - mPos.y;
		m_fSpeedY = 0.75f;
	}

	setPosition(mPos);
}

void CItemSprite::collisionLogic(void)
{
	if (m_eCurState >= IS_HIDE)
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
				ASSESS_DATA mData;
				switch(m_eKind)
				{
				case IK_HP:
					{
						pPlayer->addHealthPoint(10);
						mData.mKind = ASK_HP;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_FIREPOWER:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_FIRE;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_IRONCURTAIN:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_IRONCURTAIN;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_FIREBALL:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_FIREBALL;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_TRACKROCKET:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_TRACKROCKET;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_SHIELDTAKEN:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_SHIELDTAKEN;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_LIFE:
					{
						CGlobalData::getSingleton()->addLife(1);
						mData.mKind = ASK_LIFE;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_SUPERGUN:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_SUPERGUN;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_SIDEBULLET:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_SIDEBULLET;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				case IK_WINGMAN:
					{
						pPlayer->addItemKind(m_eKind);
						mData.mKind = ASK_WINGMAN;
						mData.mPos = getPosition();
						CAssess *pAssess = CAssess::createAssess(mData);
						getParent()->addChild(pAssess, ASSESS_ZORDER);
					}
					break;
				}
				m_eCurState = IS_HIDE;

				Music::playItemEffect();
				break;
			}
		}
	}
}

void CItemSprite::randomItem(void)
{
	float fRandomNum = CCRANDOM_0_1() * (((int)IK_MAX) - 1);
	int nKind = (int)(fRandomNum + 1.0f);
	m_eKind = (ITEM_KINDS)nKind;
	//m_eKind = IK_WINGMAN;
	if (m_eKind == IK_TRACKROCKET && CGlobalData::getSingleton()->getRocket() > 30)
	{
		m_eKind = IK_HP;
		
	}

	if (m_eKind == IK_WINGMAN && CGlobalData::getSingleton()->isExistWingman())
	{
		m_eKind = IK_HP;
	}

	if (m_eKind == IK_LIFE/* && CGlobalData::getSingleton()->getLife() > 1*/)
	{
		m_eKind = IK_FIREPOWER;
	}

}
