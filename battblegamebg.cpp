//
//  battblegamebg.cpp
//  ECIT
//
//  Created by student on 15/9/10.
//
//

#include "battblegamebg.h"
#include "Monster.h"
#include "definelb.h"
#include "movehandler.h"
#include "Interfactionlayer.h"
#include "DataManager.h"
USING_NS_CC;
battbleScene * battbleScene::createscene(const std::string bgname)
{
    battbleScene *pRet = new(std::nothrow) battbleScene();
    if (pRet && pRet->init(bgname))
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


bool  battbleScene::init(const std::string bgname)
{
   
    bg=Sprite::create(bgname);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(0, 0));
    this->addChild(bg);
    this->initmonster();
    schedule(CC_CALLBACK_1(battbleScene::updatemonstermove,this), 4.1,"updatemove");
    dhero->fsm->doEvent("stop");
    return true;
}

void battbleScene::initmonster()
{

     std::vector<Monster*>::iterator it;
     auto vec=DataManager::getInstance()->monsterVec;


    for(int i=0;i<dscene[dscenes-1][dlevels-1]->getMonsterNum();i++)
    {
        int _index=arc4random()%5;
        int npcX=200+arc4random()%200;
        int npcY=50+arc4random()%1800;
        auto npc=Monster::createwith(dscene[dscenes-1][dlevels-1]->mtype[_index]);
        
        
        for(it=vec.begin();it!=vec.end();it++)
        {
            if((*it)->name==dscene[dscenes-1][dlevels-1]->mtype[_index])
            {
                npc->blood=(*it)->blood;
                npc->attck=(*it)->attck;
                npc->currentblood=npc->blood;
                break;
            }
               
        }
        npc->setPosition(Vec2(npcY, npcX));
        npc->fsm->doEvent("stop");
        monsterArr.pushBack(npc);
        this->addChild(npc);
    }
    
    auto boss=Monster::createwith(dscene[dscenes-1][dlevels-1]->getboss());
    boss->setPosition(Vec2(1800, 320));
    boss->fsm->doEvent("stop");
    boss->retain();
    this->addChild(boss);
    monsterArr.pushBack(boss);
    

    for(it=vec.begin();it!=vec.end();it++)
    {
        log("%s",(*it)->name.c_str());
       if((*it)->name==dscene[dscenes-1][dlevels-1]->getboss())
       {
         boss->blood=(*it)->blood;
         boss->attck=(*it)->attck;
         boss->currentblood=boss->blood;
         break;
           
       }
    }


}


void battbleScene::updatemonstermove(float dt)
{
    std::vector<Monster*>::iterator t;
    for(t=monsterArr.begin();t!=monsterArr.end();t++)
       {
           auto monster=(*t);
           if(monster->fsm->_currentState=="beingHit")
           {
               continue;
           }
           if(hero->getPosition().x>monster->getPosition().x)
           {
               monster->setScaleX(-1);
               monster->boolstate->setScaleX(-1);
           }
           else
           {
               monster->setScaleX(1);
               monster->boolstate->setScaleX(1);
           }
           
           if((distance(hero->getPosition(),monster->getPosition()))<500)
           {
               if((distance(hero->getPosition(),monster->getPosition()))<100)
               {
                  
                   monster->fsm->doEvent("attack1");
                   hero->stopAllActions();
                   hero->resumestate();
                   hero->currentblood-=monster->attck;
                   if(hero->currentblood<=0)
                   {
                       hero->fsm->doEvent("die");
                       scheduleOnce([this](float dt){
                           this->getParent()->getParent()->addChild(Interfactionlayer::create(402));
                           Director::getInstance()->pause();
                       }, 1, "gameover");
                       
                   }
                   else {
                   hero->fsm->doEvent("beHit");
                   }
                   ((Movehandler*) this->getParent()->getChildByTag(998))->updatedetal();
                   continue;
               }
               monster->fsm->doEvent("run");
               movemonster(monster);
           }
          else
          {
               monster->fsm->doEvent("stop");
          }
       }
 
}

void battbleScene::updateheroattack(float dt)
{
    if(hero->fsm->_currentState=="attacking1")
    {
        hero->setattack(80);
        this->attackrect(100);
    }
    else if(hero->fsm->_currentState=="attacking2")
    {
        hero->setattack(100);
        this->attackrect(120);
    }
    else if (hero->fsm->_currentState=="attacking3")
    {
        hero->setattack(120);
        this->attackrect(200);
    }
    else if (hero->fsm->_currentState=="skill1")
    {
        hero->setattack(150);
        this->attackrect(250);
    }
    else if (hero->fsm->_currentState=="skill12")
    {
        hero->setattack(150);
        this->attackrect(300);
    }
    else if(hero->fsm->_currentState=="skill3")
    {
        hero->setattack(160);
        this->attackrect(500);
    }
    else if(hero->fsm->_currentState=="skill4")
    {
        hero->setattack(170);
        this->attackrect(600);
    }
 
}

void battbleScene::attackrect(int attackdistance)
{
    std::vector<Monster*>::iterator t;
    for(t=monsterArr.begin();t!=monsterArr.end();t++)
    {
        auto monster=(*t);
        if((distance(hero->getPosition(),monster->getPosition()))<=attackdistance)
        {
            monster->stopAllActions();
            monster->fsm->doEvent("beHit");
            monster->currentblood-=hero->getattack();
            
            hero->setgold(hero->getgold()+50);
            hero->setcurrentEXP(hero->getcurrentEXP()+50);
            ((Movehandler*) this->getParent()->getChildByTag(998))->updatedetal();
            
            if(monster->currentblood<=0)
            {
                monster->fsm->doEvent("die");
                auto callf=CallFunc::create([this,monster](){
                monster->removeFromParent();
                });
                this->monsterArr.eraseObject(monster);
                this->runAction(Sequence::create(DelayTime::create(1.0),callf, NULL));
                
                log("%lo",monsterArr.size());
                
                if(!monsterArr.size())
                {
                    auto call=CallFunc::create([this](){
                        auto layer=Interfactionlayer::create(403);
                        this->getParent()->getParent()->addChild(layer);});
                    this->runAction(Sequence::create(DelayTime::create(3),call, NULL));
                }
                break;
            }
            
            
            
            else{
             monster->updatemonsterhp();
            }
           
            continue;
        }
    }
    
}

void battbleScene::movemonster(Monster* monster)
{
   angle=corea(hero->getPosition(),monster->getPosition());
   Size csize=Director::getInstance()->getVisibleSize();
   int mintus=3;
   int dis=80;
   MoveBy *move;
   Point p1=hero->getPosition();
   Point p2=monster->getPosition();
   if(p1.x>p2.x)
     {
         if(p1.y==p2.y)
         {
             move=MoveBy::create(mintus, Vec2(dis,0 ));
         }
         else if (p1.y>p2.y)
         {
             move=MoveBy::create(mintus,Vec2(sqrt(dis*dis)*cosf(angle),dis*sinf(angle)));
         }
         else if(p1.y<p2.y)
         {
             move=MoveBy::create(mintus, Vec2(sqrt(dis*dis)*cosf(angle),-dis*sinf(angle)));
         }
         }
    else if(p1.x<p2.x)
    {
        if(p1.y==p2.y)
         {
             move=MoveBy::create(mintus, Vec2(-dis,0 ));
         }
        else if(p1.y>p2.y)
        {
            move=MoveBy::create(mintus,Vec2(-sqrt(dis*dis)*cosf(angle), -dis*sinf(angle)));
        }
        else if(p1.y<p2.y)
        {
            move=MoveBy::create(mintus,Vec2(-sqrt(dis*dis)*cosf(angle), +dis*sinf(angle)));
        }
    }
  monster->runAction(move);
}



