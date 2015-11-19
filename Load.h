//
//  Load.h
//  pass
//
//  Created by student on 15/9/6.
//
//

#ifndef __pass__Load__
#define __pass__Load__
#include <stdio.h>
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

class Load:public Layer  
{
public:
    
    static Scene * createScene();
    virtual bool init();
    CREATE_FUNC(Load);
    
   
    void LoadingBar(float dt);
};


#endif /* defined(__pass__Load__) */
