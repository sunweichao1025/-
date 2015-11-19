//
//  movehandler.h
//  ECIT
//
//  Created by student on 15/9/6.
//
//

#ifndef __ECIT__movehandler__
#define __ECIT__movehandler__

#include <iostream>
#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;
using namespace cocostudio;


enum JoystickEnum
{
    DEFAULT,       //
    D_UP,          //上
    D_DOWN,        //下
    D_LEFT,        //左
    D_RIGHT,       //右
    D_LEFT_UP,     //左上
    D_LEFT_DOWN,   //左下
    D_RIGHT_UP,    //右上
    D_RIGHT_DOWN   //右下
};

class Movehandler : public cocos2d::Layer
{
public:
    static  Movehandler * createlayer(Hero *hero);
    virtual bool init(Hero *hero);
    void initherostate();
    
    void dispathch();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void updatehero(float dt);                   //移动英雄
    void checkdirection(float angle,Point p);    //判断英雄移动的方向
    void updatedetal();
    
    JoystickEnum direction;     //移动的方向
    float currentangle;         //移动的角度
    void   herorun();
    void updatebg();
    
    bool currendir;
    bool predir;
    
    bool ischang;
    int raduis;
    Hero *_hero;    //英雄
    Sprite *circle;  //圆
    Sprite *point;    //动点
    bool isboundth;
    Label *herolevel; //英雄级别
    Label *HPText;   //血条
    Label *ExpText;  //经验条
    Label *glodText; //金币数
    
    MenuItemImage  *skill1;
    MenuItemImage  *skill2;
    MenuItemImage  *skill3;
    MenuItemImage  *skill4;
    
    void SkillState(const char *pic,Point p,int t,Ref *sender);
    void updateSingleDelay(float dt);//单击
    void updateDoubleDelay(float dt);//双击
    void ThreeClicked();//三击
    void resumeclick();
    int ClickedCounts;  //点击的数量
    ProgressTimer *hp;
    ProgressTimer *exp;
};


#endif /* defined(__ECIT__movehandler__) */
