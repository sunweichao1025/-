//
//  PrepareGame.h
//  GD
//
//  Created by student on 15/8/28.
//
//

#ifndef __GD__PrepareGame__
#define __GD__PrepareGame__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocos2d::ui;

class PrepareGame:public Layer{
public:
    static Scene *createScene();
    virtual bool init();
    
    void antionMove(Button *btn);
    CREATE_FUNC(PrepareGame);
    
};

#endif /* defined(__GD__PrepareGame__) */
