//
//  MenuLayer.h
//  PrePreGame
//
//  Created by student on 15/8/29.
//
//

#ifndef __PrePreGame__MenuLayer__
#define __PrePreGame__MenuLayer__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "Mercenary.h"
#include "Aplements.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
USING_NS_CC;
class MenuLayer:public Layer{
public:
     ~MenuLayer();
    static MenuLayer *createScene(int Tag);
    virtual bool init(int Tag);
    void createShop();
    void createHeros();
    void createslider();
    void createquene();
    void createAchievement();
    void createnotebook();
    Sprite*addCell(Aplements *aple,int index);
    void updatemerdata(std::string merName,int _index);
    void Shop(Node *node);
    void onPress(float dt);
    void merInf(Mercenary*mer,Node *csb);
    
    ScrollView* sc;
    Vector<Sprite*>spvec;
    __Array *nodeArray;
    Node *mer;  
    Mercenary *mernary;
    bool isExit;
    int index;
};

#endif /* defined(__PrePreGame__MenuLayer__) */
