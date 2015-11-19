

//
//  CharpterUIview.h
//  ECIT
//
//  Created by student on 15/8/28.
//
//

#ifndef __ECIT__CharpterUIview__
#define __ECIT__CharpterUIview__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;


class CharpterUIview:public Layer
{
public:
    static Scene*  createwithCharpterUIview();
    virtual bool init();
    CREATE_FUNC(CharpterUIview);
    
    void initUIview();
    void updatepage(Ref*sender);
    
    
    Vector<Node*>scenenode;
    ui::Text* ourpower;      //我方战斗力
    ui::Text* emoptypower;   //地方战斗力
    ui::TextBMFont* level;   //关卡
    ui::Text* dollor;  //金钱
    ui::TextBMFont* sign;    //标记
};

#endif /* defined(__ECIT__CharpterUIview__) */
