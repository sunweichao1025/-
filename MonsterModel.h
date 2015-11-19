//
//  MonsterModel.h
//  ECIT
//
//  Created by student on 15/9/20.
//
//

#ifndef __ECIT__MonsterModel__
#define __ECIT__MonsterModel__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class MonsterModel{
public:
    MonsterModel(int _MonsterNum,int _scene,int _chapter,bool _locked,std::string _boss);
    std::string mtype[5];
    std::string map;
    CC_SYNTHESIZE(std::string, boss, boss);
    CC_SYNTHESIZE(bool, locked, locked);
    CC_SYNTHESIZE(int, scene, scene);
    CC_SYNTHESIZE(int, capictual, capictual);
    CC_SYNTHESIZE(int, MonsterNum, MonsterNum);
    CC_SYNTHESIZE(int, chapter, chapter);
};

#endif /* defined(__ECIT__MonsterModel__) */
