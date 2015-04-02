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
    typedef cocos2d::CCScene* (*func)();

    virtual bool init();
    
    static cocos2d::CCScene* scene(std::string file, float time, func f);
    
    void onEnter();
    void finishSplash(float dt);

private:
    std::string _file;
    float       _time;
    func        _f;

    static SplashScreenScene*  create(std::string file, float time, func f);
   // CREATE_FUNC(SplashScreenScene);
};


#endif
