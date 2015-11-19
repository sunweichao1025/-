//
//  Interfactionlayer.h
//  ECIT
//
//  Created by student on 15/8/27.
//
//

#ifndef __ECIT__Interfactionlayer__
#define __ECIT__Interfactionlayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class Interfactionlayer:public LayerColor
{
public:
    static Interfactionlayer * create(int tag);
    virtual bool init(int tag);
  
    void initstartUIview();
    void initwithshop(const std::string &name);
    void initwithsetting();
    void gameover();
    void gamevetor();
};

#endif /* defined(__ECIT__Interfactionlayer__) */
