#include "MainScene.h"
#include "GameScene.h"
#include "OptionScene.h"
#include "SplashScreenScene.h"
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
    if (!CCLayer::init())
        return false;

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite* background = CCSprite::create("BackgroundMain.jpg");

    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background, -1);

    CCMenuItem* playItem = CCMenuItemImage::create("Play.png", "PlaySelected.png", this, menu_selector(MainScene::onClickPlay));
    CCMenuItem* optionsItem = CCMenuItemImage::create("Option.png", "OptionSelected.png", this, menu_selector(MainScene::onClickOptions));
    CCMenuItem* exitItem = CCMenuItemImage::create("Exit.png", "ExitSelected.png", this, menu_selector(MainScene::onClickExit));

    playItem->setPosition(ccp(screenSize.width / 4, screenSize.height / 3));
    optionsItem->setPosition(ccp(screenSize.width / 4 * 2, screenSize.height / 3));
    exitItem->setPosition(ccp(screenSize.width / 4 * 3, screenSize.height / 3));

    CCMenu* menu = CCMenu::create(playItem, optionsItem, exitItem, NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu, 1);

    this->setTouchEnabled(true);
    //this->schedule(schedule_selector(MainScene::update));

    return true;
}

/*void MainScene::update(float dt)
{

}*/

void MainScene::onClickPlay(Ref* pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void MainScene::onClickOptions(Ref* pSender)
{
    CCDirector::sharedDirector()->replaceScene(OptionScene::scene());
}

void MainScene::onClickExit(Ref* pSender)
{
    CCDirector::sharedDirector()->replaceScene(SplashScreenScene::scene("SplashScreenExit", 5.0, NULL));
}
