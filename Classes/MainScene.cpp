#include "MainScene.h"
#include "GameScene.h"
#include "OptionScene.h"
#include "SplashScreenScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainScene::scene()
{
    static CCScene *scene = CCScene::create();
    static MainScene *layer = MainScene::create();
    static bool first = true;

    if (first)
    {
        scene->addChild(layer);
        first = !first;
    }
    return scene;
}

bool MainScene::init()
{
    if (!CCLayer::init())
        return false;

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItem* playItem = MenuItemImage::create("Play.png", "PlaySelected.png", CC_CALLBACK_1(MainScene::onClickPlay, this));
    CCMenuItem* optionsItem = MenuItemImage::create("Options.png", "OptionsSelected.png", CC_CALLBACK_1(MainScene::onClickPlay, this));
    CCMenuItem* exitItem = MenuItemImage::create("Exit.png", "ExitSelected.png", CC_CALLBACK_1(MainScene::onClickPlay, this));

    playItem->setPosition(ccp(screenSize.width / 4, screenSize.height / 3));
    optionsItem->setPosition(ccp(screenSize.width / 4 * 2, screenSize.height / 3));
    exitItem->setPosition(ccp(screenSize.width / 4 * 3, screenSize.height / 3));

    CCMenu* menu = CCMenu::create(playItem, optionsItem, exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
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
