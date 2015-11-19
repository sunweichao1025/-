//
//  GameScene.h
//  ECIT
//
//  Created by student on 15/9/6.
//
//

#ifndef __ECIT__GameScene__
#define __ECIT__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Hero.h"
#include "battblegamebg.h"
USING_NS_CC;
using namespace ui;


class GameScene:public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    Hero *hero;
    
    PhysicsBody *body2;
    PhysicsBody *body3;
    battbleScene *battlebg;
    

public:
    void initview();
};

#endif /* defined(__ECIT__GameScene__) */
