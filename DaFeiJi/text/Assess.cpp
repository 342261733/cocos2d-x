#include "Assess.h"

CAssess::CAssess(void)
{
}

CAssess::~CAssess(void)
{
}

CAssess* CAssess::createAssess(ASSESS_DATA sData)
{
	CAssess *pAssess = new CAssess();
	pAssess->m_sCurData = sData;
	pAssess->createSprite();
	return pAssess;
}

void CAssess::createSprite(void)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	char szName[128] = {0};
	m_eLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();

	memset(m_sPrefix,0,sizeof(m_sPrefix));


	if (m_eLanguageType == kLanguageChinese)
	{
		sprintf(m_sPrefix,"CN_");
	}
	else
	{
		sprintf(m_sPrefix,"EN_");
	}

	sprintf(szName, "%s%s%02d.png", m_sPrefix, "Assess", (int)m_sCurData.mKind + 1);
	initWithSpriteFrame(m_pCurCache->spriteFrameByName(szName));

	setPosition(m_sCurData.mPos);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CAssess::removeCallback));
	runAction((CCActionInterval*)(CCSequence::create( CCScaleTo::create(0.1f,1.5f), CCScaleTo::create(0.2f, 1.0f), pCallback,NULL)));
}

void CAssess::removeCallback(void)
{
	getParent()->removeChild(this, true);
}