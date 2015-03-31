//
//  OptionScene.cpp
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#include "OptionScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* OptionScene::scene()
{
    CCScene *scene = CCScene::create();
    OptionScene *layer = OptionScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool OptionScene::init()
{
    if ( !CCLayer::init() )
        return false;
    return true;
}

void OptionScene::menuCloseCallback(Ref* pSender)
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