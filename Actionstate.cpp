//
//  Actionstate.cpp
//  ECIT
//
//  Created by student on 15/9/8.
//
//

#include "Actionstate.h"

Actionstate::Actionstate(std::string state, std::function<void()> onEnter)
{
    _currentState = state;
    _previousState = "";
    this->addState(state, onEnter);
}

Actionstate* Actionstate::create(std::string state, std::function<void()> onEnter)
{
    Actionstate* fsm = new Actionstate(state, onEnter);
    if(fsm && fsm->init())
    {
        fsm->autorelease();
        return fsm;
    }
    else
    {
        CC_SAFE_DELETE(fsm);
        return nullptr;
    }
}

Actionstate* Actionstate::addState(std::string state, std::function<void()> onEnter)
{
    if("" == state)
    {
        cocos2d::log("FSM::addState: state can't be empty string!");
        return nullptr;
    }
    _states.insert(state);
    _onEnters.insert(std::pair<std::string, std::function<void()>>(state, onEnter));
    return this;
}

bool Actionstate::isContainState(std::string stateName)
{
    return _states.find(stateName) != _states.end();
}

void Actionstate::printState()
{
    //	std::for_each(_states.begin(), _states.end(), &FSM::print);
    cocos2d::log("FSM::printState: list of states");
    for(auto iter = _states.begin(); iter!=_states.end(); iter++)
    {
        cocos2d::log("%s",iter->c_str());
    }
}

void Actionstate::changeToState(std::string state)
{
    if(isContainState(state))
    {
        _previousState = _currentState;
        _currentState = state;
        cocos2d::log("FSM::changeToState: %s -> %s", _previousState.c_str(), _currentState.c_str());
        if(_onEnters[state])
            _onEnters[state]();
    }
    else
    {
        cocos2d::log("FSM::changeToState: no such state as %s , state unchanged", state.c_str());
    }
}

Actionstate* Actionstate::addEvent(std::string eventName, std::string from, std::string to)
{
    if("" == eventName)
    {
        cocos2d::log("FSM::addEvent: eventName can't be empty!");
        return nullptr;
    }
    if(!isContainState(from))
    {
        cocos2d::log("FSM::addEvent: from state %s does not exit", from.c_str());
        return nullptr;
    }
    if(!isContainState(to))
    {
        cocos2d::log("FSM::addEvent: to state %s does not exit", to.c_str());
        return nullptr;
    }
    std::unordered_map<std::string, std::string>&oneEvent = _events[eventName];
    oneEvent[from] = to;
    return this;
}

bool Actionstate::canDoEvent(std::string eventName)
{
    return _events[eventName].find(_currentState) != _events[eventName].end();
}

void Actionstate::doEvent(std::string eventName)
{

    if(canDoEvent(eventName))
    {
        cocos2d::log("FSM::doEvent: doing event %s", eventName.c_str());
        log("aaaaa");
        changeToState(_events[eventName][_currentState]);
    }
    else
    {
        cocos2d::log("FSM::doEvent: cannot do event %s", eventName.c_str());
    }
}

void Actionstate::setOnEnter(std::string state, std::function<void()> onEnter)
{
    if(isContainState(state))
    {
        _onEnters[state] = onEnter;
    }
    else
    {
        cocos2d::log("FSM::setOnEnter: no state named %s", state.c_str());
    }
}

bool Actionstate::init()
{
       this->addState("running",[](){cocos2d::log("Enter running");
         })
        ->addState("attacking1",[](){cocos2d::log("Enter attacking1");})
        ->addState("attacking2",[](){cocos2d::log("Enter attacking2");})
        ->addState("attacking3",[](){cocos2d::log("Enter attacking3");})
        ->addState("dead",[](){cocos2d::log("Enter dead");})
        ->addState("beingHit",[](){cocos2d::log("Enter beingHit");})
        ->addState("skill1",[](){cocos2d::log("Enter skill1");})
        ->addState("skill2",[](){cocos2d::log("Enter skill2");})
        ->addState("skill3",[](){cocos2d::log("Enter skill3");})
         ->addState("skill4",[](){cocos2d::log("Enter skill4");});
    
        this->addEvent("run","idle","running")        //跑
            ->addEvent("run","running","running")
            ->addEvent("run","attacking1","running")
            ->addEvent("run","attacking2","running")
            ->addEvent("run","attacking3","running")
            ->addEvent("run","skill1","running")
            ->addEvent("run","skill2","running")
            ->addEvent("run","skill3","running")
            ->addEvent("run","skill4","running")
    
            ->addEvent("attack1","idle","attacking1")   //攻击1
            ->addEvent("attack1","running", "attacking1")
            ->addEvent("attack1","attacking1", "attacking1")
            ->addEvent("attack1","attacking3", "attacking1")
            ->addEvent("attack1","attacking2", "attacking1")
            ->addEvent("attack1","skill1", "attacking1")
            ->addEvent("attack1","skill2", "attacking1")
            ->addEvent("attack1","skill3", "attacking1")
            ->addEvent("attack1","skill4", "attacking1")
    
            ->addEvent("attack2","idle","attacking2")   //攻击2
            ->addEvent("attack2","running", "attacking2")
            ->addEvent("attack2","attacking1", "attacking2")
            ->addEvent("attack2","attacking2", "attacking2")
            ->addEvent("attack2","attacking3", "attacking2")
            ->addEvent("attack2","skill1", "attacking2")
            ->addEvent("attack2","skill2", "attacking2")
            ->addEvent("attack2","skill3", "attacking2")
            ->addEvent("attack2","skill4", "attacking2")
    
            ->addEvent("attack3","idle","attacking3")   //攻击3
            ->addEvent("attack3","running", "attacking3")
            ->addEvent("attack3","attacking3", "attacking3")
            ->addEvent("attack3","attacking2", "attacking3")
            ->addEvent("attack3","attacking1", "attacking3")
            ->addEvent("attack3","skill1", "attacking3")
            ->addEvent("attack3","skill2", "attacking3")
            ->addEvent("attack3","skill3", "attacking3")
            ->addEvent("attack3","skill4", "attacking3")
    
            ->addEvent("die","idle","dead")           //死亡
            ->addEvent("die","running","dead")
            ->addEvent("die","attacking1","dead")
            ->addEvent("die","beingHit","dead")
    
            ->addEvent("stop","running","idle")       //待机
            ->addEvent("stop","attacking1","idle")
            ->addEvent("stop","attacking2","idle")
            ->addEvent("stop","attacking3","idle")
            ->addEvent("stop","beingHit","idle")
            ->addEvent("stop","idle","idle")
            ->addEvent("stop", "skill1", "idle")
            ->addEvent("stop", "skill2", "idle")
            ->addEvent("stop", "skill3", "idle")
            ->addEvent("stop", "dead", "idle")
    
            ->addEvent("beHit","idle","beingHit")      //挨打
            ->addEvent("beHit","running","beingHit")
    
            ->addEvent("skilling1","idle","skill1")   //技能1
            ->addEvent("skilling1","running", "skill1")
            ->addEvent("skilling1","attacking1", "skill1")
            ->addEvent("skilling1","attacking2", "skill1")
            ->addEvent("skilling1","attacking3", "skill1")
            
            ->addEvent("skilling2","idle","skill2")   //技能2
            ->addEvent("skilling2","running", "skill2")
            ->addEvent("skilling2","attacking1", "skill2")
            ->addEvent("skilling2","attacking2", "skill2")
            ->addEvent("skilling2","attacking3", "skill2")

            
            ->addEvent("skilling3","idle","skill3")   //技能3
            ->addEvent("skilling3","running", "skill3")
            ->addEvent("skilling3","attacking1", "skill3")
            ->addEvent("skilling3","attacking2", "skill3")
            ->addEvent("skilling3","attacking3", "skill3")
            
    
            ->addEvent("skilling4","idle","skill4")   //技能4
            ->addEvent("skilling4","running", "skill4")
            ->addEvent("skilling4","attacking1", "skill4")
            ->addEvent("skilling4","attacking2", "skill4")
            ->addEvent("skilling4","attacking3", "skill4");
    return true;
}