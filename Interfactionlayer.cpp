//
//  Interfactionlayer.cpp
//  ECIT
//
//  Created by student on 15/8/27.
//
//

#include "Interfactionlayer.h"
#include "MenuLayer.h"
#include "CharpterUIview.h"
#include "PrepareGame.h"
#include "GameScene.h"
#include "definelb.h"
#include "DataManager.h"
#include "Load.h"
//#include "ui/CocosGUI.h"
USING_NS_CC;


Interfactionlayer * Interfactionlayer::create(int tag)
{
    Interfactionlayer * layer = new (std::nothrow) Interfactionlayer();
    if(layer && layer->init(tag))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
 
}

bool Interfactionlayer::init(int tag)
{
  Size csize=Director::getInstance()->getVisibleSize();
  this->initWithColor(Color4B(0, 0, 0, 200), csize.width,csize.height);
    
  auto listener=EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);
  listener->onTouchBegan=[this](Touch*, Event*){return true;};
  this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    switch (tag) {
            case 100:
            this->initstartUIview();
            break;
            case 101:
            this->initwithshop("shop_goods_18.png");
            break;
            case 102:
            this->initwithshop("shop_goods_19.png");
            break;
            case 103:
            this->initwithshop("shop_goods_15.png");
            break;
            case 401:
            this->initwithsetting();
            break;
            case 402:
            this->gameover();
            break;
            case 403:
            this->gamevetor();
        default:
            break;
    }
    return true;
}

void Interfactionlayer::initstartUIview()
{
    Size csize=Director::getInstance()->getVisibleSize();
    auto isoverbar=Sprite::create("box_kuang.png");
    isoverbar->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(isoverbar);
    
    Size barsize=isoverbar->getContentSize();
    auto goback=MenuItemImage::create("box_btn_fanhui_0.png", "box_btn_fanhui_1.png", [this](Ref*){
        this->removeFromParent();
    });
    auto contain=MenuItemImage::create("box_btn_queding_0.png","box_btn_queding_1.png",[this](Ref*){
        exit(0);
    });
    auto menu=Menu::create(goback,contain, NULL);
    menu->alignItemsHorizontallyWithPadding(20);
    menu->setPosition(Vec2(barsize.width/2, 50));
    isoverbar->addChild(menu);
    
    auto deletebtn=MenuItemImage::create("btn_clouse_1.png", "btn_clouse_2.png", [this](Ref*){
        this->removeFromParent();
    });
    auto menu1=Menu::create(deletebtn,NULL);
    menu1->alignItemsHorizontallyWithPadding(20);
    menu1->setPosition(Vec2(barsize.width-20, barsize.height-20));
    isoverbar->addChild(menu1);
    
    
    auto label=Label::createWithSystemFont("确定退出游戏？", "arial.ttf", 20);
    label->setTextColor(cocos2d::Color4B::GREEN);
    label->setPosition(Vec2(barsize.width/2, barsize.height/2+30));
    isoverbar->addChild(label,100);
}

void Interfactionlayer::initwithshop(const std::string &name)
{
    Size csize=Director::getInstance()->getVisibleSize();
    auto isoverbar=Sprite::create(name);
    isoverbar->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(isoverbar);
    
    Size barsize=isoverbar->getContentSize();
    auto pickup=MenuItemImage::create("box_btn_lingqu_0.png", "box_btn_lingqu_1.png", [this](Ref*){
    });
    auto menu=Menu::create(pickup,NULL);
    menu->setPosition(Vec2(barsize.width/2, 50));
    isoverbar->addChild(menu);
    
    auto deletebtn=MenuItemImage::create("btn_clouse_1.png", "btn_clouse_2.png", [this](Ref*){
        this->removeFromParent();
    });
    auto menu1=Menu::create(deletebtn,NULL);
    menu1->alignItemsHorizontallyWithPadding(20);
    menu1->setPosition(Vec2(barsize.width-40, barsize.height-20));
    isoverbar->addChild(menu1);
}

void Interfactionlayer::initwithsetting()
{
    
    Size csize=Director::getInstance()->getVisibleSize();
    auto isoverbar=Sprite::create("battle_stop_bg.png");
    isoverbar->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(isoverbar);
    
    Size barsize=isoverbar->getContentSize();
    
    //继续游戏
    auto resumeback=MenuItemImage::create("battle_stop_btn_continue_1.png", "battle_stop_btn_continue_2.png", [this](Ref*){
        this->removeFromParent();
        Director::getInstance()->resume();
    });
    
    //重新开始
    auto restart=MenuItemImage::create("battle_stop_btn_restart_1.png","battle_stop_btn_restart_2.png",[this](Ref*){
        log("重新开始");
        Director::getInstance()->resume();
    });
    
   //选择关卡
    auto selectgame=MenuItemImage::create("battle_stop_btn_tollgate_1.png","battle_stop_btn_tollgate_2.png",[this](Ref*){
        Director::getInstance()->replaceScene(CharpterUIview::createwithCharpterUIview());
        Director::getInstance()->resume();
    });
    
    //商店
    auto shopstore=MenuItemImage::create("battle_stop_btn_shop_1.png","battle_stop_btn_shop_1.png",[this](Ref*){
        this->addChild(MenuLayer::createScene(202));
        Director::getInstance()->resume();
    });
    
    auto menu=Menu::create(resumeback,restart,selectgame,shopstore,NULL);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(Vec2(barsize.width/2, barsize.height/2));
    isoverbar->addChild(menu);
    Director::getInstance()->pause();
}


void Interfactionlayer::gameover()
{
    Size csize=Director::getInstance()->getVisibleSize();
    auto isoverbar=Sprite::create("box_kuang.png");
    isoverbar->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(isoverbar);
    
    Size barsize=isoverbar->getContentSize();

    auto contain=MenuItemImage::create("box_btn_queding_0.png","box_btn_queding_1.png",[this](Ref*){
         Director::getInstance()->replaceScene(PrepareGame::createScene());
         Director::getInstance()->resume();
    });
    auto menu=Menu::create(contain, NULL);
    menu->setPosition(Vec2(barsize.width/2, 50));
    isoverbar->addChild(menu);
    
    auto deletebtn=MenuItemImage::create("btn_clouse_1.png", "btn_clouse_2.png", [this](Ref*){
        Director::getInstance()->replaceScene(PrepareGame::createScene());
        Director::getInstance()->resume();
    });
    
    auto menu1=Menu::create(deletebtn,NULL);
    menu1->alignItemsHorizontallyWithPadding(20);
    menu1->setPosition(Vec2(barsize.width-20, barsize.height-20));
    isoverbar->addChild(menu1);
    
    
    auto label=Label::createWithSystemFont("GAME OVER", "arial.ttf", 20);
    label->setTextColor(cocos2d::Color4B::GREEN);
    label->setPosition(Vec2(barsize.width/2, barsize.height/2+30));
    isoverbar->addChild(label);
}

void Interfactionlayer::gamevetor()
{
    Size csize=Director::getInstance()->getVisibleSize();
    auto isoverbar=Sprite::create("box_kuang.png");
    isoverbar->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(isoverbar);
    
    Size barsize=isoverbar->getContentSize();
    auto goback=MenuItemImage::create("battle_stop_btn_tollgate_1.png","battle_stop_btn_tollgate_2.png", [this](Ref*){
        Director::getInstance()->replaceScene(CharpterUIview::createwithCharpterUIview());
    });
    auto contain=MenuItemImage::create("box_btn_queding_0.png","box_btn_queding_1.png",[this](Ref*){
        if(dlevels==5)
        {
            dlevels=1;
        }
        else
        {
            dlevels++;
        }
        
        Director::getInstance()->replaceScene(Load::createScene());
    });
    auto menu=Menu::create(goback,contain, NULL);
    menu->alignItemsHorizontallyWithPadding(20);
    menu->setPosition(Vec2(barsize.width/2, 50));
    isoverbar->addChild(menu);
    
    auto deletebtn=MenuItemImage::create("btn_clouse_1.png", "btn_clouse_2.png", [this](Ref*){
        Director::getInstance()->replaceScene(CharpterUIview::createwithCharpterUIview());
    });
    auto menu1=Menu::create(deletebtn,NULL);
    menu1->alignItemsHorizontallyWithPadding(20);
    menu1->setPosition(Vec2(barsize.width-20, barsize.height-20));
    isoverbar->addChild(menu1);
    
    
    auto label=Label::createWithSystemFont("进入下一关？", "arial.ttf", 20);
    label->setTextColor(cocos2d::Color4B::GREEN);
    label->setPosition(Vec2(barsize.width/2, barsize.height/2+30));
    isoverbar->addChild(label);

 
}

