//
//  ScrollViewImage.h
//  PrePreGame
//
//  Created by student on 15/9/7.
//
//

#ifndef __PrePreGame__ScrollViewImage__
#define __PrePreGame__ScrollViewImage__

#include <stdio.h>
#include <iostream>
#include "PrepareGame.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;
class ScrollViewImage:public Scene{
public:
    static Scene *CrateLayer();
    virtual bool init();
    void replaceScene();
    PrepareGame *prepare;
    CREATE_FUNC(ScrollViewImage);
    


};


#endif /* defined(__PrePreGame__ScrollViewImage__) */
