//
//  Load.cpp
//  pass
//
//  Created by student on 15/9/6.
//
//

#include "Load.h"
#include "GameScene.h"
#include "Interfactionlayer.h"


Scene * Load::createScene()
{
    auto scene=Scene::create();
    auto layer=Load::create();
    scene->addChild(layer);
    return scene;
}

bool Load::init()
{
    
    if (!Layer::init()) {
        return false;
    }
    
    auto listenerkey=EventListenerKeyboard::create();
    listenerkey->onKeyReleased=[this](EventKeyboard::KeyCode keyCode, Event* event){
        if(keyCode==EventKeyboard::KeyCode::KEY_BACKSPACE)
        {
            auto interact=Interfactionlayer::create(100);
            this->addChild(interact);
        }
    };
    
    auto size = Director::getInstance()->getVisibleSize();
    
    auto loadbg = Sprite::create("loading_word.png");
    loadbg->setPosition(Vec2(size.width/2,size.height/2-50));
    addChild(loadbg);
    auto bg = Sprite::create("loading_progress_1.png");
    bg->setPosition(Vec2(size.width/2,size.height/2));
    addChild(bg);
    
    auto lb = LoadingBar::create("loading_progress_2.png");
    lb->setPosition(Vec2(size.width/2,size.height/2));
    lb->setDirection(LoadingBar::Direction::LEFT);
    lb->setPercent(0);
    addChild(lb,1,1);//同时设置Tag值为1
    schedule(CC_CALLBACK_1(Load::LoadingBar,this),"LoadingBar");
    return true;
}

void Load::LoadingBar(float dt)
{
    auto size = Director::getInstance()->getVisibleSize();

    auto lb = dynamic_cast<class LoadingBar*>(getChildByTag(1));
    float per = lb->getPercent() + 1.0f;
    lb->setPercent(per);
   //图片加载
    auto load = Sprite::create("load.png");
    load->setPosition(Vec2(size.width/2-150,size.height/2+60));
    auto moveTo = MoveTo::create(0.6,Vec2( size.width/2+130,size.height/2+60));
    auto seq = Sequence::create(moveTo, NULL);
    load->runAction(seq);
    addChild(load);
    
   if (per==100) {
       unschedule("LoadingBar");
       auto callf=CallFunc::create([this](){
           Director::getInstance()->replaceScene(GameScene::createScene());
       });
       auto seq=Sequence::create(DelayTime::create(1.1), callf,NULL);
       this->runAction(seq);
   }
    
}

    