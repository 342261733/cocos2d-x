#include "MissionScene.h"

CMissionScene::CMissionScene(void)
{
}

CMissionScene::~CMissionScene(void)
{
}

CCScene* CMissionScene::scene()  
{  
	CCScene* scene = CCScene::create();  
	CMissionLayer* layer = CMissionLayer::create();  
	scene->addChild(layer);  
	return scene;  
}