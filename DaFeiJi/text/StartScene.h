/*
 * StartSceneLayer.h
 *
 *  Created on: 2013-10-7
 *      Author: Administrator
 */

#ifndef StartScene_H_
#define StartScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class StartScene: public CCLayer 
{
private:
	CCSprite *startSprite;

public:

	bool init();
	void onEnter();

	static CCScene* scene();

	void waitRing();
	bool LoadResource();
	bool initUserData();
	void actionFinished();
	void loadingCallBack(CCObject* obj);

	CREATE_FUNC(StartScene);
};

#endif /* StartSceneLAYER_H_ */
