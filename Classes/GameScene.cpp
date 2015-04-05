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

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    _drawer = DrawNode::create();
    this->addChild(_drawer, 1);

    _started = false;

    _gl = new GameLogic(CCSize(screenSize.width, screenSize.height));
    _gl->addPlayer();
    _gl->addPlayer();

    /*CCSprite* background = CCSprite::create("BackgroundGame.jpg");

    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background, -1);*/

    _leftButton = MenuItemImage::create("GameButton.jpg", "GameButtonPressed.jpg");
    _rightButton = MenuItemImage::create("GameButton.jpg", "GameButtonPressed.jpg");

    _leftButton->setPosition(ccp(_leftButton->getContentSize().width / 2, _leftButton->getContentSize().height / 2));
    _rightButton->setPosition(ccp(screenSize.width - _rightButton->getContentSize().width / 2, _rightButton->getContentSize().height / 2));

    CCMenu* gameButtons = CCMenu::create(_leftButton, _rightButton, NULL);
    gameButtons->setPosition(Vec2::ZERO);
    this->addChild(gameButtons, 1);

    this->setTouchEnabled(true);
    this->schedule(schedule_selector(GameScene::update));

    this->scheduleOnce(schedule_selector(GameScene::startGame), 3.0);

    return true;
}

void GameScene::update(float dt)
{
    time_t start, end;
    time(&start);

    if (!_started)
        return;

    if (_leftButton->isSelected())
        onClickLeftButton(dt);
    if (_rightButton->isSelected())
        onClickRightButton(dt);

    _gl->update(dt);

    if (_gl->hasGameEnd())
    {
        _started = false;
        this->scheduleOnce(schedule_selector(GameScene::endGame), 3.0);
    }

    time(&end);
    double dif = difftime(end, start);
    CCLOG("Update %.5lf seconds.", dif);
}

void GameScene::draw(Renderer *renderer, const kmMat4 &transform, uint32_t flags)
{
    time_t start, end;
    time(&start);

    for (auto p : _gl->getPlayers())
    {
        //ccColor4F c(p->getColor().r, p->getColor().g, p->getColor().b, p->getColor().a);
        ccColor4F c(0.2, 0.2, 0.8, 1);
        /*for (auto pos : p->getAllPos())
        {
            //_drawer->setDrawColor4B(p->getColor().r, p->getColor().g, p->getColor().b, p->getColor().a);
            //_drawer->drawSolidCircle(ccp(pos.x, pos.y), pos.size, 1, 100, c);
        }*/
        _drawer->drawSolidCircle(ccp(p->getPos().x, p->getPos().y), p->getPos().size, 1, 100, c);
//        DrawPrimitives::setDrawColor4B(p->getColor().r, p->getColor().g, p->getColor().b, p->getColor().a);
//        DrawPrimitives::drawSolidCircle(ccp(p->getPos().x, p->getPos().y), p->getPos().size, 1, 100);
    }

    time(&end);
    double dif = difftime(end, start);
    CCLOG("Draw %.5lf seconds.", dif);
}

void GameScene::startGame(float)
{
    for (auto p : _gl->getPlayers())
        p->isMoving(true);
    _started = true;
}

void GameScene::endGame(float)
{
    _gl->nextGame();
    this->scheduleOnce(schedule_selector(GameScene::startGame), 3.0);
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