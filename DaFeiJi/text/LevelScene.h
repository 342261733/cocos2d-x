#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "LevelLayer.h"


class CLevelScene :
	public CCScene
{
public:
	CLevelScene(void);
	~CLevelScene(void);
public:
	static CCScene* scene();
};

#endif
