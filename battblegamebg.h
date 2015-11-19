//
//  battblegamebg.h
//  ECIT
//
//  Created by student on 15/9/10.
//
//

#ifndef __ECIT__battblegamebg__
#define __ECIT__battblegamebg__

#include <iostream>
#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
USING_NS_CC;

class battbleScene:public Node
{
public:
    static battbleScene* createscene(const std::string bgname);
    virtual bool init(const std::string bgname);
   

    void initmonster();
    void updateboundthrect(float dt);
    void updatemonstermove(float dt);
    void updateheroattack(float dt);
    void attackrect(int attackdistance);
    
    void movemonster(Monster* monster);
    void pausheroaction(float dt);
    
    
    Vector<Monster*>monsterArr;   //怪物容器
    
     float angle;  //攻击的角度范围
     Sprite *bg;  //地图map
     Hero *hero;  //英雄
 
};

#endif /* defined(__ECIT__battblegamebg__) */
