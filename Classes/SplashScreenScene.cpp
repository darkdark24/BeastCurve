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

CCScene* SplashScreenScene::scene(std::string file, float time, func f)
{
    CCScene *scene = CCScene::create();
    SplashScreenScene *layer = SplashScreenScene::create(file, time, f);

    scene->addChild(layer);
    return scene;
}

bool SplashScreenScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* splashSprite = CCSprite::create(_file.c_str());

    splashSprite->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    splashSprite->setScale(screenSize.width / splashSprite->getContentSize().width, screenSize.height / splashSprite->getContentSize().height);
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
    if (_f == NULL)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#else
        CCDirector::getInstance()->end();
#endif
    }
    CCDirector::sharedDirector()->replaceScene(_f());
}

SplashScreenScene*  SplashScreenScene::create(std::string file, float time, func f)
{
    SplashScreenScene*  ret = new SplashScreenScene;

    if (ret)
    {
        ret->_file = file;
        ret->_time = time;
        ret->_f = f;
    }
    if (ret && ret->init())
    {
        ret->autorelease();
        return (ret);
    }
    return (NULL);
}

