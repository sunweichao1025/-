//
//  Mercenary.h
//  pass
//
//  Created by student on 15/9/7.
//
//

#ifndef __pass__Monster__
#define __pass__Monster__

#include <iostream>
#include "cocos2d.h"
#include "Actionstate.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace std;
using namespace cocostudio;
USING_NS_CC;

class Monster:public cocostudio::Armature
{
public:
    static Monster * createwith(std::string name);
    virtual bool initMonster(std::string name); //初始化精灵


    int currentblood; //当前血量
    int blood;    //血量
    int attck;    //攻击力
    int defence;  //防御
    std::string name;
    
  
    void initbleedstate();
    void FolloWRun(Node *m_hero,Node *map);    //在可视范围内 ，怪物跟随英雄移动
    void JudegeAttack();                        //判断是否攻击
    void MonsterSeeRun();                       //怪物巡逻路线
    void StartListen(Node* m_hero,Node* m_map);//怪物启动监听英雄
    void monsterresumestate();
    void updatemonsterhp();
    
    float   dis;//当前怪物和英雄的距离
    
    void initmonsterfun();        //状态机的回调
    ProgressTimer *boolstate;     //血条
    Actionstate *fsm;             //状态机制
    ProgressTimer *hp;
};



#endif /* defined(__pass__Mercenary__) */
