#include "Music.h"

void Music::preloadResouse()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MAINUI_BG_MUSIC);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BOSS_1_BG_MUSIC);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(LEVEL_1_BG_MUSIC);

	SimpleAudioEngine::sharedEngine()->preloadEffect(CLICK_EFFECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(ITEM_EFFECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(FIRE_EFFECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(Explode_1_EffECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(Explode_2_EffECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(Explode_3_EffECT);
}

void Music::playClickEffect()
{
	SimpleAudioEngine::sharedEngine()->playEffect(CLICK_EFFECT);
}

void Music::playWarnEffect()
{
	SimpleAudioEngine::sharedEngine()->playEffect(WARN_EFFECT);
}

void Music::playItemEffect()
{
	SimpleAudioEngine::sharedEngine()->playEffect(ITEM_EFFECT);
}

void Music::playFireEffect()
{
	SimpleAudioEngine::sharedEngine()->playEffect(FIRE_EFFECT);
}

void Music::playExplode1Effect()
{
	SimpleAudioEngine::sharedEngine()->playEffect(Explode_1_EffECT);
}

void Music::playExplode2Effect()
{
	SimpleAudioEngine::sharedEngine()->playEffect(Explode_2_EffECT);
}

void Music::playExplode3Effect()
{
	SimpleAudioEngine::sharedEngine()->playEffect(Explode_3_EffECT);
}

void Music::playBoss_1_BgMusic()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BOSS_1_BG_MUSIC, true);
}

void Music::playLevel_1_BgMusic()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(LEVEL_1_BG_MUSIC, true);
}

void Music::playMainUIBgMusic()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MAINUI_BG_MUSIC, true);
}

void Music::pauseBackgroundMusic()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void Music::resumeBackgroundMusic()
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void Music::stopBackgroundMusic(bool bReleaseData)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
}

void Music::setEffectVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

void Music::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}