#include "LevelScene.h"

CLevelScene::CLevelScene(void)
{
}

CLevelScene::~CLevelScene(void)
{
}

CCScene* CLevelScene::scene()  
{  
	CCScene* scene = CCScene::create();  
	CLevelLayer* layer = CLevelLayer::create();  
	scene->addChild(layer);  
	return scene;  
}