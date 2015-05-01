#include "StartScene.h"
#include "Music.h"
#include "MainUIScene.h"

CCScene* StartScene::scene()
{
    CCScene *scene = CCScene::create();

    StartScene *layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance
bool StartScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize win_size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* startSprite = CCSprite::create("MainBG.jpg");
	startSprite->setScaleX(win_size.width / startSprite->getContentSize().width);
	startSprite->setScaleY(win_size.height / startSprite->getContentSize().height);
	startSprite->setPosition(CCPoint(win_size.width / 2, win_size.height / 2));
	addChild(startSprite);

	//waitRing();
	LoadResource();
	
	CCSequence* seq = CCSequence::create(CCDelayTime::create(6.0f),
										 CCCallFunc::create(this,callfunc_selector(StartScene::actionFinished)),
										 NULL);

	runAction(seq);

    return true;
}

void StartScene::onEnter()
{
	CCLayer::onEnter();
}


void StartScene::waitRing()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize win_size = pDirector->getWinSize();
	CCSprite* s_wait = CCSprite::create("waterfall_rings.png");
	s_wait->setAnchorPoint(ccp(0.5f,0.5f));
	s_wait->setPosition(ccp(win_size.width / 2,win_size.height / 2));
	s_wait->setScale(0.5f);
	CCActionInterval *rot = CCRotateBy::create(2, 360*2);
	s_wait->runAction(CCRepeatForever::create(rot));
	addChild(s_wait);
}

bool StartScene::LoadResource()
{
	CCTextureCache::sharedTextureCache()->addImageAsync("army/Army.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("bullet/Bullet.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("cloud/Cloud.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("effect/Effect.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("enemy/NPC_Plane.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("item/Item.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("level/Level01.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("level/Level02.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("level/Level03.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("level/Level04.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("player/Player.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("UI/UI.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("UI/UI_2.png", this, callfuncO_selector(StartScene::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("UI/UI_3.png", this, callfuncO_selector(StartScene::loadingCallBack));

	//加载声音文件
	Music::preloadResouse();

	return true;
}

void StartScene::actionFinished()
{
	CCTexture2D* Army = CCTextureCache::sharedTextureCache()->textureForKey("army/Army.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("army/Army.plist", Army);

	CCTexture2D* Bullet = CCTextureCache::sharedTextureCache()->textureForKey("bullet/Bullet.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet/Bullet.plist", Bullet);

	CCTexture2D* Cloud = CCTextureCache::sharedTextureCache()->textureForKey("cloud/Cloud.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cloud/Cloud.plist", Cloud);

	CCTexture2D* Effect = CCTextureCache::sharedTextureCache()->textureForKey("effect/Effect.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect/Effect.plist", Effect);

	CCTexture2D* NPC_Plane = CCTextureCache::sharedTextureCache()->textureForKey("enemy/NPC_Plane.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("enemy/NPC_Plane.plist", NPC_Plane);

	CCTexture2D* Item = CCTextureCache::sharedTextureCache()->textureForKey("item/Item.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("item/Item.plist", Item);

	CCTexture2D* Level01 = CCTextureCache::sharedTextureCache()->textureForKey("level/Level01.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("level/Level01.plist", Level01);

	CCTexture2D* Level02 = CCTextureCache::sharedTextureCache()->textureForKey("level/Level02.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("level/Level02.plist", Level02);

	CCTexture2D* Level03 = CCTextureCache::sharedTextureCache()->textureForKey("level/Level03.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("level/Level03.plist", Level03);

	CCTexture2D* Player = CCTextureCache::sharedTextureCache()->textureForKey("player/Player.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("player/Player.plist", Player);

	CCTexture2D* UI = CCTextureCache::sharedTextureCache()->textureForKey("UI/UI.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UI.plist", UI);

	CCTexture2D* UI_2 = CCTextureCache::sharedTextureCache()->textureForKey("UI/UI_2.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UI_2.plist", UI_2);

	CCTexture2D* UI_3 = CCTextureCache::sharedTextureCache()->textureForKey("UI/UI_3.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UI_3.plist", UI_3);

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, CMainUIScene::scene()));
}

void StartScene::loadingCallBack(CCObject* obj) 
{

}


bool StartScene::initUserData()
{
	return true;
}

