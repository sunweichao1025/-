//
//  Hero.cpp
//  pass
//
//  Created by student on 15/9/7.
//
//

#include "Hero.h"
#include "cocos2d.h"

Hero::Hero(HeroType type,std::string _name)
{
    
    heroSkill=hidle;
    Herotype=type;
    name=_name;
    isdirecton=true;
    predirection=true;
    isaction=false;             //是否正在执行动画
    int totalblood=1000;       //总血量
    int currentblood=1000;    //待定值
    lv = 1;                  //等级
    this->initHero();
    this->heroaction();
   
}

void Hero::initHero()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("nanheiqishi0.pvr.ccz", "nanheiqishi0.plist", "nanheiqishi.ExportJson");
    if(!Armature::init("nanheiqishi"))
    {
        return ;
    }
    getAnimation()->playWithIndex(8,1,false);
    this->setPosition(Vec2(100, 200));
    auto body=PhysicsBody::createCircle(this->getContentSize().width/8);
    body->setGravityEnable(false);
    body->setCategoryBitmask(1);
    body->setCollisionBitmask(1);
    body->setContactTestBitmask(1);
    this->setPhysicsBody(body);

   
}

void Hero::heroaction()
{
    fsm=Actionstate::create("idle",[this](){
        this->getAnimation()->playWithIndex(0,1,true);
    });
    fsm->retain();
    
    fsm->setOnEnter("running",[this](){
        this->getAnimation()->playWithIndex(3,1,false);
    });
    
    fsm->setOnEnter("attacking1",[this](){
        this->getAnimation()->playWithIndex(7,1,false);
        this->resumestate();
    });

    fsm->setOnEnter("attacking2",[this](){
        this->getAnimation()->playWithIndex(8,1,false);
        this->resumestate();
    });
    
    fsm->setOnEnter("attacking3",[this](){
       this->getAnimation()->playWithIndex(9,1,false);
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo("huimiezhijian0.pvr.ccz","huimiezhijian0.plist","huimiezhijian.ExportJson");
        auto a = Armature::create("huimiezhijian");
        a->getAnimation()->playWithIndex(0,1,false);
        if (isdirecton) {
            a->setPosition(Vec2(this->getPosition().x+150,this->getPosition().y-100));
        }else{
            a->setPosition(Vec2(this->getPosition().x-150,this->getPosition().y-100));
        }
        this->getParent()->addChild(a);
        auto fun = CallFunc::create([this,a](){
            a->removeFromParent();
        });
        auto seq = Sequence::create(DelayTime::create(2),fun, NULL);
        a->runAction(seq);
        this->resumestate();
    });
    

    fsm->setOnEnter("skill1",[this](){
       this->getAnimation()->playWithIndex(4,1,false);
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo("jinglingjinjie0.pvr.ccz", "jinglingjinjie0.plist", "jinglingjinjie.ExportJson");
        auto a = Armature::create("jinglingjinjie");
        a->getAnimation()->playWithIndex(0,1,false);
        a->setPosition(Vec2(this->getPosition()));
        this->getParent()->addChild(a);
    
        ArmatureDataManager::getInstance()->addArmatureFileInfo(
                                                                "toushezhiyan0.pvr.ccz","toushezhiyan0.plist","toushezhiyan.ExportJson");
        auto b = Armature::create("toushezhiyan");
        b->getAnimation()->playWithIndex(0,1,false);
        if(this->isdirecton){
            b->setPosition(Vec2(this->getPosition().x+300,this->getPosition().y));
        }else{
            b->setPosition(Vec2(this->getPosition().x-200,this->getPosition().y));
        }
        b->setScale(2);
        this->getParent()->addChild(b);
        this->resumestate();
        auto callf=CallFunc::create([b,a,this](){
            this->resumestate();
            b->removeFromParent();
            a->removeFromParent();
            
        });
        b->runAction(Sequence::create(DelayTime::create(2), callf,NULL));
    });
    
    fsm->setOnEnter("skill2",[this](){
        this->getAnimation()->playWithIndex(6,1,false);
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo("xinlingjianxiao0.pvr.ccz", "xinlingjianxiao0.plist", "xinlingjianxiao.ExportJson");
        auto a = Armature::create("xinlingjianxiao");
        a->getAnimation()->playWithIndex(0,1,false);
        a->setPosition(Vec2(this->getPosition()));
        this->getParent()->addChild(a);
        auto callfn=CallFunc::create([a,this](){
            a->removeFromParent();
            this->resumestate();
        });
        
        
        a->runAction(Sequence::create(DelayTime::create(1), callfn,NULL));
        
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo("siwangnuyi0.pvr.ccz","siwangnuyi0.plist","siwangnuyi.ExportJson");
        auto c = Armature::create("siwangnuyi");
        c->getAnimation()->playWithIndex(0,3,false);
        if(this->isdirecton){
            c->setPosition(Vec2(this->getPosition().x+300,this->getPosition().y));
        }else{
            c->setPosition(Vec2(this->getPosition().x-200,this->getPosition().y));
        }
        c->setScale(3);
        this->getParent()->addChild(c);
        
        auto callf=CallFunc::create([c,a,this](){
            c->removeFromParent();
        });
        c->runAction(Sequence::create(DelayTime::create(2), callf,NULL));
        this->resumestate();
    });
    
    fsm->setOnEnter("skill3",[this](){
        this->getAnimation()->playWithIndex(9,1,false);
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo("shengmingkaijia0.pvr.ccz", "shengmingkaijia0.plist", "shengmingkaijia.ExportJson");
        auto a = Armature::create("shengmingkaijia");
        a->getAnimation()->playWithIndex(0,1,false);
        a->setPosition(Vec2(this->getPosition()));
        this->getParent()->addChild(a);
        auto callfn=CallFunc::create([a,this](){
            a->removeFromParent();
            this->resumestate();
        });
        a->runAction(Sequence::create(DelayTime::create(2), callfn,NULL));
        
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo("shandianfengbao0.pvr.ccz","shandianfengbao0.plist","shandianfengbao.ExportJson");
        auto c = Armature::create("shandianfengbao");
        c->getAnimation()->playWithIndex(0,3,false);
        if(this->isdirecton){
            c->setPosition(Vec2(this->getPosition().x+300,this->getPosition().y));
        }else{
            c->setPosition(Vec2(this->getPosition().x-200,this->getPosition().y));
        }
        
        c->setScale(3);
        this->getParent()->addChild(c);
        
        auto callf=CallFunc::create([c,a,this](){
            c->removeFromParent();
        });
        c->runAction(Sequence::create(DelayTime::create(2), callf,NULL));
        this->resumestate();
    });
    
    fsm->setOnEnter("skill4", [this](){
      
        ArmatureDataManager::getInstance()->addArmatureFileInfo("jufengjiasuo0.pvr.ccz", "jufengjiasuo0.plist", "jufengjiasuo.ExportJson");
        auto a = Armature::create("jufengjiasuo");
        a->getAnimation()->playWithIndex(0,1,false);
        a->setPosition(Vec2(this->getPosition()));
        this->getParent()->addChild(a);
        auto callfn=CallFunc::create([a,this](){
            a->removeFromParent();
            this->resumestate();
        });
        a->runAction(Sequence::create(DelayTime::create(5), callfn,NULL));
        
        auto size = Director::getInstance()->getWinSize();
        ArmatureDataManager::getInstance()->addArmatureFileInfo("youlinghu0.pvr.ccz","youlinghu0.plist","youlinghu.ExportJson");
        auto c = Armature::create("youlinghu");
        
        ArmatureDataManager::getInstance()->addArmatureFileInfo("jianhunpojia0.pvr.ccz", "jianhunpojia0.plist", "jianhunpojia.ExportJson");
        
        auto d = Armature::create("jianhunpojia");
        
        
        if (this->isdirecton) {
            c->setScaleX(-1);
            if(this->getPosition().x>960){
                c->setPosition(Vec2(960+size.width/2,size.height/2-200));
                d->setPosition(Vec2(960+size.width/2+500,size.height/2-200));
            }else{
                c->setPosition(Vec2(size.width/2,size.height/2-200));
                d->setPosition(Vec2(size.width/2+350,size.height/2-200));
            }
            
        }else
        {
            c->setScaleX(1);
            if(this->getPosition().x>960){
                
                c->setPosition(Vec2(960+size.width/2,size.height/2-200));
                d->setPosition(Vec2(960+size.width/2+500,size.height/2-200));
            }else{
                c->setPosition(Vec2(size.width/2,size.height/2-200));
                d->setPosition(Vec2(size.width/2+350,size.height/2-200));
            }
        }
        d->getAnimation()->playWithIndex(0,1,false);
        d->setScale(3);
        this->getParent()->addChild(d);
        
        
        auto callf1 = CallFunc::create([c,this](){
            c->getAnimation()->playWithIndex(2,1,false);
        });
        auto callf2 = CallFunc::create([c,this](){
            c->getAnimation()->playWithIndex(3,2,false);
        });
        auto callf3 = CallFunc::create([c,this](){
            c->getAnimation()->playWithIndex(5,2,false);
            
        });
        auto callf4 =CallFunc::create([d,this](){
            d->getAnimation()->playWithIndex(0,1,false);
        });
        auto callf5=CallFunc::create([c,d,this](){
            c->removeFromParent();
            d->removeFromParent();
        });
        this->getParent()->addChild(c);
        c->runAction(Sequence::create(callf1,DelayTime::create(1),callf2,DelayTime::create(1),callf3,DelayTime::create(1),callf4,DelayTime::create(3),callf5,NULL));
        this->resumestate();
    });
    
    fsm->setOnEnter("beingHit",[this](){
        this->getAnimation()->playWithIndex(1,1,false);
    });
    
    fsm->setOnEnter("dead",[this](){
        this->getAnimation()->playWithIndex(2,1,false);
    });

}

void Hero::resumestate()
{
    auto callf=CallFunc::create([this](){
        this->fsm->doEvent("stop");
        this->isaction=false;
    });
    this->runAction(Sequence::create(DelayTime::create(1),callf, NULL));
}


