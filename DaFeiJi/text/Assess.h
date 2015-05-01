#ifndef ASSESS_H
#define ASSESS_H

#include "cocos2d.h"
#include "GlobalData.h"

using namespace cocos2d;

class CAssess :
	public CCSprite
{
public:
	CAssess(void);
	~CAssess(void);
public:
	static CAssess* createAssess(ASSESS_DATA sData);
private:
	void createSprite(void);
	void removeCallback(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	ASSESS_DATA m_sCurData;

	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];
};

#endif