//
//  Mercenary.h
//  ECIT
//
//  Created by student on 15/9/15.
//
//

#ifndef __ECIT__Mercenary__
#define __ECIT__Mercenary__

#include <iostream>
#include "cocos2d.h"
#include "Actionstate.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace std;
using namespace cocostudio;
USING_NS_CC;
typedef enum{
    nvheiqishi=0,
    angren,
    shiwang
} MercenaryName;


class Mercenary:public Armature{
public:
    static Mercenary * crateWith(std::string name);
    virtual bool init(std::string name);
    CC_SYNTHESIZE(std::string, skill1, skill1);
    CC_SYNTHESIZE(std::string, skill2, skill2);
    
    void  initFsm();
    int   blood; //血量
    int   attack; //攻击
    int   defense; //防御
    int   needBlood;
    int   needAttack;
    int   needGlod;
    int   locked;
    int   merpos;
    Sprite* icon;
    std::string merName;
    std::string merinfo2;
    Actionstate *fsm;   //状态机制


};



#endif /* defined(__ECIT__Mercenary__) */
