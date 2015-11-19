//
//  Mercenary.cpp
//  ECIT
//
//  Created by student on 15/9/15.
//
//

#include "Mercenary.h"
Mercenary * Mercenary::crateWith(std::string name){
    Mercenary *armature = new (std::nothrow) Mercenary();
    armature->init(name);
    
    return armature;

}
bool Mercenary:: init(std::string name){
    this->initFsm();
    char name1[60];
    char name2[60];
    char name3[60];
    sprintf(name1,"%s.ExportJson",name.c_str());
    sprintf(name2, "%s0.plist",name.c_str());
    sprintf(name3, "%s0.pvr.ccz",name.c_str());
    ArmatureDataManager::getInstance()->addArmatureFileInfo(name3, name2, name1);
    if(!Armature::init(name))
    {
        return false;
    }
    return true;
}

void Mercenary:: initFsm(){
    fsm=Actionstate::create("idle",[this](){
        this->getAnimation()->playWithIndex(0,1,true);
    });
     fsm->retain();
    fsm->setOnEnter("running", [this](){
        this->getAnimation()->playWithIndex(1,1,true);
    });
    fsm->setOnEnter("attacking1", [this](){
        this->getAnimation()->playWithIndex(2,1,true);
    });
      fsm->setOnEnter("dead", [this](){
        this->getAnimation()->playWithIndex(4,1,true);
    });
}



