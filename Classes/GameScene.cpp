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
    static CCScene *scene = CCScene::create();
    static GameScene *layer = GameScene::create();
    static bool first = true;

    if (first)
    {
        scene->addChild(layer);
        first = !first;
    }
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init())
        return false;

    _gl = new GameLogic(CCDirector::sharedDirector()->getWinSize());
    _gl->addPlayer();
    _gl->addPlayer();
    _gl->addPlayer();
    for (auto p : _gl->getPlayers())
    {
        p->isMoving(true);
    }

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    _leftButton = MenuItemImage::create("GameButton.jpg", "GameButtonPressed.jpg");
    _rightButton = MenuItemImage::create("GameButton.jpg", "GameButtonPressed.jpg");

    _leftButton->setPosition(ccp(_leftButton->getContentSize().width / 2, _leftButton->getContentSize().height / 2));
    _rightButton->setPosition(ccp(screenSize.width - _rightButton->getContentSize().width / 2, _rightButton->getContentSize().height / 2));

    CCMenu* gameButtons = CCMenu::create(_leftButton, _rightButton, NULL);
    gameButtons->setPosition(Vec2::ZERO);
    this->addChild(gameButtons, 1);

    this->setTouchEnabled(true);
    this->schedule(schedule_selector(GameScene::update));

    return true;
}

void GameScene::update(float dt)
{
    if (_leftButton->isSelected())
        onClickLeftButton(dt);
    if (_rightButton->isSelected())
        onClickRightButton(dt);
    _gl->update(dt);
}

void GameScene::draw(Renderer *renderer, const kmMat4 &transform, uint32_t flags)
{
    for (auto p : _gl->getPlayers())
    {
        for (auto pos : p->getAllPos())
        {
            DrawPrimitives::setDrawColor4B(p->getColor().r, p->getColor().g, p->getColor().b, p->getColor().a);
            DrawPrimitives::drawSolidCircle(pos, 4, 1, 100);
        }
        DrawPrimitives::setDrawColor4B(p->getColor().r, p->getColor().g, p->getColor().b, p->getColor().a);
        DrawPrimitives::drawSolidCircle(p->getPos(), 4, 1, 100);
    }
}

void GameScene::onClickLeftButton(float dt)
{
    _gl->movePlayerLeft(dt);
}

void GameScene::onClickRightButton(float dt)
{
    _gl->movePlayerRight(dt);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
}