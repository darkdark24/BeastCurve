//
//  GameScene.cpp
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#include "GameScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init())
        return false;

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    _gl = new GameLogic(CCSize(screenSize.width, screenSize.height - HeightHUD));
    _gl->setOnDeadCallback(this);
    _gl->addPlayer();
    _gl->addPlayer();

	_listIA.push_back(new IA(_gl->addPlayer()));
	_listIA.push_back(new IA(_gl->addPlayer()));

    _drawer = DrawNode::create();
    _drawer->drawRect(ccp(1, HeightHUD), ccp(screenSize.width - 1, screenSize.height - 1), Color4F::GRAY);
    this->addChild(_drawer, 1);

    for (auto p : _gl->getPlayers())
    {
        std::string s("Player");
        s += std::to_string(p->getId());
        _playerLabel.push_back(CCLabelTTF::create(s, "Arial", 18));
        _playerLabel.back()->setPosition(ccp(p->getPos().x, p->getPos().y + 180));
        this->addChild(_playerLabel.back());
    }

    std::string s("Scores | First to ");
    s += std::to_string(ScoreMax);
    CCLabelTTF* _labelScore = CCLabelTTF::create(s, "Arial", 32);
    _labelScore->setPosition(ccp(screenSize.width / 2, HeightHUD / 4 * 3));
    this->addChild(_labelScore);
    
    _scores.push_back(CCLabelTTF::create("Player 1: 0", "Arial", 24));
    _scores.back()->setPosition(ccp(screenSize.width / 10 * 4, HeightHUD / 4 * 2));
    if (_gl->getPlayers().size() < 1)
        _scores.back()->setVisible(false);
    this->addChild(_scores.back(), 1);
    
    _scores.push_back(CCLabelTTF::create("Player 2: 0", "Arial", 24));
    _scores.back()->setPosition(ccp(screenSize.width / 10 * 6, HeightHUD / 4 * 2));
    if (_gl->getPlayers().size() < 2)
        _scores.back()->setVisible(false);
    this->addChild(_scores.back(), 1);
    
    _scores.push_back(CCLabelTTF::create("Player 3: 0", "Arial", 24));
    _scores.back()->setPosition(ccp(screenSize.width / 10 * 4, HeightHUD / 4));
    if (_gl->getPlayers().size() < 3)
        _scores.back()->setVisible(false);
    this->addChild(_scores.back(), 1);

    _scores.push_back(CCLabelTTF::create("Player 4: 0", "Arial", 24));
    _scores.back()->setPosition(ccp(screenSize.width / 10 * 6, HeightHUD / 4));
    if (_gl->getPlayers().size() < 4)
        _scores.back()->setVisible(false);
    this->addChild(_scores.back(), 1);

    _winnerLabel = CCLabelTTF::create("", "Arial", 48);
    _winnerLabel->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    _winnerLabel->setVisible(true);
    this->addChild(_winnerLabel, 1);

    _started = false;

    /*CCSprite* background = CCSprite::create("BackgroundGame.jpg");

    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background, -1);*/

    _leftButton = CCMenuItemImage::create("GameButtonLeft.png", "GameButtonLeftPressed.png");
    _rightButton = CCMenuItemImage::create("GameButtonRight.png", "GameButtonRightPressed.png");
    _replay = CCMenuItemImage::create("GameButtonLeft.png", "GameButtonLeftPressed.png", CC_CALLBACK_0(GameScene::onClickReplayButton, this));
    _quit = CCMenuItemImage::create("GameButtonRight.png", "GameButtonRightPressed.png", CC_CALLBACK_0(GameScene::onClickQuitButton, this));

    _leftButton->setScale(HeightHUD / _leftButton->getContentSize().width, HeightHUD / _leftButton->getContentSize().height);
    _leftButton->setPosition(ccp(HeightHUD / 2, HeightHUD / 2));
    _rightButton->setScale(HeightHUD / _rightButton->getContentSize().width, HeightHUD / _rightButton->getContentSize().height);
    _rightButton->setPosition(ccp(screenSize.width - HeightHUD / 2, HeightHUD / 2));
    _replay->setScale(HeightHUD / 2 / _rightButton->getContentSize().width, HeightHUD / 2 / _rightButton->getContentSize().height);
    _replay->setPosition(ccp(HeightHUD + HeightHUD / 2, HeightHUD / 2));
    _quit->setScale(HeightHUD / 2 / _rightButton->getContentSize().width, HeightHUD / 2 / _rightButton->getContentSize().height);
    _quit->setPosition(ccp(screenSize.width - HeightHUD - HeightHUD / 2, HeightHUD / 2));

    CCMenu* gameButtons = CCMenu::create(_leftButton, _rightButton, _replay, _quit, nullptr);
    gameButtons->setPosition(ccp(0, 0));
    this->addChild(gameButtons, 1);

    this->setTouchEnabled(true);
    this->schedule(schedule_selector(GameScene::update));

    this->scheduleOnce(schedule_selector(GameScene::startGame), 3.0);

    return true;
}

void GameScene::update(float dt)
{
    if (!_started)
        return;

    if (_leftButton->isSelected())
        onClickLeftButton(dt);
    if (_rightButton->isSelected())
        onClickRightButton(dt);

    /*if (_replay->isSelected())
        onClickReplayButton(dt);
    if (_quit->isSelected())
        onClickQuitButton(dt);*/

    _gl->update(dt);

	for (std::vector<IA*>::iterator it = _listIA.begin(); it != _listIA.end(); ++it) {
		(*it)->update();
		if ((*it)->_dir == Direction::LEFT)
			_gl->movePlayerLeft(dt, (*it)->_player->getId());
		else
			_gl->movePlayerRight(dt, (*it)->_player->getId());
	}

    if (_gl->hasGameEnd())
    {
        _started = false;
        std::string s("Player ");
        s += std::to_string(_gl->getWinner()->getId());
        s += " won";
        _winnerLabel->setString(s);
        _winnerLabel->setVisible(true);
        this->scheduleOnce(schedule_selector(GameScene::endGame), 5.0);
    }
}

void GameScene::draw(Renderer *renderer, const kmMat4 &transform, uint32_t flags)
{
    for (auto p : _gl->getPlayers())
    {
        //ccColor4F c(p->getColor().r, p->getColor().g, p->getColor().b, p->getColor().a);
        //ccColor4F c(0.2, 0.2, 0.8, 1);
        DrawPrimitives::setDrawColor4B(p->getColor().r, p->getColor().g, p->getColor().b, p->getColor().a);
        for (auto pos : p->getAllPos())
        {
            //_drawer->drawSolidCircle(ccp(pos.x, pos.y), pos.size, 1, 100, c);
            DrawPrimitives::drawSolidCircle(ccp(pos.x, pos.y + HeightHUD), pos.size, 1, 100);
        }
        //_drawer->drawSolidCircle(ccp(p->getPos().x, p->getPos().y), p->getPos().size, 1, 100, c);
        DrawPrimitives::drawSolidCircle(ccp(p->getPos().x, p->getPos().y + HeightHUD), p->getPos().size, 1, 100);
    }

	for (auto b : _gl->getBonus())
	{
		if (!b->isActive())
		{
			DrawPrimitives::setDrawColor4B(b->getColor().r, b->getColor().g, b->getColor().b, b->getColor().a);
			DrawPrimitives::drawSolidCircle(ccp(b->getPosition().x, b->getPosition().y + HeightHUD), b->getPosition().size, 1, 100);	
		}
	}
}

void GameScene::startGame(float)
{
    for (auto lbl : _playerLabel)
        lbl->setVisible(false);
    for (auto p : _gl->getPlayers())
        p->isMoving(true);
    _started = true;
}

void GameScene::endGame(float)
{
    _started = false;
    _gl->nextGame();
    _winnerLabel->setVisible(false);
    for (auto p : _gl->getPlayers())
    {
        _playerLabel[p->getId() - 1]->setPosition(ccp(p->getPos().x, p->getPos().y + 180));
        _playerLabel[p->getId() - 1]->setVisible(true);
    }
    if (_gl->finalWinner())
    {
        std::string s("Player ");
        s += std::to_string(_gl->finalWinner()->getId());
        s += " has won !";
        _winnerLabel->setScale(1.5, 1.5);
        _winnerLabel->setString(s);
        _winnerLabel->setVisible(true);

    }
    else
        this->scheduleOnce(schedule_selector(GameScene::startGame), 3.0);
}

void GameScene::onDead()
{
    for (auto p : _gl->getPlayers())
    {
        std::string s("Player ");
        s += std::to_string(p->getId());
        s += ": ";
        s += std::to_string(p->getScore());
        _scores[p->getId() - 1]->setString(s);
    }
}

void GameScene::onClickLeftButton(float dt)
{
    _gl->movePlayerLeft(dt, _gl->getPlayers().front()->getId());
}

void GameScene::onClickRightButton(float dt)
{
	_gl->movePlayerRight(dt, _gl->getPlayers().front()->getId());
}

void GameScene::onClickReplayButton()
{
    _gl->reset();
    endGame(0);
}

void GameScene::onClickQuitButton()
{
    CCDirector::sharedDirector()->replaceScene(MainScene::scene());
}

void GameScene::menuCloseCallback(Ref* pSender)
{
}