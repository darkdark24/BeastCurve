//
//  SplashScreenScene.cpp
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#include "SplashScreenScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* SplashScreenScene::scene(std::string file, float time)
{
    CCScene *scene = CCScene::create();
    SplashScreenScene *layer = SplashScreenScene::create(file, time);
    
    scene->addChild(layer);
    return scene;
}

bool SplashScreenScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* splashSprite = CCSprite::create(_file);
    
    splashSprite->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(splashSprite, -1);
    return true;
}

void SplashScreenScene::onEnter()
{
    CCLayer::onEnter();
    this->scheduleOnce(schedule_selector(SplashScreenScene::finishSplash), _time);
}

void SplashScreenScene::finishSplash(float dt)
{
    CCDirector::sharedDirector()->replaceScene(MainScene::scene());
}

void SplashScreenScene::menuCloseCallback(Ref* pSender)
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

SplashScreenScene*  SplashScreenScene::create(std::string file, float time)
{
    SplashScreenScene*  ret = new SplashScreenScene;

    if (ret)
    {
        ret->_file = file;
        ret->_time = time;
    }
    if (ret && ret->init())
    {
        ret->autorelease();
        return (ret);
    }
    return (NULL);
}
