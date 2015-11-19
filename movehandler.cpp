//
//  movehandler.cpp
//  ECIT
//
//  Created by student on 15/9/6.
//
//

#include "Movehandler.h"
#include "Actionstate.h"
#include "GameScene.h"
#include "definelb.h"
#include "DataManager.h"
#include "battblegamebg.h"

USING_NS_CC;


Movehandler*  Movehandler::createlayer(Hero *hero)
{
    Movehandler *pRet = new(std::nothrow) Movehandler();
    if (pRet && pRet->init(hero))
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
bool Movehandler::init(Hero *hero)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    currendir=true;
    predir=true;
    _hero=hero;
    dhero->currentblood=dhero->getblood();
    
    //初始化英雄的默认移动方向（ps：不移动）
    direction=DEFAULT;
    //园盘
    circle=Sprite::create("img_joystick_bg.png");
    circle->setPosition(Vec2(center, center));

    //移动点
    point=Sprite::create("img_joystick.png");
    point->setPosition(Vec2(center, center));
    this->addChild(circle);
    this->addChild(point);
    this->dispathch();
    //半径的距离
    raduis=circle->getBoundingBox().size.width/2;
    
    _hero->fsm->doEvent("stop");
    this->initherostate();
    return true ;
}

void Movehandler::initherostate()
{
    Size csize=Director::getInstance()->getVisibleSize();
    
    //点击次数
    ClickedCounts=0;
    auto attackbtn=MenuItemImage::create("battle_gongji_0.png", "battle_gongji_1.png", [this](Ref*){
        log("%d",ClickedCounts);
        if (ClickedCounts==2) {
            ThreeClicked();
        }else if (ClickedCounts==1){
            scheduleOnce(schedule_selector(Movehandler::updateDoubleDelay),0.1f);
            ClickedCounts++;
        }else{
            scheduleOnce(schedule_selector(Movehandler::updateSingleDelay),0.1f);
            ClickedCounts++;
        }
    });
    
    //血量
    auto hpbg = Sprite::create("battle_bar_hp_1.png");
    hpbg->setPosition(Vec2(csize.width/2-250,csize.height/2+280));
    addChild(hpbg);
    
    hp = ProgressTimer::create(Sprite::create("battle_bar_hp.png"));
    hp->setType(ProgressTimer::Type::BAR);
    hp->setMidpoint(Vec2(0,0.5));
    hp->setPercentage(100);
    hp->setPosition(Vec2(csize.width/2-250,csize.height/2+280));
    addChild(hp);
    
    //经验值
    auto expbg = Sprite::create("battle_bar_exp_1.png");
    expbg->setPosition(Vec2(csize.width/2-250,csize.height/2+250));
    addChild(expbg);
    
    exp = ProgressTimer::create(Sprite::create("battle_bar_exp.png"));
    exp->setType(ProgressTimer::Type::BAR);
    exp->setMidpoint(Vec2(0,0.5));
    exp->setPercentage(100);
    exp->setPosition(Vec2(csize.width/2-250,csize.height/2+250));
    addChild(exp);
    
    //进度上面显示的值---------------------------
    HPText = Label::createWithTTF("HP","fonts/arial.ttf" , 20);
    HPText->setColor(Color3B::WHITE);
    HPText->setPosition(Vec2(csize.width/2-170,csize.height/2+278));
    addChild(HPText);
    
    ExpText = Label::createWithTTF("Exp","fonts/arial.ttf" , 20);
    ExpText->setColor(Color3B::WHITE);
    ExpText->setPosition(Vec2(csize.width/2-190,csize.height/2+250));    addChild(ExpText);
    
    
    //金币
    auto glod = Sprite::create("public_gold.png");
    glod->setPosition(Vec2(csize.width/2,csize.height/2+290));
    addChild(glod);
    
    
    //技能
     skill1=MenuItemImage::create("battle_skill1_1.png", "hsk_0.png", [this,csize](Ref*sender){
        printf("%s",cocos2dVersion());
      ((MenuItemImage*)sender)->getParent()->setVisible(false);
        Point p=(Vec2(800, 35));
        _hero->fsm->doEvent("skilling1");
         this->SkillState("battle_skill1_1.png",p,30,sender);
         this->skill2->setEnabled(false);
         this->skill3->setEnabled(false);
         this->skill4->setEnabled(false);
         
         auto callf=CallFunc::create([this](){
             this->skill2->setEnabled(true);
             this->skill3->setEnabled(true);
             this->skill4->setEnabled(true);
         });
         this->runAction(Sequence::create(DelayTime::create(1), callf,NULL));
        ((battbleScene*)this->getParent()->getChildByTag(997))->updateheroattack(0);
    });
    
     skill2=MenuItemImage::create("battle_skill2_1.png", "hsk_1.png", [this](Ref*sender){
        ((MenuItemImage*)sender)->getParent()->setVisible(false);
        Point p=(Vec2(800, 110));
        this->SkillState("battle_skill2_1.png",p,40,sender);
        _hero->fsm->doEvent("skilling2");
    
         this->skill1->setEnabled(false);
         this->skill3->setEnabled(false);
         this->skill4->setEnabled(false);
         
         auto callf=CallFunc::create([this](){
             this->skill1->setEnabled(true);
             this->skill3->setEnabled(true);
             this->skill4->setEnabled(true);
         });
         this->runAction(Sequence::create(DelayTime::create(1), callf,NULL));
         ((battbleScene*)this->getParent()->getChildByTag(997))->updateheroattack(0);
         });
    
     skill3=MenuItemImage::create("battle_skill3_1.png", "hsk_2.png", [this](Ref*sender){
        ((MenuItemImage*)sender)->getParent()->setVisible(false);
        Point p=(Vec2(850, 163));
        this->SkillState("battle_skill3_1.png",p,40,sender);
        _hero->fsm->doEvent("skilling3");
         
         this->skill1->setEnabled(false);
         this->skill2->setEnabled(false);
         this->skill4->setEnabled(false);
         
         auto callf=CallFunc::create([this](){
             this->skill1->setEnabled(true);
             this->skill2->setEnabled(true);
             this->skill4->setEnabled(true);
         });
         this->runAction(Sequence::create(DelayTime::create(1), callf,NULL));
         ((battbleScene*)this->getParent()->getChildByTag(997))->updateheroattack(0);
    });
     skill4=MenuItemImage::create("battle_dazhao_2.png", "hsk_3.png", [this](Ref*sender){
        ((MenuItemImage*)sender)->getParent()->setVisible(false);
        Point p=(Vec2(920, 165));
        this->SkillState("battle_dazhao_2.png",p,60,sender);
        _hero->fsm->doEvent("skilling4");
    
         this->skill2->setEnabled(false);
         this->skill3->setEnabled(false);
         this->skill1->setEnabled(false);
         
         auto callf=CallFunc::create([this](){
             this->skill2->setEnabled(true);
             this->skill3->setEnabled(true);
             this->skill1->setEnabled(true);
         });
         this->runAction(Sequence::create(DelayTime::create(1), callf,NULL));
         ((battbleScene*)this->getParent()->getChildByTag(997))->updateheroattack(0);
            });
    
    
    auto attackmenu=Menu::create(attackbtn, NULL);
    attackmenu->setPosition(Vec2(csize.width-70, 70));
    this->addChild(attackmenu);
    
    auto menu1=Menu::create(skill1, NULL);
    menu1->setPosition(Vec2(800, 35));
    this->addChild(menu1);
    
    auto menu2=Menu::create(skill2, NULL);
    menu2->setPosition(Vec2(800, 110));
    this->addChild(menu2);
    
    auto menu3=Menu::create(skill3, NULL);
    menu3->setPosition(Vec2(850, 163));
    this->addChild(menu3);
    
    auto menu4=Menu::create(skill4, NULL);
    menu4->setPosition(Vec2(920, 165));
    this->addChild(menu4);
    
    auto iconbg=Sprite::create("btn_beijing.png");
    iconbg->setScale(2);
    iconbg->setPosition(Vec2(60, 580));
    this->addChild(iconbg);
    
    auto leveliamge=Sprite::create("battle_word_lv.png");
    leveliamge->setPosition(Vec2(40,10));
    leveliamge->setScale(0.7);
    iconbg->addChild(leveliamge,1);
    
    auto battle_hero = Sprite::create("r8.png");
    battle_hero->setPosition(Vec2(30,30));
    battle_hero->setScale(0.7);
    iconbg->addChild(battle_hero);
    
    herolevel=Label::createWithCharMap("battle_num1.png", 20, 26, '0');
    herolevel->setString("2");
    herolevel->setScale(0.7);
    herolevel->setPosition(Vec2(65, 10));
    iconbg->addChild(herolevel,1);
    
    //金币数量
    glodText = Label::createWithTTF("2000","fonts/arial.ttf" , 30);
    glodText->setTextColor(cocos2d::Color4B::YELLOW);
    glodText->setPosition(Vec2(csize.width/2+50,csize.height/2+290));
    addChild(glodText);
    
    this->updatedetal();
}

void Movehandler::updatedetal(){
    char c[50];
    sprintf(c, "%d/%d",dhero->currentblood,dhero->getblood());
    HPText->setString(c);
    
    
    hp->setPercentage((dhero->currentblood/((float)dhero->getblood()))*100);
    

    
    sprintf(c, "%d",dhero->getgold());
    glodText->setString(c);
    
    if(dhero->getcurrentEXP()>dhero->getneedEXP())
    {
        dhero->setcurrentEXP(0);
        dhero->setlv(dhero->getlv()+1);
        dhero->setneedEXP(DataManager::getInstance()->needlvarr[dhero->getlv()]);
    }
    sprintf(c,"%d",dhero->getlv());
    herolevel->setString(c);
    
    sprintf(c,"%d/%d",dhero->getcurrentEXP(),dhero->getneedEXP());
    ExpText->setString(c);
    exp->setPercentage((dhero->getcurrentEXP()/((float)dhero->getneedEXP()))*100);
}

//单击
void Movehandler::updateSingleDelay(float dt)
{
    if (ClickedCounts == 1) {
        if(_hero->isaction)
        {
            return ;
        }
        log("单击");
        _hero->isaction=true;
        _hero->fsm->doEvent("attack1");
        _hero->resumestate();
        auto callf=CallFunc::create(CC_CALLBACK_0(Movehandler::resumeclick, this));
        this->runAction(Sequence::create(DelayTime::create(0.5),callf, NULL));
        ((battbleScene*)this->getParent()->getChildByTag(997))->updateheroattack(0);
    }
}
//双击
void Movehandler::updateDoubleDelay(float dt)
{
    if (ClickedCounts == 2 )
    {
        if(_hero->isaction)
        {
            return ;
        }
        log("双击");
        _hero->isaction=true;
        _hero->fsm->doEvent("attack2");
        _hero->resumestate();
        auto callf=CallFunc::create(CC_CALLBACK_0(Movehandler::resumeclick, this));
        this->runAction(Sequence::create(DelayTime::create(0.5),callf, NULL));
        ((battbleScene*)this->getParent()->getChildByTag(997))->updateheroattack(0);
    }
}
//三击
void Movehandler::ThreeClicked()
{
    if(_hero->isaction)
    {
        return ;
    }
    log("三击");
    _hero->isaction=true;
    _hero->fsm->doEvent("attack3");
    _hero->resumestate();
    auto callf=CallFunc::create(CC_CALLBACK_0(Movehandler::resumeclick, this));
    this->runAction(Sequence::create(DelayTime::create(0.5),callf, NULL));
   ((battbleScene*)this->getParent()->getChildByTag(997))->updateheroattack(0);
}

void Movehandler::resumeclick()
{
    this->ClickedCounts=0;
}

//技能冷却
void Movehandler::SkillState(const char *pic,Point p,int t,Ref *sender){
    
    auto sprite = Sprite::create(pic);
    sprite->setPosition(p);
    this->addChild(sprite, 0);
    
    auto sprite1 = Sprite::create(pic);
    sprite1->setColor(Color3B::GRAY);
    
    ProgressTimer *pt=ProgressTimer::create(sprite1);
    pt->setPosition(p);
    pt->setType(ProgressTimerType::RADIAL);
    this->addChild(pt, 0);
    
    ProgressTo *Pt=ProgressTo::create(t, 100);
    CallFuncN* call=CallFuncN::create([pt,this,sender](Node *node){
         pt->setVisible(false);
       ((MenuItemImage*)sender)->getParent()->setVisible(true);
     
    });
    pt->runAction(Sequence::create(Pt,call,NULL));
}

//注册监听（ps：监听移动点）
void Movehandler::dispathch()
{
    auto cahe=Director::getInstance()->getEventDispatcher();
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=CC_CALLBACK_2(Movehandler::onTouchBegan,this);
    listener->onTouchEnded=CC_CALLBACK_2(Movehandler::onTouchEnded,this);
    listener->onTouchMoved=CC_CALLBACK_2(Movehandler::onTouchMoved,this);
    cahe->addEventListenerWithSceneGraphPriority(listener,point);
}

bool Movehandler:: onTouchBegan(Touch *touch, Event *unused_event)
{
    Point p=touch->getLocation();
    if((distance(p,Point(center,center))<raduis))
    {
        Point p=touch->getLocation();
        Point p2=Point(center,center);
        float angle=acosf(corea(p,p2));
        currentangle=angle;
        checkdirection(angle,p);
        point->setPosition(Vec2(p.x, p.y));
        if(_hero->fsm->_currentState=="beingHit")
        {
            unschedule("updatehero");
        }
        else
        {
        schedule(CC_CALLBACK_1(Movehandler::updatehero, this), 0.5, "updatehero");
        }
        
        return true;
    }
    return false;
}

void Movehandler::onTouchMoved(Touch *touch, Event *unused_event){
    Point p=touch->getLocation();
    Point p2=Point(center,center);
    float angle=acosf(corea(p,p2));
    currentangle=angle;
    checkdirection(angle,p);
    if((distance(p,Point(center,center))>raduis))
    {
        float x=raduis*cosf(angle);
        float y=raduis*sinf(angle);
        if(p.y>=center)
        {
            point->setPosition(Vec2(center+x, center+y));
        }
        else
        {
            float x=raduis*cosf(angle);
            float y=raduis*sinf(angle);
            log("%f",angle);
            point->setPosition(Vec2(center+x, center-y));
        }
    }
    else{
        point->setPosition(touch->getLocation());
    }

    schedule(CC_CALLBACK_1(Movehandler::updatehero, this), 0.5, "updatehero");
}

void Movehandler::onTouchEnded(Touch *touch, Event *unused_event){
    point->setPosition(Vec2(center, center));
    unschedule("updatehero");
    _hero->stopAllActions();
    this->_hero->fsm->doEvent("stop");
    _hero->isaction=false;
    ((GameScene*)this->getParent())->battlebg->stopAllActions();
}

//判断hero移动的方向
void Movehandler::checkdirection(float angle,Point p)
{
    if(!(predir==currendir))
    {
        predir=currendir;
        _hero->stopAllActions();
        ((GameScene*)this->getParent())->battlebg->stopAllActions();
        return;
    }
    
   
    if(p.y>=center&&p.x>=center)
    {
        _hero->setScaleX(-1);
        _hero->isdirecton=true;
        currendir=true;
        if(CC_RADIANS_TO_DEGREES(angle)>22.5||CC_RADIANS_TO_DEGREES(angle)<75)
        {
            direction=D_RIGHT_UP;//右上
            return;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)>75)
        {
            direction=D_UP;      //上
            return ;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)<22.5)
        {    direction=D_RIGHT;   //右
            return;
        }
    }
 
    else if (p.y>=center&&p.x<=center)
    {
        _hero->setScaleX(1);
        _hero->isdirecton=false;
        currendir=false;
        if(CC_RADIANS_TO_DEGREES(angle)>22.5||CC_RADIANS_TO_DEGREES(angle)<75)
        {
            direction=D_LEFT_UP;    //左上
            return ;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)>75)
        {
            direction=D_UP;         //上
            return;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)<22.5)
        {
            direction=D_LEFT;       //左
            return ;
        }
    }
  
    else if(p.y<=center&&p.x<center)
    {
        _hero->setScaleX(1);
        _hero->isdirecton=false;
        currendir=false;
        if(CC_RADIANS_TO_DEGREES(angle)>22.5||CC_RADIANS_TO_DEGREES(angle)<75)
        {
            direction=D_LEFT_DOWN;    //左下
            return ;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)>75)
        {
            direction=D_DOWN;         //下
            return;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)<22.5)
        {
            direction=D_LEFT;         //左
            return ;
        }
    }
    
    else if(p.x>center&&p.y<center)
    {
        _hero->setScaleX(-1);
        _hero->isdirecton=true;
        currendir=true;
        if(CC_RADIANS_TO_DEGREES(angle)>22.5||CC_RADIANS_TO_DEGREES(angle)<75)
        {
            direction=D_RIGHT_DOWN;    //右下
            return ;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)>75)
        {
            direction=D_DOWN;          //下
            return;
        }
        else if (CC_RADIANS_TO_DEGREES(angle)<22.5)
        {
            direction=D_LEFT;          //左
            return ;
        }
    }
    
}

void Movehandler::updatehero(float dt)
{ 
    Size csize=Director::getInstance()->getVisibleSize();
    int mintus=2;
    MoveBy *move;
    switch (direction) {
        case 0:
            break;
        case 1:
        {
            move=MoveBy::create(mintus,Vec2(0, yidongdistance));
            break;
        }
        case 2:
        {
            move=MoveBy::create(mintus, Vec2(0, -yidongdistance));
            break;
        }
        case 3:
        {
            move=MoveBy::create(mintus, Vec2(-yidongdistance, 0));
            break;
        }
        case 4:
        {
            move=MoveBy::create(mintus, Vec2(yidongdistance, 0));
            break;
        }
        case 5:
        {
            move=MoveBy::create(mintus, Vec2(sqrt(yidongdistance*yidongdistance)*cosf(currentangle), yidongdistance*sinf(currentangle)));
            break;
        }
        case 6:
        {
            move=MoveBy::create(mintus, Vec2(sqrt(yidongdistance*yidongdistance)*cosf(currentangle), -yidongdistance*sinf(currentangle)));
            break;
        }
        case 7:
        {
            move=MoveBy::create(mintus, Vec2(sqrt(yidongdistance*yidongdistance)*cosf(currentangle),yidongdistance*sinf(currentangle)));
            break;
        }
        case 8:
        {
            move=MoveBy::create(mintus, Vec2(sqrt(yidongdistance*yidongdistance)*cosf(currentangle),-yidongdistance*sinf(currentangle)));
            break;
        }
        default:
            break;
    }
    if(_hero->fsm->_currentState=="beingHit")
    {
        return ;
    }
    this->updatebg();
    this->_hero->fsm->doEvent("run");
    _hero->runAction(move);
    
}

void Movehandler::updatebg()
{
    auto parent=(GameScene*)this->getParent();
    int x;
    Size csize=Director::getInstance()->getVisibleSize();

    x=MAX(_hero->getPosition().x,csize.width/2+40);
    if(_hero->getPosition().x<=csize.width/2)
    {
        ((GameScene*)this->getParent())->body3->setEnable(true);
        return ;
    }
    else
    {
        ((GameScene*)this->getParent())->body3->setEnable(false);
    }
    
    x=MIN(x,parent->battlebg->bg->getContentSize().width-csize.width/2-30);
    if(x>=parent->battlebg->bg->getContentSize().width-csize.width/2-30)
    {
        ((GameScene*)this->getParent())->body2->setEnable(true);
        parent->battlebg->stopAllActions();
        return ;
    }
    else
    {
       ((GameScene*)this->getParent())->body2->setEnable(false);
    }
    
    Point currentp=Point(x,0);
    Point centerp=Point(csize.width/2-30,0);
    Point actualp=centerp-currentp;
    auto move=MoveTo::create(0.7,actualp);
    parent->battlebg->runAction(move);
}





