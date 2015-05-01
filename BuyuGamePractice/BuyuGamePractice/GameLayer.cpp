//
//  GameLayer.cpp
//  BuyuGamePractice
//
//  Created by xunianqiang on 14/11/7.
//
//

#include "GameLayer.h"

#include "StartLayer.h"

using namespace cocos2d;
using namespace std;

bool GameLayer::init()
{
    bool ret = CCLayer::init();
    if (ret==false) {
        return false;
    }
    
    setTouchEnabled(true);//缺省的cclayer不能点,需要打开触摸
    
//    CCSprite *bgSprite = CCSprite::create("battle_bg2-hd.png");
    CCSprite *bgSprite = new CCSprite();
    bgSprite->initWithFile("battle_bg2-hd.png");
    bgSprite->setPosition(ccp(0, 0));
    bgSprite->setAnchorPoint(ccp(0, 0));
    this->addChild(bgSprite);
    
//    CCMenuItemImage *backItemImage = CCMenuItemImage::create("btn_close_1-hd.png", "btn_close_2-hd.png",this,menu_selector(GameLayer::backClick));
//    CCDirector *dic = CCDirector::sharedDirector();
//    CCSize size = dic->getWinSize();
//    backItemImage->setPosition(ccp(size.width/2, size.height/2));
//    backItemImage->setAnchorPoint(ccp(0, 0));
//    
//    CCMenu *menu = CCMenu::create(backItemImage,NULL);
//    this->addChild(menu);
    
    CCDirector *dic = CCDirector::sharedDirector();
    CCSize size = dic->getWinSize();
//
//    CCMenuItemImage *otherItm = CCMenuItemImage::create("btn_close_2-hd.png","btn_close_1-hd.png", this, menu_selector(GameLayer::backClick));
////    otherItm->setPosition(80, -228);
//    
//    otherItm->setPosition(400, 250);
////    otherItm->setAnchorPoint(ccp(0, 0));
//    
//    CCMenu *menu = CCMenu::create(otherItm,NULL);
//    this->addChild(menu,1);
 
//    /*
    CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage("btn_close_2-hd.png");
    CCScale9Sprite *backgroundButton = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrame::createWithTexture(texture, CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height)));
    CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("btn_close_1-hd.png", CCRect(0, 0, texture->getContentSize().width,texture->getContentSize().height));
    CCControlButton *m_button = CCControlButton::create(backgroundButton);
    m_button->setZoomOnTouchDown(false); //设置不现实按钮效果
    m_button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    m_button->setPreferredSize(CCSizeMake(80, 80));
    //m_button->setContentSize(CCSizeMake(size.height, size.height));
    m_button->setPosition(ccp(size.width-50,size.height-50));
    m_button->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backClick), CCControlEventTouchUpInside);
    addChild(m_button, 1);
//     */
    
    addStaticFish();
    schedule(schedule_selector(GameLayer::fishTimer),3.0f);//1s添加一个小鱼
    
    
    /*
     如何根据plist文件和png图片添加精灵?
     
     */
    //创建一个炮台
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fishingjoy_resource.plist");
//    
//    //    int frameCount = CCDirector::sharedDirector()-> ("fish_frame_count");
//    //设置文件路径
//    const char* plistPath = "fishingjoy_resource.plist";
//    CCFileUtils* fileutils = CCFileUtils::sharedFileUtils();
//    std::string pfullPath = fileutils->fullPathFromRelativePath(plistPath);
//    const char *cfullPath = pfullPath.c_str();
//    
//    CCDictionary *rootdic = CCDictionary::createWithContentsOfFile(cfullPath);
////    CCLog("%s",rootdic->objectForKey("123"));
//    //
//    CCDictionary *frameDic = (CCDictionary *)rootdic->objectForKey("frames");
//    CCString *bulletStr = (CCString *)frameDic->objectForKey("bullet.png");
//    CCLog("bullet str is %s",bulletStr);
//    CCSpriteFrame *bulletSpriteframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(bulletStr->getCString());
//    CCSprite *bulletSprite = CCSprite::createWithSpriteFrame(bulletSpriteframe);
//    bulletSprite->setPosition(ccp(200, 200));
//    this->addChild(bulletSprite);

    
    return true;
    
}



void GameLayer::backClick(cocos2d::CCObject *sender)
{
    CCLog("后退按钮");
    CCScene *ss = CCScene::create();//问题果然出在这里:create != new init
    StartLayer *start = StartLayer::create();
    ss->addChild(start);
    CCDirector *d = CCDirector::sharedDirector();
    d->replaceScene(ss);   

}


void GameLayer::fishTimer(float dt)
{
    addStaticFish();
}


void GameLayer::addStaticFish()
{
    fish = CCSprite::create("fish1313.png");
    fish->setTag(1);
    CCDirector *dir = CCDirector::sharedDirector();
    CCSize size = dir->getWinSize();
    
    float x=size.width-arc4random()%100;//出现的位置横坐标
    CCLog("random is: %d x is:%f",(arc4random()%100),x);
    float y=arc4random()%((int)size.height);//纵坐标
    
    float scale = arc4random()%50+40;
    fish->setScale(50.0/scale);
    fish->setPosition(ccp(x, y));
    addChild(fish);
    
    
    //乌龟游动
    CCPoint destPosition = CCPoint(size.width/2,y);
    CCMoveTo *move = CCMoveTo::create(2, destPosition);
    
    CCPoint desP2 = CCPoint( 50,y);
    CCJumpTo *jump = CCJumpTo::create(2, desP2, arc4random()%200, 1);
    
    CCPoint destP3 = CCPoint(size.width,y);
    CCMoveTo *move3 = CCMoveTo::create(2, destP3);
    
//    CCPoint desP4 = CCPoint( 50,y);
//    CCJumpTo *jump2 = CCJumpTo::create(2, desP4, arc4random()%200, 1);
    
    //这个动作是一个函数调用动作 是一个假动作
    CCCallFuncN *turnHead = CCCallFuncN::create(this, callfuncN_selector(GameLayer::trunHead));
    CCCallFuncN *removeAction = CCCallFuncN::create(this, callfuncN_selector(GameLayer::removeFish));
    
    CCFiniteTimeAction *allAction = CCSequence::create(move,jump,turnHead,move3,removeAction,NULL);
    fish->runAction(allAction);
    
}

void GameLayer::removeFish(cocos2d::CCObject *sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    sprite->removeFromParentAndCleanup(true);
}

void GameLayer::trunHead(cocos2d::CCObject *sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    sprite->setRotation(180);
}

//#define STATIC_DATA_INT(key) StaticData::sharedStaticData()->intFromKey(key)

void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCLog("touches --------------------");
    
    CCTouch *oneTouch = (CCTouch *)pTouches->anyObject();
    //获取当前触摸
    CCPoint touchPoint = oneTouch->getLocation();
    
    CCDirector *dc = CCDirector::sharedDirector();
    CCSize size = dc->getWinSize();
    CCLog("x is %f,y is %f",touchPoint.x,touchPoint.y);
    
    CCPoint beginPoint = CCPoint(size.width/2,0);//发射位置在中间
//    CCPoint beginPoint = CCPoint(touchPoint.x,0);//发射位置不在中间
    bullet = CCSprite::create("bullet010_2.png");
    bullet->setPosition(beginPoint);
  

    if (touchPoint.x<size.width/2) {
        bullet->setRotation(-45);
    }
    else{
        bullet->setRotation(45);
    }
    addChild(bullet);
    
    CCMoveTo *move = CCMoveTo::create(1.0f, touchPoint);
    
    CCCallFuncN *removeAction = CCCallFuncN::create(this, callfuncN_selector(GameLayer::removeFish));
    CCFiniteTimeAction *allAction = CCSequence::create(move,removeAction);
    bullet->runAction(allAction);
    


    //起一个计时器
//    schedule(schedule_selector(GameLayer::checkHit),1.0f);//1s添加一个小鱼
    checkHit(0.0f);
    
    
}


void GameLayer::checkHit(float dt)
{
    //起个计时器吧
    CCPoint fishPosition = fish->getPosition();
    CCLog("fish position is %f,y is %f",fishPosition.x,fishPosition.y);
    //获取当前子弹的位置
    CCPoint bulletPosition = bullet->getPosition();
    CCLog("bullet position is %f,y is %f",bulletPosition.x,bulletPosition.y);
    
    if (((fishPosition.x < bulletPosition.x+10) )&& ((fishPosition.y < bulletPosition.y+10 ))) {
        CCLog("******************-------------------------------------碰撞了");
    }
}

//void GameLayer::onEnter()
//{
//    
//}
//
//
//void GameLayer::onEnterTransitionDidFinish()
//{
//    
//}
//
//
//void GameLayer::onExit()
//{
//    
//}
//




