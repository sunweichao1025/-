
//
//  MenuLayer.cpp
//  PrePreGame
//
//  Created by student on 15/8/29.
//
//
#include "PrepareGame.h"
#include "MenuLayer.h"
#include "CharpterUIview.h"
#include "ui/CocosGUI.h"
#include "DataManager.h"
#include "definelb.h"
using namespace ui;
MenuLayer * MenuLayer::createScene(int Tag){
    MenuLayer *pRet = new (std::nothrow) MenuLayer();
    if (pRet&&pRet->init(Tag)){
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

bool MenuLayer:: init(int Tag){
    if (!Layer::init()) {
        return false;
    }
    index=1;
    

    //触摸事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = ([](Touch *touch, Event *unused_event){
        auto p = touch->getLocation();
        return true;
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    nodeArray=__Array::create();
    nodeArray->retain();
    switch (Tag) {
        case 200:
            createslider();
            break;
        case 201:
            createHeros();
            break;
        case 202:
            createShop();
            break;
        case 203:
            createAchievement();
            break;
        case 204:
            createquene();
            break;
        case 301:
            createnotebook();
            break;
        default:
            break;
    }
    return true;
}
MenuLayer::~MenuLayer(){
    nodeArray->release();
}


void MenuLayer::createslider()
{  
    mer = CSLoader::createNode("Slider.csb");
    addChild(mer);
    for(int i=1;i<7;i++)
    {   char c[10];
        sprintf(c, "merc%d",i);
        auto mer1 = mer->getChildByName<Button*>(c);
        mer1->setScale(2);
        mer1->addClickEventListener([this,c,i](Ref* ref){
            this->updatemerdata(c,i);
        });
    }
    //关闭按钮
    auto close = mer->getChildByName<Button*>("close");
    close->addClickEventListener([this](Ref* ref){
        this->removeFromParent();
    });
    this->updatemerdata("merc1", 0);
    
}

void MenuLayer::updatemerdata(std::string merName ,int _index)
{
    //血量
    char str[50];
    sprintf(str, "%d",((Mercenary*)DataManager::getInstance()->merMap[merName])->blood);
    mernary=(Mercenary*)DataManager::getInstance()->merMap[merName];
    mernary->setPosition(Vec2(480, 350));
    mernary->setTag(70);
    mernary->setScaleX(-1);
    if (_index==index) {
        return;
    }else{
        if(!(_index==0)){
            index=_index;
        }
        this->removeChildByTag(70);
        this->addChild(mernary);
    }
    
    //中间的金币数量
    sprintf(str, "%d",DataManager::getInstance()->getheros()->getgold());
    auto glod = mer->getChildByName<Text*>("Text_glod");
    glod->setString(str);
    
    mernary->fsm->doEvent("stop");
    auto blood = mer->getChildByName<Text*>("Text_blood");
    blood->setString(str);
    
    //攻击
    sprintf(str,"%d",((Mercenary*)DataManager::getInstance()->merMap[merName])->attack);
    auto attack = mer->getChildByName<Text*>("Text_attack");
    attack->setString(str);
    
    
    //防御
    sprintf(str,"%d",((Mercenary*)DataManager::getInstance()->merMap[merName])->defense);
    auto defense = mer->getChildByName<Text*>("Text_defense");
    defense->setString(str);
    
    //需要血量
    sprintf(str,"%d",((Mercenary*)DataManager::getInstance()->merMap[merName])->needBlood);
    auto needBlood = mer->getChildByName<Text*>("Text_needBlood");
    needBlood->setString(str);
    
    //需要攻击量
    sprintf(str,"%d",((Mercenary*)DataManager::getInstance()->merMap[merName])->needAttack);
    auto needAttack = mer->getChildByName<Text*>("Text_needAttack");
    needAttack->setString(str);
    
    //需要金币
    sprintf(str,"%d",((Mercenary*)DataManager::getInstance()->merMap[merName])->needGlod);
    auto needGlod = mer->getChildByName<Text*>("Text_needGold");
    needGlod->setString(str);
    
    //显示佣兵
    auto merinfo = mer->getChildByName<Node*>("node");
    
    //显示佣兵简介
    auto merinfo2 = mer->getChildByName<Text*>("merinf");
    //等级
    auto merGrade = mer->getChildByName<Text*>("grade");
    

    
    //升级按钮
    auto upgrade = mer->getChildByName<Button*>("upgrade");
    upgrade->addClickEventListener([](Ref* ref){
    });
}


void MenuLayer:: createShop(){
    //背景
    auto node0=CSLoader::createNode("BackGroundScene.csb");
    this->addChild(node0);
    
    //关闭按钮
    auto deletebutton=node0->getChildByName<ui::Button*>("Close");
    deletebutton->addClickEventListener([this](Ref*){
    this->removeFromParent();
    });
    
    //超级热卖
    auto *node=CSLoader::createNode("ShopScene.csb");
    node0->addChild(node,1);
    nodeArray->addObject(node);
    auto button0=node->getChildByName<ui::Button*>("Button_1");
    button0->addClickEventListener([this,node](Ref*){
        this->Shop(node);
    });
    //辅助强化
    auto *node1=CSLoader::createNode("Shop1Scene.csb");
    node0->addChild(node1,0);
    nodeArray->addObject(node1);
    auto button1=node1->getChildByName<ui::Button*>("Button_1");
    button1->addClickEventListener([this,node1](Ref*){
        this->Shop(node1);
    });
    //金币强化
    auto node2=CSLoader::createNode("Shop2Scene.csb");
    node0->addChild(node2,0);
    nodeArray->addObject(node2);
    auto button2=node2->getChildByName<ui::Button*>("Button_1");
    button2->addClickEventListener([this,node2](Ref*){
        this->Shop(node2);
    });
    
    char str[20];
    sprintf(str, "%d",DataManager::getInstance()->getheros()->getgold());
    auto gold=node0->getChildByName<Text*>("GoldScore");
    gold->setString(str);
}
void MenuLayer:: Shop(Node* node){
for (int j=0; j<nodeArray->count(); j++) {
       auto loder=(Node*)nodeArray->getObjectAtIndex(j);
        if(node==loder)
        loder->setZOrder(1);
        else
        loder->setZOrder(0);
    }
}

void MenuLayer::createHeros(){
    auto hero = CSLoader::createNode("MainScene.csb");
    this->addChild(hero);
  
    //这里不用看，是数据
    DataManager::getInstance()->getheros()->setPosition(230,430);
    DataManager::getInstance()->getheros()->setScaleX(-1);
    DataManager::getInstance()->getheros()->fsm->doEvent("stop");
    DataManager::getInstance()->getheros()->setTag(999);
    this->addChild(DataManager::getInstance()->getheros());
    
    //获取背包pageview
    auto pageView = hero->getChildByName<PageView*>("PageView");
    
    //四个显示技能的
    auto skil1 = hero->getChildByName<Button*>("skil1");
    auto skil2 = hero->getChildByName<Button*>("skil2");
    auto skil3 = hero->getChildByName<Button*>("skil3");
    auto skil4 = hero->getChildByName<Button*>("skil4");
    
    //关闭按钮
    auto close = hero->getChildByName<Button*>("close");
    //取消按钮,关闭整个界面
    close->addClickEventListener([this](Ref* ref){
        this->removeFromParent();
    });
    
    auto page1= pageView->getChildByName<ui::Layout*>("page1");
    
    auto image1=page1->getChildByName<ui::ImageView*>("Image1");
    auto node11=image1->getChildByName<Node*>("node");
    
    //ui界面的一些控件
    auto gold = hero->getChildByName<Text*>("Text_glod");
    auto lv = hero->getChildByName<Text*>("Text_1");
    auto blood = hero->getChildByName<Text*>("Text_blood");
    auto attack = hero->getChildByName<Text*>("Text_attack");
    auto defense = hero->getChildByName<Text*>("Text_defense");
    auto pro = hero->getChildByName<Text*>("Text_value");
    auto load = hero->getChildByName<LoadingBar*>("LoadingBar");
    auto skillInf = hero->getChildByName<Text*>("Text_skillinf");
 
   //设置控件的信息
    char q[20];
    sprintf(q, "%d/%d",DataManager::getInstance()->getheros()->getcurrentEXP(),(DataManager::getInstance()->getheros()->getneedEXP()));
    pro->setString(q);
    
    
    sprintf(q, "%d",(DataManager::getInstance()->getheros())->getgold());
    gold->setString(q);
    
    sprintf(q,"%d",(DataManager::getInstance()->getheros())->getlv());
    lv->setString(q);
    
    sprintf(q,"%d",(DataManager::getInstance()->getheros())->getblood());
    blood->setString(q);
    
    sprintf(q,"%d",(DataManager::getInstance()->getheros())->getattack());
    attack->setString(q);
    
    sprintf(q,"%d",(DataManager::getInstance()->getheros())->getdefense());
    defense->setString(q);
    
    
    skil1->addClickEventListener([this,skillInf](Ref*){
        char a[50];
        sprintf(a,"%s",(DataManager::getInstance()->getheros())->getskill1().c_str());
        skillInf->setString(a);
       DataManager::getInstance()->getheros()->fsm->doEvent("skilling1");
    });
    
    skil2->addClickEventListener([this,skillInf](Ref*){
        char a[50];
        sprintf(a,"%s",(DataManager::getInstance()->getheros())->getskill2().c_str());
        skillInf->setString(a);
       DataManager::getInstance()->getheros()->fsm->doEvent("skilling2");
    });
    
    skil3->addClickEventListener([this,skillInf](Ref*){
        char a[50];
        sprintf(a,"%s",(DataManager::getInstance()->getheros())->getskill3().c_str());
        skillInf->setString(a);
       DataManager::getInstance()->getheros()->fsm->doEvent("skilling3");
    });
    
    skil4->addClickEventListener([this,skillInf](Ref*){
        char a[50];
        sprintf(a,"%s",(DataManager::getInstance()->getheros())->getskill4().c_str());
        skillInf->setString(a);
        DataManager::getInstance()->getheros()->fsm->doEvent("skilling4");
    });
    
    //左边四个显示框
    auto clothes = hero->getChildByName<ImageView*>("select1");
    sprintf(q, "%s.png",DataManager::getInstance()->getheros()->getclothes().c_str());
    auto menuimage=MenuItemImage::create(q,q);
    auto menu=Menu::create(menuimage, NULL);
    menu->setPosition(Vec2(clothes->getContentSize().width/2, clothes->getContentSize().height/2));
    clothes->addChild(menu);
    
    auto weapen = hero->getChildByName<ImageView*>("select2");
    sprintf(q, "%s.png",DataManager::getInstance()->getheros()->getweapen().c_str());
    auto menuimage2=MenuItemImage::create(q,q);
    auto menu2=Menu::create(menuimage2, NULL);
    menu2->setPosition(Vec2(clothes->getContentSize().width/2, clothes->getContentSize().height/2));
    weapen->addChild(menu2);

    
    auto necklace = hero->getChildByName<ImageView*>("select3");
    sprintf(q, "%s.png",DataManager::getInstance()->getheros()->getnecklace().c_str());
    auto menuimage3=MenuItemImage::create(q,q);
    auto menu3=Menu::create(menuimage3, NULL);
    menu3->setPosition(Vec2(clothes->getContentSize().width/2, clothes->getContentSize().height/2));
    necklace->addChild(menu3);
    
    
    auto stone = hero->getChildByName<ImageView*>("select4");
    
    auto data=DataManager::getInstance();
    
    //设置每个页面的节点
    for(int m=0;m<4;m++)
    {   char c[10];
        sprintf(c, "page%d",m+1);    //page层
        auto p = pageView->getChildByName<ui::Layout*>(c);
        char d[10];
        sprintf(d, "Image%d",m+1);   //图片层
        auto image = p->getChildByName<ui::ImageView*>(d);
        
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                if(m==0&&i==0&&j==0)
                {
                   continue;
                }
             
                auto n = Node::create();
                n->setPosition(Vec2(35+75*j,250-75*i));
                image->addChild(n);
                
                if(data->shoppage[m][i*4+j]==1)
                {   log("%d",i*4+j);
                    auto equit=MenuItemImage::create("public_lock.png","public_lock.png");
                    auto menu=Menu::create(equit, NULL);
                    menu->setPosition(Vec2(0, 0));
                    n->addChild(menu);
                }
                if (i==0) {
                    n->setTag(1+j);
                }else if(i==1){
                    n->setTag(5+j);
                }else if (i==2){
                    n->setTag(9+j);
                }else{
                    n->setTag(13+j);
                }
            }
            
        }
    }
    
    
    //pageview
    pageView->addEventListener([pageView](Ref* ref,PageView::EventType type){
    });
    
}

void MenuLayer::createquene(){
    auto embattle = CSLoader::createNode("quene.csb");
    addChild(embattle);
    
    //显示6个佣兵的图片，6个节点
    auto node1 = embattle->getChildByName<Node*>("node1");
    node1->setTag(11);
    auto node2 = embattle->getChildByName<Node*>("node2");
    node2->setTag(12);
    auto node3 = embattle->getChildByName<Node*>("node3");
    node3->setTag(13);
    auto node4 = embattle->getChildByName<Node*>("node4");
    node4->setTag(14);
    auto node5 = embattle->getChildByName<Node*>("node5");
    node5->setTag(15);
    auto node6 = embattle->getChildByName<Node*>("node6");
    node6->setTag(16);
    
    
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            
            auto n = Node::create();
            n->setPosition(Vec2(650+80*j,470-80*i));
            embattle->addChild(n);
            //设置每个节点的Tag值，tag值是从1-16；1-4 左上--左下
            if (i==0) {
                n->setTag(1+j);
            }else if(i==1){
                n->setTag(4+j);
            }else {
                n->setTag(7+j);
            }
        }
    }
    
    std::unordered_map<std::string,Mercenary*> vec=DataManager::getInstance()->merMap;
    std::unordered_map<std::string,Mercenary*>::iterator it;
    for(it=vec.begin();it!=vec.end();it++)
    {
        auto merr=it->second;
        if(merr->locked==0)
        {
            
            merr->icon=Sprite::create("img_weapon_0.png");
            merr->icon->setPosition(Vec2(0, 0));
            node1->addChild(merr->icon);
            spvec.pushBack(merr->icon);
            
            auto listener=EventListenerTouchOneByOne::create();
            
            listener->onTouchBegan=[this,merr,embattle](Touch* touch, Event*_event){
                
                log("%f,,,%f",touch->getLocation().x,touch->getLocation().y);
                
                Point p=merr->icon->convertToNodeSpace(touch->getLocation());
                auto mer=(Mercenary*)_event->getCurrentTarget();
                Rect rect=mer->getBoundingBox();
                Rect  merrect=Rect(0, 0, rect.size.width, rect.size.height);
                if(merrect.containsPoint(p))
                {
                    
                    this->merInf(merr,embattle);
                    this->scheduleOnce(CC_CALLBACK_1(MenuLayer::onPress, this), 1, "changesize");
                 
                    return true;
                }
                return false;
            };
            
            listener->onTouchMoved=[this,merr](Touch* touch, Event* event){
                if(merr->icon->getScale()<=1)
                    return ;
                Point p=event->getCurrentTarget()->getParent()->convertToNodeSpace(touch->getLocation());  //获取node的坐标
                merr->icon->setPosition(p);
            };
            
            listener->onTouchEnded=[this,merr,embattle](Touch* touch, Event* event)
            {
                this->unschedule("changesize");
                merr->icon->setScale(1);
                
                Point p1=touch->getLocation();
                log("%f   %f",touch->getLocation().x,touch->getLocation().y);
                
                if (p1.x>600 && p1.x<900 && p1.y>250 && p1.y<600) {
                    float x=0;
                    Node* posNode;
                    for(int i=1;i<10;i++)
                    {
                        
                        if(i==5)
                            continue;
                        
                        auto node=embattle->getChildByTag(i);
                        float x1=distance(p1, node->getPosition());
                        if(x==0||x1<x)
                        {   x=x1;
                            posNode=node;
                        }
                    }
                    if(posNode->getChildrenCount()==0)
                    {
                        merr->icon->removeFromParent();
                        posNode->addChild(merr->icon);
                        merr->icon->setPosition(0, 0);
                    }
                    else
                    {
                        merr->icon->setPosition(Vec2(0, 0));
                    }
                    
                }
                else
                {
                    merr->icon->setPosition(Vec2(0, 0));
                }
                
                
                if(p1.x<270)
                {
                    for (int i = 11; i<17; i++) {
                        auto node = embattle->getChildByTag(i);
                        if(node->getChildrenCount()==0)
                        {
                            merr->icon->removeFromParent();
                            node->addChild(merr->icon);
                            merr->icon->setPosition(0, 0);
                            break;
                        }
                }
                }
                
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, merr->icon);
        }

    }
    //战斗按钮
    auto fight = embattle->getChildByName<Button*>("getChildByName<Button*>");
    auto close = embattle->getChildByName<Button*>("close");
    close->addClickEventListener([this](Ref*){
        this->removeFromParent();
    });
    
    //显示中间佣兵的动作
    auto nodeMer = embattle->getChildByName<Node*>("node9");
    
    
    //auto mer1 = embattle->getChildByName<ImageView*>("mer1");
    auto node = embattle->getChildByName<Node*>("node");//设置节点
    
    it=vec.begin();
    this->merInf(it->second,embattle);

}
    
void MenuLayer::merInf(Mercenary*mer,Node *csb)
{
        //label
        auto fightLabel = csb->getChildByName<Text*>("Text_fight");
        auto merName = csb->getChildByName<Text*>("Text_6");
        auto blood = csb->getChildByName<Text*>("Text_c");
        auto attack = csb->getChildByName<Text*>("Text_attack");
        auto defense = csb->getChildByName<Text*>("Text_defense");
        auto num = csb->getChildByName<Text*>("Text_num");
        
        char a[30];
        sprintf(a, "%d",mer->blood);
        blood->setString(a);
        
        
        sprintf(a, "%s",mer->merName.c_str());
        merName->setString(a);
        sprintf(a, "%d",mer->attack);
        attack->setString(a);
        sprintf(a, "%d",mer->defense);
        defense->setString(a);
        //出阵人数
        sprintf(a, "%d",0);
        num->setString(a);
        
        
}

void MenuLayer::onPress(float dt)
{
    std::vector<Sprite*>::iterator it;
    it=spvec.begin();
    (*it)->setScale(1.2);
    
}
    

void MenuLayer::createAchievement()
{
    auto achi=CSLoader::createNode("AchievementScene1.csb");
    this->addChild(achi);
    
    sc=achi->getChildByName<ScrollView*>("ScrollView_6");
    //关闭按钮
    auto close=achi->getChildByName<Button*>("Button_1");
    close->addClickEventListener([this](Ref *){
        this->removeFromParent();
    });
    auto apc= DataManager::getInstance()->apleVec;
    for (index=0; index<7; index++) {
        sc->addChild(addCell(apc.at(index),index));
    }
    
}

Sprite * MenuLayer:: addCell(Aplements *aple,int index){
    auto sprite=Sprite::create("success_box.png");
    auto name=Text::create(aple->name,"arial.ttf",20);
    name->setPosition(Vec2(194.01, 56.48));
    auto level=Text::create(aple->level,"arial.ttf",20);
    level->setPosition(Vec2(195.69, 23.37));
    auto discription=Text::create(aple->discription,"arial.ttf",20);
    discription->setPosition(Vec2(387.54, 61.02));
    auto reward=Text::create(aple->reward,"arial.ttf",20);
    reward->setPosition(Vec2(466.69, 26.62));
    auto item=MenuItemImage::create("success_btn_receive_2.png", "success_btn_receive_2.png");
    auto item2=MenuItemImage::create("success_btn_receive_1.png", "success_btn_receive_1.png");
    auto toggle=MenuItemToggle::create();
    toggle->addSubItem(item);
    toggle->addSubItem(item2);
    if (atoi(aple->locked.c_str())==1) {
        toggle->setSelectedIndex(1);
        toggle->setCallback([this,sprite](Ref *){
            Point p=Point(sprite->getPosition());
            sprite->removeFromParent();
            auto apc= DataManager::getInstance()->apleVec;
            auto sprite0=this->addCell(apc.at(this->index++), this->index++);
            log("+++++++++++++%d++++++++++++",this->index);
            sprite0->setPosition(p.x+300,p.y);
            auto move=MoveTo::create(0.5, p);
            sprite0->runAction(move);
            sc->addChild(sprite0);
        });
    }else{
        toggle->setSelectedIndex(0);
        toggle->setEnabled(false);
    }
    auto menu=Menu::create(toggle, NULL);
    menu->setPosition(Vec2(639.13, 46.09));
    sprite->addChild(menu);
    sprite->addChild(name);
    sprite->addChild(level);
    sprite->addChild(discription);
    sprite->addChild(reward);
    sprite->setPosition(Vec2(101.21,65+(18*(index+1))+5));
    sprite->setScale(0.2, 0.2);
    return sprite;
}

void MenuLayer::createnotebook()
{
    auto node=CSLoader::createNode("notebook.csb");
    this->addChild(node);
    
    //返回按钮
    auto  gobackbtn=node->getChildByName<ui::Button*>("gobackbtn");
    gobackbtn->addClickEventListener([this](Ref*){
        Director::getInstance()->replaceScene(CharpterUIview::createwithCharpterUIview());
    });
    
    //goldlabel金币数
    auto GoldScore=node->getChildByName<ui::Text*>("goldlabel");
    GoldScore->setString("GoldScore");
    
    //notebook
    auto notebook_1=node->getChildByName<ui::Button*>("notebook_1");
    auto notebook_2=node->getChildByName<ui::Button*>("notebook_2");
    auto notebook_3=node->getChildByName<ui::Button*>("notebook_3");
    auto notebook_4=node->getChildByName<ui::Button*>("notebook_4");
    auto notebook_5=node->getChildByName<ui::Button*>("notebook_5");

}
