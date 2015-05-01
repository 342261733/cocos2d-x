#include "SelectScene.h"

/*
CSelectScene::CSelectScene(void)
{
}

CSelectScene::~CSelectScene(void)
{
}
*/
CCScene* CSelectScene::scene()
{
	CCScene* scene = CCScene::create();
	CSelectLayer* layer = CSelectLayer::create();
	scene->addChild(layer);
	return scene;
}
