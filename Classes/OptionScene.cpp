//
//  OptionScene.cpp
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#include "OptionScene.h"
#include "MainScene.h"
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
    CCDirector::sharedDirector()->replaceScene(MainScene::scene());
}