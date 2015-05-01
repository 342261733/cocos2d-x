#include "GlobalData.h"

CGlobalData::CGlobalData(void)
{
	m_vPlayerDataVector.clear();
	m_vLevelDataVector.clear();

	m_fGameTime = 0.0f;
	m_fItemDropTime = 0.0f;
	m_nEndlessNum = 0;
	m_bRefreshData = false;

	m_nLevelUnlock = 0;
	m_nPlaneUnlock = 0;

	m_sPlaneLevelVector.clear();

	m_pSaveData = CCUserDefault::sharedUserDefault();
	if (!m_pSaveData->getBoolForKey("isExisted"))
	{
		//初始化数据
		initProData();
		m_pSaveData->setBoolForKey("isExisted", true);
	}

	loadProData();

	//总分
	m_nScoreTotal = m_nScore01 + m_nScore02 + m_nScore03 + m_nScore04 + m_nScore05 + m_nScore06 + m_nScore07;
	//temp
	//关卡数据
	LEVEL_DATA mLevelData;
	mLevelData.mBossTime = 120.0f;
	mLevelData.mLevel = 1;
	mLevelData.mMapSpeed = 110.0f;
	mLevelData.mMission = "";

	m_vLevelDataVector.push_back(mLevelData);

	mLevelData.mLevel = 2;
	m_vLevelDataVector.push_back(mLevelData);
	mLevelData.mLevel = 3;
	m_vLevelDataVector.push_back(mLevelData);
	mLevelData.mLevel = 4;
	m_vLevelDataVector.push_back(mLevelData);
	mLevelData.mLevel = 5;
	m_vLevelDataVector.push_back(mLevelData);
	mLevelData.mLevel = 6;
	m_vLevelDataVector.push_back(mLevelData);
	mLevelData.mLevel = 7;
	m_vLevelDataVector.push_back(mLevelData);

	//挑战关
	mLevelData.mLevel = 8;
	m_vLevelDataVector.push_back(mLevelData);


	
	//玩家数据
	PLAYER_DATA mData;
	mData.mArmor = 0;
	mData.mAttack = 5;			//（MAX 10）
	mData.mBonusAttack = 0;
	mData.mFreePropertyPoints = 0;
	mData.mHealthPoint = 100;
	mData.mIndex = 1;
	mData.mKind = PK_DEFAULT;
	mData.mLevel = 1;
	mData.mSpeed = 750.0f;		//(MAX 1200)
	mData.mWeapon = PW_DEFAULT;
	m_vPlayerDataVector.push_back(mData);
	mData.mKind = PK_HURRICANE;
	mData.mIndex = 2;
	m_vPlayerDataVector.push_back(mData);

	mData.mKind = PK_WOLFANG;
	mData.mIndex = 3;
	m_vPlayerDataVector.push_back(mData);

	mData.mKind = PK_EAGLEEYE;
	mData.mIndex = 4;
	m_vPlayerDataVector.push_back(mData);

	mData.mKind = PK_KINGKONG;
	mData.mIndex = 5;
	m_vPlayerDataVector.push_back(mData);

	mData.mKind = PK_TITAN;
	mData.mIndex = 6;
	m_vPlayerDataVector.push_back(mData);

	//敌人飞机数据
	ENEMY_DATA mEdata;
	mEdata.mAttack = 13;
	mEdata.mAttitude = FA_DEFAULT;
	mEdata.mHealthPoint = 10;
	mEdata.mIndex = 1;
	mEdata.mKind = EK_DEFAULT;
	mEdata.mMoveSpeed = 500.0f;
	mEdata.mScoreValue = 50;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 2;
	mEdata.mKind = EK_PLANE02;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 3;
	mEdata.mKind = EK_PLANE03;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 4;
	mEdata.mKind = EK_PLANE04;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 7;
	mEdata.mScoreValue = 100;
	mEdata.mKind = EK_HELI01;
	mEdata.mMoveSpeed = 200.0f;
	mEdata.mHealthPoint = 450;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 8;
	mEdata.mScoreValue = 100;
	mEdata.mKind = EK_HELI02;
	mEdata.mMoveSpeed = 200.0f;
	mEdata.mHealthPoint = 200;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 5;
	mEdata.mScoreValue = 100;
	mEdata.mKind = EK_AIRMINE;
	mEdata.mMoveSpeed = 50.0f;
	mEdata.mHealthPoint = 150;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 6;
	mEdata.mScoreValue = 130;
	mEdata.mKind = EK_ARMOR;
	mEdata.mAttack = 27;
	mEdata.mMoveSpeed = 150.0f;
	mEdata.mHealthPoint = 400;
	m_vEnemyDataVector.push_back(mEdata);
	mEdata.mIndex = 9;
	mEdata.mScoreValue = 50;
	mEdata.mKind = EK_MINE;
	mEdata.mMoveSpeed = 60.0f;
	mEdata.mHealthPoint = 66;
	mEdata.mAttack = 20;
	m_vEnemyDataVector.push_back(mEdata);



	//敌人地面部队数据
	ARMY_DATA mAData;
	mAData.mAttack = 13;
	mAData.mHealthPoint = 200;
	mAData.mIndex = 1;
	mAData.mKind = AK_DEFAULT;
	mAData.mMoveSpeed = 110.0f;
	mAData.mScoreValue = 100;
	mAData.mDirection = ccp(0.0f,-1.0f);
	m_vArmyDataVector.push_back(mAData);
	mAData.mKind = AK_MISSILEARMY;
	mAData.mIndex = 2;
	m_vArmyDataVector.push_back(mAData);
	mAData.mKind = AK_GREENGUN01;
	//mAData.mHealthPoint = 35;
	mAData.mIndex = 3;
	m_vArmyDataVector.push_back(mAData);
	mAData.mKind = AK_GREENGUN02;
	mAData.mIndex = 4;
	m_vArmyDataVector.push_back(mAData);
	mAData.mKind = AK_BATTERY01;
	//mAData.mHealthPoint = 35;
	mAData.mIndex = 5;
	m_vArmyDataVector.push_back(mAData);
	mAData.mKind = AK_BATTERY02;
	//mAData.mHealthPoint = 35;
	mAData.mIndex = 6;
	m_vArmyDataVector.push_back(mAData);
	mAData.mKind = AK_BUNKER01;
	//mAData.mHealthPoint = 45;
	mAData.mIndex = 7;
	m_vArmyDataVector.push_back(mAData);
	mAData.mKind = AK_BUNKER02;
	mAData.mIndex = 8;
	m_vArmyDataVector.push_back(mAData);

	m_nCurScore = 0;
}

CGlobalData::~CGlobalData(void)
{
}

CGlobalData* CGlobalData::getSingleton(void)
{
	static CGlobalData mGlobalData;
	return &mGlobalData;
}

void CGlobalData::setSelectedPlayerID(unsigned int nIndexID)
{
	if (nIndexID < m_vPlayerDataVector.size())
	{
		m_sCurPalyerData = m_vPlayerDataVector[nIndexID];

		//temp
		m_eSelectPlayer = m_sCurPalyerData.mKind;
	}
}

void CGlobalData::setLevelID(unsigned int nLevelID)
{
	if (nLevelID < m_vLevelDataVector.size())
	{
		m_sCurLevelData = m_vLevelDataVector[nLevelID];
	}

	//介个是通用的关卡解锁进度
	if (nLevelID > m_nLevelUnlock && nLevelID < 7)
	{
		char szName[DATA_LENTH_MAX] = {0};
		m_nLevelUnlock = nLevelID;
		sprintf(szName, "LevelUnlock");
		m_pSaveData->setIntegerForKey(szName, m_nLevelUnlock);

		m_pSaveData->flush();
	}

	//介个是各个飞机的关卡解锁进度m_eSelectPlayer
	if (nLevelID > m_sPlaneLevelVector[m_eSelectPlayer] && nLevelID < 7)
	{
		char szName[DATA_LENTH_MAX] = {0};
		m_sPlaneLevelVector[m_eSelectPlayer] = nLevelID;
		sprintf(szName, "Plane%02dLevelUnlock", m_eSelectPlayer);
		m_pSaveData->setIntegerForKey(szName, m_sPlaneLevelVector[m_eSelectPlayer]);

		if (nLevelID > 3 && m_eSelectPlayer == m_nPlaneUnlock)
		{
			m_nPlaneUnlock ++;
			sprintf(szName, "PlaneUnlock");
			m_pSaveData->setIntegerForKey(szName, m_nPlaneUnlock);
		}

		m_pSaveData->flush();
	}
}

void CGlobalData::saveFighterConfigure(void)
{
	char szName[DATA_LENTH_MAX] = {0};
	//玩家属性点
	sprintf(szName, "PlayerPoint");
	m_pSaveData->setIntegerForKey(szName, m_nPlayerPoint);

	//玩家速度属性点
	sprintf(szName, "PlayerSpeed");
	m_pSaveData->setIntegerForKey(szName, m_nPlayerSpeed);

	//玩家护甲属性点
	sprintf(szName, "PlayerArmor");
	m_pSaveData->setIntegerForKey(szName, m_nPlayerArmor);

	//玩家攻击属性点
	sprintf(szName, "PlayerAttack");
	m_pSaveData->setIntegerForKey(szName, m_nPlayerAttack);

	//玩家特殊武器属性点
	sprintf(szName, "PlayerBouns");
	m_pSaveData->setIntegerForKey(szName, m_nPlayerBouns);

	m_pSaveData->flush();
}

ENEMY_DATA CGlobalData::getDataByKind(ENEMY_KINDS eKind)
{
	ENEMY_DATA mData;
	memset(&mData, 0, sizeof(mData));
	std::vector<ENEMY_DATA>::iterator it = m_vEnemyDataVector.begin();
	for (; it!=m_vEnemyDataVector.end(); it++)
	{
		if ((*it).mKind == eKind)
		{
			mData = *it;
			break;
		}
	}

	mData.mHealthPoint = mData.mHealthPoint * (1.0f + 0.2f * (m_sCurLevelData.mLevel - 1))/*pow(1.2f, m_sCurLevelData.mLevel - 1)*/;
	return mData;
}

PLAYER_DATA CGlobalData::getDataByKind(PLAYER_KINDS eKind)
{
	PLAYER_DATA mData;
	memset(&mData, 0, sizeof(mData));
	std::vector<PLAYER_DATA>::iterator it = m_vPlayerDataVector.begin();
	for (; it!=m_vPlayerDataVector.end(); it++)
	{
		if ((*it).mKind == eKind)
		{
			mData = *it;
			break;
		}
	}

	mData.mArmor = mData.mArmor + m_nPlayerArmor;
	mData.mSpeed = mData.mSpeed + 450.0f * m_nPlayerSpeed * 0.05f;
	mData.mAttack = mData.mAttack + m_nPlayerAttack;
	mData.mBonusAttack = m_nPlayerBouns;
	mData.mHealthPoint = mData.mHealthPoint - mData.mHealthPoint * 0.5f * m_fDifficultyVolume;
	return mData;
}

ARMY_DATA CGlobalData::getDataByKind(ARMY_KINDS eKind)
{
	ARMY_DATA mData;
	memset(&mData, 0, sizeof(mData));
	std::vector<ARMY_DATA>::iterator it = m_vArmyDataVector.begin();
	for (; it!=m_vArmyDataVector.end(); it++)
	{
		if ((*it).mKind == eKind)
		{
			mData = *it;
			break;
		}
	}
	return mData;
}

void CGlobalData::resetPlayerData(void)
{
	m_nRocketNumber = 0;
}

//temp
void CGlobalData::loadProData(void)
{
	char szName[DATA_LENTH_MAX] = {0};
	sprintf(szName, "PlayerPoint");
	m_nPlayerPoint = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "PlayerSpeed");
	m_nPlayerSpeed = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "PlayerArmor");
	m_nPlayerArmor = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "PlayerAttack");
	m_nPlayerAttack = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "PlayerBouns");
	m_nPlayerBouns = m_pSaveData->getIntegerForKey(szName);

	//关卡点数奖励
	sprintf(szName, "Level01Point");
	m_nLevel01Point = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "Level02Point");
	m_nLevel02Point = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "Level03Point");
	m_nLevel03Point = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "Level04Point");
	m_nLevel04Point = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "Level05Point");
	m_nLevel05Point = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "Level06Point");
	m_nLevel06Point = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "Level07Point");
	m_nLevel07Point = m_pSaveData->getIntegerForKey(szName);

	sprintf(szName, "Music");
	m_bOpenMusic = m_pSaveData->getBoolForKey(szName);

	sprintf(szName, "FX");
	m_bOpenFX = m_pSaveData->getBoolForKey(szName);

	sprintf(szName, "Touch");
	m_bTouchControl = m_pSaveData->getBoolForKey(szName);

	sprintf(szName, "Gravity");
	m_bGravityControl = m_pSaveData->getBoolForKey(szName);

	sprintf(szName, "Run");
	m_bRunControl = m_pSaveData->getBoolForKey(szName);

	sprintf(szName, "Double");
	m_bDoubleControl = m_pSaveData->getBoolForKey(szName);

	//音乐大小
	sprintf(szName, "MusicValue");
	m_fMusicVolume = m_pSaveData->getFloatForKey(szName);
	//音效大小
	sprintf(szName, "FXValue");
	m_fFXVolume = m_pSaveData->getFloatForKey(szName);
	//难度
	sprintf(szName, "Difficulty");
	m_fDifficultyVolume = m_pSaveData->getFloatForKey(szName);

	//
	sprintf(szName, "Level01Score");
	m_nScore01 = m_pSaveData->getIntegerForKey(szName);
	//
	sprintf(szName, "Level02Score");
	m_nScore02 = m_pSaveData->getIntegerForKey(szName);
	//
	sprintf(szName, "Level03Score");
	m_nScore03 = m_pSaveData->getIntegerForKey(szName);
	//
	sprintf(szName, "Level04Score");
	m_nScore04 = m_pSaveData->getIntegerForKey(szName);
	//
	sprintf(szName, "Level05Score");
	m_nScore05 = m_pSaveData->getIntegerForKey(szName);
	//
	sprintf(szName, "Level06Score");
	m_nScore06 = m_pSaveData->getIntegerForKey(szName);
	//
	sprintf(szName, "Level07Score");
	m_nScore07 = m_pSaveData->getIntegerForKey(szName);
	//
	sprintf(szName, "Level08Score");
	m_nScore08 = m_pSaveData->getIntegerForKey(szName);

	//
	sprintf(szName, "LevelUnlock");
	m_nLevelUnlock = m_pSaveData->getIntegerForKey(szName);
	//各个飞机的关卡解锁进度
	for (int i=0; i<PLAYER_MAX; i++)
	{
		sprintf(szName, "Plane%02dLevelUnlock", i);
		int nLevel = m_pSaveData->getIntegerForKey(szName);
		m_sPlaneLevelVector.push_back(nLevel);
	}
	//
	sprintf(szName, "PlaneUnlock");
	m_nPlaneUnlock = m_pSaveData->getIntegerForKey(szName);

}

void CGlobalData::initProData(void)
{
	char szName[DATA_LENTH_MAX] = {0};

	for (int i=0; i<PLAYER_MAX; i++)
	{
		sprintf(szName,"%s%02d","PLAYER",i);
	}

	//玩家属性点
	sprintf(szName, "PlayerPoint");
	m_pSaveData->setIntegerForKey(szName, 0);

	//玩家速度属性点
	sprintf(szName, "PlayerSpeed");
	m_pSaveData->setIntegerForKey(szName, 5);

	//玩家护甲属性点
	sprintf(szName, "PlayerArmor");
	m_pSaveData->setIntegerForKey(szName, 5);

	//玩家攻击属性点
	sprintf(szName, "PlayerAttack");
	m_pSaveData->setIntegerForKey(szName, 5);

	//玩家特殊武器属性点
	sprintf(szName, "PlayerBouns");
	m_pSaveData->setIntegerForKey(szName, 5);

	//关卡点数奖励
	sprintf(szName, "Level01Point");
	m_pSaveData->setIntegerForKey(szName, 0);

	sprintf(szName, "Level02Point");
	m_pSaveData->setIntegerForKey(szName, 0);

	sprintf(szName, "Level03Point");
	m_pSaveData->setIntegerForKey(szName, 0);

	sprintf(szName, "Level04Point");
	m_pSaveData->setIntegerForKey(szName, 0);

	sprintf(szName, "Level05Point");
	m_pSaveData->setIntegerForKey(szName, 0);

	sprintf(szName, "Level06Point");
	m_pSaveData->setIntegerForKey(szName, 0);

	sprintf(szName, "Level07Point");
	m_pSaveData->setIntegerForKey(szName, 0);

	//音乐开关
	sprintf(szName, "Music");
	m_pSaveData->setBoolForKey(szName, false);
	//音效开关
	sprintf(szName, "FX");
	m_pSaveData->setBoolForKey(szName, false);
	//触摸开关
	sprintf(szName, "Touch");
	m_pSaveData->setBoolForKey(szName, true);
	//重力开关
	sprintf(szName, "Gravity");
	m_pSaveData->setBoolForKey(szName, false);
	//立即开关
	sprintf(szName, "Run");
	m_pSaveData->setBoolForKey(szName, true);
	//双击开关
	sprintf(szName, "Double");
	m_pSaveData->setBoolForKey(szName, false);
	//音乐大小
	sprintf(szName, "MusicValue");
	m_pSaveData->setFloatForKey(szName, 0.5f);
	//音效大小
	sprintf(szName, "FXValue");
	m_pSaveData->setFloatForKey(szName, 0.5f);
	//难度
	sprintf(szName, "Difficulty");
	m_pSaveData->setFloatForKey(szName, 0.0f);

	//
	sprintf(szName, "Level01Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore01);
	//
	sprintf(szName, "Level02Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore02);
	//
	sprintf(szName, "Level03Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore03);
	//
	sprintf(szName, "Level04Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore04);
	//
	sprintf(szName, "Level05Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore05);
	//
	sprintf(szName, "Level06Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore06);
	//
	sprintf(szName, "Level07Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore07);
	//
	sprintf(szName, "Level08Score");
	m_pSaveData->setIntegerForKey(szName, m_nScore08);

	//统一的解锁进度
	sprintf(szName, "LevelUnlock");
	m_pSaveData->setIntegerForKey(szName, m_nLevelUnlock);
	//各个飞机的关卡解锁进度
	for (int i=0; i<PLAYER_MAX; i++)
	{
		sprintf(szName, "Plane%02dLevelUnlock", i);
		m_pSaveData->setIntegerForKey(szName, 1);		//modify by dsw
	}
	//
	sprintf(szName, "PlaneUnlock");
	m_pSaveData->setIntegerForKey(szName, m_nPlaneUnlock);
}

void CGlobalData::addScore(int nScore)
{
	m_nCurScore += nScore;
}

std::vector<FLY_DATA> CGlobalData::getLevelPlaneData(int nLevel)
{
	//敌人飞行方式数据
	m_vLevelPlaneData.clear();
	FLY_DATA mFdata;
	mFdata.mKind = EK_DEFAULT;
	mFdata.m_fTime = 4.0f;
	mFdata.mAttitude = FA_DEFAULT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(120.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mPosition = ccp(360.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	//temp
	//mFdata.mKind = EK_AIRMINE;
	//mFdata.mPosition = ccp(530.0f, 600.0f);
	//mFdata.mAttitude = FA_AIRMINE;
	//m_vLevelPlaneData.push_back(mFdata);

	//mFdata.mKind = EK_ARMOR;
	//mFdata.mPosition = ccp(240.0f, 900.0f);
	//mFdata.mAttitude = FA_ARMOR;
	//m_vLevelPlaneData.push_back(mFdata);
	//temp end

	mFdata.mKind = EK_HELI02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(160.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LEFTTORIGHT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 600.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RIGHTTOLEFT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 600.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	//temp
	mFdata.mKind = EK_AIRMINE;
	mFdata.mPosition = ccp(530.0f, 600.0f);
	mFdata.mAttitude = FA_AIRMINE;
	m_vLevelPlaneData.push_back(mFdata);


	//temp end

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LEANLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(0.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LEANRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(480.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_ARMOR;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mPosition = ccp(240.0f, 900.0f);
	mFdata.mAttitude = FA_ARMOR;
	m_vLevelPlaneData.push_back(mFdata);
	//mFdata.m_fTime += SLOT_TIME;
	//mFdata.m_fTime += SLOT_TIME;
	//mFdata.m_fTime += SLOT_TIME;
	//mFdata.mPosition = ccp(320.0f, 800.0f);
	//m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 400.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 400.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI01;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(320.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_DEFAULT;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LROUNDBT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 400.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	//mFdata.mKind = EK_HELI01;
	//mFdata.mAttitude = FA_M_A_M;
	//mFdata.mPosition = ccp(320.0f, 800.0f);
	//m_vLevelPlaneData.push_back(mFdata);

	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RROUNDBT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 400.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(160.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TROUNDLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(240.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(240.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	//temp
	mFdata.mKind = EK_AIRMINE;
	mFdata.mPosition = ccp(530.0f, 600.0f);
	mFdata.mAttitude = FA_AIRMINE;
	m_vLevelPlaneData.push_back(mFdata);

	//temp end

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LQROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 0.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_ARMOR;
	mFdata.mPosition = ccp(240.0f, 900.0f);
	mFdata.mAttitude = FA_ARMOR;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RQROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 0.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI01;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(160.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI01;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(320.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LEFTTORIGHT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 600.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RIGHTTOLEFT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 600.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_HELI02;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(320.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TROUNDLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(240.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(240.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	//temp
	mFdata.mKind = EK_AIRMINE;
	mFdata.mPosition = ccp(530.0f, 600.0f);
	mFdata.mAttitude = FA_AIRMINE;
	m_vLevelPlaneData.push_back(mFdata);


	//temp end

	mFdata.mKind = EK_DEFAULT;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LROUNDBT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 400.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_DEFAULT;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RROUNDBT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 400.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI01;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(160.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(160.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LQROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 0.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RQROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 0.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI02;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(320.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LQROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 0.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	//temp
	mFdata.mKind = EK_AIRMINE;
	mFdata.mPosition = ccp(530.0f, 600.0f);
	mFdata.mAttitude = FA_AIRMINE;
	m_vLevelPlaneData.push_back(mFdata);

	//temp end

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RQROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 0.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LEFTTORIGHT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 600.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_ARMOR;
	mFdata.mPosition = ccp(240.0f, 900.0f);
	mFdata.mAttitude = FA_ARMOR;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_RIGHTTOLEFT;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 600.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI01;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(320.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE02;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_HELI01;
	mFdata.mAttitude = FA_M_A_M;
	mFdata.mPosition = ccp(320.0f, 800.0f);
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_ARMOR;
	mFdata.mPosition = ccp(240.0f, 900.0f);
	mFdata.mAttitude = FA_ARMOR;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);


	mFdata.mKind = EK_PLANE03;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_LQROUNDTB;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 0.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDRL;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(-100.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_ARMOR;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mPosition = ccp(240.0f, 900.0f);
	mFdata.mAttitude = FA_ARMOR;
	m_vLevelPlaneData.push_back(mFdata);

	mFdata.mKind = EK_PLANE04;
	mFdata.m_fTime += ROUND_TIME;
	mFdata.mAttitude = FA_TQROUNDLR;
	mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
	mFdata.mPosition = ccp(580.0f, 800.0f);
	mFdata.mPosition = getPosByFlyAttitude(mFdata.mAttitude);
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);
	mFdata.m_fTime += SLOT_TIME;
	m_vLevelPlaneData.push_back(mFdata);

	//m_vLevelPlaneData.clear();
	return m_vLevelPlaneData;
}

std::vector<LAND_DATA> CGlobalData::getLevelLandData(int nLevel)
{
	//敌人陆军数据
	m_vLevelLandData.clear();

	LAND_DATA mLData;
	mLData.m_fTime = 10.0f;
	mLData.mKind = AK_MISSILEARMY;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	//mLData.mPosition = ccp(120.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(240.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(360.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 20.0f;
	mLData.mKind = AK_DEFAULT;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	mLData.mPosition = ccp(360.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(240.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	//mLData.mPosition = ccp(120.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 30.0f;
	mLData.mKind = AK_BATTERY01;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	//mLData.mPosition = ccp(160.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(320.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 40.0f;
	mLData.mKind = AK_BUNKER01;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	mLData.mPosition = ccp(320.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	//mLData.mPosition = ccp(160.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 50.0f;
	mLData.mKind = AK_DEFAULT;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	mLData.mPosition = ccp(240.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(360.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	//mLData.mPosition = ccp(120.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 60.0f;
	mLData.mKind = AK_DEFAULT;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	mLData.mPosition = ccp(240.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	//mLData.mPosition = ccp(120.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);
	mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(360.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 70.0f;
	mLData.mKind = AK_DEFAULT;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	mLData.mPosition = ccp(240.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	//mLData.mPosition = ccp(120.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);
	mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(360.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 90.0f;
	mLData.mKind = AK_DEFAULT;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	mLData.mPosition = ccp(240.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	//mLData.mPosition = ccp(120.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);
	mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(360.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);

	mLData.m_fTime = 100.0f;
	mLData.mKind = AK_DEFAULT;
	mLData.mKind = (ARMY_KINDS)((int)(CCRANDOM_0_1() * AK_ARMY_MAX));
	mLData.mPosition = ccp(240.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);
	//mLData.m_fTime += LAND_TIME;
	//mLData.mPosition = ccp(120.0f, 800.0f);
	//m_vLevelLandData.push_back(mLData);
	mLData.m_fTime += LAND_TIME;
	mLData.mPosition = ccp(360.0f, 800.0f - BANNER_HEIGHT);
	m_vLevelLandData.push_back(mLData);

	if (nLevel == 4)
	{
		m_vLevelLandData.clear();
	}
	return m_vLevelLandData;
}

void CGlobalData::resetLevelScore(void)
{
	m_vDesAirScore.clear();
	m_vAirScore.clear();
	m_vDesArmyScore.clear();
	m_vArmyScore.clear();

	for (int i=0; i<8; i++)
	{
		m_vDesAirScore.push_back(0);
		m_vAirScore.push_back(0);
	}

	for (int i=0; i<4; i++)
	{
		m_vDesArmyScore.push_back(0);
		m_vArmyScore.push_back(0);
	}
	
	resetBombPercentage();
	m_nRocketNumber = 0;
	m_nLifeNumber = INIT_LIFE;
	m_bLevelClear = false;
	m_eHoldItem = IK_DEFAULT;
	m_nCurScore = 0;
}

void CGlobalData::addAirScore(ENEMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	if (it < m_vAirScore.size())
	{
		m_vAirScore[it] += 1;
	}
}

void CGlobalData::addDesAirScore(ENEMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	if (it < m_vDesAirScore.size())
	{
		m_vDesAirScore[it] += 1;
	}
}

void CGlobalData::addArmyScore(ARMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	it = it / 2;
	if (it < m_vArmyScore.size())
	{
		m_vArmyScore[it] += 1;
	}
}

void CGlobalData::addDesArmyScore(ARMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	it = it / 2;
	if (it < m_vDesArmyScore.size())
	{
		m_vDesArmyScore[it] += 1;
	}
}

int CGlobalData::getAirScoreByIndex(ENEMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	if (it < m_vAirScore.size())
	{
		return m_vAirScore[it];
	}
	return 0;
}

int CGlobalData::getArmyScoreByIndex(ARMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	it = it / 2;
	if (it < m_vArmyScore.size())
	{
		return m_vArmyScore[it];
	}
	return 0;
}

int CGlobalData::getDesAirScoreByIndex(ENEMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	if (it < m_vDesAirScore.size())
	{
		return m_vDesAirScore[it];
	}
	return 0;
}

int CGlobalData::getDesArmyScoreByIndex(ARMY_KINDS eKind)
{
	unsigned int it = (unsigned int)eKind;
	it = it / 2;
	if (it < m_vDesArmyScore.size())
	{
		return m_vDesArmyScore[it];
	}
	return 0;
}

int CGlobalData::getDesPercentage(void)
{
	int Percentage = 0;
	int totalScore = 0;
	int totalDesScore = 0;
	for (unsigned i=0; i<m_vArmyScore.size(); i++)
	{
		totalScore += m_vArmyScore[i];
	}

	for (unsigned i=0; i<m_vAirScore.size(); i++)
	{
		totalScore += m_vAirScore[i];
	}

	for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
	{
		totalDesScore += m_vDesArmyScore[i];
	}

	for (unsigned i=0; i<m_vDesAirScore.size(); i++)
	{
		totalDesScore += m_vDesAirScore[i];
	}

	Percentage = (int)(100.0f * totalDesScore / totalScore);
	if (Percentage > 100)
	{
		Percentage = 100;
	}

	if (Percentage < 0)
	{
		Percentage = 0;
	}
	return Percentage;
}

CCPoint CGlobalData::getPosByFlyAttitude(FLYING_ATTITUDE eKind)
{
	CCPoint mPos = CCPointMake(0,0);
	switch(eKind)
	{
	case FA_DEFAULT:
		mPos = ccp(120.0f + CCRANDOM_0_1() * 240.0f, 800.0f - BANNER_HEIGHT);;
		break;
	case FA_LEFTTORIGHT:
		mPos = ccp(-100.0f, 600.0f - BANNER_HEIGHT * 0.5f);
		break;
	case FA_RIGHTTOLEFT:
		mPos = ccp(580.0f, 600.0f - BANNER_HEIGHT * 0.5f);
		break;
	case FA_LEANLR:
		mPos = ccp(0.0f, 800.0f - BANNER_HEIGHT);
		break;
	case FA_LEANRL:
		mPos = ccp(480.0f, 800.0f - BANNER_HEIGHT);
		break;
	case FA_LROUNDTB:
		mPos = ccp(-100.0f, 400.0f - BANNER_HEIGHT * 0.5f);
		break;
	case FA_RROUNDTB:
		mPos = ccp(580.0f, 400.0f - BANNER_HEIGHT * 0.5f);
		break;
	case FA_LROUNDBT:
		mPos = ccp(-100.0f, 400.0f - BANNER_HEIGHT * 0.5f);
		break;
	case FA_RROUNDBT:
		mPos = ccp(580.0f, 400.0f - BANNER_HEIGHT * 0.5f);
		break;
	case FA_TROUNDLR:
		mPos = ccp(240.0f, 800.0f - BANNER_HEIGHT);
		break;
	case FA_TROUNDRL:
		mPos = ccp(240.0f, 800.0f - BANNER_HEIGHT);
		break;
	case FA_LQROUNDTB:
		mPos = ccp(-100.0f, 0.0f);
		break;
	case FA_RQROUNDTB:
		mPos = ccp(580.0f, 0.0f);
		break;
	case FA_TQROUNDLR:
		mPos = ccp(580.0f, 800.0f - BANNER_HEIGHT);
		break;
	case FA_TQROUNDRL:
		mPos = ccp(-100.0f, 800.0f - BANNER_HEIGHT);
		break;
	}

	return mPos;
}

void CGlobalData::setRewardByLevel(int nLevel)
{
	char szName[DATA_LENTH_MAX] = {0};
	switch(nLevel)
	{
	case 1:
		if (m_nCurScore > m_nScore01)
		{
			m_nScore01 = m_nCurScore;
			sprintf(szName, "Level01Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore01);
		}
		sprintf(szName, "Level01Point");
		m_pSaveData->setIntegerForKey(szName, m_nLevel01Point);
		break;
	case 2:
		if (m_nCurScore > m_nScore02)
		{
			m_nScore02 = m_nCurScore;
			sprintf(szName, "Level02Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore02);
		}
		sprintf(szName, "Level02Point");
		m_pSaveData->setIntegerForKey(szName, m_nLevel02Point);
		break;
	case 3:
		if (m_nCurScore > m_nScore03)
		{
			m_nScore03 = m_nCurScore;
			sprintf(szName, "Level03Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore03);
		}
		sprintf(szName, "Level03Point");
		m_pSaveData->setIntegerForKey(szName, m_nLevel03Point);
		break;
	case 4:
		if (m_nCurScore > m_nScore04)
		{
			m_nScore04 = m_nCurScore;
			sprintf(szName, "Level04Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore04);
		}
		sprintf(szName, "Level04Point");
		m_pSaveData->setIntegerForKey(szName, m_nLevel04Point);
		break;
	case 5:
		if (m_nCurScore > m_nScore05)
		{
			m_nScore05 = m_nCurScore;
			sprintf(szName, "Level05Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore05);
		}
		sprintf(szName, "Level05Point");
		m_pSaveData->setIntegerForKey(szName, m_nLevel05Point);
		break;
	case 6:
		if (m_nCurScore > m_nScore06)
		{
			m_nScore06 = m_nCurScore;
			sprintf(szName, "Level06Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore06);
		}
		sprintf(szName, "Level06Point");
		m_pSaveData->setIntegerForKey(szName, m_nLevel06Point);
		break;
	case 7:
		if (m_nCurScore > m_nScore07)
		{
			m_nScore07 = m_nCurScore;
			sprintf(szName, "Level07Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore07);
		}
		sprintf(szName, "Level07Point");
		m_pSaveData->setIntegerForKey(szName, m_nLevel07Point);
		break;
	case 8:
		if (m_nCurScore > m_nScore08)
		{
			m_nScore08 = m_nCurScore;
			sprintf(szName, "Level08Score");
			m_pSaveData->setIntegerForKey(szName, m_nScore08);
		}
		break;
	}
	
	m_nScoreTotal = m_nScore01 + m_nScore02 + m_nScore03 + m_nScore04 + m_nScore05 + m_nScore06 + m_nScore07 + m_nScore08;

	sprintf(szName, "PlayerPoint");
	m_pSaveData->setIntegerForKey(szName, m_nPlayerPoint);

	m_pSaveData->flush();
}

int CGlobalData::getScoreByLevel(int nLevel)
{
	int mScore = 0;
	switch(nLevel)
	{
	case 1:
		mScore = m_nScore01;
		break;
	case 2:
		mScore = m_nScore02;
		break;
	case 3:
		mScore = m_nScore03;
		break;
	case 4:
		mScore = m_nScore04;
		break;
	case 5:
		mScore = m_nScore05;
		break;
	case 6:
		mScore = m_nScore06;
		break;
	case 7:
		mScore = m_nScore07;
		break;
	case 8:
		mScore = m_nScore08;
		break;
	}

	return mScore;
}

void CGlobalData::countCurLevelReward(int nLevel)
{
	if (!isLevelClear())
	{
		return ;
	}
	switch(nLevel)
	{
	case 1:
		{
			if (m_nLevel01Point < 3)
			{
				m_nCurRewardPoint = (getDesPercentage() - 70 - m_nLevel01Point * 10) / 10;
				if (m_nCurRewardPoint < 0)
				{
					m_nCurRewardPoint = 0;
				}
				m_nLevel01Point += m_nCurRewardPoint;
			}
			int totalDesScore = 0;

			for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
			{
				totalDesScore += m_vDesArmyScore[i];
			}

			for (unsigned i=0; i<m_vDesAirScore.size(); i++)
			{
				totalDesScore += m_vDesAirScore[i];
			}

			m_nCurRewardScore = totalDesScore * 10;
		}
		break;
	case 2:
		{
			if (m_nLevel02Point < 3)
			{
				m_nCurRewardPoint = (getDesPercentage() - 70 - m_nLevel02Point * 10) / 10;
				if (m_nCurRewardPoint < 0)
				{
					m_nCurRewardPoint = 0;
				}
				m_nLevel02Point += m_nCurRewardPoint;
			}
			int totalDesScore = 0;

			for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
			{
				totalDesScore += m_vDesArmyScore[i];
			}

			for (unsigned i=0; i<m_vDesAirScore.size(); i++)
			{
				totalDesScore += m_vDesAirScore[i];
			}

			m_nCurRewardScore = totalDesScore * 10;
		}
		break;
	case 3:
		{
			if (m_nLevel03Point < 3)
			{
				m_nCurRewardPoint = (getDesPercentage() - 70 - m_nLevel03Point * 10) / 10;
				if (m_nCurRewardPoint < 0)
				{
					m_nCurRewardPoint = 0;
				}
				m_nLevel03Point += m_nCurRewardPoint;
			}
			int totalDesScore = 0;

			for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
			{
				totalDesScore += m_vDesArmyScore[i];
			}

			for (unsigned i=0; i<m_vDesAirScore.size(); i++)
			{
				totalDesScore += m_vDesAirScore[i];
			}

			m_nCurRewardScore = totalDesScore * 10;
		}
		break;
	case 4:
		{
			if (m_nLevel04Point < 3)
			{
				m_nCurRewardPoint = (getDesPercentage() - 70 - m_nLevel04Point * 10) / 10;
				if (m_nCurRewardPoint < 0)
				{
					m_nCurRewardPoint = 0;
				}
				m_nLevel04Point += m_nCurRewardPoint;
			}
			int totalDesScore = 0;

			for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
			{
				totalDesScore += m_vDesArmyScore[i];
			}

			for (unsigned i=0; i<m_vDesAirScore.size(); i++)
			{
				totalDesScore += m_vDesAirScore[i];
			}

			m_nCurRewardScore = totalDesScore * 10;
		}
		break;
	case 5:
		{
			if (m_nLevel05Point < 3)
			{
				m_nCurRewardPoint = (getDesPercentage() - 70 - m_nLevel05Point * 10) / 10;
				if (m_nCurRewardPoint < 0)
				{
					m_nCurRewardPoint = 0;
				}
				m_nLevel05Point += m_nCurRewardPoint;
			}
			int totalDesScore = 0;

			for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
			{
				totalDesScore += m_vDesArmyScore[i];
			}

			for (unsigned i=0; i<m_vDesAirScore.size(); i++)
			{
				totalDesScore += m_vDesAirScore[i];
			}

			m_nCurRewardScore = totalDesScore * 10;
		}
		break;
	case 6:
		{
			if (m_nLevel06Point < 3)
			{
				m_nCurRewardPoint = (getDesPercentage() - 70 - m_nLevel06Point * 10) / 10;
				if (m_nCurRewardPoint < 0)
				{
					m_nCurRewardPoint = 0;
				}
				m_nLevel06Point += m_nCurRewardPoint;
			}
			int totalDesScore = 0;

			for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
			{
				totalDesScore += m_vDesArmyScore[i];
			}

			for (unsigned i=0; i<m_vDesAirScore.size(); i++)
			{
				totalDesScore += m_vDesAirScore[i];
			}

			m_nCurRewardScore = totalDesScore * 10;
		}
		break;
	case 7:
		{
			if (m_nLevel07Point < 3)
			{
				m_nCurRewardPoint = (getDesPercentage() - 70 - m_nLevel07Point * 10) / 10;
				if (m_nCurRewardPoint < 0)
				{
					m_nCurRewardPoint = 0;
				}
				m_nLevel07Point += m_nCurRewardPoint;
			}
			int totalDesScore = 0;

			for (unsigned i=0; i<m_vDesArmyScore.size(); i++)
			{
				totalDesScore += m_vDesArmyScore[i];
			}

			for (unsigned i=0; i<m_vDesAirScore.size(); i++)
			{
				totalDesScore += m_vDesAirScore[i];
			}

			m_nCurRewardScore = totalDesScore * 10;
		}
		break;
	}
}

bool CGlobalData::convertRewardScore(void)
{
	if (m_nCurRewardScore == 0 && m_nCurRewardPoint == 0)
	{
		return true;
	}

	if (m_nCurRewardScore > 100)
	{
		m_nCurRewardScore -= 100;
		addScore(100);
	}
	else
	{
		addScore(m_nCurRewardScore);
		m_nCurRewardScore = 0;
	}

	if (m_nCurRewardPoint > 0)
	{
		m_nPlayerPoint ++;
		m_nCurRewardPoint --;
	}

	return false;
}

void CGlobalData::convertAllRewardScore(void)
{
	while(!convertRewardScore())
	{
	}
}

void CGlobalData::setOption(void)
{
	char szName[DATA_LENTH_MAX] = {0};
	//音乐开关
	sprintf(szName, "Music");
	m_pSaveData->setBoolForKey(szName, m_bOpenMusic);
	//音效开关
	sprintf(szName, "FX");
	m_pSaveData->setBoolForKey(szName, m_bOpenFX);
	//触摸开关
	sprintf(szName, "Touch");
	m_pSaveData->setBoolForKey(szName, m_bTouchControl);
	//重力开关
	sprintf(szName, "Gravity");
	m_pSaveData->setBoolForKey(szName, m_bGravityControl);
	//立即开关
	sprintf(szName, "Run");
	m_pSaveData->setBoolForKey(szName, m_bRunControl);
	//双击开关
	sprintf(szName, "Double");
	m_pSaveData->setBoolForKey(szName, m_bDoubleControl);
	//音乐大小
	sprintf(szName, "MusicValue");
	m_pSaveData->setFloatForKey(szName, m_fMusicVolume);
	//音效大小
	sprintf(szName, "FXValue");
	m_pSaveData->setFloatForKey(szName, m_fFXVolume);
	//难度
	sprintf(szName, "Difficulty");
	m_pSaveData->setFloatForKey(szName, m_fDifficultyVolume);

	m_pSaveData->flush();
}

void CGlobalData::resetEndlessData(void)
{
	m_nEndlessNum ++;
	m_bRefreshData = true;
}
