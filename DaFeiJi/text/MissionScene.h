#ifndef MISSIONSCENE_H
#define MISSIONSCENE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "MissionLayer.h"


class CMissionScene :
	public CCScene
{
public:
	CMissionScene(void);
	~CMissionScene(void);
public:
	static CCScene* scene();
};


#endif