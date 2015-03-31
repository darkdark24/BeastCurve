//
//  OptionScene.h
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#ifndef Beast_Curve_OptionScene_h
#define Beast_Curve_OptionScene_h

#include "cocos2d.h"

class OptionScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(OptionScene);
};

#endif
