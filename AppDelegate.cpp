#include "AppDelegate.h"
#include "StartUIview.h"
#include "cocostudio/CocoStudio.h"
#include "DataManager.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
   
    
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::EXACT_FIT);
    DataManager::getInstance();
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
   auto scene =StartUIview::createwithstartUI();
   // auto scene=Movehandler::createScene();
    
    std::string wrPath=FileUtils::getInstance()->getWritablePath();
    log("%s",wrPath.c_str());
    bool bfirst=UserDefault::getInstance()->getBoolForKey("first");
      if(!bfirst)
      {
          UserDefault::getInstance()->setBoolForKey("first", true);
          UserDefault::getInstance()->flush();
      }
    else
    {
        log("you are not first ");
    }
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
