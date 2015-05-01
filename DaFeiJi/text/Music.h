#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define CLICK_EFFECT	"sounds/Click_01.ogg"
#define WARN_EFFECT		"sounds/Warning.ogg"
#define ITEM_EFFECT		"sounds/Item01.ogg"
#define FIRE_EFFECT		"sounds/Fire01.ogg"

#define Explode_1_EffECT	"sounds/Explode01.ogg"		//爆炸音效
#define Explode_2_EffECT	"sounds/Explode02.ogg"
#define Explode_3_EffECT	"sounds/N_Explode03.ogg"

#define MAINUI_BG_MUSIC		"sounds/MainUI.ogg"
#define BOSS_1_BG_MUSIC		"sounds/Boss01.ogg"
#define LEVEL_1_BG_MUSIC	"sounds/Level01.ogg"

class Music
{
public:

	static void preloadResouse();

	static void playClickEffect();
	static void playWarnEffect();		//警告音效
	
	static void playItemEffect();		//接受技能音效
	static void playFireEffect();		//开火音效
	static void playExplode1Effect();	//爆炸1音效
	static void playExplode2Effect();	//爆炸2音效
	static void playExplode3Effect();	//爆炸2音效

	
	static void playBoss_1_BgMusic();		//Boss音效
	static void playLevel_1_BgMusic();
	static void playMainUIBgMusic();
	
	static void pauseBackgroundMusic();
	static void resumeBackgroundMusic();
	static void stopBackgroundMusic(bool bReleaseData);

	static void setEffectVolume(float volume);
	static void setBackgroundMusicVolume(float volume);

private:
	
};


#endif