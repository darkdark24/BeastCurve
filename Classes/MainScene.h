#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    //void update(float dt);
    
    CREATE_FUNC(MainScene);

private:
    void onClickPlay(Ref* pSender);
    void onClickOptions(Ref* pSender);
    void onClickExit(Ref* pSender);
};

#endif // __MAIN_SCENE_H__
