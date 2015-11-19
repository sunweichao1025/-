//
//  GameScene.cpp
//  ECIT
//
//  Created by student on 15/9/6.
//
//

#include "GameScene.h"
#include "movehandler.h"
#include "Interfactionlayer.h"
#include "battblegamebg.h"
#include "MenuLayer.h"
#include "DataManager.h"
#include "definelb.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


Scene * GameScene::createScene()
{
    //创建一个带有物理世界的舞台
    auto scene=Scene::createWithPhysics();
   // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    //初始化layer
    auto layer=GameScene::create();
    //设置一个静态的刚体（边界）
    Size csize=Director::getInstance()->getVisibleSize();

    auto  body=PhysicsBody::createEdgeBox(Size(csize.width*2.5, csize.height-250),PHYSICSSHAPE_MATERIAL_DEFAULT,10);
    auto rectnode=Node::create();
    rectnode->setPhysicsBody(body);
    rectnode->setPosition(Vec2(csize.width, csize.height/2-60));
    
    auto body2=PhysicsBody::createEdgeBox(Size(csize.width*2-50, csize.height-200),PHYSICSSHAPE_MATERIAL_DEFAULT,10);
    auto rect1node=Node::create();
    rect1node->setPhysicsBody(body2);
    rect1node->setPosition(Vec2(0, csize.height/2-60));
    body2->setEnable(false);
    layer->body2=body2;
    
    auto body3=PhysicsBody::createEdgeBox(Size(10, csize.height-200),PHYSICSSHAPE_MATERIAL_DEFAULT,10);
    auto rect2node=Node::create();
    rect2node->setPhysicsBody(body3);
    rect2node->setPosition(Vec2(30, csize.height/2-60));
    body3->setEnable(false);
    layer->body3=body3;
    
    scene->addChild(rect2node);
    scene->addChild(rect1node);
    scene->addChild(rectnode);
    scene->addChild(layer);
    return scene;
}


bool GameScene::init()
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

    
    this->initview();
    return true;
}


void GameScene::initview()
{
  
    Size csize=Director::getInstance()->getVisibleSize();
    
    battlebg=battbleScene::createscene(dscene[dscenes-1][dlevels-1]->map);
    battlebg->setTag(997);
    battlebg->setPosition(Vec2(-30, 0));
    this->addChild(battlebg);
    
    DataManager::getInstance()->getheros()->setPosition(300,200);
    DataManager::getInstance()->getheros()->setScaleX(-1);
    battlebg->addChild(DataManager::getInstance()->getheros());
    battlebg->hero=DataManager::getInstance()->getheros();
    hero=DataManager::getInstance()->getheros();
  
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("login01.mp3",true);
    
    //摇杆图层
    auto movelayer=Movehandler::createlayer(hero);
    movelayer->setTag(998);
    this->addChild(movelayer);
    
    //设置
    auto Setting=MenuItemImage::create("battle_btn_stop_1.png", "battle_btn_stop_2.png", [this](Ref*){
        this->addChild(Interfactionlayer::create(401));
    });
    auto menu=Menu::create(Setting, NULL);
    menu->setPosition(Vec2(csize.width-50, csize.height-50));
    this->addChild(menu);
      
    auto contact=EventListenerPhysicsContact::create();
    contact->onContactBegin=[](PhysicsContact& contact){
        return true;
     };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);
}


