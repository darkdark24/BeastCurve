#include "MainScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainScene::scene()
{
    CCScene *scene = CCScene::create();
    MainScene *layer = MainScene::create();

    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !CCLayer::init() )
        return false;
    return true;
}

void MainScene::onClickPlay()
{
    
}

void MainScene::onClickOption()
{
    
}

void MainScene::onClickExit()
{
    
}

void MainScene::menuCloseCallback(Ref* pSender)
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