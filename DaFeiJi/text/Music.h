#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define CLICK_EFFECT	"sounds/Click_01.ogg"
#define WARN_EFFECT		"sounds/Warning.ogg"
#define ITEM_EFFECT		"sounds/Item01.ogg"
#define FIRE_EFFECT		"sounds/Fire01.ogg"

#define Explode_1_EffECT	"sounds/Explode01.ogg"		//��ը��Ч
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
	static void playWarnEffect();		//������Ч
	
	static void playItemEffect();		//���ܼ�����Ч
	static void playFireEffect();		//������Ч
	static void playExplode1Effect();	//��ը1��Ч
	static void playExplode2Effect();	//��ը2��Ч
	static void playExplode3Effect();	//��ը2��Ч

	
	static void playBoss_1_BgMusic();		//Boss��Ч
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