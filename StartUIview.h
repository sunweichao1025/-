//
//  StartUIview.h
//  ECIT
//
//  Created by student on 15/8/27.
//
//

#ifndef __ECIT__StartUIview__
#define __ECIT__StartUIview__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
static bool flag = true;

class StartUIview:public Layer
{
public:
    static Scene * createwithstartUI();
    virtual bool init();
    CREATE_FUNC(StartUIview);
    
};

#endif /* defined(__ECIT__StartUIview__) */
