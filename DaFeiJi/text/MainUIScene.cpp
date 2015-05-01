#include "MainUIScene.h"

CMainUIScene::CMainUIScene(void)
{
}

CMainUIScene::~CMainUIScene(void)
{
}

CCScene* CMainUIScene::scene()  
{  
	CCScene* scene = CCScene::create();
	CMainUILayer* layer = CMainUILayer::create();

	Music::preloadResouse();

	scene->addChild(layer);
	layer->setTag(MAIN_UI);
	return scene;  
}