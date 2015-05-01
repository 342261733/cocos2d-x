#ifndef SUPERBOMB_H
#define SUPERBOMB_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "ArmySprite.h"
#include "EnemySprite.h"
#include "HelicopterSprite.h"

#include "Drone.h"
#include "BossTwo.h"
#include "BossThree.h"
#include "BossFour.h"
#include "BossFive.h"
#include "BossSix.h"
#include "BossSeven.h"
#include "Bullet.h"

class CSuperBomb :
	public CCNode
{
public:
	CSuperBomb(void);
	~CSuperBomb(void);
public:
	static CSuperBomb* createSuperBomb(void);
	void onEnter();
	void onExit();
public:
private:
	void createSprite(void);
	void runExplode(void);
	void removeSelf(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	CCSprite *m_pBombSprite;

	//Effect
	CCSprite *m_pMainExplode;			//主爆炸
	CCSprite *m_pAssistExplode01;		//辅爆炸
	CCSprite *m_pAssistExplode02;		//辅爆炸
	CCSprite *m_pShockHalo;				//冲击波光环
};

#endif