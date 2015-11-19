//
//  Mercenary.cpp
//  pass
//
//  Created by student on 15/9/7.
//
//

#include "Monster.h"
#include "Actionstate.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;

Monster * Monster::createwith(std::string name)
{
    Monster *pRet = new(std::nothrow) Monster();
    if (pRet && pRet->initMonster(name))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool Monster::initMonster(std::string name)
{
    char name1[50];
    char name2[50];
    char name3[50];
    sprintf(name1,"%s.ExportJson",name.c_str());
    sprintf(name2, "%s0.plist",name.c_str());
    sprintf(name3, "%s0.pvr.ccz",name.c_str());
    ArmatureDataManager::getInstance()->addArmatureFileInfo(name3, name2, name1);
    
    if(!Armature::init(name))
    {
        return false;
    }
    this->initmonsterfun();
    this->initbleedstate();
    
    auto body=PhysicsBody::createCircle(this->getContentSize().width/8);
    body->setGravityEnable(false);
    body->setGroup(-1);
    this->setPhysicsBody(body);
    
    return true;
}

//转态击执行的动作

void Monster::initmonsterfun()
{
    
    fsm=Actionstate::create("idle",[this](){
        std::vector<std::string>vec(1,"stand");
        this->getAnimation()->playWithNames(vec,1,true);
    });
    fsm->retain();
    
    fsm->setOnEnter("running", [this](){
        this->getAnimation()->play("run");
    });
    
    fsm->setOnEnter("attacking1", [this](){
        this->getAnimation()->play("attack01",1,false);
    this->monsterresumestate();
    });
    
    fsm->setOnEnter("beingHit", [this](){
        this->getAnimation()->play("hurt",1,false);
        this->monsterresumestate();
    });
    
    fsm->setOnEnter("dead", [this](){
        
        this->getAnimation()->play("dead",1,false);
    });
 
}

//血量状态
void Monster::initbleedstate()
{
     //血条
    auto rect=this->getBoundingBox();
    auto size=this->getContentSize();
    auto bleedbg=Sprite::create("battle_bar_direnhp_1.png");
    bleedbg->setPosition(Vec2(0,rect.size.height));
    this->addChild(bleedbg);
    
    auto hp=Sprite::create("battle_bar_direnhp.png");
    boolstate=ProgressTimer::create(hp);
    boolstate->setPosition(Vec2(0,rect.size.height));
    boolstate->setType(cocos2d::ProgressTimer::Type::BAR);
    boolstate->setMidpoint(Vec2(0,0.5));
    boolstate->setPercentage(99.9f);
    boolstate->setTag(888);
    this->addChild(boolstate);
}


void Monster::monsterresumestate()
{
    auto callf=CallFunc::create([this](){
        this->stopAllActions();
        this->fsm->doEvent("stop");
    });
    this->runAction(Sequence::create(DelayTime::create(1.01),callf, NULL));
}


void Monster::updatemonsterhp()
{
    boolstate->setPercentage((currentblood/(float)blood)*100);
}


