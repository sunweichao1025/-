//
//  DataManager.cpp
//  ECIT
//
//  Created by student on 15/8/28.
//
//

#include "DataManager.h"
#include "MonsterModel.h"

static DataManager* instance=nullptr;
DataManager * DataManager::getInstance()
{
    if(instance==nullptr)
    {
        instance=new DataManager();
        CCASSERT(instance, "FATAL: Not enough memory");
        return instance;
    }
    return instance;
}

bool DataManager::purgeInstance()
{
    CCASSERT(instance, "instance can not emptoy");
    if(instance){
        delete instance;
        instance=nullptr;
    }
    return true;
}

DataManager::DataManager()
{
    this->readJson();
}

void DataManager::readJson()
{
    this->DateJson();
    this->packJson();
    this->heroJson();
    this->AplementJson();
    this->MonsterJson();
    this->sceneJson();
}
void DataManager::MonsterJson(){
    FileUtils *fu = FileUtils::getInstance();
    string wrpath = fu->getWritablePath();
    string filename="monster.json";
    wrpath += filename;
    this->copyFileToPath(filename);
    rapidjson::Document doc;
    string data = FileUtils::getInstance()->getStringFromFile(wrpath);
    string clearData(data);
    size_t pos = clearData.rfind("}");
    clearData = clearData.substr(0,pos+1);
    doc.Parse<rapidjson::kParseDefaultFlags>(clearData.c_str());
    if (doc.HasParseError()) {
        log("GetparseError %s\n",doc.GetParseError());
        return;
    }
    rapidjson::Value &array = doc["Monster"];
    log("%d",array.Size());
    for (int i =1 ; i<=array.Size(); i++) {
        char mon[30];
        sprintf(mon, "mon%d",i);
        rapidjson::Value &first = array[i-1];
        rapidjson::Value &monster1 = first[mon];
        rapidjson::Value & blood=monster1["blood"];
        rapidjson::Value & attack=monster1["attack"];
        rapidjson::Value & name=monster1["name"];
        log("%s",name.GetString());
        monster=Monster::createwith(name.GetString());
        monster->blood=blood.GetInt();
        monster->attck=attack.GetInt();
        monster->name=name.GetString();
        monsterVec.pushBack(monster);
    }
    
    
}
void DataManager::DateJson(){
    FileUtils *fu=FileUtils::getInstance();
    std:: string path=fu->getWritablePath();
    path+="Mercenary.json";
    this->copyFileToPath("Mercenary.json");
    rapidjson::Document doc;
    std::string data=fu->getStringFromFile(path);
    
    std:: string clearData(data);
    size_t pos=clearData.rfind("}");
    clearData =clearData.substr(0,pos+1);
    
    doc.Parse<kParseDefaultFlags>(clearData.c_str());
    if (doc.HasParseError()) {
        log("GetParaseErro %s\n",doc.GetParseError());
    }
    char c[60];
    rapidjson::Value &array=doc["Mercenary"];
    for (int i=0; i<array.Size(); i++) {
            sprintf(c, "merc%d",i+1);
            rapidjson::Value & first=array[i];
            rapidjson::Value & mer1=first[c];
            rapidjson::Value & blood=mer1["blood"];
            rapidjson::Value & attack=mer1["attack"];
            rapidjson::Value & defense=mer1["defense"];
            rapidjson::Value & needBlood=mer1["needBlood"];
            rapidjson::Value & needAttack=mer1["needAttack"];
            rapidjson::Value & needGlod=mer1["needGlod"];
            rapidjson::Value & skill1=mer1["skill1"];
            rapidjson::Value & skill2=mer1["skill2"];
            rapidjson::Value & merinfo2=mer1["merinfo2"];
            rapidjson::Value & mername=mer1["name"];
            rapidjson::Value & locked = mer1["locked"];
            rapidjson::Value & pos = mer1["pos"];//位置数组
            mercenary=Mercenary::crateWith(mer1["name"].GetString());
            mercenary->blood=blood.GetInt();
            mercenary->attack=attack.GetInt();
            mercenary->defense=defense.GetInt();
            mercenary->needGlod=needGlod.GetInt();
            mercenary->needAttack=needAttack.GetInt();
            mercenary->needBlood=needBlood.GetInt();
            mercenary->setskill1(skill1.GetString());
            mercenary->setskill2(skill2.GetString());
            mercenary->merinfo2=merinfo2.GetString();
            mercenary->merName=mername.GetString();
            mercenary->locked=locked.GetInt();
            mercenary->merpos=pos.GetInt();
            merMap[c]=mercenary;
    }
}
void DataManager::packJson(){
    FileUtils *fu=FileUtils::getInstance();
    std:: string path=fu->getWritablePath();
    path+="shopstore.json";
    this->copyFileToPath("shopstore.json");
    rapidjson::Document doc;
    std::string data=fu->getStringFromFile(path);
    
    std:: string clearData(data);
    size_t pos=clearData.rfind("}");
    clearData =clearData.substr(0,pos+1);
    
    doc.Parse<kParseDefaultFlags>(clearData.c_str());
    if (doc.HasParseError()) {
        log("GetParaseErro %s\n",doc.GetParseError());
    }
    char c[10];
    rapidjson::Value &array=doc["shopstore"];
    for (int i=0; i<array.Size(); i++) {
        rapidjson::Value & first=array[i];
        sprintf(c, "page%d",i+1);
        rapidjson::Value & page=first[c];
        for(int j=0;j<page.Size();j++)
        {
            rapidjson::Value &c=page[j];
            shoppage[i][j]=c.GetInt();
        }
     
    }

}
void DataManager::heroJson(){
    heros=new Hero(HERO,"aaa");
    
    FileUtils *fu = FileUtils::getInstance();
    string wrpath = fu->getWritablePath();
    string filename="embattle.json";
    wrpath += filename;
    this->copyFileToPath(filename);
    
    rapidjson::Document doc;
    string data = FileUtils::getInstance()->getStringFromFile(wrpath);
    
    string clearData(data);
    size_t pos = clearData.rfind("}");
    clearData = clearData.substr(0,pos+1);
    
    doc.Parse<rapidjson::kParseDefaultFlags>(clearData.c_str());
    
    if (doc.HasParseError()) {
        log("GetparseError %s\n",doc.GetParseError());
        return;
    }
    
    rapidjson::Value &array = doc["hero"];
    log("%d",array.Size());
    for (int i =0 ; i<array.Size(); i++) {
        rapidjson::Value &first = array[i];
        rapidjson::Value &gold = first["gold"];
        rapidjson::Value &lv = first["lv"];
        rapidjson::Value &currentEXp = first["currentEXP"];
        rapidjson::Value &blood = first["blood"];
        rapidjson::Value &attack = first["attack"];
        rapidjson::Value &defense = first["defense"];
        rapidjson::Value &skill1 = first["skill1"];
        rapidjson::Value &skill2 = first["skill2"];
        rapidjson::Value &skill3 = first["skill3"];
        rapidjson::Value &skill4 = first["skill4"];
        rapidjson::Value &clothes = first["clothes"];
        rapidjson::Value &weapen = first["weapen"];
        rapidjson::Value &necklace = first["necklace"];
        rapidjson::Value &stone = first["stone"];
        rapidjson::Value &skillInf = first["skillInf"];
        rapidjson::Value &needEXP = first["needEXP"];
        rapidjson::Value &ourfighting = first["ourfighting"];
        rapidjson::Value &currentchapter = first["currentchapter"];
        rapidjson::Value &currentpass = first["currentpass"];
        
        for(int j=0;j<needEXP.Size();j++)
        {
            rapidjson::Value &needvalue=needEXP[j];
            needlvarr[j]=needvalue.GetInt();
            
        }
        heros->setgold(gold.GetInt());
        heros->setlv(lv.GetInt());
        heros->setcurrentEXP(currentEXp.GetInt());
        heros->setblood(blood.GetInt());
        heros->setattack(attack.GetInt());
        heros->setdefense(defense.GetInt());
        heros->setskill1(skill1.GetString());
        heros->setskill2(skill2.GetString());
        heros->setskill3(skill3.GetString());
        heros->setskill4(skill4.GetString());
        heros->setclothes(clothes.GetString());
        heros->setweapen(weapen.GetString());
        heros->setnecklace(necklace.GetString());
        heros->setstone(stone.GetString());
        heros->setskillInf(skillInf.GetString());
        heros->setneedEXP(needlvarr[lv.GetInt()-1]);
        heros->setourfighting(ourfighting.GetInt());
        heros->setcurrentchapter(currentchapter.GetInt());
        heros->setcurrentpass(currentpass.GetInt());
    }

 
}
void DataManager::AplementJson(){
    FileUtils *fu=FileUtils::getInstance();
    std:: string path=fu->getWritablePath();
    path+="Aplements.json";
    
    this->copyFileToPath("Aplements.json");
    
    rapidjson::Document doc;
    std::string data=fu->getStringFromFile(path);
    std:: string clearData(data);
    size_t pos=clearData.rfind("}");
    clearData =clearData.substr(0,pos+1);
    
    doc.Parse<kParseDefaultFlags>(clearData.c_str());
    
    if (doc.HasParseError()) {
        log("GetParaseErro %s\n",doc.GetParseError());
    }
    rapidjson::Value &array=doc["Aplements"];
    char name[10];
    for (int i=0; i<array.Size(); i++) {
        sprintf(name, "name%d",i);
        rapidjson::Value & first=array[i];
        rapidjson::Value & ap=first[name];
        rapidjson::Value & name1=ap["name"];
        rapidjson::Value & level=ap["level"];
        rapidjson::Value & discription=ap["discription"];
        rapidjson::Value & reward=ap["reward"];
        rapidjson::Value & locked=ap["lockl"];
       auto aple= new Aplements(name1.GetString(),level.GetString(),discription.GetString(),reward.GetString(),locked.GetString());
        apleVec.pushBack(aple);
    }
    
}
void DataManager::sceneJson(){
    secne=1;
    level=1;
    
    FileUtils *fu=FileUtils::getInstance();
    std:: string path=fu->getWritablePath();
    path+="chapter.json";
    
    this->copyFileToPath("chapter.json");
    
    rapidjson::Document doc;
    std::string data=fu->getStringFromFile(path);
    std:: string clearData(data);
    size_t pos=clearData.rfind("}");
    clearData =clearData.substr(0,pos+1);
    
    doc.Parse<kParseDefaultFlags>(clearData.c_str());
    
    if (doc.HasParseError()) {
        log("GetParaseErro %s\n",doc.GetParseError());
        return;
    }
    rapidjson::Value &array=doc["chapter"];
    for (int i=0; i<array.Size(); i++) {
        char cap[30];
        sprintf(cap, "chapter%d",i+1);
        rapidjson::Value &first=array[i];
        rapidjson::Value &captial=first[cap];
        rapidjson::Value &locked=captial["locked"];
        rapidjson::Value &monsterNum=captial["monsterNum"];
        rapidjson::Value &chapter=captial["chapter"];
        rapidjson::Value &boss=captial["boss"];
        rapidjson::Value &monsterName=captial["monsterName"];
        rapidjson::Value &bg=captial["bgname"];
        
        auto mon=new MonsterModel(monsterNum.GetInt(),1,i,locked.GetInt(),boss.GetString());
        for(int j=0;j<monsterName.Size();j++)
        {
            mon->mtype[j]=monsterName[j].GetString();
         
        }
        mon->map=bg.GetString();
        scenechapter[0][i]=mon;
    }

}


void DataManager:: copyFileToPath(std::string path){
    //获取文件复制的原路径和目录路径
    FileUtils *fu=FileUtils::getInstance();
    std::string wrpath=fu->getWritablePath();
    wrpath+=path;
    log("%s",wrpath.c_str());
    if (!fu->isFileExist(wrpath)) {
        //获取app里面的路径
        std::string datapath=fu->fullPathForFilename(path.c_str());
        log("datapath=%s",datapath.c_str());
        //根据这个路径来获取到文件
        std::string pFileContent=fu->getStringFromFile(datapath);
         CCLOG("%s",pFileContent.c_str());
        //将文件内容读出，写入到沙盒中
        FILE *file=fopen(wrpath.c_str(), "w");
        if (file) {
            fputs(pFileContent.c_str(), file);
            fclose(file);
        }
    }
}

DataManager::~DataManager()
{}

