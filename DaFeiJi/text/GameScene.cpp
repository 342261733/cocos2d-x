#include "GameScene.h"

CGameScene::CGameScene(void)
{
}

CGameScene::~CGameScene(void)
{
}

CCScene* CGameScene::scene()  
{  
	CCScene* scene = CCScene::create();  
	CGameLayer* layer = CGameLayer::create();  
	scene->addChild(layer);  
	return scene;  
}