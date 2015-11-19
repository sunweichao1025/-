//
//  CharpterUIview.cpp
//  ECIT
//
//  Created by student on 15/8/28.
//
//

#include "CharpterUIview.h"
#include "PrepareGame.h"
#include "GameScene.h"
#include "Interfactionlayer.h"
#include "MenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Load.h"
#include "DataManager.h"
#include "definelb.h"

using namespace cocostudio;
using namespace ui;
using namespace timeline;

Scene * CharpterUIview::createwithCharpterUIview()
{
    auto scene=Scene::create();
    auto layer=CharpterUIview::create();
    scene->addChild(layer);
    return scene;
}




bool CharpterUIview::init()
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

    
    this->initUIview();
    return true ;
}


void CharpterUIview::initUIview()
{
    auto node =CSLoader::createNode("charpter.csb");
    this->addChild(node);
    
    for (int i=1;i<=8;i++)
    {
        auto page=node->getChildByName<ui::PageView*>("Chapterpage");
        auto chap=page->getChildByName<ui::Layout*>("Chapter1");
        auto image=chap->getChildByName<ui::ImageView*>("chapter1");
        auto g1=image->getChildByName<Node*>(__String::createWithFormat("c1_%d",i)->getCString());
        scenenode.pushBack(g1);
    }
    
    auto light=CSLoader::createTimeline("charpter.csb");
    light->gotoFrameAndPlay(0, 60, true);
    node->runAction(light);
    
    //返回
    auto backbtn=node->getChildByName<ui::Button*>("backbtn");
    backbtn->addClickEventListener([this](Ref*){
        Director::getInstance()->replaceScene(PrepareGame::createScene());
    });
    
    //战斗
    auto fightbtn=node->getChildByName<ui::Button*>("fight");
    fightbtn->addClickEventListener([this](Ref*){
        Director::getInstance()->replaceScene(Load::createScene());
    });
    
    //副本
    auto fightbookbtn=node->getChildByName<ui::Button*>("fightbook");
    fightbookbtn->addClickEventListener([this](Ref*){
        auto layer=MenuLayer::createScene(301);
        this->addChild(layer);
    });
    
    //礼盒
    auto goods=node->getChildByName<ui::Button*>("goods");
    goods->addClickEventListener([this](Ref*){
        auto interact=Interfactionlayer::create(103);
        this->addChild(interact);
    });
 
    auto pageview=node->getChildByName<ui::PageView*>("Chapterpage");
    pageview->addEventListener([this,pageview](Ref*, PageView::EventType){
    if(pageview->getCurPageIndex()==0&&this->getChildByTag(10))
      {
          this->removeChildByTag(10);
      }
      else if (!this->getChildByTag(10))
      {
          auto leftbtn=ui::Button::create("tollgate_btn_arrow_1.png");
          leftbtn->loadTexturePressed("tollgate_btn_arrow_1.png");
          leftbtn->loadTextureDisabled("tollgate_btn_arrow_1.png");
          leftbtn->setScale9Enabled(true);
          leftbtn->setPosition(Vec2(50,360));
          leftbtn->addClickEventListener([this,pageview](Ref*sender){
              pageview->scrollToPage(pageview->getCurPageIndex()-1);
              if(pageview->getCurPageIndex()==0&&(!this->getChildByTag(10)))
              {
                  auto leftbtn=(ui::Button*)sender;
                  leftbtn->removeFromParent();
              }
          });
          leftbtn->setTag(10);
          this->addChild(leftbtn,10);
      }
    });
 
    //pageview移动按钮
    auto rightbtn=node->getChildByName<ui::Button*>("rightbtn");
    rightbtn->addClickEventListener([this,pageview](Ref*sender){
        auto rightbtn=(ui::Button*)sender;
      if(pageview->getCurPageIndex()==0&&(!this->getChildByTag(10)))
      {
          auto leftbtn=ui::Button::create("tollgate_btn_arrow_1.png");
          leftbtn->loadTexturePressed("tollgate_btn_arrow_1.png");
          leftbtn->loadTextureDisabled("tollgate_btn_arrow_1.png");
          leftbtn->setScale9Enabled(true);
          leftbtn->setPosition(Vec2(50,rightbtn->getPosition().y));
          leftbtn->addClickEventListener([this,pageview](Ref*sender){
              pageview->scrollToPage(pageview->getCurPageIndex()-1);
              if(pageview->getCurPageIndex()==0&&this->getChildByTag(10))
              {
                  auto leftbtn=(ui::Button*)sender;
                  leftbtn->removeFromParent();
            }
          });
          leftbtn->setTag(10);
          this->addChild(leftbtn,10);
      }
        pageview->scrollToPage(pageview->getCurPageIndex()+1);
      
    });
    
    char str[30];
    //关卡
    sprintf(str, "%d-%d",dhero->getcurrentchapter(),dhero->getcurrentpass());
    level=node->getChildByName<ui::TextBMFont*>("selectlevel");
    level->setString(str);
    
    //金钱
    sprintf(str, "%d",dhero->getgold());
    dollor=node->getChildByName<ui::Text*>("dollor");
    dollor->setString(str);
    
    //标记
    sign=node->getChildByName<ui::TextBMFont*>("signlevel");
   
    //敌方战斗力
    emoptypower=node->getChildByName<ui::Text*>("ourpower");
    //我方战斗力
    sprintf(str, "%d",dhero->getourfighting());
    ourpower=node->getChildByName<ui::Text*>("emenptypower");
    ourpower->setString(str);

}