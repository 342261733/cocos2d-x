#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"
#include "Music.h"
#include "ItemSprite.h"

using namespace CocosDenshion;

#define PFRAME_TIME	0.1f

enum PLAYER_STATE
{
	PS_DEFAULT,
	PS_AUTOMOVE,
	PS_MOVE,
	PS_AUTOFLY,
	PS_LANDING,
	PS_EXPLODE,
	PS_HIDE,			//表示被摧毁
};

class CPlayerSprite :
	public CCNode
{
public:
	CPlayerSprite(void);
	~CPlayerSprite(void);

public:
	static CPlayerSprite* createPlayer(PLAYER_KINDS eKind);
	void setTargetPoint(const CCPoint& pos);
	//CC_PROPERTY_PASS_BY_REF(CCPoint, m_tTargetPosition, TargetPosition)
	void underAttack(int nHurt);
	void addHealthPoint(int nValue);

	void setGravityOffset(CCPoint Offset){m_sGravityOffset = Offset;}
	//void addFire(void);
	//void addIronCurtain(void);

	//
	void addItemKind(ITEM_KINDS eKind);
	//使用保留的道具
	void usingHoldItem(void);
	void addItem(ITEM_KINDS eKind);
	bool isDead(void);
	bool isShieldTaken(void);
	float getHPPercentage(void);
	PLAYER_STATE getCurState(void){return m_eCurState;} 
	void setAutoFly(void);
	void runLand(const CCPoint& pos);
public:
private:
	void createSprite(PLAYER_KINDS eKind);
	void playerUpdate(float fEscapeTime);
	void setFlyingAttitude(float fOffset);				//设置飞行姿态
	void displayFrameByIndex(unsigned int nIndex);
	void fireBullet(float fEscapeTime);

	void itemUpdate(float fEscapeTime);
	void itemLogic(ITEM_KINDS eKind, float fEscapeTime);
	void removeItemIndex(ITEM_KINDS eKind);
	void removeItemByKind(ITEM_KINDS eKind);
	bool isExistItem(ITEM_KINDS eKind);
	void removeAllItem(void);

	void removeSelf(void);
	void runEffect(void);
	void activatePlayer(void);
	void returnNormalTexture(void);

	//FIRE BALL
	void addFireBall(void);
	//POWER
	void addPower(void);
	//IRON CURTAIN
	void addIronCurtain(void);
	//TRACK ROCKET
	void addTarckRocket(void);
	//SHIELD TAKEN
	void addShieldTaken(void);
	void removeIronCurtain(void);
	//WING MAN
	void addWingMan(void);
	void removeWingMan(void);

	void lostPower(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	PLAYER_DATA m_sCurData;
	PLAYER_DATA m_sInitData;
	std::vector<CCSprite*> m_vPlayerSpriteVector;
	CCPoint m_tTargetPosition;
	float m_fTime;
	int m_nCurFrame;
	CCSprite *m_pEffectSprite;
	PLAYER_STATE m_eCurState;

	int m_nFireLevel;
	float m_fFireHoldTime;			//火力持续时间

	//FIRE BALL
	float m_fFireBallTime;			//火球持续时间
	float m_fFireBallSlot;			//火球开火时间间隔累加

	//IRON CURTAIN
	float m_fIronCurtainTime;		//铁幕持续时间
	ccColor3B m_sOriginalColor;		//原始颜色

	//TRACK ROCKET
	float m_fTarckRocketSlot;		//导弹时间间隔累加

	//SHIELD TAKEN
	float m_fShieldTakenTime;		//反射盾持续时间
	CCSprite *m_pShieldTaken;

	//SUPER GUN
	float m_fSuperGunTime;			//超级枪持续时间
	float m_fSuperGunSlot;			//超级枪开火时间间隔累加
	float m_fSuperGunPos;			//开火位置
	//SIDE BULLET
	float m_fSideBulletTime;		//散弹持续时间
	float m_fSideBulletSlot;		//散弹开火时间间隔累加
	//WING MAN
	float m_fWingManTime;			//僚机持续时间
	float m_fWingManSlot;			//僚机开火时间间隔累加
	CCSprite *m_pLeftWingMan;
	CCSprite *m_pRightWingMan;		

	CCSprite *m_pShadow;			//影子
	bool m_bIsNormal;

	CCSprite *m_pFireFlashSprite;
	CCAction *m_pFireFlash;
	//CPlayerWeapon *m_pPlayerWeapon;

	std::vector<ITEM_KINDS> m_vItemVector;

	//Gravity Offset
	CCPoint m_sGravityOffset;

	//当前玩家时间
	float m_fPlayerTime;

	//保留的ITEM
	ITEM_KINDS m_eHoldItem;

	//temp
	float m_fBtime;
	float m_fBRoundTime;
	int m_nBNumber;

	ccColor3B color;
	float m_fFlashTime;
};

#endif