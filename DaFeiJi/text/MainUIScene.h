#ifndef MAINUISCENE_H
#define MAINUISCENE_H
#include "cocos2d.h"

#include "GlobalData.h"
#include "MainUILayer.h"

using namespace cocos2d;

class CMainUIScene :public CCScene
{
public:
	CMainUIScene(void);
	~CMainUIScene(void);
public:
	static CCScene* scene();
};


#endif