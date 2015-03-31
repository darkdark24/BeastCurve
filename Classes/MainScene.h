#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    void onClickPlay();
    void onClickOption();
    void onClickExit();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
