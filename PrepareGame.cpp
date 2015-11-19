//
//  PrepareGame.cpp
//  GD
//
//  Created by student on 15/8/28.
//
//
#include "PrepareGame.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StartUIview.h"
#include "CharpterUIview.h"
#include "MenuLayer.h"
#include "Interfactionlayer.h"

using namespace cocostudio;
using namespace ui;
using namespace timeline;

USING_NS_CC;
Scene * PrepareGame::createScene(){
    auto scene=Scene::create();
    auto layer=PrepareGame::create();
    scene->addChild(layer);
    return scene;
}
bool PrepareGame:: init(){
    if (!Layer::init()) {
        return false;
    }
    this->setKeyboardEnabled(true);
    auto listenerkey=EventListenerKeyboard::create();
    listenerkey->onKeyReleased=[this](EventKeyboard::KeyCode keyCode, Event* event){
        auto interact=Interfactionlayer::create(100);
        if(!this->getChildByTag(666))
        {
            interact->setTag(666);
            this->addChild(interact);
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkey, this);

    
    //加载csb
    auto node=CSLoader::createNode("Scene.csb");
    this->addChild(node);
    
    //按钮
    auto Legend=node->getChildByName<ui::Button*>("Legend");
    Legend->setTag(101);
    auto equitMent=node->getChildByName<ui::Button *>("equitMent");
    equitMent->setTag(102);
    auto Package=node->getChildByName<ui::Button*>("Package");
    Package->setTag(103);
    
    //佣兵
    auto Soldiers=node->getChildByName<ui::Button*>("Soldiers");
    Soldiers->addClickEventListener([this](Ref*){
        auto layer=MenuLayer::createScene(200);
        this->addChild(layer,11);
    });
    
    //英雄
    auto Hero=node->getChildByName<ui::Button*>("Hero");
    Hero->addClickEventListener([this](Ref*){
        auto layer=MenuLayer::createScene(201);
        this->addChild(layer,11);
    });
    
    //商店
    auto Shop=node->getChildByName<ui::Button*>("Shop");
    Shop->addClickEventListener([this](Ref*){
        auto layer=MenuLayer::createScene(202);
        this->addChild(layer,11);
    });
    
    //成就
    auto Achievement=node->getChildByName<ui::Button*>("Achievement");
    Achievement->addClickEventListener([this](Ref*){
        auto layer=MenuLayer::createScene(203);
        this->addChild(layer);
    });
    
    //布阵
    auto Lineup=node->getChildByName<ui::Button*>("Lineup");
    Lineup->addClickEventListener([this](Ref*){
        auto layer=MenuLayer::createScene(204);
        this->addChild(layer);
        
    });
    
    
    //返回
    auto Direction=node->getChildByName<ui::Button*>("Direction");
    Direction->addClickEventListener([this](Ref*){
        Director::getInstance()->replaceScene(StartUIview::createwithstartUI());
    });
    
    //战斗
    auto Fighting=node->getChildByName<ui::Button*>("Fighting");
    Fighting->addClickEventListener([this](Ref*sender){
        Director::getInstance()->replaceScene(CharpterUIview::createwithCharpterUIview());
    });
    
    //分数
    auto GoldScore=node->getChildByName<ui::TextField*>("GoldScore");
    //音乐
    auto MusicImage=node->getChildByName<ui::ImageView*>("music");
    auto VoiceImage=node->getChildByName<ui::ImageView*>("voice");
   
    auto musicbtn1=MenuItemImage::create("btn_yinyue_0.png", "btn_yinyue_0.png");
    auto musicbtn2=MenuItemImage::create("btn_yinyue_1.png", "btn_yinyue_1.png");
    auto toggle1=MenuItemToggle::createWithCallback([this](Ref*){
        log("sds");
    },musicbtn1,musicbtn2, NULL);
    toggle1->setSelectedIndex(0);
    auto menu1=Menu::create(toggle1, NULL);
    menu1->setPosition(Vec2(23, 23));
    MusicImage->addChild(menu1);
    
    //声音
    auto voicebtn1=MenuItemImage::create("btn_shengyin_0.png", "btn_shengyin_0.png");
    auto voicebtn2=MenuItemImage::create("btn_shengyin_1.png", "btn_shengyin_1.png");
    auto toggle2=MenuItemToggle::createWithCallback([this](Ref*){},voicebtn1,voicebtn2, NULL);
    toggle2->setSelectedIndex(0);
    auto menu2=Menu::create(toggle2, NULL);
    menu2->setPosition(Vec2(23, 23));
    VoiceImage->addChild(menu2);
    
    //传奇佣兵，史诗套装，至尊礼盒
    Legend->addClickEventListener([this](Ref *){
        auto interact=Interfactionlayer::create(101);
        this->addChild(interact);
    });
    equitMent->addClickEventListener([this](Ref*){
        auto interact=Interfactionlayer::create(102);
        this->addChild(interact);
    });
    Package->addClickEventListener([this](Ref *){
        auto interact=Interfactionlayer::create(103);
        this->addChild(interact);
    });
 

    this->antionMove(Soldiers);
    this->antionMove(Hero);
    this->antionMove(Shop);
    this->antionMove(Achievement);
    this->antionMove(Lineup);
    this->antionMove(Legend);
    this->antionMove(equitMent);
 
    return true;
}

void PrepareGame:: antionMove(Button *btn){
      Point p=btn->getPosition();
    if(btn->getTag()==101||btn->getTag()==102)
    {
        auto sprite1=Sprite::create("img_light.png");
        sprite1->setPosition( Vec2(p.x+5 ,p.y+2));
        this->addChild(sprite1,1);
        auto rotate=RotateBy::create(1.5, 180);
        auto fade=FadeTo::create(1.5, 1.5);
        auto spaw=Spawn::create(rotate,fade, NULL);
        auto fade1=FadeIn::create(1.5);
        auto spawn1=Spawn::create(rotate->clone(),fade1, NULL);
        auto cosequence=Sequence::create(spaw,spawn1, NULL);
        sprite1->runAction(RepeatForever::create(cosequence));
        return;
    }
    auto move=MoveTo::create(1, Vec2(p.x+1, p.y+3));
    auto move1=MoveTo::create(1, p);
    auto sequence=Sequence::create(move,move1, NULL);
    btn->runAction(RepeatForever::create(sequence));
}




