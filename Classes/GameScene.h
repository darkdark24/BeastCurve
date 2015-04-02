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

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void update(float dt);
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::kmMat4 &transform, uint32_t flags);

    void onClickLeftButton(float dt);
    void onClickRightButton(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);

private:
    cocos2d::CCMenuItem* _leftButton;
    cocos2d::CCMenuItem* _rightButton;
    GameLogic *_gl;
};

#endif
