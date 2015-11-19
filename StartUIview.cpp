//
//  StartUIview.cpp
//  ECIT
//
//  Created by student on 15/8/27.
//
//

#include "StartUIview.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Interfactionlayer.h"
#include "PrepareGame.h"
#include "ScrollViewImage.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace cocostudio;
using namespace timeline;

Scene * StartUIview::createwithstartUI()
{
    auto scene=Scene::create();
    auto layer=StartUIview::create();
    scene->addChild(layer);            
    return scene;
}


bool  StartUIview::init()
{

    if(!Layer::init())
    {
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
    
    
    Size csize=Director::getInstance()->getVisibleSize();
   
    //雪花粒子
    ParticleSystem  *coment=ParticleSnow::create();
    coment->setTexture(Director::getInstance()->getTextureCache()->addImage("Comet.png"));
    coment->setPosition(Vec2(csize.width/2,csize.height));
    coment->setSpeed(50);
    this->addChild(coment,10);
    
    //场景
    auto startview=CSLoader::createNode("startview.csb");
    this->addChild(startview);
    
    //声音，音乐，开始，删除按钮
    auto bgbtn1=startview->getChildByName<ui::ImageView*>("btnbg");
    auto bgbtn2=startview->getChildByName<ui::ImageView*>("btnbg1");
    auto startbtn=startview->getChildByName<ui::Button *>("start");
    auto deletebtn=startview->getChildByName<ui::Button*>("trash");
    
    deletebtn->addClickEventListener([this](Ref*sender){
        auto interact=Interfactionlayer::create(100);
        this->addChild(interact);
    });
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("lieyankuilong0.pvr.ccz","lieyankuilong0.plist","lieyankuilong.ExportJson");
    auto c = Armature::create("lieyankuilong");
    c->getAnimation()->playWithIndex(5,1,true);
    c->setScale(0.2);
    c->setScaleX(-1);
    c->setScaleY(0.5);
    c->setPosition(Vec2(300,120));
    addChild(c);
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("nanbaiqishi0.pvr.ccz","nanbaiqishi0.plist","nanbaiqishi.ExportJson");
    auto a = Armature::create("nanbaiqishi");
    a->getAnimation()->playWithIndex(0,1,true);
    a->setPosition(Vec2(800,100));
    a->setScale(1.5);
    addChild(a);
    
   CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battle02.mp3",true);
    

    //音乐按钮
    auto musicbtn1=MenuItemImage::create("btn_yinyue_0.png", "btn_yinyue_0.png");
    auto musicbtn2=MenuItemImage::create("btn_yinyue_1.png", "btn_yinyue_1.png");
    auto toggle1=MenuItemToggle::createWithCallback([this](Ref*){
        
        if (flag) {
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            flag = false;
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
            flag = true;
        }

        
    },musicbtn1,musicbtn2, NULL);
    toggle1->setSelectedIndex(0);
    auto menu1=Menu::create(toggle1, NULL);
    menu1->setPosition(Vec2(23, 23));
    bgbtn2->addChild(menu1);
    
     //声音按钮
    auto voicebtn1=MenuItemImage::create("btn_shengyin_0.png", "btn_shengyin_0.png");
    auto voicebtn2=MenuItemImage::create("btn_shengyin_1.png", "btn_shengyin_1.png");
    auto toggle2=MenuItemToggle::createWithCallback([this](Ref*){},voicebtn1,voicebtn2, NULL);
    
    toggle2->setSelectedIndex(0);
    auto menu2=Menu::create(toggle2, NULL);
    menu2->setPosition(Vec2(23, 23));
    bgbtn1->addChild(menu2);
    
    //开始按钮
    startbtn->addClickEventListener([this,a,c](Ref*sender){
        auto start=(ui::Button*)sender;
        Point p=start->getPosition();
        
        auto btn1=ui::Button::create("btn_cundang_0.png");
        btn1->setPosition(Vec2(p.x, p.y+50));
        btn1->addClickEventListener([](Ref*){
            Director::getInstance()->replaceScene(ScrollViewImage::CrateLayer());
        });
        auto btn2=ui::Button::create("btn_cundang_1.png");
        btn2->setPosition(Vec2(p.x, p.y-50));
        btn2->addClickEventListener([](Ref*){});
    
        this->addChild(btn1);
        this->addChild(btn2);
        a->removeFromParent();
        c->removeFromParent();
        start->removeFromParent();
    });
    
    
    
    return true;
}

