//
//  DataManager.h
//  ECIT
//
//  Created by student on 15/8/28.
//
//

#ifndef __ECIT__DataManager__
#define __ECIT__DataManager__

#include <iostream>
#include "cocos2d.h"
#include "Mercenary.h"
#include "Aplements.h"
#include "Monster.h"
#include "Hero.h"
#include "MonsterModel.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "tinyxml2/tinyxml2.h"
USING_NS_CC;
using namespace rapidjson;

class DataManager
{
public:
    static DataManager * getInstance();
    static bool purgeInstance();
    void DateJson();
    void packJson();
    void heroJson();
    void AplementJson();
    void MonsterJson();
    void sceneJson();
    void readJson();
    void writeJson();
    
    void copyFileToPath(std::string path);
    int shoppage[4][16];
    int needlvarr[10];
    std::unordered_map<std::string,Mercenary*>merMap;
    
    MonsterModel* scenechapter[5][8];
    Vector<Aplements*>apleVec;
    Vector<Monster *>monsterVec;
    
    int secne;
    int level;

    CC_SYNTHESIZE(Monster *, monster, monster);
    CC_SYNTHESIZE(Hero*, heros, heros);
    CC_SYNTHESIZE(Mercenary*,mercenary,mercenary);
protected:
     DataManager();
    ~DataManager();
};

#endif /* defined(__ECIT__DataManager__) */
