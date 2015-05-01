#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;


enum ENEMY_KINDS
{
	EK_DEFAULT,			//默认
	EK_PLANE02,			//
	EK_PLANE03,			//
	EK_PLANE04,			//
	EK_HELI01,
	EK_HELI02,
	EK_AIRMINE,			//空中地雷飞机
	EK_ARMOR,			//重甲机
	EK_MINE,			//空中地雷
};

enum ARMY_KINDS
{
	AK_DEFAULT,				//默认
	AK_MISSILEARMY,			//导弹坦克
	AK_GREENGUN01,			//格林炮01
	AK_GREENGUN02,			//格林炮02
	AK_BATTERY01,			//炮兵01
	AK_BATTERY02,			//炮兵02
	AK_BUNKER01,			//地堡01
	AK_BUNKER02,			//地堡02
	AK_ARMY_MAX,			//最大值
};

enum FLYING_ATTITUDE	//飞行姿态
{
	FA_DEFAULT,			//直线自上而下
	FA_LEFTTORIGHT,		//从左到右
	FA_RIGHTTOLEFT,		//从右到左
	FA_LEANLR,			//斜向（左上-右下）
	FA_LEANRL,			//斜向（右上-左下）
	FA_LROUNDTB,		//左环绕（左上半部分出现绕半个弧形左下半部分）
	FA_RROUNDTB,		//右环绕（右上半部分出现绕半个弧形右下半部分）
	FA_LROUNDBT,		//左环绕（左下半部分出现绕半个弧形左上半部分）
	FA_RROUNDBT,		//右环绕（右下半部分出现绕半个弧形右上半部分）
	FA_TROUNDLR,		//顶部（顶部出现绕半个弧形飞出从左到右）
	FA_TROUNDRL,		//顶部（顶部出现绕半个弧形飞出从右到左）
	FA_LQROUNDTB,		//左环绕1/4（左上半部分出现绕1/4弧形底部消失）
	FA_RQROUNDTB,		//右环绕1/4（右上半部分出现绕1/4弧形底部消失）
	FA_TQROUNDLR,		//顶环绕1/4（左上半部分出现绕1/4弧形右边消失）
	FA_TQROUNDRL,		//顶环绕1/4（右上半部分出现绕1/4弧形左边消失)
	FA_ENEMY_MAX,		//敌机最大值
	FA_M_A_M,			//直升机特有(从上而下移动,悬停,随机上下移动飞出)
	FA_AIRMINE,			//空中地雷机
	FA_MINE,			//空中地雷(不是飞机)
	FA_ARMOR,			//重甲机
};

enum PLAYER_KINDS
{
	PK_DEFAULT,			//雷霆
	PK_HURRICANE,		//飓风hurricane
	PK_WOLFANG,			//狼牙Wolfang
	PK_EAGLEEYE,		//鹰眼eagle eye
	PK_KINGKONG,		//金刚King Kong
	PK_TITAN,			//泰坦Titan
};

//玩家武器
enum PLAYER_WEAPON
{
	PW_DEFAULT,
};

enum ENEMY_WEAPON
{
	EW_DEFAULT,
	EW_NONE,		//无武器
	EW_SCATTER,		//散射
	EW_AIRMINE,		//空中地雷
	EW_HOLDFIRE,	//连续发射
};

enum BULLET_KINDS
{
	BK_DEFAULT,
	BK_DEFAULT01,
	BK_ARMY01,
	BK_ENEMY01,
	BK_FIREBALL,
	BK_TARCKROCKET,
	BK_SUPERGUN,	//迷你机枪
	BK_LASER,		//激光柱
	BK_THUNDERBALL,	//雷球
	BK_BLUE,		//蓝色子弹
	BK_SINBALL,		//正弦曲线子弹
	BK_USINBALL,	//反正弦曲线子弹
	BK_CRESCEN,		//月牙形右偏弧
	BK_UCRESCEN,	//月牙形左偏弧
};

//击毁飞机时的道具类型
enum ITEM_KINDS
{
	IK_DEFAULT,
	IK_HP,				
	IK_FIREPOWER,
	IK_FIREBALL,
	IK_IRONCURTAIN,
	IK_SHIELDTAKEN,
	IK_TRACKROCKET,
	IK_SUPERGUN,
	IK_LIFE,
	IK_WINGMAN,
	IK_SIDEBULLET,

	IK_MAX,
};

enum BOSS_KINDS
{
	BOK_DEFAULT,
	BOK_LEVEL01,
	BOK_LEVEL02,
	BOK_LEVEL03,
	BOK_LEVEL04,
	BOK_LEVEL05,
	BOK_LEVEL06,
	BOK_LEVEL07,
	BOK_LEVEL08,
};

enum BOSS_STATE
{
	BOS_DEFAULT,
	BOS_READY,
	BOS_READY_RUN,
	BOS_STAGE,
	BOS_STAGE_RUN,
	BOS_FIRE,
	BOS_FIRE_RUN,
	BOS_EXPLODE,
	BOS_EXPLODE_RUN,
	BOS_HIDE,
};

enum STAGE_BOSS
{
	STAGE_DEFAULT,
	STAGE_READY01,
	STAGE_ACTION01,
	STAGE_READY02,
	STAGE_ACTION02,
	STAGE_READY03,
	STAGE_ACTION03,
	STAGE_READY04,
	STAGE_ACTION04,
	STAGE_READY05,
	STAGE_ACTION05,
	STAGE_EXPLODE,
};

#define  STAGEEND_HP	0		//结束

struct BULLET_DATA
{
	BULLET_KINDS mKind;
	float mMoveSpeed;		//飞行速度
	CCPoint mDirection;		//飞行方向
	int mAttack;			//伤害值
	//振幅
	float m_fAmplitude;
};

struct ENEMY_DATA				//敌人数据
{
	ENEMY_KINDS mKind;			//种类
	int mIndex;					//编号索引
	FLYING_ATTITUDE mAttitude;	//飞行方式
	int mScoreValue;			//分值(打爆后获得的分数)
	float mMoveSpeed;			//速度
	//int mDirection;			//朝向
	int mHealthPoint;			//HP
	//CCPoint mPoint;			//位置
	int mAttack;				//攻击力
};

struct ARMY_DATA
{
	ARMY_KINDS mKind;
	int mIndex;
	int mScoreValue;
	float mMoveSpeed;
	CCPoint mDirection;			//炮塔朝向
	int mHealthPoint;
	int mAttack;
};

struct FLY_DATA
{
	FLYING_ATTITUDE mAttitude;
	CCPoint mPosition;			//初始位置
	//temp
	float m_fTime;				//出生时间
	ENEMY_KINDS mKind;			//飞机样式
};

struct LAND_DATA
{
	CCPoint mPosition;			//初始位置
	//temp
	float m_fTime;				//出生时间
	ARMY_KINDS mKind;			//陆军样式
};

struct PLAYER_DATA
{
	PLAYER_KINDS mKind;			//种类
	PLAYER_WEAPON mWeapon;		//武器类型
	int mLevel;
	int mFreePropertyPoints;	//自由属性点
	int mSpeed;					//速度
	int mArmor;					//装甲
	int mAttack;				//攻击力加成
	int mBonusAttack;			//道具加成
	int mHealthPoint;			//HP
	int mIndex;					//编号索引
};

struct WEAPON_DATA
{
	PLAYER_WEAPON mKind;
	float mAttackSpeed;
};

struct LEVEL_DATA
{
	int mLevel;
	std::string	mMission;
	float mMapSpeed;
	float mBossTime;			//BOSS出现的时间
};

//评价
enum ASSESS_KINDS
{
	ASK_DEFAULT,
	ASK_PERFECT,
	ASK_ADD50,
	ASK_ADD100,
	ASK_FIRE,
	ASK_HP,
	ASK_LIFE,
	ASK_FIREBALL,
	ASK_IRONCURTAIN,
	ASK_SHIELDTAKEN,
	ASK_TRACKROCKET,
	ASK_SUPERGUN,
	ASK_WINGMAN,
	ASK_SIDEBULLET,
};
struct	ASSESS_DATA
{
	ASSESS_KINDS mKind;
	CCPoint mPos;
};

#define DATA_LENTH_MAX	128	//保存字符串长度

#define INIT_LIFE	3		//初始生命数
#define PLAYER_MAX	6		//玩家可选飞机数
#define LEVEL_MAX	8		//玩家可选关卡数
#define ANIMATE_MAX 32		//最大动画帧数
#define OFFSET_MAX	10.0f	//玩家移动最大误差
#define FLYING_MAX	0.0f	//飞行姿态偏移误差
#define ITEM_LIFE	10.0f	//道具存在周期
#define FIRE_MAX	2		//火力最大级别(从零算起)
#define FIRE_HOLD	10.0f	//火力持续时间
#define IRON_HOLD	10.0f	//铁幕持续时间
#define FIREBALL_SLOT	0.4f	//火球发射间隔
#define SUPERGUN_SLOT	0.05f	//超级枪发射间隔
#define SIDEBULLET_SLOT	0.2f	//散弹发射间隔
#define WINGMAN_HOLD	13.0f	//僚机持续时间
#define WINGMAN_SLOT	0.2f	//僚机发射间隔
#define TARCKROCKET_SLOT	1.0f//导弹发射间隔
#define TOUCH_OFFSET	75.0f	//触摸位置偏移
#define BANNER_HEIGHT	70.0f	//广告条高度
#define DROPITEM_SLOT	5.0f	//物品掉落时间间隔
#define NUCLEAR_HURT	1000	//核弹的伤害值
#define ROCKET_NUM		10		//导弹增加量
#define SHIELD_DES		64.0f	//反射判定距离
#define LACKEY_TIME		3.0f	//酱油飞机出现时间 

#define DOUBLE_TIME		0.5f	//双击事件判定时间间隔

#define SLOT_TIME	0.5f		//飞机出现间隔
#define LAND_TIME	1.0f		//飞机着陆时间
#define ROUND_TIME	1.0f		//飞机队与队之间间隔

#define ENEMY_TYPE		10000
#define ARMY_TYPE		11000
#define BOSS_TYPE		12000
#define HELI_TYPE		13000
#define DRONE_TYPE		14000
#define PALYER_TYPE		20000
#define ENEMY_BULLET	30000
#define PALYER_BULLET	40000

#define MAP_ZORDER		1		//地面背景Z-order
#define ARMY_ZORDER		11		//地面部队Z-order
#define BOMB_ZORDER		20		//对地炸弹Z-order
#define LCLOUD_ZORDER	21		//低层云Z-order
#define ABULLET_ZORDER	30		//空中部队子弹Z-order
#define AIR_ZORDER		31		//空中部队Z-order
#define BOSS_ZORDER	34			//BOSS Z-order
#define BBULLET_ZORDER	35		//BOSS子弹 Z-order
#define PBULLET_ZORDER	40		//玩家子弹Z-order
#define FLASH_ZORDER	41		//玩家开火闪光Z-order
#define PLAYER_ZORDER	42		//玩家Z-order
#define HCLOUD_ZORDER	51		//高层云Z-order
#define ASSESS_ZORDER	58		//评价Z-order
#define GAMEUI_ZORDER	61		//游戏UI的Z-order

#define MAIN_UI			1000
#define SELECT_UI		2000
#define SHOP_UI			3000
#define MISSION_UI		4000

#define VERSION			2		//版本控制（1为完全版2为去广告海外版）

class CGlobalData
{
public:
	CGlobalData(void);
	~CGlobalData(void);
public:
	static CGlobalData* getSingleton(void);

	void setSelectedPlayerID(unsigned int nIndexID);
	void setLevelID(unsigned int nLevelID);
	LEVEL_DATA getCurLevelData(void)
	{
		return m_sCurLevelData;
	}

	void saveFighterConfigure(void);

	std::string getNameByKind();
	ENEMY_DATA getDataByKind(ENEMY_KINDS eKind);
	ARMY_DATA getDataByKind(ARMY_KINDS eKind);
	PLAYER_DATA getDataByKind(PLAYER_KINDS eKind);
	//temp end
	void initProData(void);
	void loadProData(void);

	void addScore(int nScore);
	int getCurScore(void)
	{
		return m_nCurScore;
	}

	int getCurPoint(void)
	{
		return m_nPlayerPoint;
	}

	PLAYER_KINDS getSelectKind(void) 
	{
		return m_eSelectPlayer;
	}

	std::vector<FLY_DATA> getLevelPlaneData(int nLevel);
	std::vector<LAND_DATA> getLevelLandData(int nLevel);

	void resetLevelScore(void);
	void addAirScore(ENEMY_KINDS eKind);
	void addArmyScore(ARMY_KINDS eKind);
	void addDesAirScore(ENEMY_KINDS eKind);
	void addDesArmyScore(ARMY_KINDS eKind);
	int getAirScoreByIndex(ENEMY_KINDS eKind);
	int getArmyScoreByIndex(ARMY_KINDS eKind);
	int getDesAirScoreByIndex(ENEMY_KINDS eKind);
	int getDesArmyScoreByIndex(ARMY_KINDS eKind);

	int getDesPercentage(void);

	void upDateGameTime(float fEscapeTime)
	{
		m_fGameTime += fEscapeTime;
	}

	void recordDropTime(void)
	{
		m_fItemDropTime = m_fGameTime;
	}

	bool isDropItem(void)
	{
		if (abs(m_fItemDropTime - m_fGameTime) > DROPITEM_SLOT)
		{
			return true;
		}
		return false;
	}

	void addBombPercentage(void)
	{
		m_fBombPercentage += 0.5f;
		if (m_fBombPercentage > 100.0f)
		{
			m_fBombPercentage = 100.0f;
		}
	}

	void resetBombPercentage(void)
	{
		m_fBombPercentage = 0.0f;
	}

	float getBombPercentage(void)
	{
		return m_fBombPercentage;
	}

	void addRocket(int nNumber)
	{
		m_nRocketNumber += nNumber;
		if (m_nRocketNumber > 99)
		{
			m_nRocketNumber = 99;
		}
	}

	void reduceRocket(int nNumber)
	{
		m_nRocketNumber -= nNumber;
		if (m_nRocketNumber < 0)
		{
			m_nRocketNumber = 0;
		}
	}

	int getRocket(void)
	{
		return m_nRocketNumber;
	}

	void reduceLife(void)
	{
		m_nLifeNumber --;
		if (m_nLifeNumber < 0)
		{
			m_nLifeNumber = 0;
		}
	}

	void addLife(int nNumber)
	{
		m_nLifeNumber += nNumber;
		if (m_nLifeNumber > 9)
		{
			m_nLifeNumber = 9;
		}
	}
	
	int getLife(void)
	{
		return m_nLifeNumber;
	}

	void resetPlayerData(void);

	void setIsWingman(bool bIsExist)
	{
		m_bWingmanExist = bIsExist;
	}

	bool isExistWingman(void)
	{
		return m_bWingmanExist;
	}

	void setLevelClear(bool bIsClear)
	{
		m_bLevelClear = true;
	}

	bool isLevelClear(void)
	{
		return m_bLevelClear;
	}

	//选项
	void setOption(void);
	void setMusicONOFF(bool bOnOff)
	{
		m_bOpenMusic = bOnOff;
	}

	bool isOpenMusic(void)
	{
		return m_bOpenMusic;
	}

	void setFXONOFF(bool bOnOff)
	{
		m_bOpenFX = bOnOff;
	}

	bool isOpenFX(void)
	{
		return m_bOpenFX;
	}

	void setMusicVolume(float fVolume)
	{
		m_fMusicVolume = fVolume;
	}

	float getMusicVolume(void)
	{
		return m_fMusicVolume;
	}

	void setFXVolume(float fVolume)
	{
		m_fFXVolume = fVolume;
	}

	float getFXVolume(void)
	{
		return m_fFXVolume;
	}

	void setDifficultyVolume(float fVolume)
	{
		m_fDifficultyVolume = fVolume;
	}

	float getDifficultyVolume(void)
	{
		return m_fDifficultyVolume;
	}

	bool isTouchControl(void)
	{
		return m_bTouchControl;
	}

	void setTouchControl(bool bTouch)
	{
		m_bTouchControl = bTouch;
	}

	bool isGravityControl(void)
	{
		return m_bGravityControl;
	}

	void setGravityControl(bool bGravity)
	{
		m_bGravityControl = bGravity;
	}

	bool isRunControl(void)
	{
		return m_bRunControl;
	}

	void setRunControl(bool bRun)
	{
		m_bRunControl = bRun;
	}

	bool isDoubleControl(void)
	{
		return m_bDoubleControl;
	}

	void setDoubleControl(bool bDouble)
	{
		m_bDoubleControl = bDouble;
	}

	void setPlayerPoint(int nPoint)
	{
		m_nPlayerPoint = nPoint;
	}

	int getPlayerPoint(void)
	{
		return m_nPlayerPoint;
	}

	void setPlayerSpeed(int nSpeed)
	{
		m_nPlayerSpeed = nSpeed;
	}

	int getPlayerSpeed(void)
	{
		return m_nPlayerSpeed;
	}

	void setPlayerArmor(int nArmor)
	{
		m_nPlayerArmor = nArmor;
	}

	int getPlayerArmor(void)
	{
		return m_nPlayerArmor;
	}

	void setPlayerAttack(int nAttack)
	{
		m_nPlayerAttack = nAttack;
	}

	int getPlayerAttack(void)
	{
		return m_nPlayerAttack;
	}

	void setPlayerBouns(int nBouns)
	{
		m_nPlayerBouns = nBouns;
	}

	int getPlayerBouns(void)
	{
		return m_nPlayerBouns;
	}

	//记录当前关卡奖励
	void setRewardByLevel(int nLevel);

	int getTotalScore(void){return m_nScoreTotal;}

	int getScoreByLevel(int nLevel);

	//当前关卡奖励分数
	void countCurLevelReward(int nLevel);
	int getCurRewardScore(void)
	{
		return m_nCurRewardScore;
	}
	int getCurRewardPoint(void)
	{
		return m_nCurRewardPoint;
	}

	//转换奖励分数和经验
	bool convertRewardScore(void);
	//立即转换奖励
	void convertAllRewardScore(void);

	//当前的保留技能
	void setHoldItem(ITEM_KINDS eKind)
	{
		m_eHoldItem = eKind;
	}
	ITEM_KINDS getHoldItem(void)
	{
		return m_eHoldItem;
	}

	CCPoint getPosByFlyAttitude(FLYING_ATTITUDE eKind);		//根据飞行姿态获得初始位置

	//挑战赛
	void addEndlessNum(void)
	{
		m_nEndlessNum ++;
	}
	int getEndlessNum(void)
	{
		return m_nEndlessNum;
	}

	void resetEndlessData(void);
	bool isRefreshEndlessData(void)
	{
		return m_bRefreshData;
	}
	void resetRefreshData(bool bResfresh)
	{
		m_bRefreshData = bResfresh;
	}
	void setEndlessBossID(int nBossID)
	{
		m_nEndlessBossID = nBossID;
	}
	int getEndlessBossID(void)
	{
		return m_nEndlessBossID;
	}

	//飞机锁
	int getUnlockPlane(void)
	{
		return m_nPlaneUnlock;
	}

	//关卡锁
	int getUnlockLevel(void)
	{
		return m_nLevelUnlock;
	}
	int getCurUnlockLevel(void)
	{
		return m_sPlaneLevelVector[m_eSelectPlayer];
	}
private:
	
private:
	CCUserDefault *m_pSaveData;

	std::vector<PLAYER_DATA> m_vPlayerDataVector;
	std::vector<LEVEL_DATA> m_vLevelDataVector;
	std::vector<ENEMY_DATA> m_vEnemyDataVector;
	std::vector<ARMY_DATA> m_vArmyDataVector;
	std::vector<FLY_DATA> m_vFlyDataVector;
	PLAYER_DATA m_sCurPalyerData;
	LEVEL_DATA m_sCurLevelData;


	PLAYER_KINDS m_eSelectPlayer;
	int m_nRocketNumber;

	int m_nLifeNumber;

	//当前保留的技能
	ITEM_KINDS m_eHoldItem;

	//temp

	//当前分数
	int m_nCurScore;
	//当前奖励
	//int m_nCurLevelPoint;
	std::vector<FLY_DATA> m_vLevelPlaneData;
	std::vector<LAND_DATA> m_vLevelLandData;

	std::vector<int> m_vDesAirScore;
	std::vector<int> m_vAirScore;

	std::vector<int> m_vDesArmyScore;
	std::vector<int> m_vArmyScore;

	float m_fGameTime;
	float m_fItemDropTime;
	//float m_fBombTime;		//核弹时间
	float m_fBombPercentage;	//核弹进度
	bool m_bWingmanExist;		//是否已经有僚机

	bool m_bLevelClear;			//本关卡是否完成

	bool m_bOpenMusic;
	bool m_bOpenFX;
	float m_fMusicVolume;
	float m_fFXVolume;
	float m_fDifficultyVolume;

	bool m_bTouchControl;
	bool m_bGravityControl;
	bool m_bRunControl;
	bool m_bDoubleControl;
	//玩家属性点
	int m_nPlayerPoint;

	int m_nPlayerSpeed;
	int m_nPlayerArmor;
	int m_nPlayerAttack;
	int m_nPlayerBouns;

	//每关已经奖励点数
	int m_nLevel01Point;
	int m_nLevel02Point;
	int m_nLevel03Point;
	int m_nLevel04Point;
	int m_nLevel05Point;
	int m_nLevel06Point;
	int m_nLevel07Point;

	//当前奖励点数
	int m_nCurRewardPoint;
	//当前奖励分数
	int m_nCurRewardScore;

	//总分
	int m_nScoreTotal;
	//每关统计分数
	int m_nScore01;
	int m_nScore02;
	int m_nScore03;
	int m_nScore04;
	int m_nScore05;
	int m_nScore06;
	int m_nScore07;

	//挑战赛分数
	int m_nScore08;
	//挑战赛随机BOSS的ID
	int m_nEndlessBossID;
	//挑战赛重复次数
	int m_nEndlessNum;
	//是否需要刷新数据
	bool m_bRefreshData;

	//关卡锁
	int m_nLevelUnlock;
	//飞机锁
	int m_nPlaneUnlock;

	//各个飞机的关卡解锁进度
	std::vector<int> m_sPlaneLevelVector;
	int m_nPlane01Level;
	int m_nPlane02Level;
	int m_nPlane03Level;
	int m_nPlane04Level;
	int m_nPlane05Level;
	int m_nPlane06Level;

};


#endif