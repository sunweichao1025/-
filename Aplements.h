//
//  Aplements.h
//  ECIT
//
//  Created by student on 15/9/16.
//
//

#ifndef __ECIT__Aplements__
#define __ECIT__Aplements__

#include <stdio.h>
#include <iostream>
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;
class Aplements:public Node
{
public:
    Aplements(std::string _name,std::string _level,std::string _discription,std::string _reward, std:: string _locked);
    std:: string level;
    std:: string name;
    std:: string discription;
    std:: string reward;
    std:: string locked;

};

#endif /* defined(__ECIT__Aplements__) */
