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
    static CCScene *scene = CCScene::create();
    static OptionScene *layer = OptionScene::create();
    static bool first = true;

    if (first)
    {
        scene->addChild(layer);
        first = !first;
    }
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