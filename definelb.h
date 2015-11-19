//
//  definelb.h
//  ECIT
//
//  Created by student on 15/9/10.
//
//

#ifndef ECIT_definelb_h
#define ECIT_definelb_h

#define center 100
#define yidongdistance 80
#define distance(p1,p2) sqrt(((p1.x)-(p2.x))*((p1.x)-(p2.x))+((p1.y)-(p2.y))*((p1.y)-(p2.y)))
#define corea(p1,p2)  ((p1.x)-(p2.x))/distance(p1,p2)
#define dhero DataManager::getInstance()->getheros()
#define dscenes  DataManager::getInstance()->secne
#define dlevels  DataManager::getInstance()->level
#define dscene DataManager::getInstance()->scenechapter

#endif
