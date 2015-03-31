//
//  GameScene.cpp
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !CCLayer::init() )
        return false;
    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}