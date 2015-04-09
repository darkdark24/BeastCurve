#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

//#ifdef __APPLE__
//# define Ref cocos@d::CCObject
//#endif

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    //void update(float dt);
    
    CREATE_FUNC(MainScene);

private:
    void onClickPlay(cocos2d::Ref* pSender);
    void onClickOptions(cocos2d::Ref* pSender);
    void onClickExit(cocos2d::Ref* pSender);
};

#endif // __MAIN_SCENE_H__
