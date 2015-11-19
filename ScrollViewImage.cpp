//
//  ScrollViewImage.cpp
//  PrePreGame
//
//  Created by student on 15/9/7.
//
//

#include "ScrollViewImage.h"
#include "DataManager.h"
#include "Interfactionlayer.h"
Scene * ScrollViewImage::CrateLayer(){
    ScrollViewImage *ret = new (std::nothrow) ScrollViewImage();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool ScrollViewImage::init(){

    auto ly=Layer::create();
    this->addChild(ly);
    
    auto sp=Sprite::create("a.png");
    
    auto listenerkey=EventListenerKeyboard::create();
    listenerkey->onKeyReleased=[this](EventKeyboard::KeyCode keyCode, Event* event){
        auto interact=Interfactionlayer::create(100);
        if(!this->getChildByTag(666))
        {
            interact->setTag(666);
            this->addChild(interact);
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkey, ly);
    
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    sp->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    ly->addChild(sp);
    
    auto move=MoveTo::create(5, Vec2(visibleSize.width/2-700, visibleSize.height/2));
    auto call=CallFunc::create(CC_CALLBACK_0(ScrollViewImage::replaceScene, this));
    auto sequence=Sequence::create(move,call, NULL);
    sp->runAction(sequence);
    
    auto lable=Label::createWithSystemFont("跳过","fonts/arial.ttf", 40);
    auto item=MenuItemLabel::create(lable, CC_CALLBACK_0(ScrollViewImage::replaceScene, this));
    auto menu=Menu::create(item, NULL);
    menu->setPosition(visibleSize.width/2+430,visibleSize.height/2+300);
    this->addChild(menu);
    return true;
}

void ScrollViewImage::replaceScene(){
     DataManager::getInstance();
     Director::getInstance()->replaceScene(prepare->PrepareGame::createScene());
}


