//
//  SplashScreenScene.h
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#ifndef Beast_Curve_SplashScreenScene_h
#define Beast_Curve_SplashScreenScene_h

#include "cocos2d.h"

class SplashScreenScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene(std::string file, float time);
    
    void onEnter();
    void finishSplash(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);

private:
    std::string _file;
    float       _time;

    static SplashScreenScene*  create(std::string file, float time);
   // CREATE_FUNC(SplashScreenScene);
};


#endif
