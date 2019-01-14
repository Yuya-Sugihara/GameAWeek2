#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"
using namespace cocos2d;

class Muzzle;
class StateMachine;

class Enemy:public Character
{
private:
    
public:
    Enemy(float width,float height);
    
    void update();
    
    CC_SYNTHESIZE(StateMachine*, mStateMachine, StateMachine);
};
#endif /* Enemy_hpp */
