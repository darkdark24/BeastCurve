//
//  GameScene.h
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#ifndef Beast_Curve_GameScene_h
#define Beast_Curve_GameScene_h

#include "cocos2d.h"
#include "GameLogic.h"
#include	"IA.h"
#include <vector>

/*#ifdef __APPLE__
# define Ref CCObject
#endif*/

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void update(float dt);
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::kmMat4 &transform, uint32_t flags);

    void startGame(float dt);
    void endGame(float dt);

    void onDead();
    
    void onClickLeftButton(float dt);
    void onClickRightButton(float dt);
    void onClickReplayButton();
    void onClickQuitButton();
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);

    static const uint16_t HeightHUD = 150;
    static const uint16_t ScoreMax = 10;

private:
    cocos2d::DrawNode* _drawer;
    bool _started;
    cocos2d::CCMenuItem* _leftButton;
    cocos2d::CCMenuItem* _rightButton;
    cocos2d::CCMenuItem* _replay;
    cocos2d::CCMenuItem* _quit;
    std::vector<cocos2d::CCLabelTTF*> _playerLabel;
    std::vector<cocos2d::CCLabelTTF*> _scores;
    cocos2d::CCLabelTTF* _winnerLabel;
    GameLogic *_gl;

	std::vector<IA*>	_listIA;
};

#endif
