#include "SuperBomb.h"

CSuperBomb::CSuperBomb(void)
{
}

CSuperBomb::~CSuperBomb(void)
{
}

CSuperBomb* CSuperBomb::createSuperBomb(void)
{
	CSuperBomb *pBomb = new CSuperBomb();
	pBomb->createSprite();

	pBomb->autorelease();
	return pBomb;
}

void CSuperBomb::createSprite(void)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_pBombSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Bomb01.png"));
	addChild(m_pBombSprite);

	m_pMainExplode = CCSprite::create();
	addChild(m_pMainExplode);

	m_pAssistExplode01 = CCSprite::create();
	m_pAssistExplode01->setPosition(ccp(50.0f, 50.0f));
	m_pAssistExplode01->setScale(2.0f);
	addChild(m_pAssistExplode01);

	m_pAssistExplode02 = CCSprite::create();
	m_pAssistExplode02->setPosition(ccp(-50.0f, 50.0f));
	m_pAssistExplode02->setScale(2.0f);
	addChild(m_pAssistExplode02);

	m_pShockHalo = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Halo01_01.png"));
	addChild(m_pShockHalo);
	m_pShockHalo->setScale(0.2f);
}

void CSuperBomb::onEnter()
{
	CCPoint pos = ccp(CCRANDOM_0_1() * mScreenSize.width * 0.75f + mScreenSize.width * 0.125f, -mScreenSize.height * 0.5f);
	setPosition(pos);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CSuperBomb::runExplode));
	runAction((CCActionInterval*)(CCSequence::create(
										CCMoveTo::create(0.5f,ccp(getPosition().x, CCRANDOM_0_1() * mScreenSize.height * 0.75f + mScreenSize.height * 0.125f)),
										pCallback,NULL)));
	CCNode::onEnter();
}

void CSuperBomb::onExit()
{
	CCNode::onExit();
}

void CSuperBomb::runExplode(void)
{
	//隐藏飞弹
	m_pBombSprite->setVisible(false);


	//创建并运行爆炸动画
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


	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);

	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	m_pMainExplode->runAction(pAnimate);

	CCAnimation *pAnimation01 = CCAnimation::create();
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "Explode01_%02d.png", i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation01->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}

	pAnimation01->setDelayPerUnit(0.1f);
	pAnimation01->setRestoreOriginalFrame(true);
	CCAnimate *pAnimate01 = CCAnimate::create(pAnimation01);
	m_pAssistExplode01->runAction(pAnimate01);


	CCAnimation *pAnimation02 = CCAnimation::create();
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "Explode01_%02d.png", i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation02->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}

	pAnimation02->setDelayPerUnit(0.1f);
	pAnimation02->setRestoreOriginalFrame(true);
	CCAnimate *pAnimate02 = CCAnimate::create(pAnimation02);
	m_pAssistExplode01->runAction(pAnimate02);


	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CSuperBomb::removeSelf));
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create( CCScaleTo::create(0.8f, 5.0f),pCallback,NULL) );
	m_pShockHalo->runAction(pAction);

	//启动震屏效果
//	CCActionInterval* effect = CCShaky3D::create(0.5f, CCSize(2,2), 2, false);
    
//    CCSizeFromString(CCSize(2,2))
//    CCActionInterval* effect = CCShaky3D::create(0.5f, CCSizeMake(2,2), 2, false);
    CCActionInterval* effect = CCShaky3D::create(4,false,ccg(2,2),0.5f);
	getParent()->runAction(effect);

	CCObject* pObj = NULL;
	CCARRAY_FOREACH(getParent()->getChildren(), pObj)
	{
		CCNode* pNode = (CCNode*) pObj;
		if (pNode->getTag() == ENEMY_TYPE)
		{
			CEnemySprite* pEnemy = (CEnemySprite*)pObj;				//敌机
			pEnemy->underAttack(NUCLEAR_HURT);
		}

		if (pNode->getTag() == ARMY_TYPE)
		{
			CArmySprite* pEnemy = (CArmySprite*)pObj;				//陆军
			pEnemy->underAttack(NUCLEAR_HURT);
		}

		if (pNode->getTag() == HELI_TYPE)
		{
			CHelicopterSprite* pHeli = (CHelicopterSprite*)pObj;	//直升飞机
			pHeli->underAttack(NUCLEAR_HURT);
		}

		if (pNode->getTag() == ENEMY_BULLET)
		{
			CBullet *pBullet = (CBullet*)pNode;						//子弹
			pBullet->removeSelf();
		}

		switch(CGlobalData::getSingleton()->getCurLevelData().mLevel)
		{
		case 2:
			{
				if (pNode->getTag() == BOSS_TYPE)
				{
					CBossTwo* pBoss = (CBossTwo*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(NUCLEAR_HURT);
					}
				}

			}
			break;
		case 3:
			{
				if (pNode->getTag() == BOSS_TYPE)
				{
					CBossThree* pBoss = (CBossThree*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(NUCLEAR_HURT);
					}
				}

			}
			break;
		case 4:
			{
				if (pNode->getTag() == BOSS_TYPE)
				{
					CBossFour* pBoss = (CBossFour*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(NUCLEAR_HURT);
					}
				}

			}
			break;
		case 5:
			{
				if (pNode->getTag() == BOSS_TYPE)
				{
					CBossFive* pBoss = (CBossFive*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(NUCLEAR_HURT);
					}
				}

			}
			break;
		case 6:
			{
				if (pNode->getTag() == BOSS_TYPE)
				{
					CBossSix* pBoss = (CBossSix*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(NUCLEAR_HURT);
					}
				}

			}
			break;
		case 7:
			{
				if (pNode->getTag() == BOSS_TYPE)
				{
					CBossSeven* pBoss = (CBossSeven*)pObj;
					if (pBoss->isCheck() && boundingBox().intersectsRect(pBoss->getCurBoundbox()))
					{
						pBoss->underAttack(NUCLEAR_HURT);
					}
				}


				if (pNode->getTag() == DRONE_TYPE)
				{
					CDrone* pDrone = (CDrone*)pObj;
					if (pDrone->isCheck())
					{
						pDrone->underAttack(NUCLEAR_HURT);
					}
				}

			}
			break;
		}
	}
}

void CSuperBomb::removeSelf(void)
{
	getParent()->removeChild(this, true);
}
