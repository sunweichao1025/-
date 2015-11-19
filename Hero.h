//
//  Hero.h
//  pass
//
//  Created by student on 15/9/7.
//
//

#ifndef __pass__Hero__
#define __pass__Hero__

#include <iostream>
#include "cocos2d.h"
#include "Actionstate.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace std;
using namespace cocostudio;
USING_NS_CC;

//英雄技能
typedef enum
{   hidle=0,
    hsk0,
    hsk1,
    hsk2,
    hsk3,
}HeroSkill;

//英雄的状态
typedef enum
{
    HERO,
    LENDTH,
}HeroType;


class Hero:public cocostudio::Armature
{
public:
    Hero(HeroType type,std::string _name);                //默认构造函数，初始化一些属性
    void initHero();
    void heroaction();
    void attackaction(std::string actioname);
    
public:
    
    HeroSkill heroSkill;
    HeroType Herotype;

    
    CC_SYNTHESIZE(int, gold,gold);    //当前金币数
    CC_SYNTHESIZE(int, lv, lv);          //需要等级分数
    CC_SYNTHESIZE(int,currentEXP,currentEXP);
    CC_SYNTHESIZE(int,needEXP,needEXP);
    CC_SYNTHESIZE(int,blood,blood);
    CC_SYNTHESIZE(int,ourfighting,ourfighting);
    CC_SYNTHESIZE(int,currentchapter,currentchapter);
    CC_SYNTHESIZE(int,currentpass,currentpass);
    CC_SYNTHESIZE(int,attack,attack);
    CC_SYNTHESIZE(int, defense, defense);
    CC_SYNTHESIZE(string,clothes, clothes);
    CC_SYNTHESIZE(string,weapen, weapen);
    CC_SYNTHESIZE(string,necklace, necklace);
    CC_SYNTHESIZE(string,stone, stone);
    CC_SYNTHESIZE(string,skill1, skill1);
    CC_SYNTHESIZE(string,skill2, skill2);
    CC_SYNTHESIZE(string,skill3, skill3);
    CC_SYNTHESIZE(string,skill4, skill4);
    CC_SYNTHESIZE(string,skillInf, skillInf);
    
    bool isdirecton;     //判断是前进还是后退
    bool predirection;
    bool isaction;       //是否正在执行动画
    int currentblood;    //当前血量

    
    std::string name;
    std::string actionname;

    void resumestate();
    Actionstate * fsm;      //状态机制
    Sprite* p1;
};


#endif /* defined(__pass__Hero__) */
